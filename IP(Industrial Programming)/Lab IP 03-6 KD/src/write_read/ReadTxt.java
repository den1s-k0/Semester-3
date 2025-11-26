package write_read;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadTxt{
    public static String ReadTxt(String file_name) throws IOException {
        String line;
        try(BufferedReader scanner = new BufferedReader(new FileReader(file_name))){
            line = scanner.readLine();
        }
        return line;
    }
}
