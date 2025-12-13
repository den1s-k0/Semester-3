import java.io.*;
import java.util.*;

import static java.lang.Math.min;

class WriteRead {
    public static Graf read() throws IOException {
        try (BufferedReader rd = new BufferedReader(new FileReader("input.txt"))) {
            String[] line = rd.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            Graf graf = new Graf(n);
            for (int i = 0; i < m; i++) {
                line = rd.readLine().split(" ");
                int f = Integer.parseInt(line[0]);
                int t = Integer.parseInt(line[1]);
                int c = Integer.parseInt(line[2]);
                graf.addEdge(f - 1, t - 1, c);
            }
            rd.close();
            return graf;
        } catch (IOException e) {
            e.fillInStackTrace();
            return null;
        }
    }

    public static void write(long answer) throws IOException {
        try (BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"))) {
            wr.write(Long.toString(answer));
            wr.close();
        } catch (IOException e) {
            e.fillInStackTrace();
        }
    }
}

class Graf {
    class Edge {
        public int from, to, cost;

        public Edge (int from, int to, int cost) {
            this.from = from;
            this.to = to;
            this.cost = cost;
        }
    }
    public ArrayList<ArrayList<Edge>> gr;

    public Graf(int size) {
        gr = new ArrayList<>(size);
        for(int  i = 0; i < size; i++){
            gr.add(new ArrayList<Edge>());
        }
    }

    public void addEdge (int from, int to, int cost) {
        gr.get(from).add(new Edge(from, to, cost));
        gr.get(to).add(new Edge(to, from, cost));
    }

    public long distances() {
        int n = gr.size();
        long[] dist = new long[n];
        Arrays.fill(dist, Long.MAX_VALUE);
        dist[0] = 0;
        PriorityQueue<long[]> pq = new PriorityQueue<>(Comparator.comparingLong(a -> a[0]));
        pq.offer(new long[]{0, 0});

        while (!pq.isEmpty()) {
            long[] current = pq.poll();
            long currentDist = current[0];

            if (currentDist != dist[(int)current[1]]) {
                continue;
            }

            for (Edge edge : gr.get((int)current[1])) {
                long newDist = currentDist + edge.cost;

                if (newDist < dist[edge.to]) {
                    dist[edge.to] = newDist;
                    pq.offer(new long[]{newDist, edge.to});
                }
            }
        }

        return dist[n - 1];
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        Graf graf = WriteRead.read();
        if (graf != null) {
            WriteRead.write(graf.distances());
        }
    }
}