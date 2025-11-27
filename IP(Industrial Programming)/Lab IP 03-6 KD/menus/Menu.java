package menus;

import CafeMenu.CafeMenuPosition;
import CafeMenu.Dessert;
import CafeMenu.Drink;
import CafeMenu.MainCourse;
import rolls.ListRoll;
import rolls.MapRoll;
import rolls.Rolls;

import java.util.Comparator;
import java.util.Scanner;

public class Menu {
    private Rolls<CafeMenuPosition> currentRoll;
    private ListRoll<CafeMenuPosition> listRoll;
    private MapRoll<CafeMenuPosition> mapRoll;
    private Scanner scanner;

    public Menu() {
        this.listRoll = new ListRoll<>();
        this.mapRoll = new MapRoll<>();
        this.currentRoll = listRoll;
        this.scanner = new Scanner(System.in);
    }

    public void start() {
        System.out.println("=== МЕНЮ РЕДАКТИРОВАНИЯ ===");

        while (true) {
            printMainMenu();
            int choice = readIntInput("Выберите действие: ");

            switch (choice) {
                case 1 -> selectRollType();
                case 2 -> addElement();
                case 3 -> deleteElement();
                case 4 -> replaceElement();
                case 5 -> getElement();
                case 6 -> printAllElements();
                case 7 -> sortElements();
                case 8 -> clearRoll();
                case 9 -> showRollInfo();
                case 0 -> {
                    System.out.println("Выход из программы.");
                    return;
                }
                default -> System.out.println("Неверный выбор. Попробуйте снова.");
            }
        }
    }

    private void printMainMenu() {
        System.out.println("Текущий тип хранения: " + (currentRoll instanceof ListRoll ? "ListRoll" : "MapRoll"));
        System.out.println("1. Выбрать тип хранения");
        System.out.println("2. Добавить элемент");
        System.out.println("3. Удалить элемент");
        System.out.println("4. Заменить элемент");
        System.out.println("5. Найти элемент");
        System.out.println("6. Показать все элементы");
        System.out.println("7. Сортировать элементы");
        System.out.println("8. Очистить список");
        System.out.println("9. Информация о текущем списке");
        System.out.println("0. Выход");
    }

    private void selectRollType() {
        System.out.println("\n=== ВЫБОР ТИПА ХРАНЕНИЯ ===");
        System.out.println("1. ListRoll (список)");
        System.out.println("2. MapRoll (словарь)");
        int choice = readIntInput("Выберите тип: ");

        switch (choice) {
            case 1 -> {
                currentRoll = listRoll;
                System.out.println("Выбран ListRoll");
            }
            case 2 -> {
                currentRoll = mapRoll;
                System.out.println("Выбран MapRoll");
            }
            default -> System.out.println("Неверный выбор. Оставлен текущий тип.");
        }
    }

    private void addElement() {
        System.out.println("\n=== ДОБАВЛЕНИЕ ЭЛЕМЕНТА ===");
        System.out.println("1. Основное блюдо");
        System.out.println("2. Напиток");
        System.out.println("3. Десерт");
        int type = readIntInput("Выберите тип элемента: ");

        CafeMenuPosition element = createElement(type);
        if (element != null) {
            currentRoll.AddElement(element);
        }
    }

    private CafeMenuPosition createElement(int type) {
        try {
            int id = readIntInput("ID: ");
            String name = readStringInput("Название: ");
            double price = readDoubleInput("Цена: ");
            String category = readStringInput("Категория: ");
            double calories = readDoubleInput("Калории: ");

            switch (type) {
                case 1 -> {
                    int mass = readIntInput("Масса (г): ");
                    boolean vegetarian = readBooleanInput("Вегетарианский (true/false): ");
                    return new MainCourse(id, name, price, category, calories, mass, vegetarian);
                }
                case 2 -> {
                    int volume = readIntInput("Объем (мл): ");
                    boolean alcoholic = readBooleanInput("Алкогольный (true/false): ");
                    return new Drink(id, name, price, category, calories, volume, alcoholic);
                }
                case 3 -> {
                    int mass = readIntInput("Масса (г): ");
                    boolean sweet = readBooleanInput("Сладкий (true/false): ");
                    return new Dessert(id, name, price, category, calories, mass, sweet);
                }
                default -> {
                    System.out.println("Неверный тип элемента.");
                    return null;
                }
            }
        } catch (Exception e) {
            System.out.println("Ошибка при создании элемента: " + e.getMessage());
            return null;
        }
    }

