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

class DFS{

    public static void dfs(int[][] matr, int[] labels, boolean[] visited, int[] label, int start) {
        visited[start] = true;
        labels[start] = label[0]++;
        for (int i = 0; i < matr[start].length; i++) {
            if (matr[start][i] == 1 && !visited[i]) {
                dfs(matr, labels, visited, label, i);
            }
        }
    }
    public static int[] startDfs(int[][] matr) {
        int[] labels = new int[matr.length];
        boolean[] visited = new boolean[matr.length];
        int[] label = {1};
        boolean is_all = false;
        while (!is_all) {
            int start = 0;
            for (int i = 0; i < visited.length; i++) {
                if (!visited[i]) {
                    start = i;
                    break;
                }
            }
            dfs(matr, labels, visited, label, start);
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
        int[] labels = DFS.startDfs(matr);
        ReadWriteMatr.write(labels);
    }
}