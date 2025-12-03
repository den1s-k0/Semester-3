package cafe_menu;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Drink extends CafeMenuPosition{

    public int getVolume() {
        return volume;
    }

    public boolean isAlcoholic() {
        return alcoholic;
    }

    public void setVolume(int volume) {
        this.volume = volume;
    }

    public void setAlcoholic(boolean alcoholic) {
        this.alcoholic = alcoholic;
    }

    private int volume;
    private boolean alcoholic;

    public Drink(int ID, String NAME, double PRICE, String CATEGORY, double CALORIES, int VOLUME, boolean ALCOHOLIC) {
        super(ID, NAME, PRICE, CATEGORY, CALORIES);
        this.volume = VOLUME;
        this.alcoholic = ALCOHOLIC;
    }

    @Override
    public String toString(){
        return String.format(
           super.toString() + "Объем: %d мл.\nТип: %s", volume,
                isAlcoholic() ? "Алкогольный" : "Безалкогольный"
        );
    }

    public void getInfo(){
        System.out.println("\"ID: " + getId());
        System.out.println("Название: " + getName());
        System.out.println("Категория: " +  getCategory());
        System.out.println(isAlcoholic() ? "Алкогольный" : "Безалкогольный");
        System.out.println("Цена: " + getPrice());
        System.out.println("Объем" + volume);
        System.out.println("Калории: " + getCalories());
        System.out.println("Дата добавления: " + getAddedDate());
    }

    @Override
    public String getDishType() {
        return (isAlcoholic() ? "Алкогольный" : "Безалкогольный") + " напиток ";
    }

    @Override
    public String toFileString() {
        return "DRINK;" + super.toFileString() + String.format(";%d;%b",
                volume, alcoholic);
    }

    public static Drink fromFileString(String line) {
        String[] parts = line.split(";");
        if (!parts[0].equals("DRINK") || parts.length != 9) {
            throw new IllegalArgumentException("Неверный формат строки для Drink");
        }

        parts[3] = parts[3].replace(',', '.');
        parts[5] = parts[5].replace(',', '.');

        Drink drink = new Drink(
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
            drink.setAddedDate(sdf.parse(parts[6]));
        } catch (Exception e) {}

        return drink;
    }
}
