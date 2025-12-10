import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        try(Scanner rd = new Scanner(new FileReader("input.txt"))){
            int n, m, from, to;
            n = rd.nextInt();
            m = rd.nextInt();
            List<Integer>[] lst = new ArrayList[n + 1];
            for(int i = 1; i < n + 1; i++)
                lst[i] = new ArrayList<>();

            for(int i = 0; i < m; i++){
                from = rd.nextInt();
                to = rd.nextInt();
                lst[from].add(to);
                lst[to].add(from);
            }
            try(BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"))){
                for(int i = 1; i < n + 1; i++){
                    wr.write(Integer.toString(lst[i].size()) + ' ');
                    for(int j = 0; j < lst[i].size(); j++)
                        wr.write(Integer.toString(lst[i].get(j)) + ' ');
                    wr.write('\n');
                }
            } catch(IOException e){
                e.printStackTrace();
            }
        } catch(IOException e){
            e.printStackTrace();
        }
    }
}