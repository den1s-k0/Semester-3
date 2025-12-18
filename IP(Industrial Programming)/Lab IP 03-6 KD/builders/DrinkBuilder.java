package builders;

import cafe_menu.Drink;
import java.text.SimpleDateFormat;
import java.util.Date;

public class DrinkBuilder implements CafeMenuBuilder {
    private int id;
    private String name;
    private double price;
    private String category;
    private double calories;
    private int volume;
    private boolean alcoholic;
    private Date addedDate;

    public DrinkBuilder() {
        this.addedDate = new Date();
        this.category = "Напитки";
    }

    @Override
    public DrinkBuilder setId(int id) {
        this.id = id;
        return this;
    }

    @Override
    public DrinkBuilder setName(String name) {
        this.name = name;
        return this;
    }

    @Override
    public DrinkBuilder setPrice(double price) {
        this.price = price;
        return this;
    }

    @Override
    public DrinkBuilder setCategory(String category) {
        this.category = category;
        return this;
    }

    @Override
    public DrinkBuilder setCalories(double calories) {
        this.calories = calories;
        return this;
    }

    public DrinkBuilder setVolume(int volume) {
        this.volume = volume;
        return this;
    }

    public DrinkBuilder setAlcoholic(boolean alcoholic) {
        this.alcoholic = alcoholic;
        return this;
    }

    public DrinkBuilder setAddedDate(Date addedDate) {
        this.addedDate = addedDate;
        return this;
    }

    public DrinkBuilder setAddedDate(String dateString) {
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
            this.addedDate = sdf.parse(dateString);
        } catch (Exception e) {
            this.addedDate = new Date();
        }
        return this;
    }

    @Override
    public Drink build() {
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
        if (volume <= 0) {
            throw new IllegalArgumentException("Volume must be positive");
        }

        Drink drink = new Drink(id, name, price, category, calories, volume, alcoholic);
        drink.setAddedDate(addedDate);
        return drink;
    }
}