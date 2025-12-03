package menus;

import cafe_menu.*;
import file_manager.FileManager;
import rolls.ListRoll;
import rolls.MapRoll;
import rolls.Rolls;

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
        System.out.println("0. Выход");
        System.out.print("> ");
    }

    private void loadFromFile() {
        System.out.print("Введите имя файла (по умолчанию menu.txt): ");
        String filename = scanner.nextLine().trim();

        if (filename.isEmpty()) {
            filename = "menu.txt";
        }

        List<CafeMenuPosition> positions = FileManager.readFromFile(filename);

        currentRoll.Clear();
        for (CafeMenuPosition position : positions) {
            if (FileManager.validatePosition(position)) {
                currentRoll.AddElement(position);
            }
        }
    }

    private void saveToFile() {
        System.out.print("Введите имя файла (по умолчанию menu.txt): ");
        String filename = scanner.nextLine().trim();

        if (filename.isEmpty()) {
            filename = "menu.txt";
        }

        FileManager.writeToFile(filename, currentRoll.GetAllElements());
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