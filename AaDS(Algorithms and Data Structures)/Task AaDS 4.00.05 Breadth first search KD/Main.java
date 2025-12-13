import java.io.*;
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
class ReadWriteMatr{
    public static int[][] read() throws FileNotFoundException {
        try (Scanner rd = new Scanner(new FileReader("input.txt"))){
            int n = rd.nextInt();
            int[][] matr = new int[n][n];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    matr[i][j] = rd.nextInt();
                }
            }
            return matr;
        } catch (FileNotFoundException e){
            e.fillInStackTrace();
            return null;
        }
    }

    public static void write(int[] labels) throws IOException {
        try (BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"))) {
            for (int label : labels) {
                wr.write(Integer.toString(label));
                wr.write(" ");
            }
        } catch (IOException e) {
            e.fillInStackTrace();
        }

    }
}

class BFS{
    public static int[] bfs(int[][] matr){
        int[] labels = new int[matr.length];
        boolean[] visited = new boolean[matr.length];
        ArrayDeque<Integer> q = new ArrayDeque<Integer>();
        int v, label = 1;
        boolean is_all = false;
        while (!is_all) {
            int start = 0;
            for (int i = 0; i < visited.length; i++) {
                if (!visited[i]) {
                    start = i;
                    break;
                }
            }
            q.addLast(start);
            visited[start] = true;
            labels[start] = label++;
            while (!q.isEmpty()) {
                v = q.poll();
                for (int i = 0; i < matr.length; i++) {
                    if (matr[v][i] == 1 & !visited[i]) {
                        visited[i] = true;
                        labels[i] = label++;
                        q.addLast(i);
                    }
                }
            }
            is_all = true;
            for (int i = 0; i < visited.length; i++) {
                if (!visited[i]) {
                    is_all = false;
                    break;
                }
            }
        }
        return labels;
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        int[][] matr = ReadWriteMatr.read();
        int[] labels = BFS.bfs(matr);
        ReadWriteMatr.write(labels);
    }
}