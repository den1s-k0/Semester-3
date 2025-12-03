package file_manager;

import cafe_menu.*;
import java.io.*;
import java.util.*;

public class FileManager {

    public static List<CafeMenuPosition> readFromFile(String filename) {
        List<CafeMenuPosition> positions = new ArrayList<>();
        File file = new File(filename);

        if (!file.exists()) {
            System.out.println("Файл не найден: " + filename);
            return positions;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            int lineNumber = 0;

            while ((line = reader.readLine()) != null) {
                lineNumber++;
                line = line.trim();

                if (line.isEmpty() || line.startsWith("#")) {
                    continue;
                }

                try {
                    CafeMenuPosition position = parsePosition(line);
                    positions.add(position);
                } catch (Exception e) {
                    System.err.println("Ошибка в строке " + lineNumber + ": " + e.getMessage());
                    System.err.println("Содержимое строки: " + line);
                }
            }

            System.out.println("Загружено " + positions.size() + " позиций из файла " + filename);

        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла: " + e.getMessage());
        }

        return positions;
    }

    private static String normalizeNumber(String numberStr) {
        return numberStr.replace(',', '.');
    }

    private static CafeMenuPosition parsePosition(String line) {
        String[] parts = line.split(";");

        for (int i = 0; i < parts.length; i++) {
            parts[i] = normalizeNumber(parts[i]);
        }

        String type = parts[0].toUpperCase();

        switch (type) {
            case "DRINK":
                return Drink.fromFileString(line);
            case "MAIN_COURSE":
                return MainCourse.fromFileString(line);
            case "DESSERT":
                return Dessert.fromFileString(line);
            default:
                throw new IllegalArgumentException("Неизвестный тип позиции: " + type);
        }
    }

    public static void writeToFile(String filename, List<CafeMenuPosition> positions) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            writer.write("# Файл меню кафе\n");
            writer.write("# Формат: TYPE;ID;NAME;PRICE;CATEGORY;CALORIES;DATE;PARAM1;PARAM2\n");
            writer.write("# Типы: DRINK, MAIN_COURSE, DESSERT\n\n");

            for (CafeMenuPosition position : positions) {
                writer.write(position.toFileString());
                writer.newLine();
            }

            System.out.println("Сохранено " + positions.size() + " позиций в файл " + filename);

        } catch (IOException e) {
            System.err.println("Ошибка при записи в файл: " + e.getMessage());
        }
    }

    public static boolean validatePosition(CafeMenuPosition position) {
        if (position.getId() <= 0) {
            System.err.println("Ошибка: ID должен быть положительным");
            return false;
        }

        if (position.getPrice() < 0) {
            System.err.println("Ошибка: цена не может быть отрицательной");
            return false;
        }

        if (position.getCalories() < 0) {
            System.err.println("Ошибка: калории не могут быть отрицательными");
            return false;
        }

        if (position.getName() == null || position.getName().trim().isEmpty()) {
            System.err.println("Ошибка: название не может быть пустым");
            return false;
        }

        return true;
    }
}