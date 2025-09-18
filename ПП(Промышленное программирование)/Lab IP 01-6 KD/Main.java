import java.util.Scanner;
import java.util.Formatter;
import static java.lang.Math.sinh;
import java.math.BigInteger;
import java.math.BigDecimal;
import java.math.MathContext;


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
    public static BigDecimal CalculateBigE(BigInteger k){
        int scale = k.intValue() + 50;
        MathContext mc = new MathContext(scale);

        BigDecimal E = BigDecimal.valueOf(1);
        BigDecimal T = BigDecimal.valueOf(10);
        BigInteger O = BigInteger.valueOf(1);
        BigInteger i = BigInteger.valueOf(0);

        while(i.compareTo(k) < 0){
            E = E.divide(T, mc);
            i = i.add(O);
        }

        return E;
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        BigDecimal x = BigDecimal.valueOf(0);
        BigInteger k = BigInteger.valueOf(0);
        BigDecimal e = BigDecimal.valueOf(0);

        System.out.print("Enter x: ");
        x = in.nextBigDecimal();
        System.out.print("Enter k: ");
        k = in.nextBigInteger();
        e = CalculateBigE(k);
        BigDecimal res = CalculateBigTailor.CalculateBigSum(x, e, k);
        System.out.printf("Result Tailor: " + res + "\n");
        System.out.println("Result Built-in: " + sinh(x.doubleValue()));

        in.close();
    }
}

class CalculateBigTailor extends BigTailor{
    public static BigDecimal CalculateBigSum(BigDecimal x, BigDecimal e, BigInteger k){
        BigDecimal sum = BigDecimal.valueOf(0);
        BigDecimal component = x;
        int scale = k.intValue() + 50;
        MathContext mc = new MathContext(scale);
        //component *= (double) (x * x) / ((2 * i - 1) * (2 * i - 2));

        BigDecimal i = BigDecimal.valueOf(2);

        while(component.compareTo(e) > 0){
            sum = sum.add(component);
            component = component.multiply(x.multiply(x));
            component = (component.divide((i.multiply(BigDecimal.valueOf(2))).subtract(BigDecimal.valueOf(1)), mc))
                    .divide((i.multiply(BigDecimal.valueOf(2))).subtract(BigDecimal.valueOf(2)), mc);
            i = i.add(BigDecimal.valueOf(1));
        }
        return sum;
    }
}
