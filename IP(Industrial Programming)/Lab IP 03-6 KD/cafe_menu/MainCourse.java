package cafe_menu;

import java.text.SimpleDateFormat;

public class MainCourse extends CafeMenuPosition{

    public int getMass() {
        return mass;
    }

    public boolean isVegetarian() {
        return vegetarian;
    }

    public void setMass(int mass) {
        this.mass = mass;
    }

    public void setVegetarian(boolean vegetarian) {
        this.vegetarian = vegetarian;
    }

    private int mass;
    private boolean vegetarian;

    public MainCourse(int ID, String NAME, double PRICE, String CATEGORY, double CALORIES, int MASS, boolean VEGETARIAN) {
        super(ID, NAME, PRICE, CATEGORY, CALORIES);
        this.mass = MASS;
        this.vegetarian = VEGETARIAN;
    }

    @Override
    public String toString(){
        return String.format(
                super.toString() + "Масса: %d г.\nТип: %s", mass,
                isVegetarian() ? "Вегетарианский" : "Не вегетарианский"
        );
    }

    public void getInfo(){
        System.out.println("\"ID: " + getId());
        System.out.println("Название: " + getName());
        System.out.println("Категория: " +  getCategory());
        System.out.println(isVegetarian() ? "Вегетарианский" : "Не вегетарианский");
        System.out.println("Цена: " + getPrice());
        System.out.println("Масса" + getMass());
        System.out.println("Калории: " + getCalories());
        System.out.println("Дата добавления: " + getAddedDate());
    }

    @Override
    public String getDishType() {
        return (isVegetarian() ? "Вегетарианское" : "Не вегетарианское" + " блюдо ");
    }


    @Override
    public String toFileString() {
        return "MAIN_COURSE;" + super.toFileString() + String.format(";%d;%b",
                mass, vegetarian);
    }

    public static MainCourse fromFileString(String line) {
        String[] parts = line.split(";");
        if (!parts[0].equals("MAIN_COURSE") || parts.length != 9) {
            throw new IllegalArgumentException("Неверный формат строки для MainCourse");
        }

        parts[3] = parts[3].replace(',', '.');
        parts[5] = parts[5].replace(',', '.');

        MainCourse mainCourse = new MainCourse(
                Integer.parseInt(parts[1]),
                parts[2],
                Double.parseDouble(parts[3]),
                parts[4],
                Double.parseDouble(parts[5]),
                Integer.parseInt(parts[7]),
                Boolean.parseBoolean(parts[8])
        );

        try {
            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
            mainCourse.setAddedDate(sdf.parse(parts[6]));
        } catch (Exception e) {}

        return mainCourse;
    }
}

