import java.util.Scanner;
import java.util.Formatter;
import static java.lang.Math.sinh;
import java.math.BigInteger;

public class Main {
    public static void main(String[] args) {

        System.out.println("Hello and welcome!");

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
        Formatter fmt = new Formatter();

        System.out.print("Enter x: ");
        long x = in.nextLong();
        System.out.print("Enter k: ");
        int k = in.nextInt();
        double e = CalculateE(k);
        double res = CalculateTailor.CalculateSum(x, e);
        fmt.format("Dec x: %d \nHex x: %x \nOctal x: %o \n", x, x, x);
        System.out.print(fmt);
        System.out.printf("Result Tailor: %.12e \n", res);
        System.out.println("Result Built-in: " + sinh(x));


        in.close();
        fmt.close();
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

class BigTailor{
    public static double CalculateBigE(int k){
        return 0;
    }

    public static void main(String[] args){

    }
}
