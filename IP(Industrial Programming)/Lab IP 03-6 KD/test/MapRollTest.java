package test;

import cafe_menu.CafeMenuPosition;
import cafe_menu.Drink;
import cafe_menu.MainCourse;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import rolls.MapRoll;

import java.util.Comparator;
import java.util.List;
import static org.junit.jupiter.api.Assertions.*;

class MapRollTest {

    private MapRoll<Drink> drinkRoll;
    private Drink coffee;
    private Drink tea;

    @BeforeEach
    void setUp() {
        drinkRoll = new MapRoll<>();
        coffee = new Drink(1, "Coffee", 150.0, "Напитки", 50.0, 200, false);
        tea = new Drink(2, "Tea", 100.0, "Напитки", 5.0, 250, false);
    }

    @Test
    void testMapRollAddAndGet() {
        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(tea);

        assertEquals(2, drinkRoll.GetSize());

        Drink found = drinkRoll.GetElement(1, "Напитки");
        assertNotNull(found);
        assertEquals("Coffee", found.getName());
    }

    @Test
    void testMapRollDelete() {
        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(tea);

        assertTrue(drinkRoll.DeleteElement(coffee));
        assertEquals(1, drinkRoll.GetSize());

        assertFalse(drinkRoll.DeleteElement(coffee));
    }

    @Test
    void testMapRollSort() {
        Drink juice = new Drink(3, "Juice", 120.0, "Напитки", 100.0, 300, false);

        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(juice);
        drinkRoll.AddElement(tea);

        Comparator<Drink> nameComparator = Comparator.comparing(Drink::getName);
        drinkRoll.sort(nameComparator);

        List<Drink> sorted = drinkRoll.GetAllElements();
        assertEquals("Coffee", sorted.get(0).getName());
        assertEquals("Juice", sorted.get(1).getName());
        assertEquals("Tea", sorted.get(2).getName());
    }

    @Test
    void testMixedTypes() {
        MapRoll<CafeMenuPosition> mixedRoll = new MapRoll<>();

        Drink drink = new Drink(1, "Cola", 80.0, "Напитки", 100.0, 330, false);
        MainCourse main = new MainCourse(2, "Burger", 300.0, "Основные блюда", 500.0, 250, false);

        mixedRoll.AddElement(drink);
        mixedRoll.AddElement(main);

        assertEquals(2, mixedRoll.GetSize());
    }
}