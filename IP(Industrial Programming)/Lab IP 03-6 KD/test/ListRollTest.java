package test;

import cafe_menu.Drink;
import cafe_menu.MainCourse;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import rolls.ListRoll;

import java.util.Comparator;
import java.util.List;
import static org.junit.jupiter.api.Assertions.*;

class ListRollTest {

    private ListRoll<Drink> drinkRoll;
    private Drink coffee;
    private Drink tea;

    @BeforeEach
    void setUp() {
        drinkRoll = new ListRoll<>();
        coffee = new Drink(1, "Coffee", 150.0, "Напитки", 50.0, 200, false);
        tea = new Drink(2, "Tea", 100.0, "Напитки", 5.0, 250, false);
    }

    @Test
    void testAddElement() {
        assertEquals(0, drinkRoll.GetSize());

        drinkRoll.AddElement(coffee);
        assertEquals(1, drinkRoll.GetSize());

        drinkRoll.AddElement(tea);
        assertEquals(2, drinkRoll.GetSize());
    }

    @Test
    void testAddDuplicateElement() {
        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(coffee);

        assertEquals(1, drinkRoll.GetSize());
    }

    @Test
    void testDeleteElement() {
        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(tea);

        assertTrue(drinkRoll.DeleteElement(coffee));
        assertEquals(1, drinkRoll.GetSize());

        assertFalse(drinkRoll.DeleteElement(coffee));
    }

    @Test
    void testReplaceElement() {
        drinkRoll.AddElement(coffee);

        Drink newCoffee = new Drink(1, "Espresso", 200.0, "Напитки", 60.0, 50, false);
        drinkRoll.ReplaceElement(newCoffee);

        List<Drink> all = drinkRoll.GetAllElements();
        assertEquals(1, all.size());
        assertEquals("Espresso", all.get(0).getName());
        assertEquals(200.0, all.get(0).getPrice(), 0.001);
    }

    @Test
    void testGetAllElements() {
        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(tea);

        List<Drink> all = drinkRoll.GetAllElements();
        assertEquals(2, all.size());
        assertEquals("Coffee", all.get(0).getName());
        assertEquals("Tea", all.get(1).getName());
    }

    @Test
    void testClear() {
        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(tea);

        assertEquals(2, drinkRoll.GetSize());

        drinkRoll.Clear();
        assertEquals(0, drinkRoll.GetSize());
    }

    @Test
    void testSort() {
        Drink juice = new Drink(3, "Juice", 120.0, "Напитки", 100.0, 300, false);

        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(juice);
        drinkRoll.AddElement(tea);

        Comparator<Drink> priceComparator = Comparator.comparingDouble(Drink::getPrice);
        drinkRoll.sort(priceComparator);

        List<Drink> sorted = drinkRoll.GetAllElements();
        assertEquals(100.0, sorted.get(0).getPrice(), 0.001);
        assertEquals(120.0, sorted.get(1).getPrice(), 0.001);
        assertEquals(150.0, sorted.get(2).getPrice(), 0.001);
    }

    @Test
    void testPrintList() {
        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(tea);

        assertDoesNotThrow(() -> drinkRoll.PrintList());
    }

    @Test
    void testGetElement() {
        drinkRoll.AddElement(coffee);
        drinkRoll.AddElement(tea);

        Drink found = drinkRoll.GetElement(1, "Напитки");
        assertNotNull(found);
        assertEquals("Coffee", found.getName());

        Drink notFound = drinkRoll.GetElement(999, "Напитки");
        assertNull(notFound);
    }
}