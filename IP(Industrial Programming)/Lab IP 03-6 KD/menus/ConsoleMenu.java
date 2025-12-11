package menus;

import cafe_menu.*;
import file_manager.FileManager;
import rolls.ListRoll;
import rolls.MapRoll;
import rolls.Rolls;
import java.util.Date;

import java.util.*;

public class ConsoleMenu {
    private Rolls<CafeMenuPosition> currentRoll;
    private Scanner scanner;

    public ConsoleMenu() {
        this.currentRoll = new ListRoll<>();
        this.scanner = new Scanner(System.in);
    }

    public void start() {
        System.out.println("=== МЕНЮ ===");

        while (true) {
            printMenu();
            String choice = scanner.nextLine().trim();

            switch (choice) {
                case "1" -> loadFromFile();
                case "2" -> saveToFile();
                case "3" -> addPosition();
                case "4" -> showAll();
                case "5" -> editPosition();
                case "6" -> deletePosition();
                case "7" -> findPosition();
                case "8" -> switchStorage();
                case "9" -> showStats();
                case "10" -> sortPositions();
                case "0" -> {
                    System.out.println("Выход...");
                    return;
                }
                default -> System.out.println("Неверный выбор. Попробуйте снова.");
            }
        }
    }

    private void printMenu() {
        System.out.println("\nВыберите действие:");
        System.out.println("1. Загрузить из файла");
        System.out.println("2. Сохранить в файл");
        System.out.println("3. Добавить позицию");
        System.out.println("4. Показать все");
        System.out.println("5. Редактировать позицию");
        System.out.println("6. Удалить позицию");
        System.out.println("7. Найти позицию");
        System.out.println("8. Переключить хранилище");
        System.out.println("9. Статистика");
        System.out.println("10. Сортировка");
        System.out.println("0. Выход");
        System.out.print("> ");
    }

