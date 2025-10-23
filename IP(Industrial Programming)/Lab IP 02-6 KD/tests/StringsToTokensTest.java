package tests;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import static strings.StringsToTokens.*;

import java.util.Arrays;

class StringsToTokensTest {

    @Test
    void writeReadTxtFile() {
        String path = "D:\\BSU\\Third Semester\\IP(Industrial Programming)\\Lab IP 02-6 KD\\src\\Files\\test_default.txt";
        String[] test_output = {"this is the test string, which i write int file and after i will read it", " "};
        WriteTxtFile(path, test_output[0]);
        WriteTxtFile(path, test_output[1]);
        String[] test_input = ReadTxtFile(path);
        assertEquals(test_output[0], test_input[0]);
        assertEquals(test_output[1], test_input[1]);
    }

    @Test
    void writeRead_empty_str_TxtFile() {
        String path = "D:\\BSU\\Third Semester\\IP(Industrial Programming)\\Lab IP 02-6 KD\\src\\Files\\test_empty.txt";
        String[] test_output = {"", ""};
        WriteTxtFile(path, test_output[0]);
        WriteTxtFile(path, test_output[1]);
        String[] test_input = ReadTxtFile(path);
        assertEquals(test_output[0], test_input[0]);
        assertEquals(test_output[1], test_input[1]);
    }

    @Test
    void tokenizer() {
        String test_input = "String*+-+with+-*+-lots*+-*+-of-+*separators";
        String test_sep = "+-*";
        String[] test_output = Tokenizer(test_input, test_sep);
        assertEquals("String", test_output[0]);
        assertEquals("with", test_output[1]);
        assertEquals("lots", test_output[2]);
        assertEquals("of", test_output[3]);
        assertEquals("separators", test_output[4]);
    }

    @Test
    void tokenizer_empty_sep() {
        String test_input = "String*+-+with+-*+-lots*+-*+-of-+*separators";
        String test_sep = "";
        String[] test_output = Tokenizer(test_input, test_sep);
        assertEquals("String*+-+with+-*+-lots*+-*+-of-+*separators", test_output[0]);
    }

    @Test
    void tokenizer_empty_str() {
        String test_input = "";
        String test_sep = "$|";
        String[] test_output = Tokenizer(test_input, test_sep);
        assertNull(test_output);
    }

    @Test
    void tokenizer_single_separator() {
        String test_input = "word1,word2,word3";
        String test_sep = ",";
        String[] test_output = Tokenizer(test_input, test_sep);
        assertEquals(3, test_output.length);
        assertEquals("word1", test_output[0]);
        assertEquals("word2", test_output[1]);
        assertEquals("word3", test_output[2]);
    }

    @Test
    void oneSeparatorSplit() {
        String test_input = "String*+-+with+-*+-lots*+-*+-of-+*separators";
        String test_sep = "-+*";
        String[] test_output = OneSeparatorSplit(test_input, test_sep);
        assertEquals("String", test_output[0]);
        assertEquals("with", test_output[1]);
        assertEquals("lots", test_output[2]);
        assertEquals("of", test_output[3]);
        assertEquals("separators", test_output[4]);
    }

    @Test
    void oneSeparatorSplit_empty_sep() {
        String test_input = "String*+-+with+-*+-lots*+-*+-of-+*separators";
        String test_sep = "";
        String[] test_output = OneSeparatorSplit(test_input, test_sep);
        assertEquals("String*+-+with+-*+-lots*+-*+-of-+*separators", test_output[0]);
    }

    @Test
    void oneSeparatorSplit_empty_str() {
        String test_input = "";
        String test_sep = "$|";
        String[] test_output = OneSeparatorSplit(test_input, test_sep);
        assertNull(test_output);
    }

    @Test
    void oneSeparatorSplit_single_separator() {
        String test_input = "word1;word2;word3";
        String test_sep = ";";
        String[] test_output = OneSeparatorSplit(test_input, test_sep);
        assertEquals(3, test_output.length);
        assertEquals("word1", test_output[0]);
        assertEquals("word2", test_output[1]);
        assertEquals("word3", test_output[2]);
    }

