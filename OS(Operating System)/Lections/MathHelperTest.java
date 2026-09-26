package com.aptkode.math;

import io.qameta.allure.*;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.*;

@Epic("Math Operations")
@Feature("Math Helper Methods")
@DisplayName("Тестирование математических операций")
class MathHelperTest {



    @Story("Вычисление факториала")
    @Feature("Factorial Calculation")
    @DisplayName("Позитивные тесты факториала")
    @Description("Тестирование корректных значений для метода factorial")
    @Severity(SeverityLevel.CRITICAL)
    @ParameterizedTest(name = "Факториал {0} должен равняться {1}")
    @CsvSource(value = {
            "0|1",
            "1|1",
            "5|120",
            "6|720",
            "10|3628800"
    }, delimiter = '|')
    void factorial_ValidNumbers_ReturnsCorrectResult(int number, int expectedValue) {

        int actualResult = MathHelper.factorial(number);


        assertEquals(expectedValue, actualResult,
                "Факториал числа " + number + " должен быть " + expectedValue);
    }

    @Story("Обработка ошибок в факториале")
    @DisplayName("Факториал с отрицательным числом - исключение")
    @Description("Тестирование обработки невалидных входных данных")
    @Severity(SeverityLevel.NORMAL)
    @Test
    void factorial_NegativeNumber_ThrowsIllegalArgumentException() {
        // Arrange
        int negativeNumber = -5;


        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> MathHelper.factorial(negativeNumber)
        );

        assertEquals("input should be greater than 0!", exception.getMessage());
    }

    @Story("Вычисление факториала")
    @DisplayName("Факториал граничных значений")
    @Severity(SeverityLevel.MINOR)
    @Test
    void factorial_BoundaryValues_ReturnsCorrectResults() {
        // Boundary values test
        Allure.step("Проверка факториала 0", () -> {
            assertEquals(1, MathHelper.factorial(0));
        });

        Allure.step("Проверка факториала 1", () -> {
            assertEquals(1, MathHelper.factorial(1));
        });

        Allure.step("Проверка факториала 2", () -> {
            assertEquals(2, MathHelper.factorial(2));
        });
    }



    @Story("Проверка простых чисел")
    @Feature("Prime Number Detection")
    @DisplayName("Простые числа определяются корректно")
    @Description("Тестирование определения простых чисел")
    @Severity(SeverityLevel.CRITICAL)
    @ParameterizedTest(name = "Число {0} является простым")
    @ValueSource(ints = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29})
    void isPrime_PrimeNumbers_ReturnsTrue(int primeNumber) {
        Allure.step("Проверка что число " + primeNumber + " определяется как простое", () -> {
            assertTrue(MathHelper.isPrime(primeNumber),
                    "Число " + primeNumber + " должно определяться как простое");
        });
    }

    @Story("Проверка простых чисел")
    @DisplayName("Составные числа определяются корректно")
    @Severity(SeverityLevel.CRITICAL)
    @ParameterizedTest(name = "Число {0} не является простым")
    @ValueSource(ints = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18})
    void isPrime_NonPrimeNumbers_ReturnsFalse(int nonPrimeNumber) {
        Allure.step("Проверка что число " + nonPrimeNumber + " определяется как составное", () -> {
            assertFalse(MathHelper.isPrime(nonPrimeNumber),
                    "Число " + nonPrimeNumber + " должно определяться как составное");
        });
    }

    @Story("Граничные случаи простых чисел")
    @DisplayName("Граничные значения для простых чисел")
    @Severity(SeverityLevel.NORMAL)
    @Test
    void isPrime_BoundaryValues_ReturnsExpectedResults() {
        Allure.step("Проверка числа 0", () -> {
            assertFalse(MathHelper.isPrime(0), "0 не является простым числом");
        });

        Allure.step("Проверка числа 1", () -> {
            assertFalse(MathHelper.isPrime(1), "1 не является простым числом");
        });

        Allure.step("Проверка числа 2", () -> {
            assertTrue(MathHelper.isPrime(2), "2 является простым числом");
        });
    }

    @Story("Ошибки в алгоритме простых чисел")
    @DisplayName("Отрицательные числа не являются простыми")
    @Severity(SeverityLevel.MINOR)
    @Test
    void isPrime_NegativeNumber_ReturnsFalse() {

        Allure.step("Проверка отрицательного числа", () -> {
            assertFalse(MathHelper.isPrime(-5), "Отрицательные числа не могут быть простыми");
        });
    }

  

    @Story("Производительность и особые случаи")
    @DisplayName("Большие числа для факториала")
    @Severity(SeverityLevel.MINOR)
    @Test
    void factorial_LargerNumber_ReturnsCorrectValue() {
        // Note: This might fail due to integer overflow - demonstrating potential issue
        Allure.step("Вычисление факториала 12", () -> {
            int result = MathHelper.factorial(12);
            assertEquals(479001600, result, "Факториал 12 должен быть 479001600");
        });
    }

    @Story("Интеграционное тестирование")
    @Feature("Combined Operations")
    @DisplayName("Комбинированные операции")
    @Severity(SeverityLevel.NORMAL)
    @Test
    void combinedOperations_ValidScenario_WorksCorrectly() {
        Allure.step("Проверка что факториал простого числа вычисляется корректно", () -> {
            int primeNumber = 5;

            Allure.step("Проверяем что 5 является простым числом", () -> {
                assertTrue(MathHelper.isPrime(primeNumber));
            });

            Allure.step("Вычисляем факториал простого числа", () -> {
                int factorialResult = MathHelper.factorial(primeNumber);
                assertEquals(120, factorialResult);
            });
        });
    }

    @Test
    @DisplayName("Тест с падением на конкретном шаге")
    void testWithFailure_ShowsExactFailedStep() {
        Allure.step("Шаг 1: Этот шаг выполнится успешно", () -> {
            assertEquals(1, MathHelper.factorial(1));
        });

        Allure.step("Шаг 2: Этот шаг УПАДЕТ - здесь ошибка", () -> {
            // Этот assert упадет
            assertEquals(100, MathHelper.factorial(5));
        });

        Allure.step("Шаг 3: Этот шаг не выполнится из-за падения", () -> {
            assertTrue(MathHelper.isPrime(5));
        });
    }
}