    private void loadFromFile() {
        System.out.println("\n=== ЗАГРУЗКА ИЗ ФАЙЛА ===");

        System.out.println("Выберите формат файла:");
        System.out.println("1. TXT");
        System.out.println("2. XML");
        System.out.println("3. JSON");
        System.out.print("> ");

        String formatChoice = scanner.nextLine().trim();
        FileManager.FileFormat format = FileManager.FileFormat.TXT;

        switch (formatChoice) {
            case "1": format = FileManager.FileFormat.TXT; break;
            case "2": format = FileManager.FileFormat.XML; break;
            case "3": format = FileManager.FileFormat.JSON; break;
            default:
                System.out.println("Неверный выбор. Используется TXT.");
                format = FileManager.FileFormat.TXT;
        }

        System.out.println("\nФайл архивирован?");
        System.out.println("1. Нет");
        System.out.println("2. ZIP");
        System.out.println("3. JAR");
        System.out.print("> ");

        String compressionChoice = scanner.nextLine().trim();
        FileManager.Compression compression = FileManager.Compression.NONE;

        switch (compressionChoice) {
            case "1": compression = FileManager.Compression.NONE; break;
            case "2": compression = FileManager.Compression.ZIP; break;
            case "3": compression = FileManager.Compression.JAR; break;
            default:
                System.out.println("Неверный выбор. Без архивации.");
                compression = FileManager.Compression.NONE;
        }

        System.out.println("\nФайл зашифрован?");
        System.out.println("1. Нет");
        System.out.println("2. AES");
        System.out.print("> ");

        String encryptionChoice = scanner.nextLine().trim();
        FileManager.Encryption encryption = FileManager.Encryption.NONE;

        switch (encryptionChoice) {
            case "1": encryption = FileManager.Encryption.NONE; break;
            case "2": encryption = FileManager.Encryption.AES; break;
            default:
                System.out.println("Неверный выбор. Без шифрования.");
                encryption = FileManager.Encryption.NONE;
        }

        System.out.print("\nВведите имя файла: ");
        String filename = scanner.nextLine().trim();

        if (filename.isEmpty()) {
            String extension = "";
            switch (format) {
                case TXT: extension = ".txt"; break;
                case XML: extension = ".xml"; break;
                case JSON: extension = ".json"; break;
            }

            if (compression != FileManager.Compression.NONE) {
                extension = compression == FileManager.Compression.ZIP ? ".zip" : ".jar";
            }

            filename = "menu" + extension;
            System.out.println("Используется имя по умолчанию: " + filename);
        } else {
            String extension = "";
            if (compression != FileManager.Compression.NONE) {
                extension = compression == FileManager.Compression.ZIP ? ".zip" : ".jar";
            } else {
                switch (format) {
                    case TXT: extension = ".txt"; break;
                    case XML: extension = ".xml"; break;
                    case JSON: extension = ".json"; break;
                }
            }

            boolean hasCorrectExtension = false;
            if (compression != FileManager.Compression.NONE) {
                hasCorrectExtension = filename.toLowerCase().endsWith(extension);
            } else {
                hasCorrectExtension =
                        (format == FileManager.FileFormat.TXT && filename.toLowerCase().endsWith(".txt")) ||
                                (format == FileManager.FileFormat.XML && filename.toLowerCase().endsWith(".xml")) ||
                                (format == FileManager.FileFormat.JSON && filename.toLowerCase().endsWith(".json"));
            }

            if (!hasCorrectExtension) {
                filename = removeExtensions(filename);
                filename += extension;
            }
        }
        List<CafeMenuPosition> positions = FileManager.readFromFile(
                filename, format, compression, encryption
        );

        if (!positions.isEmpty()) {
            System.out.println("\nЧто сделать с текущими данными?");
            System.out.println("1. Очистить и загрузить новые");
            System.out.println("2. Добавить к существующим");
            System.out.println("3. Отменить загрузку");
            System.out.print("> ");

            String action = scanner.nextLine().trim();

            switch (action) {
                case "1":
                    currentRoll.Clear();
                    for (CafeMenuPosition position : positions) {
                        currentRoll.AddElement(position);
                    }
                    System.out.println("Данные загружены (старые удалены)");
                    break;
                case "2":
                    for (CafeMenuPosition position : positions) {
                        currentRoll.AddElement(position);
                    }
                    System.out.println("Данные добавлены к существующим");
                    break;
                case "3":
                    System.out.println("Загрузка отменена");
                    break;
                default:
                    System.out.println("Неверный выбор. Загрузка отменена.");
            }
        }
    }

