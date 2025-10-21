import java.io.*;
import java.lang.String;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class StringsToTokens {

    public static String[] ReadTxtFile(String filename) {

        try(BufferedReader br = new BufferedReader(new FileReader(filename)))
        {
            String[] s = new String[2];
            s[0]=br.readLine();
            System.out.println(s[0]);
            s[1]=br.readLine();
            System.out.println(s[1]);
            return s;
        }
        catch(IOException ex){

            System.out.println(ex.getMessage());
        }
        String[] s = {"ERROR", "TRY ONE MORE TIME"};
        return s;
    }

    public static void WriteTxtFile(String filename, String str) {

        try(BufferedWriter bw = new BufferedWriter(new FileWriter(filename, true))) {
                bw.write(str + "\n");
        }
        catch(IOException ex){

            System.out.println(ex.getMessage());
        }
    }

    public static String[] Tokenizer(String str, String sep) {
        StringTokenizer st = new StringTokenizer(str, sep);
        String[] tokens_tokenizer = new String[st.countTokens()];
        System.out.println("\nTokenizer output:");
        for(int i = 0; st.hasMoreTokens(); i++) {
            tokens_tokenizer[i] = st.nextToken();
            System.out.println(tokens_tokenizer[i]);
        }
        return tokens_tokenizer;
    }

    public static String[] OneSeparatorSplit(String str, String sep){
        String one_sep_str = sep.substring(0, 1);
        int k = 0;
        for(int i = 0; i < str.length(); i++){
            boolean is_sep = false;
            for(int j = 0; j < sep.length(); j++) {
                if (str.charAt(i) == sep.charAt(j)) {
                    is_sep = true;
                    if (one_sep_str.charAt(k) != sep.charAt(0)) {
                        one_sep_str += sep.charAt(0);
                        k++;
                    }
                    break;
                }
            }
            if(is_sep == false){
                one_sep_str += str.charAt(i);
                k++;
            }
        }

        if(one_sep_str.charAt(one_sep_str.length() - 1) == sep.charAt(0))
            one_sep_str = one_sep_str.substring(1, one_sep_str.length() - 1);
        else
            one_sep_str = one_sep_str.substring(1);

        String[] tokens_split = one_sep_str.split(sep.substring(0, 1));
        System.out.println("\nSplit output:");
        for(String token: tokens_split){
            System.out.println(token);
        }
        return tokens_split;
    }

    public static String DecimalNumbers(String[] strs){
        StringBuilder numbers = new StringBuilder();
        int number;
        System.out.println("\nNumbers output: ");
        for(int i = 0; i < strs.length; i++) {
            try {
                number = Integer.parseInt(strs[i]);
                System.out.println(number);
                numbers.append(number);
                numbers.append(' ');
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return numbers.toString();
    }

    public static void FindDates(String str){
        Pattern pattern = Pattern.compile("[0-5][0-9]\\\\([0-1][0-9]|2[0-4])\\\\[0-5][0-9]");
        System.out.println("\nDates found: ");
        Matcher matcher = pattern.matcher(str);
        while(matcher.find()) {
            System.out.println(matcher.group());
        }
    }

    public static String[] ValidTime(String[] strs) {
        StringBuilder dates_not_sorted = new StringBuilder();
        StringBuilder dates_sorted = new StringBuilder();
        StringBuilder dates_buffer= new StringBuilder();
        int date_count = 0;

        for(int i = 0; i < strs.length; i++){
            if (strs[i] == null || !strs[i].matches("\\d{2}\\\\\\d{2}\\\\\\d{2}")) {
                continue;
            }
            String normalizedTime = strs[i].replace("\\", ":");
            SimpleDateFormat sdf = new SimpleDateFormat("mm:HH:ss");
            sdf.setLenient(false);
            try {
                Date time = sdf.parse(normalizedTime);
                dates_not_sorted.append(strs[i]);
                dates_not_sorted.append(' ');
                date_count++;
            } catch (ParseException e) {
                continue;
            }
        }
        Date[] date_arr = new Date[date_count];
        date_count = 0;
        for(int i = 0; i < strs.length; i++){
            if (strs[i] == null || !strs[i].matches("\\d{2}\\\\\\d{2}\\\\\\d{2}")) {
                continue;
            }
            String normalizedTime = strs[i].replace("\\", ":");
            SimpleDateFormat sdf = new SimpleDateFormat("mm:HH:ss");
            sdf.setLenient(false);
            try {
                date_arr[date_count] = sdf.parse(normalizedTime);
                date_count++;
            } catch (ParseException e) {
                continue;
            }
        }
        Arrays.sort(date_arr);
        for(int i = 0; i < date_count; i++){
            dates_buffer.append(date_arr[i]);
            dates_buffer.delete(0, 11);
            dates_buffer.reverse();
            dates_buffer.delete(0, 9);
            dates_buffer.insert(0, ' ');
            dates_buffer.reverse();
            dates_sorted.append(dates_buffer);
        }
        String[] result = new String[2];
        result[0] = dates_not_sorted.toString();
        result[1] = dates_sorted.toString();
        result[1] = result[1].replace(":", "\\");
        System.out.println("\nDates found: ");
        System.out.println(result[0]);
        System.out.println("\nSort dates: ");
        System.out.println(result[1]);
        return result;
    }

    public static int FindMinToken(String[] strs){
        int min_length = strs[0].length(), min_index = -1;
        for(int i = 0; i < strs.length; i++) {
            if (strs[i] == null || !strs[i].matches("\\d\\.*")) {
                continue;
            }
            if(strs[i].length() < min_length){
                min_length = strs[i].length();
                min_index = i;
            }
        }
        return min_index;
    }

    public static int FindDecToken(String[] strs) {
        int dec_ind = strs.length / 2;
        for(int i = 0; i < strs.length; i++) {
            try {
                Integer.parseInt(strs[i]);
                dec_ind = i;
                break;
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return dec_ind;
    }

    public static String CreateResult(String[] strs, int min_ind, int dec_ind){
        StringBuffer result = new StringBuffer();
        for(int i = 0; i < strs.length; i++){
            if(i - 1 == dec_ind)
                result.append(((int)(Math.random() * 100)) + " ");
            if(i == min_ind)
                continue;
            result.append(strs[i] + ' ');
        }
        System.out.println("\nResult: ");
        System.out.println(result);
        return result.toString();
    }

    public static void main(String[] args){
        String input_path = "D:\\BSU\\Third Semester\\IP(Industrial Programming)\\Lab IP 02-6 KD\\src\\Files\\input.txt";
        String output_path = "D:\\BSU\\Third Semester\\IP(Industrial Programming)\\Lab IP 02-6 KD\\src\\Files\\output.txt";
        String[] inp = ReadTxtFile(input_path);

        String[] tokens_tokenizer = Tokenizer(inp[0], inp[1]);

        String[] tokens_split = OneSeparatorSplit(inp[0], inp[1]);

        String dec_numbers = DecimalNumbers(tokens_tokenizer);
        WriteTxtFile(output_path, "\nDecimal Numbers: ");
        WriteTxtFile(output_path, dec_numbers);

        String[] time = ValidTime(tokens_split);
        WriteTxtFile(output_path, "\nTime: ");
        WriteTxtFile(output_path, time[0]);
        WriteTxtFile(output_path, "\nSort Time: ");
        WriteTxtFile(output_path, time[1]);

        int min_token = FindMinToken(tokens_tokenizer);

        int dec_token = FindDecToken(tokens_split);

        String result = CreateResult(tokens_tokenizer, min_token, dec_token);
        WriteTxtFile(output_path, "\nResult: ");
        WriteTxtFile(output_path, result);
    }
}
