import org.junit.jupiter.api.Test;
import tailor.BigTailor;
import java.math.BigDecimal;
import java.math.BigInteger;

import static org.junit.jupiter.api.Assertions.*;

class BigTailorTest {

    @Test
    void calculateBigE() {
        BigInteger k = BigInteger.valueOf(3);
        BigDecimal expected = new BigDecimal("0.001");
        BigDecimal actual = BigTailor.CalculateBigE(k);

        // Сравниваем по значению, игнорируя scale
        assertTrue(actual.compareTo(expected) == 0,
                "Expected E = " + expected + ", but got " + actual);
    }

    @Test
    void calculateBigSum() {
        BigDecimal x = new BigDecimal("2");
        BigInteger k = BigInteger.valueOf(5);
        BigDecimal e = BigTailor.CalculateBigE(k);
        BigDecimal result = BigTailor.CalculateBigSum(x, e, k);

        // Проверим, что результат близок к sinh(x) - x
        BigDecimal expected = BigDecimal.valueOf(Math.sinh(2));
        BigDecimal delta = new BigDecimal("0.00001");

        assertTrue(result.subtract(expected).abs().compareTo(delta) < 0,
                "Expected ≈ " + expected + ", but got " + result);
    }
}