    private void saveToFile() {
        System.out.println("\n=== СОХРАНЕНИЕ В ФАЙЛ ===");

        if (currentRoll.GetSize() == 0) {
            System.out.println("Нет данных для сохранения!");
            return;
        }

        System.out.println("Выберите формат файла:");
        System.out.println("1. TXT");
        System.out.println("2. XML");
        System.out.println("3. JSON");
        System.out.print("> ");

        String formatChoice = scanner.nextLine().trim();
        FileManager.FileFormat format = FileManager.FileFormat.TXT;

        switch (formatChoice) {
            case "1": format = FileManager.FileFormat.TXT; break;
            case "2": format = FileManager.FileFormat.XML; break;
            case "3": format = FileManager.FileFormat.JSON; break;
            default:
                System.out.println("Неверный выбор. Используется TXT.");
                format = FileManager.FileFormat.TXT;
        }

        System.out.println("\nАрхивировать файл?");
        System.out.println("1. Нет");
        System.out.println("2. ZIP");
        System.out.println("3. JAR");
        System.out.print("> ");

        String compressionChoice = scanner.nextLine().trim();
        FileManager.Compression compression = FileManager.Compression.NONE;

        switch (compressionChoice) {
            case "1": compression = FileManager.Compression.NONE; break;
            case "2": compression = FileManager.Compression.ZIP; break;
            case "3": compression = FileManager.Compression.JAR; break;
            default:
                System.out.println("Неверный выбор. Без архивации.");
                compression = FileManager.Compression.NONE;
        }

        System.out.println("\nЗашифровать файл?");
        System.out.println("1. Нет");
        System.out.println("2. AES");
        System.out.print("> ");

        String encryptionChoice = scanner.nextLine().trim();
        FileManager.Encryption encryption = FileManager.Encryption.NONE;

        switch (encryptionChoice) {
            case "1": encryption = FileManager.Encryption.NONE; break;
            case "2": encryption = FileManager.Encryption.AES; break;
            default:
                System.out.println("Неверный выбор. Без шифрования.");
                encryption = FileManager.Encryption.NONE;
        }

        System.out.print("\nВведите имя файла: ");
        String filename = scanner.nextLine().trim();

        if (filename.isEmpty()) {
            String extension = "";
            switch (format) {
                case TXT: extension = ".txt"; break;
                case XML: extension = ".xml"; break;
                case JSON: extension = ".json"; break;
            }

            if (compression != FileManager.Compression.NONE) {
                extension = compression == FileManager.Compression.ZIP ? ".zip" : ".jar";
            }

            filename = "menu_" + new java.text.SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date()) + extension;
            System.out.println("Используется имя: " + filename);
        } else {
            String extension = "";
            if (compression != FileManager.Compression.NONE) {
                extension = compression == FileManager.Compression.ZIP ? ".zip" : ".jar";
            } else {
                switch (format) {
                    case TXT: extension = ".txt"; break;
                    case XML: extension = ".xml"; break;
                    case JSON: extension = ".json"; break;
                }
            }

            boolean hasCorrectExtension = false;
            if (compression != FileManager.Compression.NONE) {
                hasCorrectExtension = filename.toLowerCase().endsWith(extension);
            } else {
                hasCorrectExtension =
                        (format == FileManager.FileFormat.TXT && filename.toLowerCase().endsWith(".txt")) ||
                                (format == FileManager.FileFormat.XML && filename.toLowerCase().endsWith(".xml")) ||
                                (format == FileManager.FileFormat.JSON && filename.toLowerCase().endsWith(".json"));
            }

            if (!hasCorrectExtension) {
                filename = removeExtensions(filename);
                filename += extension;
            }
        }

        System.out.println("\nПараметры сохранения:");
        System.out.println("Формат: " + format);
        System.out.println("Архивация: " + compression);
        System.out.println("Шифрование: " + encryption);
        System.out.println("Файл: " + filename);
        System.out.println("Количество позиций: " + currentRoll.GetSize());

        System.out.print("\nПодтвердить сохранение? (да/нет): ");
        String confirm = scanner.nextLine().trim();

