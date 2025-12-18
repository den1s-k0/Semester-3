package file_managers;

import builders.MenuDirector;
import cafe_menu.*;
import org.w3c.dom.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.jar.JarEntry;
import java.util.jar.JarInputStream;
import java.util.jar.JarOutputStream;
import java.util.zip.*;
import javax.crypto.*;
import javax.crypto.spec.SecretKeySpec;

public class FileManager {

    private static final String ENCRYPTION_KEY = "MySecretKey12345";

    public enum FileFormat {
        TXT, XML, JSON
    }

    public enum Compression {
        NONE, ZIP, JAR
    }

    public enum Encryption {
        NONE, AES
    }

    public static List<CafeMenuPosition> readFromFile(String filename,
                                                      FileFormat format,
                                                      Compression compression,
                                                      Encryption encryption) {

        String processedFilename = filename;

        try {
            if (compression != Compression.NONE) {
                processedFilename = decompressFile(filename, compression);
            }

            InputStream inputStream;
            if (encryption != Encryption.NONE) {
                byte[] encryptedData = readFileToBytes(processedFilename);
                byte[] decryptedData = decryptData(encryptedData, encryption);
                inputStream = new ByteArrayInputStream(decryptedData);
            } else {
                inputStream = new FileInputStream(processedFilename);
            }

            List<CafeMenuPosition> positions = new ArrayList<>();

            switch (format) {
                case TXT:
                    positions = readTextFormat(inputStream);
                    break;
                case XML:
                    positions = readXMLFormat(inputStream);
                    break;
                case JSON:
                    positions = readJSONFormat(inputStream);
                    break;
            }

            inputStream.close();

            if (compression != Compression.NONE && !processedFilename.equals(filename)) {
                new File(processedFilename).delete();
            }

            System.out.println("Загружено " + positions.size() + " позиций");
            return positions;

        } catch (Exception e) {
            System.err.println("Ошибка при чтении файла: " + e.getMessage());
            e.printStackTrace();
            return new ArrayList<>();
        }
    }

    public static void writeToFile(String filename,
                                   List<CafeMenuPosition> positions,
                                   FileFormat format,
                                   Compression compression,
                                   Encryption encryption) {

        try {
            String tempFilename = "temp_" + System.currentTimeMillis();
            OutputStream outputStream = new FileOutputStream(tempFilename);

            switch (format) {
                case TXT:
                    writeTextFormat(outputStream, positions);
                    break;
                case XML:
                    writeXMLFormat(outputStream, positions);
                    break;
                case JSON:
                    writeJSONFormat(outputStream, positions);
                    break;
            }

            outputStream.close();

            String processedFilename = tempFilename;
            if (encryption != Encryption.NONE) {
                byte[] data = readFileToBytes(tempFilename);
                byte[] encryptedData = encryptData(data, encryption);
                String encryptedFilename = tempFilename + "_enc";
                writeBytesToFile(encryptedFilename, encryptedData);
                new File(tempFilename).delete();
                processedFilename = encryptedFilename;
            }

            if (compression != Compression.NONE) {
                compressFile(processedFilename, filename, compression);
                new File(processedFilename).delete();
            } else {
                Files.copy(new File(processedFilename).toPath(),
                        new File(filename).toPath(),
                        StandardCopyOption.REPLACE_EXISTING);
                new File(processedFilename).delete();
            }

            System.out.println("Сохранено " + positions.size() + " позиций");

        } catch (Exception e) {
            System.err.println("Ошибка при записи файла: " + e.getMessage());
            e.printStackTrace();
        }
    }


