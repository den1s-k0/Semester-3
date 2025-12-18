package test;

import builders.DrinkBuilder;
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

        DrinkBuilder drinkBuilder = new DrinkBuilder()
                .setCategory("Напитки")
                .setAlcoholic(false);

        coffee = drinkBuilder
                .setId(1)
                .setName("Coffee")
                .setPrice(150.0)
                .setCalories(50.0)
                .setVolume(200)
                .build();

        tea = drinkBuilder
                .setId(2)
                .setName("Tea")
                .setPrice(100.0)
                .setCalories(5.0)
                .setVolume(250)
                .build();
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
    void testReplaceElement() {
        drinkRoll.AddElement(coffee);

        Drink newCoffee = new DrinkBuilder()
                .setId(1)
                .setName("Espresso")
                .setPrice(200.0)
                .setCategory("Напитки")
                .setCalories(60.0)
                .setVolume(50)
                .setAlcoholic(false)
                .build();

        drinkRoll.ReplaceElement(newCoffee);

        List<Drink> all = drinkRoll.GetAllElements();
        assertEquals(1, all.size());
        assertEquals("Espresso", all.get(0).getName());
        assertEquals(200.0, all.get(0).getPrice(), 0.001);
    }

    @Test
    void testSort() {
        Drink juice = new DrinkBuilder()
                .setId(3)
                .setName("Juice")
                .setPrice(120.0)
                .setCategory("Напитки")
                .setCalories(100.0)
                .setVolume(300)
                .setAlcoholic(false)
                .build();

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