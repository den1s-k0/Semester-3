import java.io.*;
import java.lang.String;
import java.text.ParseException;
import java.text.SimpleDateFormat;
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

    public static int[] DecimalNumbers(String[] strs){
        int count_numbers = 0;
        for (int i = 0; i < strs.length; i++){
            try {
                Integer.parseInt(strs[i]);
                count_numbers++;
            } catch (NumberFormatException e) {
                continue;
            }
        }
        int[] numbers = new int[count_numbers];
        int j = 0;
        System.out.println("\nNumbers output: ");
        for(int i = 0; i < strs.length; i++) {
            try {
                numbers[j] = Integer.parseInt(strs[i]);
                System.out.println(numbers[j]);
                j++;
            } catch (NumberFormatException e) {
                continue;
            }
        }
        return numbers;
    }

    public static void FindDates(String str){
        Pattern pattern = Pattern.compile("[0-5][0-9]\\\\([0-1][0-9]|2[0-4])\\\\[0-5][0-9]");
        System.out.println("\nDates found: ");
        Matcher matcher = pattern.matcher(str);
        while(matcher.find()) {
            System.out.println(matcher.group());
        }
    }

    public static void isValidTime(String[] strs) {
        System.out.println("\nDates found: ");
        for(int i = 0; i < strs.length; i++){
            if (strs[i] == null || !strs[i].matches("\\d{2}\\\\\\d{2}\\\\\\d{2}")) {
                continue;
            }
            String normalizedTime = strs[i].replace("\\", ":");
            SimpleDateFormat sdf = new SimpleDateFormat("mm:HH:ss");
            sdf.setLenient(false);
            try {
                Date time = sdf.parse(normalizedTime);
                System.out.println(strs[i]);
            } catch (ParseException e) {
                continue;
            }
        }
    }

    public static void main(String[] args){
        String[] inp = ReadTxtFile("D:\\BSU\\Third Semester\\IP(Industrial Programming)\\Lab IP 02-6 KD\\src\\Files\\input.txt");
        int count_numbers = 0;

        String[] tokens_tokenizer = Tokenizer(inp[0], inp[1]);

        String[] tokens_split = OneSeparatorSplit(inp[0], inp[1]);

        int[] dec_numbers = DecimalNumbers(tokens_tokenizer);

        isValidTime(tokens_split);
    }
}