    private void deleteElement() {
        System.out.println("\n=== УДАЛЕНИЕ ЭЛЕМЕНТА ===");
        int id = readIntInput("Введите ID элемента для удаления: ");
        String category = readStringInput("Введите категорию: ");

        CafeMenuPosition element = currentRoll.GetElement(id, category);
        if (element != null) {
            if (currentRoll.DeleteElement(element)) {
                System.out.println("Элемент успешно удален.");
            } else {
                System.out.println("Не удалось удалить элемент.");
            }
        } else {
            System.out.println("Элемент не найден.");
        }
    }

    private void replaceElement() {
        System.out.println("\n=== ЗАМЕНА ЭЛЕМЕНТА ===");
        int id = readIntInput("Введите ID элемента для замены: ");
        String category = readStringInput("Введите категорию: ");

        CafeMenuPosition oldElement = currentRoll.GetElement(id, category);
        if (oldElement != null) {
            System.out.println("Найден элемент: " + oldElement.getName());
            System.out.println("Создайте новый элемент с тем же ID:");

            CafeMenuPosition newElement = createElement(getElementType(oldElement));
            if (newElement != null && newElement.getId() == id) {
                currentRoll.ReplaceElement(newElement);
            } else {
                System.out.println("ID нового элемента должен совпадать со старым.");
            }
        } else {
            System.out.println("Элемент не найден.");
        }
    }

    private int getElementType(CafeMenuPosition element) {
        if (element instanceof MainCourse) return 1;
        if (element instanceof Drink) return 2;
        if (element instanceof Dessert) return 3;
        return 1;
    }

    private void getElement() {
        System.out.println("\n=== ПОИСК ЭЛЕМЕНТА ===");
        int id = readIntInput("Введите ID элемента: ");
        String category = readStringInput("Введите категорию: ");

        CafeMenuPosition element = currentRoll.GetElement(id, category);
        if (element != null) {
            System.out.println("Найден элемент:");
            element.getInfo();
        } else {
            System.out.println("Элемент не найден.");
        }
    }

    private void printAllElements() {
        System.out.println("\n=== ВСЕ ЭЛЕМЕНТЫ ===");
        currentRoll.PrintList();
    }

    private void sortElements() {
        System.out.println("\n=== СОРТИРОВКА ===");
        System.out.println("1. По ID");
        System.out.println("2. По названию");
        System.out.println("3. По цене");
        System.out.println("4. По калориям");
        int choice = readIntInput("Выберите поле для сортировки: ");

        Comparator<CafeMenuPosition> comparator = switch (choice) {
            case 1 -> Comparator.comparingInt(CafeMenuPosition::getId);
            case 2 -> Comparator.comparing(CafeMenuPosition::getName);
            case 3 -> Comparator.comparingDouble(CafeMenuPosition::getPrice);
            case 4 -> Comparator.comparingDouble(CafeMenuPosition::getCalories);
            default -> {
                System.out.println("Неверный выбор. Сортировка отменена.");
                yield null;
            }
        };

        if (comparator != null) {
            currentRoll.sort(comparator);
            System.out.println("Элементы отсортированы.");
        }
    }

    private void clearRoll() {
        System.out.println("\n=== ОЧИСТКА СПИСКА ===");
        String confirm = readStringInput("Вы уверены? (yes/no): ");
        if (confirm.equalsIgnoreCase("yes")) {
            currentRoll.Clear();
            System.out.println("Список очищен.");
        } else {
            System.out.println("Очистка отменена.");
        }
    }

    private void showRollInfo() {
        System.out.println("\n=== ИНФОРМАЦИЯ О СПИСКЕ ===");
        System.out.println("Тип хранения: " + (currentRoll instanceof ListRoll ? "ListRoll" : "MapRoll"));
        System.out.println("Количество элементов: " + currentRoll.GetSize());
    }

    // Вспомогательные методы для ввода данных
    private int readIntInput(String prompt) {
        while (true) {
            try {
                System.out.print(prompt);
                return Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Ошибка: введите целое число.");
            }
        }
    }

    private double readDoubleInput(String prompt) {
        while (true) {
            try {
                System.out.print(prompt);
                return Double.parseDouble(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Ошибка: введите число.");
            }
        }
    }

    private String readStringInput(String prompt) {
        System.out.print(prompt);
        return scanner.nextLine();
    }

    private boolean readBooleanInput(String prompt) {
        while (true) {
            System.out.print(prompt);
            String input = scanner.nextLine().toLowerCase();
            if (input.equals("true") || input.equals("1") || input.equals("yes")) {
                return true;
            } else if (input.equals("false") || input.equals("0") || input.equals("no")) {
                return false;
            } else {
                System.out.println("Ошибка: введите 'true' или 'false'.");
            }
        }
    }
}