    @Test
    void decimalNumbers() {
        String[] test_input = {"123", "abc", "45", "def", "678", "9"};
        String result = DecimalNumbers(test_input);
        assertEquals("123 45 678 9 ", result);
    }

    @Test
    void decimalNumbers_no_numbers() {
        String[] test_input = {"abc", "def", "ghi"};
        String result = DecimalNumbers(test_input);
        assertEquals("", result);
    }

    @Test
    void decimalNumbers_empty_array() {
        String[] test_input = {};
        String result = DecimalNumbers(test_input);
        assertEquals("", result);
    }

    @Test
    void decimalNumbers_with_negative() {
        String[] test_input = {"123", "-45", "678"};
        String result = DecimalNumbers(test_input);
        assertEquals("123 -45 678 ", result);
    }

    @Test
    void findDates_no_dates() {
        String test_input = "Some text without dates";
        FindDates(test_input);
        assertFalse(FindDates(test_input));
    }

    @Test
    void validTime() {
        String[] test_input = {"12\\34\\56", "23\\45\\01", "invalid", "60\\70\\80"};
        String[] result = ValidTime(test_input);
        assertNotNull(result);
        assertEquals(2, result.length);
    }

    @Test
    void validTime_no_valid_times() {
        String[] test_input = {"60\\70\\80", "invalid", "99\\99\\99"};
        String[] result = ValidTime(test_input);
        assertNotNull(result);
        assertEquals("", result[0].trim());
        assertEquals("", result[1].trim());
    }

    @Test
    void validTime_empty_array() {
        String[] test_input = {};
        String[] result = ValidTime(test_input);
        assertNotNull(result);
        assertEquals(2, result.length);
    }

    @Test
    void findMinToken() {
        String[] test_input = {"123abc", "45xyz", "6pqr", "8901mn", "nonumber"};
        int result = FindMinToken(test_input);
        assertEquals(2, result);
    }

    @Test
    void findMinToken_no_numbers_at_start() {
        String[] test_input = {"abc123", "xyz45", "pqr"};
        int result = FindMinToken(test_input);
        assertEquals(-1, result);
    }

    @Test
    void findMinToken_empty_array() {
        String[] test_input = {};
        int result = FindMinToken(test_input);
        assertEquals(-1, result);
    }

    @Test
    void findMinToken_single_valid() {
        String[] test_input = {"123abc"};
        int result = FindMinToken(test_input);
        assertEquals(0, result);
    }

    @Test
    void findDecToken() {
        String[] test_input = {"abc", "123", "def", "456"};
        int result = FindDecToken(test_input);
        assertEquals(1, result);
    }

    @Test
    void findDecToken_no_decimals() {
        String[] test_input = {"abc", "def", "ghi"};
        int result = FindDecToken(test_input);
        assertEquals(1, result);
    }

    @Test
    void findDecToken_empty_array() {
        String[] test_input = {};
        int result = FindDecToken(test_input);
        assertEquals(0, result);
    }

    @Test
    void findDecToken_first_element() {
        String[] test_input = {"123", "abc", "def"};
        int result = FindDecToken(test_input);
        assertEquals(0, result);
    }

    @Test
    void createResult() {
        String[] test_input = {"token1", "token2", "token3", "token4"};
        int min_ind = 1;
        int dec_ind = 2;
        String result = CreateResult(test_input, min_ind, dec_ind);

        assertNotNull(result);
        assertTrue(result.contains("token1"));
        assertTrue(result.contains("token3"));
        assertTrue(result.contains("token4"));
        assertFalse(result.contains("token2"));
        assertTrue(result.matches(".*\\d+.*"));
    }

    @Test
    void createResult_no_min_token() {
        String[] test_input = {"token1", "token2", "token3"};
        int min_ind = -1;
        int dec_ind = 1;
        String result = CreateResult(test_input, min_ind, dec_ind);

        assertNotNull(result);
        assertTrue(result.contains("token1"));
        assertTrue(result.contains("token2"));
        assertTrue(result.contains("token3"));
        assertTrue(result.matches(".*\\d+.*"));
    }

    @Test
    void createResult_empty_array() {
        String[] test_input = {};
        int min_ind = -1;
        int dec_ind = 0;
        String result = CreateResult(test_input, min_ind, dec_ind);

        assertEquals("", result.trim());
    }
}