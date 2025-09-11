import java.util.Scanner;
import java.lang.Math;

import static java.lang.Math.sinh;

public class Main {
    public static void main(String[] args) {

        System.out.println("Hello and welcome!");

        for (int i = 1; i <= 5; i++) {

            System.out.println("i = " + i);
        }
    }
}

class Tailor {

    public static double CalculateE(int k){
        double E = 1;
        for(int i = 0; i < k; i++)
            E /= 10;
        return E;
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);

        System.out.print("Введите x: ");
        long x = in.nextLong();
        System.out.print("Введите k: ");
        int k = in.nextInt();
        double e = CalculateE(k);
        System.out.printf("%.12f", CalculateTailor.CalculateSum(x, e));
        System.out.print("\n" + sinh(x));

        in.close();
    }

}

class CalculateTailor extends Tailor{
    public static double CalculateSum(long x, double e){
        double sum = 0;
        double component = x;
        for(int i = 2; component > e; i++) {
            sum += component;
            component *= (double) (x * x) / ((2 * i - 1) * (2 * i - 2));
        }
        return sum;
    }
}