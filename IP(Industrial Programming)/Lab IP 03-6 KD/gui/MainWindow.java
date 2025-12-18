package gui;

import cafe_menu.*;
import builders.*;
import file_managers.FileManager;
import rolls.ListRoll;
import rolls.Rolls;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainWindow extends JFrame {
    private Rolls<CafeMenuPosition> menuRoll;
    private DefaultTableModel tableModel;
    private JTable table;
    private JTextArea logArea;
    private JComboBox<String> categoryComboBox;
    private ExecutorService executor;

    private static final String[] COLUMN_NAMES = {
            "ID", "Название", "Категория", "Цена", "Калории", "Детали", "Дата добавления"
    };

    public MainWindow() {
        menuRoll = new ListRoll<>();
        executor = Executors.newFixedThreadPool(2);

        setupWindow();
        createMenuBar();
        createToolBar();
        createMainPanel();
        createLogPanel();

        logArea.append("Готово к работе. Меню пусто.\n");
        setVisible(true);
    }

    private void setupWindow() {
        setTitle("Управление меню кафе - Лабораторная 5");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1000, 700);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout(5, 5));
    }

    private void createMenuBar() {
        JMenuBar menuBar = new JMenuBar();

        JMenu fileMenu = new JMenu("Файл");

        JMenuItem loadTxtItem = new JMenuItem("Загрузить из TXT");
        loadTxtItem.addActionListener(e -> loadFromFile(FileManager.FileFormat.TXT));

        JMenuItem loadXmlItem = new JMenuItem("Загрузить из XML");
        loadXmlItem.addActionListener(e -> loadFromFile(FileManager.FileFormat.XML));

        JMenuItem loadJsonItem = new JMenuItem("Загрузить из JSON");
        loadJsonItem.addActionListener(e -> loadFromFile(FileManager.FileFormat.JSON));

        JMenuItem saveTxtItem = new JMenuItem("Сохранить в TXT");
        saveTxtItem.addActionListener(e -> saveToFile(FileManager.FileFormat.TXT));

        JMenuItem saveXmlItem = new JMenuItem("Сохранить в XML");
        saveXmlItem.addActionListener(e -> saveToFile(FileManager.FileFormat.XML));

        JMenuItem saveJsonItem = new JMenuItem("Сохранить в JSON");
        saveJsonItem.addActionListener(e -> saveToFile(FileManager.FileFormat.JSON));

        JMenuItem saveParallelItem = new JMenuItem("Параллельное сохранение (JSON+XML)");
        saveParallelItem.addActionListener(e -> saveBothFormats());

        JMenuItem exitItem = new JMenuItem("Выход");
        exitItem.addActionListener(e -> System.exit(0));

        fileMenu.add(loadTxtItem);
        fileMenu.add(loadXmlItem);
        fileMenu.add(loadJsonItem);
        fileMenu.addSeparator();
        fileMenu.add(saveTxtItem);
        fileMenu.add(saveXmlItem);
        fileMenu.add(saveJsonItem);
        fileMenu.addSeparator();
        fileMenu.add(saveParallelItem);
        fileMenu.addSeparator();
        fileMenu.add(exitItem);

        JMenu editMenu = new JMenu("Правка");

        JMenuItem addItem = new JMenuItem("Добавить позицию");
        addItem.addActionListener(e -> showAddDialog());

        JMenuItem editItem = new JMenuItem("Редактировать");
        editItem.addActionListener(e -> showEditDialog());

        JMenuItem deleteItem = new JMenuItem("Удалить");
        deleteItem.addActionListener(e -> deleteSelectedItem());

        JMenuItem clearItem = new JMenuItem("Очистить всё");
        clearItem.addActionListener(e -> clearAll());

        editMenu.add(addItem);
        editMenu.add(editItem);
        editMenu.add(deleteItem);
        editMenu.addSeparator();
        editMenu.add(clearItem);

        JMenu sortMenu = new JMenu("Сортировка");

        JMenuItem sortByNameItem = new JMenuItem("По названию");
        sortByNameItem.addActionListener(e -> sortByName());

        JMenuItem sortByPriceItem = new JMenuItem("По цене");
        sortByPriceItem.addActionListener(e -> sortByPrice());

        JMenuItem sortByCaloriesItem = new JMenuItem("По калориям");
        sortByCaloriesItem.addActionListener(e -> sortByCalories());

        JMenuItem sortByDateItem = new JMenuItem("По дате");
        sortByDateItem.addActionListener(e -> sortByDate());

        sortMenu.add(sortByNameItem);
        sortMenu.add(sortByPriceItem);
        sortMenu.add(sortByCaloriesItem);
        sortMenu.add(sortByDateItem);

        menuBar.add(fileMenu);
        menuBar.add(editMenu);
        menuBar.add(sortMenu);

        setJMenuBar(menuBar);
    }

    private void createToolBar() {
        JToolBar toolBar = new JToolBar();
        toolBar.setFloatable(false);

        JButton addBtn = new JButton("➕ Добавить");
        addBtn.addActionListener(e -> showAddDialog());

        JButton editBtn = new JButton("✏️ Редактировать");
        editBtn.addActionListener(e -> showEditDialog());

        JButton deleteBtn = new JButton("🗑️ Удалить");
        deleteBtn.addActionListener(e -> deleteSelectedItem());

        JButton clearBtn = new JButton("🧹 Очистить");
        clearBtn.addActionListener(e -> clearAll());

        toolBar.add(addBtn);
        toolBar.add(editBtn);
        toolBar.add(deleteBtn);
        toolBar.addSeparator();
        toolBar.add(clearBtn);

        add(toolBar, BorderLayout.NORTH);
    }

    private void createMainPanel() {
        JPanel mainPanel = new JPanel(new BorderLayout(5, 5));

        tableModel = new DefaultTableModel(COLUMN_NAMES, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };

        table = new JTable(tableModel);
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        table.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if (!e.getValueIsAdjusting()) {
                    updateSelectionInfo();
                }
            }
        });

        JScrollPane tableScroll = new JScrollPane(table);
        tableScroll.setPreferredSize(new Dimension(800, 400));

        JPanel filterPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        filterPanel.setBorder(BorderFactory.createTitledBorder("Фильтры"));

        JLabel categoryLabel = new JLabel("Категория:");
        categoryComboBox = new JComboBox<>(new String[]{"Все", "Напитки", "Основные блюда", "Десерты"});
        categoryComboBox.addActionListener(e -> filterByCategory());

        JTextField searchField = new JTextField(20);
        searchField.setToolTipText("Поиск по названию");

        JButton searchBtn = new JButton("🔍 Поиск");
        searchBtn.addActionListener(e -> searchByName(searchField.getText()));

        filterPanel.add(categoryLabel);
        filterPanel.add(categoryComboBox);
        filterPanel.add(new JLabel("Поиск:"));
        filterPanel.add(searchField);
        filterPanel.add(searchBtn);

        mainPanel.add(filterPanel, BorderLayout.NORTH);
        mainPanel.add(tableScroll, BorderLayout.CENTER);

        add(mainPanel, BorderLayout.CENTER);
    }

    private void createLogPanel() {
        JPanel logPanel = new JPanel(new BorderLayout());
        logPanel.setBorder(BorderFactory.createTitledBorder("Лог действий"));
        logPanel.setPreferredSize(new Dimension(0, 150));

        logArea = new JTextArea();
        logArea.setEditable(false);
        logArea.setFont(new Font("Monospaced", Font.PLAIN, 12));

        JScrollPane logScroll = new JScrollPane(logArea);

        JButton clearLogBtn = new JButton("Очистить лог");
        clearLogBtn.addActionListener(e -> logArea.setText(""));

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(clearLogBtn);

        logPanel.add(logScroll, BorderLayout.CENTER);
        logPanel.add(buttonPanel, BorderLayout.SOUTH);

        add(logPanel, BorderLayout.SOUTH);
    }

    private void refreshTable() {
        tableModel.setRowCount(0);

        for (CafeMenuPosition item : menuRoll.GetAllElements()) {
            Object[] row = new Object[7];
            row[0] = item.getId();
            row[1] = item.getName();
            row[2] = item.getCategory();

            if (item instanceof Drink) {
                Drink drink = (Drink) item;
                row[5] = "Объем: " + drink.getVolume() + " мл, " +
                        (drink.isAlcoholic() ? "Алкогольный" : "Безалкогольный");
            } else if (item instanceof MainCourse) {
                MainCourse main = (MainCourse) item;
                row[5] = "Масса: " + main.getMass() + " г, " +
                        (main.isVegetarian() ? "Вегетарианское" : "Не вегетарианское");
            } else if (item instanceof Dessert) {
                Dessert dessert = (Dessert) item;
                row[5] = "Масса: " + dessert.getMass() + " г, " +
                        (dessert.isSweet() ? "Сладкий" : "Кислый");
            }

            row[3] = String.format("%.2f", item.getPrice());
            row[4] = String.format("%.1f", item.getCalories());
            row[6] = new SimpleDateFormat("dd.MM.yyyy").format(item.getAddedDate());

            tableModel.addRow(row);
        }

        updateStatusBar();
    }

    private void updateStatusBar() {
        int count = menuRoll.GetSize();
        logArea.append("В меню: " + count + " позиций\n");
    }

    private void updateSelectionInfo() {
        int selectedRow = table.getSelectedRow();
        if (selectedRow >= 0) {
            int id = (int) table.getValueAt(selectedRow, 0);
            String name = (String) table.getValueAt(selectedRow, 1);
            logArea.append("Выбрано: " + name + " (ID: " + id + ")\n");
        }
    }

    private void showAddDialog() {
        AddEditDialog dialog = new AddEditDialog(this, "Добавить позицию", null);
        dialog.setVisible(true);

        if (dialog.isConfirmed()) {
            CafeMenuPosition newItem = dialog.getPosition();
            if (newItem != null) {
                menuRoll.AddElement(newItem);
                refreshTable();
                logArea.append("Добавлено: " + newItem.getName() + "\n");
            }
        }
    }

    private void showEditDialog() {
        int selectedRow = table.getSelectedRow();
        if (selectedRow < 0) {
            JOptionPane.showMessageDialog(this, "Выберите позицию для редактирования",
                    "Внимание", JOptionPane.WARNING_MESSAGE);
            return;
        }

        int id = (int) table.getValueAt(selectedRow, 0);
        String category = (String) table.getValueAt(selectedRow, 2);

        CafeMenuPosition selected = menuRoll.GetElement(id, category);
        if (selected != null) {
            AddEditDialog dialog = new AddEditDialog(this, "Редактировать позицию", selected);
            dialog.setVisible(true);

            if (dialog.isConfirmed()) {
                CafeMenuPosition updated = dialog.getPosition();
                if (updated != null) {
                    menuRoll.ReplaceElement(updated);
                    refreshTable();
                    logArea.append("Обновлено: " + updated.getName() + "\n");
                }
            }
        }
    }

    private void deleteSelectedItem() {
        int selectedRow = table.getSelectedRow();
        if (selectedRow < 0) {
            JOptionPane.showMessageDialog(this, "Выберите позицию для удаления",
                    "Внимание", JOptionPane.WARNING_MESSAGE);
            return;
        }

        int id = (int) table.getValueAt(selectedRow, 0);
        String name = (String) table.getValueAt(selectedRow, 1);

        int confirm = JOptionPane.showConfirmDialog(this,
                "Удалить позицию \"" + name + "\"?",
                "Подтверждение удаления",
                JOptionPane.YES_NO_OPTION);

        if (confirm == JOptionPane.YES_OPTION) {
            String category = (String) table.getValueAt(selectedRow, 2);
            CafeMenuPosition toDelete = menuRoll.GetElement(id, category);

            if (toDelete != null && menuRoll.DeleteElement(toDelete)) {
                refreshTable();
                logArea.append("Удалено: " + name + "\n");
            }
        }
    }

    private void clearAll() {
        int confirm = JOptionPane.showConfirmDialog(this,
                "Очистить всё меню? Это действие нельзя отменить.",
                "Подтверждение очистки",
                JOptionPane.YES_NO_OPTION);

        if (confirm == JOptionPane.YES_OPTION) {
            menuRoll.Clear();
            refreshTable();
            logArea.append("Меню очищено\n");
        }
    }

    private void sortByName() {
        menuRoll.sort(Comparator.comparing(CafeMenuPosition::getName));
        refreshTable();
        logArea.append("Отсортировано по названию\n");
    }

    private void sortByPrice() {
        menuRoll.sort(Comparator.comparingDouble(CafeMenuPosition::getPrice));
        refreshTable();
        logArea.append("Отсортировано по цене\n");
    }

    private void sortByCalories() {
        menuRoll.sort(Comparator.comparingDouble(CafeMenuPosition::getCalories));
        refreshTable();
        logArea.append("Отсортировано по калориям\n");
    }

    private void sortByDate() {
        menuRoll.sort(Comparator.comparing(CafeMenuPosition::getAddedDate));
        refreshTable();
        logArea.append("Отсортировано по дате\n");
    }

    private void filterByCategory() {
        String selected = (String) categoryComboBox.getSelectedItem();
        if ("Все".equals(selected)) {
            refreshTable();
        } else {
            tableModel.setRowCount(0);
            for (CafeMenuPosition item : menuRoll.GetAllElements()) {
                if (item.getCategory().equals(selected)) {
                    addItemToTable(item);
                }
            }
        }
    }

    private void searchByName(String query) {
        if (query == null || query.trim().isEmpty()) {
            refreshTable();
            return;
        }

        tableModel.setRowCount(0);
        String searchQuery = query.toLowerCase();

        for (CafeMenuPosition item : menuRoll.GetAllElements()) {
            if (item.getName().toLowerCase().contains(searchQuery)) {
                addItemToTable(item);
            }
        }

        logArea.append("Поиск: найдено " + tableModel.getRowCount() + " позиций\n");
    }

    private void addItemToTable(CafeMenuPosition item) {
        Object[] row = new Object[7];
        row[0] = item.getId();
        row[1] = item.getName();
        row[2] = item.getCategory();

        if (item instanceof Drink) {
            Drink drink = (Drink) item;
            row[5] = "Объем: " + drink.getVolume() + " мл, " +
                    (drink.isAlcoholic() ? "Алкогольный" : "Безалкогольный");
        } else if (item instanceof MainCourse) {
            MainCourse main = (MainCourse) item;
            row[5] = "Масса: " + main.getMass() + " г, " +
                    (main.isVegetarian() ? "Вегетарианское" : "Не вегетарианское");
        } else if (item instanceof Dessert) {
            Dessert dessert = (Dessert) item;
            row[5] = "Масса: " + dessert.getMass() + " г, " +
                    (dessert.isSweet() ? "Сладкий" : "Кислый");
        }

        row[3] = String.format("%.2f", item.getPrice());
        row[4] = String.format("%.1f", item.getCalories());
        row[6] = new SimpleDateFormat("dd.MM.yyyy").format(item.getAddedDate());

        tableModel.addRow(row);
    }

    private void loadFromFile(FileManager.FileFormat format) {
        if (menuRoll.GetSize() > 0) {
            int confirm = JOptionPane.showConfirmDialog(this,
                    "Текущее меню будет очищено. Продолжить?",
                    "Подтверждение",
                    JOptionPane.YES_NO_OPTION);

            if (confirm != JOptionPane.YES_OPTION) {
                return;
            }
        }

        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Загрузить из " + format);

        int result = fileChooser.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            String filename = fileChooser.getSelectedFile().getPath();

            Thread loadThread = new Thread(() -> {
                long startTime = System.currentTimeMillis();

                SwingUtilities.invokeLater(() -> {
                    logArea.append("Начало загрузки из " + format + "...\n");
                });

                try {
                    List<CafeMenuPosition> loaded = FileManager.readFromFile(
                            filename, format,
                            FileManager.Compression.NONE,
                            FileManager.Encryption.NONE
                    );

                    long endTime = System.currentTimeMillis();

                    SwingUtilities.invokeLater(() -> {
                        menuRoll.Clear();
                        for (CafeMenuPosition item : loaded) {
                            menuRoll.AddElement(item);
                        }
                        refreshTable();
                        logArea.append("Загружено " + loaded.size() + " позиций из " +
                                format + " за " + (endTime - startTime) + " мс\n");
                    });

                } catch (Exception e) {
                    SwingUtilities.invokeLater(() -> {
                        logArea.append("Ошибка загрузки: " + e.getMessage() + "\n");
                        JOptionPane.showMessageDialog(MainWindow.this,
                                "Ошибка загрузки: " + e.getMessage(),
                                "Ошибка", JOptionPane.ERROR_MESSAGE);
                    });
                }
            });

            loadThread.start();
        }
    }

    private void saveToFile(FileManager.FileFormat format) {
        if (menuRoll.GetSize() == 0) {
            JOptionPane.showMessageDialog(this, "Меню пусто. Нечего сохранять.",
                    "Внимание", JOptionPane.WARNING_MESSAGE);
            return;
        }

        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Сохранить в " + format);

        int result = fileChooser.showSaveDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            String filename = fileChooser.getSelectedFile().getPath();

            Thread saveThread = new Thread(() -> {
                long startTime = System.currentTimeMillis();

                SwingUtilities.invokeLater(() -> {
                    logArea.append("Начало сохранения в " + format + "...\n");
                });

                try {
                    List<CafeMenuPosition> positions = menuRoll.GetAllElements();

                    FileManager.writeToFile(
                            filename, positions, format,
                            FileManager.Compression.NONE,
                            FileManager.Encryption.NONE
                    );

                    long endTime = System.currentTimeMillis();

                    SwingUtilities.invokeLater(() -> {
                        logArea.append("Сохранено " + positions.size() + " позиций в " +
                                format + " за " + (endTime - startTime) + " мс\n");
                        JOptionPane.showMessageDialog(MainWindow.this,
                                "Сохранено успешно!",
                                "Сохранение", JOptionPane.INFORMATION_MESSAGE);
                    });

                } catch (Exception e) {
                    SwingUtilities.invokeLater(() -> {
                        logArea.append("Ошибка сохранения: " + e.getMessage() + "\n");
                        JOptionPane.showMessageDialog(MainWindow.this,
                                "Ошибка сохранения: " + e.getMessage(),
                                "Ошибка", JOptionPane.ERROR_MESSAGE);
                    });
                }
            });

            saveThread.start();
        }
    }

    private void saveBothFormats() {
        if (menuRoll.GetSize() == 0) {
            JOptionPane.showMessageDialog(this, "Меню пусто. Нечего сохранять.",
                    "Внимание", JOptionPane.WARNING_MESSAGE);
            return;
        }

        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Сохранить в JSON и XML");
        fileChooser.setSelectedFile(new java.io.File("menu"));

        int result = fileChooser.showSaveDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            String filePath = fileChooser.getSelectedFile().getPath();

            if (filePath.endsWith(".json") || filePath.endsWith(".xml")) {
                filePath = filePath.substring(0, filePath.lastIndexOf('.'));
            }

            final String jsonFilename = filePath + ".json";
            final String xmlFilename = filePath + ".xml";
            final List<CafeMenuPosition> positionsCopy = new ArrayList<>(menuRoll.GetAllElements());

            logArea.append("Параллельное сохранение в JSON и XML...\n");

            Thread jsonThread = new Thread(() -> {
                saveInParallel(jsonFilename, positionsCopy, FileManager.FileFormat.JSON);
            });

            Thread xmlThread = new Thread(() -> {
                saveInParallel(xmlFilename, positionsCopy, FileManager.FileFormat.XML);
            });

            jsonThread.start();
            xmlThread.start();

            Thread monitorThread = new Thread(() -> {
                try {
                    jsonThread.join();
                    xmlThread.join();
                    SwingUtilities.invokeLater(() -> {
                        logArea.append("Оба потока завершили сохранение\n");
                    });
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
            monitorThread.start();
        }
    }

    private void saveInParallel(String filename, List<CafeMenuPosition> positions, FileManager.FileFormat format) {
        long startTime = System.currentTimeMillis();
        String formatName = format.toString();

        SwingUtilities.invokeLater(() -> {
            logArea.append("Поток " + Thread.currentThread().getId() +
                    ": начало сохранения в " + formatName + "...\n");
        });

        try {
            Thread.sleep(100);

            FileManager.writeToFile(
                    filename, positions, format,
                    FileManager.Compression.NONE,
                    FileManager.Encryption.NONE
            );

            long endTime = System.currentTimeMillis();

            SwingUtilities.invokeLater(() -> {
                logArea.append("Поток " + Thread.currentThread().getId() +
                        ": " + formatName + " сохранен за " +
                        (endTime - startTime) + " мс\n");
            });

        } catch (Exception e) {
            SwingUtilities.invokeLater(() -> {
                logArea.append("Поток " + Thread.currentThread().getId() +
                        ": ошибка сохранения " + formatName + ": " +
                        e.getMessage() + "\n");
            });
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            try {
                UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            } catch (Exception e) {
                e.printStackTrace();
            }
            new MainWindow();
        });
    }
}