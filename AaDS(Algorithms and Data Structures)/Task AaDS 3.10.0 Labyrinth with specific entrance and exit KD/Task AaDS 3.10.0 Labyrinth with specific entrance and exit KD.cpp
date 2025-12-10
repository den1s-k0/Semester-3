#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

class Net {
public:
	class Edge {
	public:
		int to, c, f, rev;

		Edge(int TO, int C, int F, int REV) : to(TO), c(C), f(F), rev(REV) {}
	};

	vector<vector <Edge>> graf;
	vector<int> level, last;
	vector<bool> visited;
	int S, T;

	Net(int n) : graf(n), level(n), last(n), visited(n) {}

	void addEdge(int from, int to, int c) {
		graf[from].push_back(Edge(to, c, 0, graf[to].size()));
		graf[to].push_back(Edge(from, 0, 0, graf[from].size() - 1));
	}

	bool bfs() {
		fill(level.begin(), level.end(), -1);
		queue<int> q;
		int top;
		q.push(S);
		level[S] = 0;
		while (!q.empty()) {
			top = q.front();
			q.pop();
			for (int i = 0; i < graf[top].size(); i++) {
				if (level[graf[top][i].to] == -1 && graf[top][i].f < graf[top][i].c) {
					q.push(graf[top][i].to);
					level[graf[top][i].to] = level[top] + 1;
				}
			}
		}
		return level[T] != -1;
	}

	int dfs(int top, int pushed) {
		if (top == T || pushed == 0)
			return pushed;

		for (int& i = last[top]; i < graf[top].size(); i++) {
			Edge& top_to = graf[top][i];
			if (level[top_to.to] == level[top] + 1 && top_to.f < top_to.c) {
				int psh = dfs(top_to.to, min(pushed, top_to.c - top_to.f));
				if (psh > 0) {
					top_to.f += psh;
					graf[top_to.to][top_to.rev].f -= psh;
					return psh;
				}
			}
		}
		return 0;
	}

	int dfs2(int start, int pushed) {
		vector<int> path_vertices;
		vector<int> path_edges;

		path_vertices.push_back(start);

		while (!path_vertices.empty()) {
			int v = path_vertices.back();

			if (v == T) {
				int min_flow = pushed;
				for (int i = 0; i < path_edges.size(); i++) {
					int from = path_vertices[i];
					int edge_idx = path_edges[i];
					Edge& e = graf[from][edge_idx];
					min_flow = min(min_flow, e.c - e.f);
				}

				for (int i = 0; i < path_edges.size(); i++) {
					int from = path_vertices[i];
					int edge_idx = path_edges[i];
					Edge& e = graf[from][edge_idx];
					e.f += min_flow;
					graf[e.to][e.rev].f -= min_flow;
				}

				return min_flow;
			}

			bool found = false;
			while (last[v] < graf[v].size()) {
				Edge& e = graf[v][last[v]];
				if (level[e.to] == level[v] + 1 && e.f < e.c) {
					path_vertices.push_back(e.to);
					path_edges.push_back(last[v]);
					found = true;
					break;
				}
				last[v]++;
			}

			if (!found) {
				path_vertices.pop_back();
				if (!path_edges.empty()) path_edges.pop_back();
				if (!path_vertices.empty()) {
					last[path_vertices.back()]++;
				}
			}
		}

		return 0;
	}

	int maxF(int s, int t) {
		S = s;
		T = t;
		int F = 0, pushed;
		while (bfs()) {
			fill(last.begin(), last.end(), 0);
			while (pushed = dfs2(s, 100000000) > 0)
				F += pushed;
		}
		return F;
	}
};

int main()
{
	ifstream in("in.txt");
	ofstream out("out.txt");
	if (!in.is_open() || !out.is_open())
		return 1;

	int n, m, k = 0, prov, zero_count = 0, s, t, graf_size;
	in >> n >> m;
	vector<vector <char>> lab(n, vector <char>(m));
	vector<vector <int>> ID(n, vector <int>(m, -1));
	vector<int> entries, exits;


	for (int i = 0; i < m; i++) {
		in >> lab[0][i];
		if (lab[0][i] == '0') {
			k++;
			ID[0][i] = zero_count++;
			entries.push_back(i);
		}
	}

	for (int i = 1; i < n; i++) {
		prov = 0;
		for (int j = 0; j < m; j++) {
			in >> lab[i][j];
			if (lab[i][j] == '0') {
				prov++;
				ID[i][j] = zero_count++;
			}
		}
		if (prov < k) {
			out << "Impossible";
			cout << "Impossible";
			in.close();
			out.close();
			return 0;
		}
	}

	for (int i = 0; i < m; i++) {
		if (lab[n - 1][i] == '0' && ID[n - 1][i] >= 0)
			exits.push_back(i);
	}

	s = zero_count * 2;
	t = s + 1;
	graf_size = zero_count * 2 + 2;
	Net net(graf_size);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (lab[i][j] == '0' && ID[i][j] >= 0) {
				net.addEdge(ID[i][j] * 2, ID[i][j] * 2 + 1, 1);
			}
		}
	}

	const int dx[4] = { 1, -1, 0, 0 };
	const int dy[4] = { 0, 0, 1, -1 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (lab[i][j] == '0' && ID[i][j] >= 0) {
				int fr_out = ID[i][j] * 2 + 1;
				for (int d = 0; d < 4; d++) {
					int to_i = i + dx[d];
					int to_j = j + dy[d];
					if (to_i >= 0 && to_i < n && to_j >= 0 && to_j < m && lab[to_i][to_j] == '0' && ID[to_i][to_j] >= 0) {
						int to_in = ID[to_i][to_j] * 2;
						net.addEdge(fr_out, to_in, 1);
					}
				}
			}
		}
	}

	for (int i = 0; i < k; i++) {
		int inID = ID[0][entries[i]] * 2;
		int outID = ID[n - 1][exits[i]] * 2 + 1;
		net.addEdge(s, inID, 1);
		net.addEdge(outID, t, 1);
	}

	if (net.maxF(s, t) == k) {
		out << "Possible";
		cout << "Possible";
	}
	else {
		out << "Impossible";
		cout << "Impossible";
	}

	in.close();
	out.close();
	return 0;
}