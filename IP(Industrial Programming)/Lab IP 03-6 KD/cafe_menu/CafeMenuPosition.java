package cafe_menu;

import java.text.SimpleDateFormat;
import java.util.Date;

public abstract class CafeMenuPosition{
    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public double getPrice() {
        return price;
    }

    public String getCategory() {
        return category;
    }

    public double getCalories() {
        return calories;
    }

    public Date getAddedDate() {
        return addedDate;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAddedDate(Date addedDate) {
        this.addedDate = addedDate;
    }

    public void setCalories(double calories) {
        this.calories = calories;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    protected int id;
    protected String name;
    protected double price;
    protected String category;
    protected double calories;
    protected Date addedDate;

    public CafeMenuPosition(int ID, String NAME, double PRICE, String CATEGORY,
                            double CALORIES){
        this.id = ID;
        this.name = NAME;
        this.price = PRICE;
        this.category = CATEGORY;
        this.calories = CALORIES;
        this.addedDate = new Date();
    }

    @Override
    public String toString(){
        return String.format(
            "ID: %d | Название: %s | Категория: %s\n" +
            "Цена: %.2f руб. | Калории: %.1f ккал\n" +
            "Дата добавления: %s\n",
            id, name, category, price, calories,
            new SimpleDateFormat("dd.MM.yyyy").format(addedDate)
        );
    }

    public abstract void getInfo();
    public abstract String getDishType();

    public String toFileString() {
        return String.format("%s;%s;%.2f;%s;%.1f;%s",
                id, name, price, category, calories,
                new SimpleDateFormat("dd.MM.yyyy").format(addedDate));
    }

    protected void fromFileString(String[] parts) {
        if (parts.length < 6) {
            throw new IllegalArgumentException("Недостаточно полей: " + parts.length);
        }

        this.id = Integer.parseInt(parts[0]);
        this.name = parts[1];
        this.price = Double.parseDouble(parts[2].replace(',', '.'));
        this.category = parts[3];
        this.calories = Double.parseDouble(parts[4].replace(',', '.'));

        try {
            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
            this.addedDate = sdf.parse(parts[5]);
        } catch (Exception e) {
            this.addedDate = new Date();
        }
    }
}

