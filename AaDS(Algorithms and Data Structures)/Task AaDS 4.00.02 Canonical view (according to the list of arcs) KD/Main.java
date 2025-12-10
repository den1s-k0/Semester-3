import java.io.*;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        int from, to, n = 0;
        try(Scanner rd = new Scanner(new FileReader("input.txt"))){
            n = rd.nextInt();
            int[] pred = new int[n + 1];
            for(int i = 0; i < n - 1; i++){
                from = rd.nextInt();
                to = rd.nextInt();
                pred[to] = from;
            }
            try(BufferedWriter wr = new BufferedWriter((new FileWriter("output.txt")))){
                for(int i = 1; i < n + 1; i++) {
                    wr.write(Integer.toString(pred[i]));
                    wr.write(' ');
                }
            } catch(IOException e){
                e.printStackTrace();
            }
        } catch(IOException e){
            e.printStackTrace();
        }
    }
}