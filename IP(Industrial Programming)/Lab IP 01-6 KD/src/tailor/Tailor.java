package tailor;

import java.util.Formatter;
import java.util.Scanner;
import static java.lang.Math.sinh;

public class Tailor {
    public static double CalculateE(int k){
        double E = 1;
        for(int i = 0; i < k; i++)
            E /= 10;
        return E;
    }

    public static double CalculateSum(long x, double e){
        double sum = 0;
        double component = x;
        for(int i = 2; component > e; i++) {
            sum += component;
            component *= (double) (x * x) / ((2 * i - 1) * (2 * i - 2));
        }
        return sum;
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        Formatter fmt = new Formatter();

        System.out.print("Enter x: ");
        long x = in.nextLong();
        System.out.print("Enter k: ");
        int k = in.nextInt();
        double e = CalculateE(k);
        double res = CalculateSum(x, e);
        fmt.format("Dec x:\t % (d \n Hex x:\t %x \n Octal x:\t %#o \n", x, x, x);
        System.out.print(fmt);
        System.out.printf("-: %-5d\n", x, 40);
        System.out.printf("+: %+d\n", +x);
        System.out.printf("Result Tailor: %.12e \n", res);
        System.out.printf("Result Tailor: % ,f \n", res);
        System.out.println("Result Built-in: " + sinh(x));
        in.close();
        fmt.close();
    }

}
