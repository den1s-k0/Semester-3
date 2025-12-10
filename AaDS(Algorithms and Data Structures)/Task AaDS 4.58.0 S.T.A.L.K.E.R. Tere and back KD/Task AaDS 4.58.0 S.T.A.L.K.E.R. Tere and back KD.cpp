#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

using namespace std;

class Net {
public:
	class Edge {
	public:
		int to, rev;
		bool is_blocked;

		Edge(int TO, int REV) : to(TO), rev(REV), is_blocked(false) {}
	};

	vector<vector <Edge>> graf;
	vector<int> dist;
	vector<int> par;

	int M, G;

	Net(int n) : graf(n), dist(n, -1), par(n, -1) {}

	void addEdge(int from, int to) {
		graf[from].push_back(Edge(to, graf[to].size()));
		graf[to].push_back(Edge(from, graf[from].size() - 1));
	}

	void blockEdge(int from, int to) {
		for (int i = 0; i < graf[from].size(); i++) {
			if (graf[from][i].to == to) {
				graf[from][i].is_blocked = true;
				graf[to][graf[from][i].rev].is_blocked = true;
				break;
			}
		}
	}

	void clear() {
		fill(dist.begin(), dist.end(), -1);
		fill(par.begin(), par.end(), -1);
	}

	int bfs(int start, int end) {
		queue<int> q;
		int top;
		bool is_find = false;
		q.push(start);
		dist[start] = 0;
		while (!q.empty()) {
			top = q.front();
			q.pop();
			for (int i = 0; i < graf[top].size(); i++) {
				if (dist[graf[top][i].to] == -1 && !graf[top][i].is_blocked) {
					q.push(graf[top][i].to);
					dist[graf[top][i].to] = dist[top] + 1;
					par[graf[top][i].to] = top;
					if (graf[top][i].to == end) {
						is_find = true;
						break;
					}
				}
			}
			if (is_find)
				break;
		}

		return dist[end];
	}

	void distances(int start) {
		bool diff = true;
		dist[start] = 0;
		for (int i = 0; i < dist.size() - 1; i++) {
			diff = false;
			for (int j = 0; j < graf.size(); j++) {
				for (int k = 0; k < graf[j].size(); k++) {
					if (dist[graf[j][k].to] > dist[j] + 1 && !graf[j][k].is_blocked) {
						dist[graf[j][k].to] = dist[j] + 1;
						par[graf[j][k].to] = j;
						diff = true;
					}
				}
			}
			if (!diff)
				break;
		}
	}

	void parents(int end) {
		int cur = end;
		while (par[cur] != -1) {
			blockEdge(cur, par[cur]);
			cur = par[cur];
		}
	}
	
};

int main()
{
	ifstream in("walk.in");
	ofstream out("walk.out");
	if (!in.is_open() || !out.is_open())
		return 1;

	int n, m, point_count = 0, start_end, key, graf_size, result;
	bool is_m = false, is_g = false;
	in >> n >> m;
	vector<vector <char>> lab(n, vector <char>(m));
	vector<vector <int>> ID(n, vector <int>(m, -1));
	vector<int> entries, exits;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			in >> lab[i][j];
			if (lab[i][j] == '.') {
				ID[i][j] = point_count++;
			}
			if (lab[i][j] == 'M') {
				ID[i][j] = point_count++;
				start_end = ID[i][j];
				is_m = true;
			}
			if (lab[i][j] == 'G') {
				ID[i][j] = point_count++;
				key = ID[i][j];
				is_g = true;
			}
		}
	}

	if (!is_m || !is_g || n == 1 || m == 1) {
		out << -1;
		in.close();
		out.close();
		return 0;
	}

	graf_size = point_count;
	Net net(graf_size);

	const int dx[4] = { 1, -1, 0, 0 };
	const int dy[4] = { 0, 0, 1, -1 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ID[i][j] >= 0) {
				for (int d = 0; d < 4; d++) {
					int to_i = i + dx[d];
					int to_j = j + dy[d];
					if (to_i >= 0 && to_i < n && to_j >= 0 && to_j < m && ID[to_i][to_j] >= 0 && ID[i][j] < ID[to_i][to_j]) {
						net.addEdge(ID[i][j], ID[to_i][to_j]);
					}
				}
			}
		}
	}

	//net.distances(start_end);
	//result = net.dist[key];
	//if (result == 1234567890) {
	//	out << -1;
	//	in.close();
	//	out.close();
	//	return 0;
	//}
	//net.parents(key);
	//net.clear();
	//net.distances(key);
	//if (net.dist[start_end] == 1234567890) {
	//	out << -1;
	//	in.close();
	//	out.close();
	//	return 0;
	//}
	result = net.bfs(start_end, key);
	if (result == -1) {
		out << -1;
		in.close();
		out.close();
		return 0;
	}
	net.parents(key);
	net.clear();
	net.bfs(key, start_end);
	if (net.dist[start_end] == -1) {
		out << -1;
		in.close();
		out.close();
		return 0;
	}
	result += net.dist[start_end];
	out << result;

	in.close();
	out.close();
	return 0;
}