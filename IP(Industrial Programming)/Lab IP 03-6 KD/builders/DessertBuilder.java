package builders;

import cafe_menu.Dessert;
import java.text.SimpleDateFormat;
import java.util.Date;

public class DessertBuilder implements CafeMenuBuilder {
    private int id;
    private String name;
    private double price;
    private String category;
    private double calories;
    private int mass;
    private boolean sweet;
    private Date addedDate;

    public DessertBuilder() {
        this.addedDate = new Date();
        this.category = "Десерты";
    }

    @Override
    public DessertBuilder setId(int id) {
        this.id = id;
        return this;
    }

    @Override
    public DessertBuilder setName(String name) {
        this.name = name;
        return this;
    }

    @Override
    public DessertBuilder setPrice(double price) {
        this.price = price;
        return this;
    }

    @Override
    public DessertBuilder setCategory(String category) {
        this.category = category;
        return this;
    }

    @Override
    public DessertBuilder setCalories(double calories) {
        this.calories = calories;
        return this;
    }

    public DessertBuilder setMass(int mass) {
        this.mass = mass;
        return this;
    }

    public DessertBuilder setSweet(boolean sweet) {
        this.sweet = sweet;
        return this;
    }

    public DessertBuilder setAddedDate(Date addedDate) {
        this.addedDate = addedDate;
        return this;
    }

    public DessertBuilder setAddedDate(String dateString) {
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
            this.addedDate = sdf.parse(dateString);
        } catch (Exception e) {
            this.addedDate = new Date();
        }
        return this;
    }

    @Override
    public Dessert build() {
        if (id <= 0) {
            throw new IllegalArgumentException("ID must be positive");
        }
        if (name == null || name.trim().isEmpty()) {
            throw new IllegalArgumentException("Name cannot be empty");
        }
        if (price < 0) {
            throw new IllegalArgumentException("Price cannot be negative");
        }
        if (calories < 0) {
            throw new IllegalArgumentException("Calories cannot be negative");
        }
        if (mass <= 0) {
            throw new IllegalArgumentException("Mass must be positive");
        }

        Dessert dessert = new Dessert(id, name, price, category, calories, mass, sweet);
        dessert.setAddedDate(addedDate);
        return dessert;
    }
}