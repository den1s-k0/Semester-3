package test;

import menus.ConsoleMenu;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.io.*;
import static org.junit.jupiter.api.Assertions.*;

class ConsoleMenuTest {

    private final ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;
    private final InputStream originalIn = System.in;

    @BeforeEach
    void setUp() {
        System.setOut(new PrintStream(outputStream, true));
    }

    @AfterEach
    void tearDown() {
        System.setOut(originalOut);
        System.setIn(originalIn);
    }

    @Test
    void testMenuInitialization() {
        ConsoleMenu menu = new ConsoleMenu();
        assertNotNull(menu);
    }

    @Test
    void testExitOption() {
        String input = "0\n";
        System.setIn(new ByteArrayInputStream(input.getBytes()));

        ConsoleMenu menu = new ConsoleMenu();

        // Запускаем в отдельном потоке, так как start() блокирующий
        Thread thread = new Thread(() -> menu.start());
        thread.start();

        // Даем время на выполнение
        try {
            Thread.sleep(100);
            thread.interrupt();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        String output = outputStream.toString();
        assertTrue(output.contains("МЕНЮ") || output.contains("Выход"));
    }

    @Test
    void testInvalidMenuOption() {
        String input = "999\n0\n";
        System.setIn(new ByteArrayInputStream(input.getBytes()));

        ConsoleMenu menu = new ConsoleMenu();

        Thread thread = new Thread(() -> menu.start());
        thread.start();

        try {
            Thread.sleep(200);
            thread.interrupt();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        String output = outputStream.toString();
        assertTrue(output.contains("Неверный выбор"));
    }
}