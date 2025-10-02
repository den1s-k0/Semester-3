import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import static java.lang.Math.sinh;
import tailor.Tailor;

class TailorTest {

    @Test
    void testCalculateE() {
        assertEquals(0.001, Tailor.CalculateE(3), 1e-10);
    }

    @Test
    void testCalculateSum() {
        double e = Tailor.CalculateE(5); // 0.00001
        double result = Tailor.CalculateSum(2, e);
        double expected = sinh(2);
        assertEquals(expected, result, 1e-5);
    }
}
