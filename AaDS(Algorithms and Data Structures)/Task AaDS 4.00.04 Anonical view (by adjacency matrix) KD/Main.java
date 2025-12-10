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
            int n, x;
            n = rd.nextInt();
            int[][] matr = new int[n][n];
            int[] pred = new int[n];

            for(int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    x = rd.nextInt();
                    if(x == 1)
                        pred[j] = i + 1;
                }
            }
            try(BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"))){
                for(int i = 0; i < n; i++){
                    wr.write(Integer.toString(pred[i]) + ' ');
                }
            } catch(IOException e){
                e.printStackTrace();
            }
        } catch(IOException e){
            e.printStackTrace();
        }
    }
}