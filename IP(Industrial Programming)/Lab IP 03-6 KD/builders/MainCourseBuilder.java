package builders;

import cafe_menu.MainCourse;
import java.text.SimpleDateFormat;
import java.util.Date;

public class MainCourseBuilder implements CafeMenuBuilder {
    private int id;
    private String name;
    private double price;
    private String category;
    private double calories;
    private int mass;
    private boolean vegetarian;
    private Date addedDate;

    public MainCourseBuilder() {
        this.addedDate = new Date();
        this.category = "Основные блюда";
    }

    @Override
    public MainCourseBuilder setId(int id) {
        this.id = id;
        return this;
    }

    @Override
    public MainCourseBuilder setName(String name) {
        this.name = name;
        return this;
    }

    @Override
    public MainCourseBuilder setPrice(double price) {
        this.price = price;
        return this;
    }

    @Override
    public MainCourseBuilder setCategory(String category) {
        this.category = category;
        return this;
    }

    @Override
    public MainCourseBuilder setCalories(double calories) {
        this.calories = calories;
        return this;
    }

    public MainCourseBuilder setMass(int mass) {
        this.mass = mass;
        return this;
    }

    public MainCourseBuilder setVegetarian(boolean vegetarian) {
        this.vegetarian = vegetarian;
        return this;
    }

    public MainCourseBuilder setAddedDate(Date addedDate) {
        this.addedDate = addedDate;
        return this;
    }

    public MainCourseBuilder setAddedDate(String dateString) {
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
            this.addedDate = sdf.parse(dateString);
        } catch (Exception e) {
            this.addedDate = new Date();
        }
        return this;
    }

    @Override
    public MainCourse build() {
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

        MainCourse mainCourse = new MainCourse(id, name, price, category, calories, mass, vegetarian);
        mainCourse.setAddedDate(addedDate);
        return mainCourse;
    }
}