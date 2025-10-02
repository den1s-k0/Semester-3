package tailor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;

import static java.lang.Math.sinh;

public class BigTailor{
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

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        BigDecimal e = BigDecimal.valueOf(0);

        System.out.print("Enter x: ");
        String input;
        input = in.readLine();
        BigDecimal x = new BigDecimal(input);
        System.out.print("Enter k: ");
        input = in.readLine();
        BigInteger k = new BigInteger(input);
        e = CalculateBigE(k);
        BigDecimal res = CalculateBigSum(x, e, k);
        System.out.printf("Result Tailor: " + res + "\n");
        System.out.println("Result Built-in: " + sinh(x.doubleValue()));

        in.close();
    }
}
