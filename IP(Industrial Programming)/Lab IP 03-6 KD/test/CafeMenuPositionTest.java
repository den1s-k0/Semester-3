package test;

import cafe_menu.Dessert;
import cafe_menu.Drink;
import cafe_menu.MainCourse;
import org.junit.jupiter.api.Test;
import java.util.Date;
import static org.junit.jupiter.api.Assertions.*;

class CafeMenuPositionTest {

    @Test
    void testDrinkCreation() {
        Drink drink = new Drink(1, "Coffee", 150.0, "Напитки", 50.0, 200, false);

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
        Drink drink = new Drink(1, "Coffee", 150.0, "Напитки", 50.0, 200, false);
        String str = drink.toString();

        assertTrue(str.contains("Coffee"));
        assertTrue(str.contains("150,00"));
        assertTrue(str.contains("Напитки"));
    }

    @Test
    void testMainCourseVegetarian() {
        MainCourse main = new MainCourse(2, "Salad", 200.0, "Основные блюда", 150.0, 300, true);

        assertEquals(2, main.getId());
        assertEquals("Salad", main.getName());
        assertTrue(main.isVegetarian());
        assertEquals(300, main.getMass());
    }

    @Test
    void testDessertSweet() {
        Dessert dessert = new Dessert(3, "Cake", 250.0, "Десерты", 400.0, 150, true);

        assertEquals(3, dessert.getId());
        assertEquals("Cake", dessert.getName());
        assertTrue(dessert.isSweet());
        assertEquals(150, dessert.getMass());
    }

    @Test
    void testToFileString() {
        Drink drink = new Drink(1, "Coffee", 150.0, "Напитки", 50.0, 200, false);
        String fileStr = drink.toFileString();

        assertTrue(fileStr.startsWith("DRINK;"));
        assertTrue(fileStr.contains("Coffee"));
        assertTrue(fileStr.contains("150,00"));
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