package test;

import cafe_menu.Dessert;
import cafe_menu.Drink;
import cafe_menu.MainCourse;
import builders.*;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class CafeMenuPositionTest {

    @Test
    void testDrinkCreation() {
        Drink drink = new DrinkBuilder()
                .setId(1)
                .setName("Coffee")
                .setPrice(150.0)
                .setCategory("Напитки")
                .setCalories(50.0)
                .setVolume(200)
                .setAlcoholic(false)
                .build();

        assertEquals(1, drink.getId());
        assertEquals("Coffee", drink.getName());
        assertEquals(150.0, drink.getPrice(), 0.001);
        assertEquals("Напитки", drink.getCategory());
        assertEquals(50.0, drink.getCalories(), 0.001);
        assertEquals(200, drink.getVolume());
        assertFalse(drink.isAlcoholic());
        assertNotNull(drink.getAddedDate());
    }

    @Test
    void testDrinkToString() {
        Drink drink = new DrinkBuilder()
                .setId(1)
                .setName("Coffee")
                .setPrice(150.0)
                .setCategory("Напитки")
                .setCalories(50.0)
                .setVolume(200)
                .setAlcoholic(false)
                .build();

        String str = drink.toString();

        assertTrue(str.contains("Coffee"));
        assertTrue(str.contains("150,00") || str.contains("150.00"));
        assertTrue(str.contains("Напитки"));
    }

    @Test
    void testMainCourseVegetarian() {
        MainCourse main = new MainCourseBuilder()
                .setId(2)
                .setName("Salad")
                .setPrice(200.0)
                .setCategory("Основные блюда")
                .setCalories(150.0)
                .setMass(300)
                .setVegetarian(true)
                .build();

        assertEquals(2, main.getId());
        assertEquals("Salad", main.getName());
        assertTrue(main.isVegetarian());
        assertEquals(300, main.getMass());
    }

    @Test
    void testDessertSweet() {
        Dessert dessert = new DessertBuilder()
                .setId(3)
                .setName("Cake")
                .setPrice(250.0)
                .setCategory("Десерты")
                .setCalories(400.0)
                .setMass(150)
                .setSweet(true)
                .build();

        assertEquals(3, dessert.getId());
        assertEquals("Cake", dessert.getName());
        assertTrue(dessert.isSweet());
        assertEquals(150, dessert.getMass());
    }

    @Test
    void testToFileString() {
        Drink drink = new DrinkBuilder()
                .setId(1)
                .setName("Coffee")
                .setPrice(150.0)
                .setCategory("Напитки")
                .setCalories(50.0)
                .setVolume(200)
                .setAlcoholic(false)
                .build();

        String fileStr = drink.toFileString();

        assertTrue(fileStr.startsWith("DRINK;"));
        assertTrue(fileStr.contains("Coffee"));
        assertTrue(fileStr.contains("150,00") || fileStr.contains("150.00"));
    }

    @Test
    void testFromFileString() {
        String line = "DRINK;1;Coffee;150.00;Напитки;50.0;01.01.2023;200;false";
        Drink drink = Drink.fromFileString(line);

        assertEquals(1, drink.getId());
        assertEquals("Coffee", drink.getName());
        assertEquals(150.0, drink.getPrice(), 0.001);
        assertEquals("Напитки", drink.getCategory());
        assertEquals(50.0, drink.getCalories(), 0.001);
        assertEquals(200, drink.getVolume());
        assertFalse(drink.isAlcoholic());
    }

    @Test
    void testInvalidFileString() {
        String line = "INVALID;1;Coffee;150.00;Напитки;50.0";

        assertThrows(IllegalArgumentException.class, () -> {
            Drink.fromFileString(line);
        });
    }
}