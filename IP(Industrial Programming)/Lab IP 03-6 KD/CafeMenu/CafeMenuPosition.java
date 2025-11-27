package CafeMenu;

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
    protected Date addedDate; // дата добавления в меню

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
            "Дата добавления: %s",
            id, name, category, price, calories,
            new SimpleDateFormat("dd.MM.yyyy").format(addedDate)
        );
    }

    public abstract void getInfo();
    abstract String getDishType();
}