    private static List<CafeMenuPosition> readTextFormat(InputStream inputStream) throws IOException {
        List<CafeMenuPosition> positions = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));

        String line;
        while ((line = reader.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty() || line.startsWith("#")) continue;

            try {
                CafeMenuPosition position = parseTextLine(line);
                positions.add(position);
            } catch (Exception e) {
                System.err.println("Ошибка при парсинге строки: " + e.getMessage());
            }
        }

        reader.close();
        return positions;
    }

    private static CafeMenuPosition parseTextLine(String line) {
        MenuDirector director = new MenuDirector();
        return director.fromFileString(line);
    }

    private static void writeTextFormat(OutputStream outputStream, List<CafeMenuPosition> positions) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));
        writer.write("# Файл меню кафе\n");
        writer.write("# Формат: TYPE;ID;NAME;PRICE;CATEGORY;CALORIES;DATE;PARAM1;PARAM2\n");
        writer.write("# Типы: DRINK, MAIN_COURSE, DESSERT\n\n");

        for (CafeMenuPosition position : positions) {
            writer.write(position.toFileString());
            writer.newLine();
        }
        writer.close();
    }

    private static List<CafeMenuPosition> readXMLFormat(InputStream inputStream) throws Exception {
        List<CafeMenuPosition> positions = new ArrayList<>();

        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document document = builder.parse(inputStream);
        document.getDocumentElement().normalize();

        NodeList positionNodes = document.getElementsByTagName("position");

        for (int i = 0; i < positionNodes.getLength(); i++) {
            Element positionElement = (Element) positionNodes.item(i);

            String type = positionElement.getAttribute("type");
            int id = Integer.parseInt(getElementText(positionElement, "id"));
            String name = getElementText(positionElement, "name");
            double price = Double.parseDouble(normalizeNumber(getElementText(positionElement, "price")));
            String category = getElementText(positionElement, "category");
            double calories = Double.parseDouble(normalizeNumber(getElementText(positionElement, "calories")));
            String date = getElementText(positionElement, "addedDate");

            CafeMenuPosition position = null;

            switch (type.toUpperCase()) {
                case "DRINK":
                    int volume = Integer.parseInt(getElementText(positionElement, "volume"));
                    boolean alcoholic = Boolean.parseBoolean(getElementText(positionElement, "alcoholic"));
                    position = new Drink(id, name, price, category, calories, volume, alcoholic);
                    break;

                case "MAIN_COURSE":
                    int mass1 = Integer.parseInt(getElementText(positionElement, "mass"));
                    boolean vegetarian = Boolean.parseBoolean(getElementText(positionElement, "vegetarian"));
                    position = new MainCourse(id, name, price, category, calories, mass1, vegetarian);
                    break;

                case "DESSERT":
                    int mass2 = Integer.parseInt(getElementText(positionElement, "mass"));
                    boolean sweet = Boolean.parseBoolean(getElementText(positionElement, "sweet"));
                    position = new Dessert(id, name, price, category, calories, mass2, sweet);
                    break;
            }

            if (position != null) {
                try {
                    SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
                    position.setAddedDate(sdf.parse(date));
                } catch (Exception e) {
                    position.setAddedDate(new Date());
                }
                positions.add(position);
            }
        }

        return positions;
    }

    private static void writeXMLFormat(OutputStream outputStream, List<CafeMenuPosition> positions) throws Exception {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document document = builder.newDocument();

        Element rootElement = document.createElement("cafeMenu");
        document.appendChild(rootElement);

        Element infoElement = document.createElement("menuInfo");
        infoElement.setTextContent("Меню кафе - " + new Date());
        rootElement.appendChild(infoElement);

        for (CafeMenuPosition position : positions) {
            Element positionElement = document.createElement("position");

            String type = "";
            if (position instanceof Drink) type = "DRINK";
            else if (position instanceof MainCourse) type = "MAIN_COURSE";
            else if (position instanceof Dessert) type = "DESSERT";

            positionElement.setAttribute("type", type);

            addChildElement(document, positionElement, "id", String.valueOf(position.getId()));
            addChildElement(document, positionElement, "name", position.getName());
            addChildElement(document, positionElement, "price", String.format("%.2f", position.getPrice()).replace(',', '.'));
            addChildElement(document, positionElement, "category", position.getCategory());
            addChildElement(document, positionElement, "calories", String.format("%.1f", position.getCalories()).replace(',', '.'));

            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
            addChildElement(document, positionElement, "addedDate", sdf.format(position.getAddedDate()));

            if (position instanceof Drink) {
                Drink drink = (Drink) position;
                addChildElement(document, positionElement, "volume", String.valueOf(drink.getVolume()));
                addChildElement(document, positionElement, "alcoholic", String.valueOf(drink.isAlcoholic()));
            } else if (position instanceof MainCourse) {
                MainCourse main = (MainCourse) position;
                addChildElement(document, positionElement, "mass", String.valueOf(main.getMass()));
                addChildElement(document, positionElement, "vegetarian", String.valueOf(main.isVegetarian()));
            } else if (position instanceof Dessert) {
                Dessert dessert = (Dessert) position;
                addChildElement(document, positionElement, "mass", String.valueOf(dessert.getMass()));
                addChildElement(document, positionElement, "sweet", String.valueOf(dessert.isSweet()));
            }

            rootElement.appendChild(positionElement);
        }

        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transformer = transformerFactory.newTransformer();
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");
        transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");

        DOMSource source = new DOMSource(document);
        StreamResult result = new StreamResult(outputStream);
        transformer.transform(source, result);
    }

    private static List<CafeMenuPosition> readJSONFormat(InputStream inputStream) throws Exception {
        List<CafeMenuPosition> positions = new ArrayList<>();

        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        StringBuilder jsonBuilder = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            jsonBuilder.append(line);
        }
        reader.close();

        String jsonString = jsonBuilder.toString();


        int positionsStart = jsonString.indexOf("\"positions\":");
        if (positionsStart == -1) {
            positionsStart = jsonString.indexOf("\"positions\" :");
        }

        if (positionsStart == -1) {
            System.err.println("Не найден массив positions в JSON");
            return positions;
        }

        int arrayStart = jsonString.indexOf('[', positionsStart);
        if (arrayStart == -1) {
            System.err.println("Не найден массив в JSON");
            return positions;
        }

        int braceCount = 0;
        int arrayEnd = findMatchingBracket(jsonString, arrayStart);
        if (arrayEnd == -1) {
            System.err.println("Некорректный JSON массив");
            return positions;
        }

        String arrayContent = jsonString.substring(arrayStart + 1, arrayEnd);
        List<String> jsonObjects = splitJSONObjects(arrayContent);

        for (String jsonObj : jsonObjects) {
            try {
                CafeMenuPosition position = parseJSONObject(jsonObj);
                if (position != null) {
                    positions.add(position);
                }
            } catch (Exception e) {
                System.err.println("Ошибка при парсинге JSON объекта: " + e.getMessage());
            }
        }

        return positions;
    }

    private static CafeMenuPosition parseJSONObject(String jsonStr) throws Exception {
        Map<String, String> fields = new HashMap<>();

        jsonStr = jsonStr.trim();
        if (jsonStr.startsWith("{") && jsonStr.endsWith("}")) {
            jsonStr = jsonStr.substring(1, jsonStr.length() - 1).trim();
        }

        String[] pairs = jsonStr.split(",");
        for (String pair : pairs) {
            pair = pair.trim();
            if (pair.isEmpty()) continue;

            int colonIndex = pair.indexOf(':');
            if (colonIndex == -1) continue;

            String key = pair.substring(0, colonIndex).trim();
            String value = pair.substring(colonIndex + 1).trim();

            key = removeQuotes(key);
            value = removeQuotes(value);

            fields.put(key, value);
        }

        String type = fields.get("type");
        if (type == null) return null;

        int id = Integer.parseInt(fields.get("id"));
        String name = fields.get("name");
        double price = Double.parseDouble(normalizeNumber(fields.get("price")));
        String category = fields.get("category");
        double calories = Double.parseDouble(normalizeNumber(fields.get("calories")));
        String date = fields.get("addedDate");

        CafeMenuPosition position = null;

        switch (type.toUpperCase()) {
            case "DRINK":
                int volume = Integer.parseInt(fields.get("volume"));
                boolean alcoholic = Boolean.parseBoolean(fields.get("alcoholic"));
                position = new Drink(id, name, price, category, calories, volume, alcoholic);
                break;

            case "MAIN_COURSE":
                int mass1 = Integer.parseInt(fields.get("mass"));
                boolean vegetarian = Boolean.parseBoolean(fields.get("vegetarian"));
                position = new MainCourse(id, name, price, category, calories, mass1, vegetarian);
                break;

            case "DESSERT":
                int mass2 = Integer.parseInt(fields.get("mass"));
                boolean sweet = Boolean.parseBoolean(fields.get("sweet"));
                position = new Dessert(id, name, price, category, calories, mass2, sweet);
                break;
        }

        if (position != null) {
            try {
                SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
                position.setAddedDate(sdf.parse(date));
            } catch (Exception e) {
                position.setAddedDate(new Date());
            }
        }

        return position;
    }

    private static void writeJSONFormat(OutputStream outputStream, List<CafeMenuPosition> positions) throws Exception {
        StringBuilder jsonBuilder = new StringBuilder();
        jsonBuilder.append("{\n");
        jsonBuilder.append("  \"menuName\": \"Меню кафе\",\n");
        jsonBuilder.append("  \"lastUpdated\": \"").append(new SimpleDateFormat("dd.MM.yyyy HH:mm:ss").format(new Date())).append("\",\n");
        jsonBuilder.append("  \"totalPositions\": ").append(positions.size()).append(",\n");
        jsonBuilder.append("  \"positions\": [\n");

        for (int i = 0; i < positions.size(); i++) {
            CafeMenuPosition position = positions.get(i);
            jsonBuilder.append("    {\n");

            String type = "";
            if (position instanceof Drink) type = "DRINK";
            else if (position instanceof MainCourse) type = "MAIN_COURSE";
            else if (position instanceof Dessert) type = "DESSERT";

            jsonBuilder.append("      \"type\": \"").append(type).append("\",\n");
            jsonBuilder.append("      \"id\": ").append(position.getId()).append(",\n");
            jsonBuilder.append("      \"name\": \"").append(escapeJSON(position.getName())).append("\",\n");
            jsonBuilder.append("      \"price\": ").append(position.getPrice()).append(",\n");
            jsonBuilder.append("      \"category\": \"").append(escapeJSON(position.getCategory())).append("\",\n");
            jsonBuilder.append("      \"calories\": ").append(position.getCalories()).append(",\n");
            jsonBuilder.append("      \"addedDate\": \"").append(new SimpleDateFormat("dd.MM.yyyy").format(position.getAddedDate())).append("\"");

            if (position instanceof Drink) {
                Drink drink = (Drink) position;
                jsonBuilder.append(",\n");
                jsonBuilder.append("      \"volume\": ").append(drink.getVolume()).append(",\n");
                jsonBuilder.append("      \"alcoholic\": ").append(drink.isAlcoholic());
            } else if (position instanceof MainCourse) {
                MainCourse main = (MainCourse) position;
                jsonBuilder.append(",\n");
                jsonBuilder.append("      \"mass\": ").append(main.getMass()).append(",\n");
                jsonBuilder.append("      \"vegetarian\": ").append(main.isVegetarian());
            } else if (position instanceof Dessert) {
                Dessert dessert = (Dessert) position;
                jsonBuilder.append(",\n");
                jsonBuilder.append("      \"mass\": ").append(dessert.getMass()).append(",\n");
                jsonBuilder.append("      \"sweet\": ").append(dessert.isSweet());
            }

            jsonBuilder.append("\n    }");

            if (i < positions.size() - 1) {
                jsonBuilder.append(",");
            }
            jsonBuilder.append("\n");
        }

        jsonBuilder.append("  ]\n");
        jsonBuilder.append("}");

        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));
        writer.write(jsonBuilder.toString());
        writer.close();
    }

    private static String decompressFile(String filename, Compression compression) throws IOException {
        String outputFilename = filename.substring(0, filename.lastIndexOf('.'));

        if (compression == Compression.ZIP) {
            try (ZipInputStream zis = new ZipInputStream(new FileInputStream(filename))) {
                ZipEntry entry = zis.getNextEntry();
                if (entry != null) {
                    try (FileOutputStream fos = new FileOutputStream(outputFilename)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = zis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
                zis.closeEntry();
            }
        } else if (compression == Compression.JAR) {
            try (JarInputStream jis = new JarInputStream(new FileInputStream(filename))) {
                JarEntry entry = jis.getNextJarEntry();
                if (entry != null) {
                    try (FileOutputStream fos = new FileOutputStream(outputFilename)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = jis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
                jis.closeEntry();
            }
        }

        return outputFilename;
    }

    private static void compressFile(String sourceFile, String destFile, Compression compression) throws IOException {
        if (compression == Compression.ZIP) {
            try (ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(destFile))) {
                ZipEntry entry = new ZipEntry(new File(sourceFile).getName());
                zos.putNextEntry(entry);

                try (FileInputStream fis = new FileInputStream(sourceFile)) {
                    byte[] buffer = new byte[1024];
                    int len;
                    while ((len = fis.read(buffer)) > 0) {
                        zos.write(buffer, 0, len);
                    }
                }

                zos.closeEntry();
            }
        } else if (compression == Compression.JAR) {
            try (JarOutputStream jos = new JarOutputStream(new FileOutputStream(destFile))) {
                JarEntry entry = new JarEntry(new File(sourceFile).getName());
                jos.putNextEntry(entry);

                try (FileInputStream fis = new FileInputStream(sourceFile)) {
                    byte[] buffer = new byte[1024];
                    int len;
                    while ((len = fis.read(buffer)) > 0) {
                        jos.write(buffer, 0, len);
                    }
                }

                jos.closeEntry();
            }
        }
    }

    private static byte[] encryptData(byte[] data, Encryption encryption) throws Exception {
        if (encryption == Encryption.AES) {
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            SecretKeySpec key = new SecretKeySpec(ENCRYPTION_KEY.getBytes(), "AES");
            cipher.init(Cipher.ENCRYPT_MODE, key);
            return cipher.doFinal(data);
        }
        return data;
    }

    private static byte[] decryptData(byte[] encryptedData, Encryption encryption) throws Exception {
        if (encryption == Encryption.AES) {
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            SecretKeySpec key = new SecretKeySpec(ENCRYPTION_KEY.getBytes(), "AES");
            cipher.init(Cipher.DECRYPT_MODE, key);
            return cipher.doFinal(encryptedData);
        }
        return encryptedData;
    }

    private static String getElementText(Element parent, String tagName) {
        NodeList nodes = parent.getElementsByTagName(tagName);
        if (nodes.getLength() > 0) {
            return nodes.item(0).getTextContent();
        }
        return "";
    }

    private static void addChildElement(Document doc, Element parent, String tagName, String textContent) {
        Element child = doc.createElement(tagName);
        child.setTextContent(textContent);
        parent.appendChild(child);
    }

    private static String normalizeNumber(String numberStr) {
        if (numberStr == null) return "0";
        return numberStr.replace(',', '.');
    }

    private static byte[] readFileToBytes(String filename) throws IOException {
        File file = new File(filename);
        byte[] data = new byte[(int) file.length()];
        try (FileInputStream fis = new FileInputStream(file)) {
            fis.read(data);
        }
        return data;
    }

    private static void writeBytesToFile(String filename, byte[] data) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(filename)) {
            fos.write(data);
        }
    }

    private static int findMatchingBracket(String str, int startIndex) {
        int count = 0;
        boolean inQuotes = false;
        char quoteChar = '\0';

        for (int i = startIndex; i < str.length(); i++) {
            char c = str.charAt(i);

            if (inQuotes) {
                if (c == quoteChar && str.charAt(i-1) != '\\') {
                    inQuotes = false;
                }
            } else {
                if (c == '"' || c == '\'') {
                    inQuotes = true;
                    quoteChar = c;
                } else if (c == '[') {
                    count++;
                } else if (c == ']') {
                    count--;
                    if (count == 0) {
                        return i;
                    }
                }
            }
        }
        return -1;
    }

    private static List<String> splitJSONObjects(String arrayContent) {
        List<String> objects = new ArrayList<>();
        StringBuilder current = new StringBuilder();
        int braceCount = 0;
        boolean inQuotes = false;
        char quoteChar = '\0';

        for (int i = 0; i < arrayContent.length(); i++) {
            char c = arrayContent.charAt(i);

            if (inQuotes) {
                current.append(c);
                if (c == quoteChar && (i == 0 || arrayContent.charAt(i-1) != '\\')) {
                    inQuotes = false;
                }
            } else {
                if (c == '{') {
                    braceCount++;
                    current.append(c);
                } else if (c == '}') {
                    braceCount--;
                    current.append(c);
                    if (braceCount == 0) {
                        objects.add(current.toString());
                        current = new StringBuilder();
                        while (i + 1 < arrayContent.length() &&
                                (arrayContent.charAt(i+1) == ',' ||
                                        Character.isWhitespace(arrayContent.charAt(i+1)))) {
                            i++;
                        }
                    }
                } else if (c == '"' || c == '\'') {
                    inQuotes = true;
                    quoteChar = c;
                    current.append(c);
                } else if (braceCount > 0) {
                    current.append(c);
                }
            }
        }

        return objects;
    }

    private static String removeQuotes(String str) {
        if (str == null || str.isEmpty()) return str;
        str = str.trim();
        if ((str.startsWith("\"") && str.endsWith("\"")) ||
                (str.startsWith("'") && str.endsWith("'"))) {
            return str.substring(1, str.length() - 1);
        }
        return str;
    }

    private static String escapeJSON(String str) {
        if (str == null) return "";
        return str.replace("\\", "\\\\")
                .replace("\"", "\\\"")
                .replace("\n", "\\n")
                .replace("\r", "\\r")
                .replace("\t", "\\t");
    }

    public static List<CafeMenuPosition> readFromFile(String filename) {
        return readFromFile(filename, FileFormat.TXT, Compression.NONE, Encryption.NONE);
    }

    public static void writeToFile(String filename, List<CafeMenuPosition> positions) {
        writeToFile(filename, positions, FileFormat.TXT, Compression.NONE, Encryption.NONE);
    }

    public static boolean validatePosition(CafeMenuPosition position) {
        if (position.getId() <= 0) {
            // System.err.println("Ошибка: ID должен быть положительным");
            return false;
        }

        if (position.getPrice() < 0) {
            // System.err.println("Ошибка: цена не может быть отрицательной");
            return false;
        }

        if (position.getCalories() < 0) {
            // System.err.println("Ошибка: калории не могут быть отрицательными");
            return false;
        }

        if (position.getName() == null || position.getName().trim().isEmpty()) {
            // System.err.println("Ошибка: название не может быть пустым");
            return false;
        }

        return true;
    }
}