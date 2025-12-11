package test;

import cafe_menu.*;
import file_manager.FileManager;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;
import java.io.File;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import static org.junit.jupiter.api.Assertions.*;

class FileManagerTest {

    @TempDir
    Path tempDir;

    @Test
    void testTextFormatReadWrite() {
        List<CafeMenuPosition> positions = createTestPositions();

        String filename = tempDir.resolve("test_menu.txt").toString();

        FileManager.writeToFile(filename, positions);

        List<CafeMenuPosition> loaded = FileManager.readFromFile(filename);

        assertEquals(3, loaded.size());
        assertEquals("Coffee", loaded.get(0).getName());
        assertEquals("Salad", loaded.get(1).getName());
        assertEquals("Cake", loaded.get(2).getName());
    }

    @Test
    void testXMLFormatReadWrite() {
        List<CafeMenuPosition> positions = createTestPositions();

        String filename = tempDir.resolve("test_menu.xml").toString();

        FileManager.writeToFile(filename, positions,
                FileManager.FileFormat.XML,
                FileManager.Compression.NONE,
                FileManager.Encryption.NONE);

        List<CafeMenuPosition> loaded = FileManager.readFromFile(filename,
                FileManager.FileFormat.XML,
                FileManager.Compression.NONE,
                FileManager.Encryption.NONE);

        assertEquals(3, loaded.size());
    }

    @Test
    void testJSONFormatReadWrite() {
        List<CafeMenuPosition> positions = createTestPositions();

        String filename = tempDir.resolve("test_menu.json").toString();

        FileManager.writeToFile(filename, positions,
                FileManager.FileFormat.JSON,
                FileManager.Compression.NONE,
                FileManager.Encryption.NONE);

        List<CafeMenuPosition> loaded = FileManager.readFromFile(filename,
                FileManager.FileFormat.JSON,
                FileManager.Compression.NONE,
                FileManager.Encryption.NONE);

        assertEquals(3, loaded.size());
    }

    @Test
    void testCompression() {
        List<CafeMenuPosition> positions = createTestPositions();

        String filename = tempDir.resolve("test_menu.zip").toString();

        FileManager.writeToFile(filename, positions,
                FileManager.FileFormat.TXT,
                FileManager.Compression.ZIP,
                FileManager.Encryption.NONE);

        File file = new File(filename);
        assertTrue(file.exists());
        assertTrue(file.length() > 0);
    }

    @Test
    void testValidatePosition() {
        Drink validDrink = new Drink(1, "Coffee", 150.0, "Напитки", 50.0, 200, false);
        assertTrue(FileManager.validatePosition(validDrink));

        Drink invalidPrice = new Drink(2, "Tea", -100.0, "Напитки", 5.0, 250, false);
        assertFalse(FileManager.validatePosition(invalidPrice));

        Drink invalidName = new Drink(3, "", 100.0, "Напитки", 5.0, 250, false);
        assertFalse(FileManager.validatePosition(invalidName));

        Drink invalidId = new Drink(0, "Juice", 120.0, "Напитки", 100.0, 300, false);
        assertFalse(FileManager.validatePosition(invalidId));
    }

    private List<CafeMenuPosition> createTestPositions() {
        List<CafeMenuPosition> positions = new ArrayList<>();

        positions.add(new Drink(1, "Coffee", 150.0, "Напитки", 50.0, 200, false));
        positions.add(new MainCourse(2, "Salad", 200.0, "Основные блюда", 150.0, 300, true));
        positions.add(new Dessert(3, "Cake", 250.0, "Десерты", 400.0, 150, true));

        return positions;
    }
}