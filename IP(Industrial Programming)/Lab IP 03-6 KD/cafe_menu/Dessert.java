package cafe_menu;

import java.text.SimpleDateFormat;

public class Dessert extends CafeMenuPosition{

    public int getMass() {
        return mass;
    }

    public boolean isSweet() {
        return sweet;
    }

    public void setSweet(boolean sweet) {
        this.sweet = sweet;
    }

    public void setMass(int mass) {
        this.mass = mass;
    }

    private int mass;
    private boolean sweet;

    public Dessert(int ID, String NAME, double PRICE, String CATEGORY, double CALORIES, int MASS, boolean SWEET) {
        super(ID, NAME, PRICE, CATEGORY, CALORIES);
        this.mass= MASS;
        this.sweet = SWEET;
    }

    @Override
    public String toString(){
        return String.format(
                super.toString() + "Масса: %d мл.\nТип: %s", mass,
                isSweet() ? "Сладкий" : "Кислый"
        );
    }

    public void getInfo(){
        System.out.println("\"ID: " + getId());
        System.out.println("Название: " + getName());
        System.out.println("Категория: " +  getCategory());
        System.out.println(isSweet() ? "Сладкий" : "Кислый");
        System.out.println("Цена: " + getPrice());
        System.out.println("Масса" + getMass());
        System.out.println("Калории: " + getCalories());
        System.out.println("Дата добавления: " + getAddedDate());
    }

    @Override
    public String getDishType() {
        return (isSweet() ? "Сладкий" : "Кислый") + " десерт ";
    }

    @Override
    public String toFileString() {
        return "DESSERT;" + super.toFileString() + String.format(";%d;%b",
                mass, sweet);
    }

    public static Dessert fromFileString(String line) {
        String[] parts = line.split(";");
        if (!parts[0].equals("DESSERT") || parts.length != 9) {
            throw new IllegalArgumentException("Неверный формат строки для Dessert");
        }

        parts[3] = parts[3].replace(',', '.');
        parts[5] = parts[5].replace(',', '.');

        Dessert dessert = new Dessert(
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
            dessert.setAddedDate(sdf.parse(parts[6]));
        } catch (Exception e) {}

        return dessert;
    }
}