        if (confirm.equalsIgnoreCase("да")) {
            FileManager.writeToFile(
                    filename,
                    currentRoll.GetAllElements(),
                    format,
                    compression,
                    encryption
            );
            System.out.println("Данные сохранены!");
        } else {
            System.out.println("Сохранение отменено.");
        }
    }

    private String removeExtensions(String filename) {
        String[] extensions = {".txt", ".xml", ".json", ".zip", ".jar"};
        String lowerFilename = filename.toLowerCase();

        for (String ext : extensions) {
            if (lowerFilename.endsWith(ext)) {
                return filename.substring(0, filename.length() - ext.length());
            }
        }
        return filename;
    }

    private void addPosition() {
        System.out.println("\nВыберите категорию позиции:");
        System.out.println("1. Напиток");
        System.out.println("2. Основное блюдо");
        System.out.println("3. Десерт");
        System.out.print("> ");

        String typeChoice = scanner.nextLine().trim();
        CafeMenuPosition position = null;

        try {
            int id = readInt("ID: ");

            if (findById(id) != null) {
                System.out.println("Ошибка: позиция с таким ID уже существует");
                return;
            }

            String name = readString("Название: ");
            double price = readDouble("Цена: ");

            String category = getCategoryByType(typeChoice);

            double calories = readDouble("Калории: ");

            switch (typeChoice) {
                case "1":
                    int volume = readInt("Объем (мл): ");
                    boolean alcoholic = readBoolean("Алкогольный (да/нет): ");
                    position = new Drink(id, name, price, category, calories, volume, alcoholic);
                    break;

                case "2":
                    int mass1 = readInt("Масса (г): ");
                    boolean vegetarian = readBoolean("Вегетарианский (да/нет): ");
                    position = new MainCourse(id, name, price, category, calories, mass1, vegetarian);
                    break;

                case "3":
                    int mass2 = readInt("Масса (г): ");
                    boolean sweet = readBoolean("Сладкий (да/нет): ");
                    position = new Dessert(id, name, price, category, calories, mass2, sweet);
                    break;

                default:
                    System.out.println("Неверный тип позиции");
                    return;
            }

            if (FileManager.validatePosition(position)) {
                currentRoll.AddElement(position);
                System.out.println("Позиция добавлена успешно!");
            }

        } catch (Exception e) {
            System.out.println("Ошибка: " + e.getMessage());
        }
    }

    private String getCategoryByType(String typeChoice) {
        switch (typeChoice) {
            case "1": return "Напитки";
            case "2": return "Основные блюда";
            case "3": return "Десерты";
            default: return "Другое";
        }
    }

    private void showAll() {
        System.out.println("\n=== ВСЕ ПОЗИЦИИ ===");
        if (currentRoll.GetSize() == 0) {
            System.out.println("Список пуст");
        } else {
            currentRoll.PrintList();
        }
    }

    private void editPosition() {
        int id = readInt("Введите ID позиции для редактирования: ");
        CafeMenuPosition oldPosition = findById(id);

        if (oldPosition == null) {
            System.out.println("Позиция не найдена");
            return;
        }

        System.out.println("Найдена позиция: " + oldPosition.getName());
        System.out.println("Введите новые данные (оставьте пустым для сохранения старого значения):");

        try {
            String name = readStringWithDefault("Название [" + oldPosition.getName() + "]: ", oldPosition.getName());
            double price = readDoubleWithDefault("Цена [" + oldPosition.getPrice() + "]: ", oldPosition.getPrice());

            // Для категории предлагаем выбрать из вариантов
            String currentCategory = oldPosition.getCategory();
            String category = editCategory(currentCategory);

            double calories = readDoubleWithDefault("Калории [" + oldPosition.getCalories() + "]: ", oldPosition.getCalories());

            CafeMenuPosition newPosition = null;

            if (oldPosition instanceof Drink) {
                Drink drink = (Drink) oldPosition;
                int volume = readIntWithDefault("Объем [" + drink.getVolume() + "]: ", drink.getVolume());
                boolean alcoholic = readBooleanWithDefault("Алкогольный [" + drink.isAlcoholic() + "]: ", drink.isAlcoholic());
                newPosition = new Drink(id, name, price, category, calories, volume, alcoholic);

            } else if (oldPosition instanceof MainCourse) {
                MainCourse main = (MainCourse) oldPosition;
                int mass = readIntWithDefault("Масса [" + main.getMass() + "]: ", main.getMass());
                boolean vegetarian = readBooleanWithDefault("Вегетарианский [" + main.isVegetarian() + "]: ", main.isVegetarian());
                newPosition = new MainCourse(id, name, price, category, calories, mass, vegetarian);

            } else if (oldPosition instanceof Dessert) {
                Dessert dessert = (Dessert) oldPosition;
                int mass = readIntWithDefault("Масса [" + dessert.getMass() + "]: ", dessert.getMass());
                boolean sweet = readBooleanWithDefault("Сладкий [" + dessert.isSweet() + "]: ", dessert.isSweet());
                newPosition = new Dessert(id, name, price, category, calories, mass, sweet);
            }

            if (newPosition != null && FileManager.validatePosition(newPosition)) {
                currentRoll.ReplaceElement(newPosition);
                System.out.println("Позиция обновлена успешно!");
            }

        } catch (Exception e) {
            System.out.println("Ошибка: " + e.getMessage());
        }
    }

    private String editCategory(String currentCategory) {
        System.out.println("\nТекущая категория: " + currentCategory);
        System.out.println("Выберите новую категорию:");
        System.out.println("1. Напитки");
        System.out.println("2. Основные блюда");
        System.out.println("3. Десерты");
        System.out.println("4. Оставить текущую: " + currentCategory);
        System.out.print("> ");

        String choice = scanner.nextLine().trim();
        switch (choice) {
            case "1": return "Напитки";
            case "2": return "Основные блюда";
            case "3": return "Десерты";
            case "4": return currentCategory;
            default:
                System.out.print("Введите свою категорию: ");
                String customCategory = scanner.nextLine().trim();
                return customCategory.isEmpty() ? currentCategory : customCategory;
        }
    }

    private void deletePosition() {
        int id = readInt("Введите ID позиции для удаления: ");
        CafeMenuPosition position = findById(id);

        if (position == null) {
            System.out.println("Позиция не найдена");
            return;
        }

        System.out.println("Найдена позиция: " + position.getName());
        String confirm = readString("Удалить? (да/нет): ");

        if (confirm.equalsIgnoreCase("да")) {
            if (currentRoll.DeleteElement(position)) {
                System.out.println("Позиция удалена");
            } else {
                System.out.println("Ошибка при удалении");
            }
        }
    }

    private void findPosition() {
        System.out.println("\nПоиск по:");
        System.out.println("1. ID");
        System.out.println("2. Названию");
        System.out.println("3. Категории");
        System.out.println("4. Типу (напиток/блюдо/десерт)");
        System.out.print("> ");

        String choice = scanner.nextLine().trim();
        List<CafeMenuPosition> all = currentRoll.GetAllElements();
        List<CafeMenuPosition> results = new ArrayList<>();

        switch (choice) {
            case "1":
                int id = readInt("Введите ID: ");
                for (CafeMenuPosition p : all) {
                    if (p.getId() == id) {
                        results.add(p);
                    }
                }
                break;

            case "2":
                String name = readString("Введите название (частично): ");
                for (CafeMenuPosition p : all) {
                    if (p.getName().toLowerCase().contains(name.toLowerCase())) {
                        results.add(p);
                    }
                }
                break;

            case "3":
                System.out.println("Доступные категории:");
                Set<String> categories = new HashSet<>();
                for (CafeMenuPosition p : all) {
                    categories.add(p.getCategory());
                }
                System.out.println(String.join(", ", categories));

                String category = readString("Введите категорию: ");
                for (CafeMenuPosition p : all) {
                    if (p.getCategory().equalsIgnoreCase(category)) {
                        results.add(p);
                    }
                }
                break;

            case "4":
                System.out.println("Выберите тип:");
                System.out.println("1. Напитки");
                System.out.println("2. Основные блюда");
                System.out.println("3. Десерты");
                System.out.print("> ");

                String typeChoice = scanner.nextLine().trim();
                for (CafeMenuPosition p : all) {
                    if (typeChoice.equals("1") && p instanceof Drink) {
                        results.add(p);
                    } else if (typeChoice.equals("2") && p instanceof MainCourse) {
                        results.add(p);
                    } else if (typeChoice.equals("3") && p instanceof Dessert) {
                        results.add(p);
                    }
                }
                break;

            default:
                System.out.println("Неверный выбор");
                return;
        }

        if (results.isEmpty()) {
            System.out.println("Ничего не найдено");
        } else {
            System.out.println("\nНайдено " + results.size() + " позиций:");
            for (int i = 0; i < results.size(); i++) {
                System.out.println((i + 1) + ". " + results.get(i));
            }
        }
    }

    private void switchStorage() {
        System.out.println("\nТекущее хранилище: " +
                (currentRoll instanceof ListRoll ? "List (список)" : "Map (словарь)"));
        System.out.println("Переключить на:");
        System.out.println("1. List (быстрый доступ по индексу)");
        System.out.println("2. Map (быстрый поиск по ID)");
        System.out.print("> ");

        String choice = scanner.nextLine().trim();
        List<CafeMenuPosition> all = currentRoll.GetAllElements();

        if (choice.equals("1") && !(currentRoll instanceof ListRoll)) {
            currentRoll = new ListRoll<>();
            System.out.println("Переключено на List");
        } else if (choice.equals("2") && !(currentRoll instanceof MapRoll)) {
            currentRoll = new MapRoll<>();
            System.out.println("Переключено на Map");
        } else {
            System.out.println("Хранилище не изменено");
            return;
        }

        for (CafeMenuPosition p : all) {
            currentRoll.AddElement(p);
        }
        System.out.println("Данные перенесены");
    }

    private void showStats() {
        List<CafeMenuPosition> all = currentRoll.GetAllElements();
        System.out.println("\n=== СТАТИСТИКА ===");
        System.out.println("Всего позиций: " + all.size());

        if (!all.isEmpty()) {
            int drinks = 0, mains = 0, desserts = 0;
            double totalPrice = 0;
            double minPrice = Double.MAX_VALUE;
            double maxPrice = Double.MIN_VALUE;
            Map<String, Integer> categoryCount = new HashMap<>();

            for (CafeMenuPosition p : all) {
                double price = p.getPrice();
                totalPrice += price;
                if (price < minPrice) minPrice = price;
                if (price > maxPrice) maxPrice = price;

                // Считаем по типам
                if (p instanceof Drink) drinks++;
                else if (p instanceof MainCourse) mains++;
                else if (p instanceof Dessert) desserts++;

                // Считаем по категориям
                String category = p.getCategory();
                categoryCount.put(category, categoryCount.getOrDefault(category, 0) + 1);
            }

            System.out.println("\nПо типам:");
            System.out.println("Напитки: " + drinks);
            System.out.println("Основные блюда: " + mains);
            System.out.println("Десерты: " + desserts);

            System.out.println("\nПо категориям:");
            for (Map.Entry<String, Integer> entry : categoryCount.entrySet()) {
                System.out.println(entry.getKey() + ": " + entry.getValue());
            }

            System.out.println("\nЦены:");
            System.out.println("Средняя цена: " + String.format("%.2f руб.", totalPrice / all.size()));
            System.out.println("Минимальная цена: " + String.format("%.2f руб.", minPrice));
            System.out.println("Максимальная цена: " + String.format("%.2f руб.", maxPrice));
            System.out.println("Общая стоимость всех позиций: " + String.format("%.2f руб.", totalPrice));
        }
    }

    private void sortPositions() {
        System.out.println("\n=== СОРТИРОВКА ПОЗИЦИЙ ===");

        if (currentRoll.GetSize() == 0) {
            System.out.println("Список пуст");
            return;
        }

        System.out.println("Выберите поле для сортировки:");
        System.out.println("1. По ID");
        System.out.println("2. По названию");
        System.out.println("3. По цене (возрастание)");
        System.out.println("4. По цене (убывание)");
        System.out.println("5. По калориям");
        System.out.println("6. По дате добавления");
        System.out.print("> ");

        String choice = scanner.nextLine().trim();
        Comparator<CafeMenuPosition> comparator = null;

        switch (choice) {
            case "1":
                comparator = Comparator.comparingInt(CafeMenuPosition::getId);
                System.out.println("Сортировка по ID");
                break;
            case "2":
                comparator = Comparator.comparing(CafeMenuPosition::getName, String.CASE_INSENSITIVE_ORDER);
                System.out.println("Сортировка по названию");
                break;
            case "3":
                comparator = Comparator.comparingDouble(CafeMenuPosition::getPrice);
                System.out.println("Сортировка по цене (возрастание)");
                break;
            case "4":
                comparator = Comparator.comparingDouble(CafeMenuPosition::getPrice).reversed();
                System.out.println("Сортировка по цене (убывание)");
                break;
            case "5":
                comparator = Comparator.comparingDouble(CafeMenuPosition::getCalories);
                System.out.println("Сортировка по калориям");
                break;
            case "6":
                comparator = Comparator.comparing(CafeMenuPosition::getAddedDate);
                System.out.println("Сортировка по дате добавления");
                break;
            default:
                System.out.println("Неверный выбор");
                return;
        }

        currentRoll.sort(comparator);
        System.out.println("Сортировка выполнена!");
    }

    private CafeMenuPosition findById(int id) {
        List<CafeMenuPosition> all = currentRoll.GetAllElements();
        for (CafeMenuPosition p : all) {
            if (p.getId() == id) {
                return p;
            }
        }
        return null;
    }

    // ... вспомогательные методы для ввода остаются без изменений ...
    private int readInt(String prompt) {
        while (true) {
            System.out.print(prompt);
            try {
                return Integer.parseInt(scanner.nextLine().trim());
            } catch (NumberFormatException e) {
                System.out.println("Ошибка: введите число");
            }
        }
    }

    private double readDouble(String prompt) {
        while (true) {
            System.out.print(prompt);
            try {
                return Double.parseDouble((scanner.nextLine().trim()).replace(',', '.'));
            } catch (NumberFormatException e) {
                System.out.println("Ошибка: введите число");
            }
        }
    }

    private String readString(String prompt) {
        System.out.print(prompt);
        return scanner.nextLine().trim();
    }

    private boolean readBoolean(String prompt) {
        while (true) {
            System.out.print(prompt);
            String input = scanner.nextLine().trim().toLowerCase();
            if (input.equals("да") || input.equals("yes") || input.equals("true") || input.equals("1")) {
                return true;
            } else if (input.equals("нет") || input.equals("no") || input.equals("false") || input.equals("0")) {
                return false;
            }
            System.out.println("Ошибка: введите 'да' или 'нет'");
        }
    }

    private String readStringWithDefault(String prompt, String defaultValue) {
        System.out.print(prompt);
        String input = scanner.nextLine().trim();
        return input.isEmpty() ? defaultValue : input;
    }

    private int readIntWithDefault(String prompt, int defaultValue) {
        System.out.print(prompt);
        String input = scanner.nextLine().trim();
        if (input.isEmpty()) return defaultValue;
        try {
            return Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.out.println("Ошибка: используется значение по умолчанию");
            return defaultValue;
        }
    }

    private double readDoubleWithDefault(String prompt, double defaultValue) {
        System.out.print(prompt);
        String input = scanner.nextLine().trim();
        if (input.isEmpty()) return defaultValue;

        input = input.replace(',', '.');

        try {
            return Double.parseDouble(input);
        } catch (NumberFormatException e) {
            System.out.println("Ошибка: используется значение по умолчанию");
            return defaultValue;
        }
    }

    private boolean readBooleanWithDefault(String prompt, boolean defaultValue) {
        System.out.print(prompt);
        String input = scanner.nextLine().trim().toLowerCase();
        if (input.isEmpty()) return defaultValue;

        if (input.equals("да") || input.equals("yes") || input.equals("true") || input.equals("1")) {
            return true;
        } else if (input.equals("нет") || input.equals("no") || input.equals("false") || input.equals("0")) {
            return false;
        } else {
            System.out.println("Ошибка: используется значение по умолчанию");
            return defaultValue;
        }
    }
}