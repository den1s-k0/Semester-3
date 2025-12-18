package test;

import builders.*;
import cafe_menu.Drink;
import cafe_menu.MainCourse;
import cafe_menu.Dessert;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class BuilderTest {

    @Test
    void testDrinkBuilder() {
        Drink drink = new DrinkBuilder()
                .setId(1)
                .setName("Cappuccino")
                .setPrice(180.0)
                .setCalories(120.0)
                .setVolume(200)
                .setAlcoholic(false)
                .setCategory("Hot Drinks")
                .build();

        assertEquals(1, drink.getId());
        assertEquals("Cappuccino", drink.getName());
        assertEquals(180.0, drink.getPrice(), 0.001);
        assertEquals("Hot Drinks", drink.getCategory());
        assertEquals(120.0, drink.getCalories(), 0.001);
        assertEquals(200, drink.getVolume());
        assertFalse(drink.isAlcoholic());
        assertNotNull(drink.getAddedDate());
    }

    @Test
    void testMainCourseBuilder() {
        MainCourse mainCourse = new MainCourseBuilder()
                .setId(2)
                .setName("Vegetarian Pizza")
                .setPrice(350.0)
                .setCalories(450.0)
                .setMass(400)
                .setVegetarian(true)
                .setCategory("Italian Cuisine")
                .build();

        assertEquals(2, mainCourse.getId());
        assertEquals("Vegetarian Pizza", mainCourse.getName());
        assertEquals(350.0, mainCourse.getPrice(), 0.001);
        assertEquals("Italian Cuisine", mainCourse.getCategory());
        assertTrue(mainCourse.isVegetarian());
        assertEquals(400, mainCourse.getMass());
    }

    @Test
    void testDessertBuilder() {
        Dessert dessert = new DessertBuilder()
                .setId(3)
                .setName("Chocolate Cake")
                .setPrice(280.0)
                .setCalories(380.0)
                .setMass(180)
                .setSweet(true)
                .setCategory("Sweet Desserts")
                .setAddedDate("15.12.2023")
                .build();

        assertEquals(3, dessert.getId());
        assertEquals("Chocolate Cake", dessert.getName());
        assertEquals(280.0, dessert.getPrice(), 0.001);
        assertEquals("Sweet Desserts", dessert.getCategory());
        assertTrue(dessert.isSweet());
        assertEquals(180, dessert.getMass());
    }

    @Test
    void testInvalidDrinkBuilder() {
        assertThrows(IllegalArgumentException.class, () -> {
            new DrinkBuilder()
                    .setId(0)
                    .setName("Test")
                    .setPrice(100.0)
                    .setCalories(50.0)
                    .setVolume(200)
                    .setAlcoholic(false)
                    .build();
        });

        assertThrows(IllegalArgumentException.class, () -> {
            new DrinkBuilder()
                    .setId(1)
                    .setName("")
                    .setPrice(100.0)
                    .setCalories(50.0)
                    .setVolume(200)
                    .setAlcoholic(false)
                    .build();
        });

        assertThrows(IllegalArgumentException.class, () -> {
            new DrinkBuilder()
                    .setId(1)
                    .setName("Test")
                    .setPrice(-50.0)
                    .setCalories(50.0)
                    .setVolume(200)
                    .setAlcoholic(false)
                    .build();
        });
    }


    @Test
    void testFromFileString() {
        MenuDirector director = new MenuDirector();

        String drinkString = "DRINK;1;Coffee;150,00;Напитки;50,0;01.01.2023;200;false";
        Drink drink = (Drink) director.fromFileString(drinkString);
        assertEquals("Coffee", drink.getName());
        assertEquals(200, drink.getVolume());
        assertFalse(drink.isAlcoholic());

        String mainCourseString = "MAIN_COURSE;2;Salad;200,00;Основные блюда;150,0;01.01.2023;300;true";
        MainCourse mainCourse = (MainCourse) director.fromFileString(mainCourseString);
        assertEquals("Salad", mainCourse.getName());
        assertTrue(mainCourse.isVegetarian());
    }
}