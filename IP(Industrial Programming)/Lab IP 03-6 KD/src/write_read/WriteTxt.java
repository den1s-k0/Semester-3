package write_read;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class WriteTxt{
    public static void WriteStr(String file_name, String str) throws IOException {
        try (BufferedWriter wr = new BufferedWriter(new FileWriter(file_name))) {
            wr.write(str);
        }
    }
}
