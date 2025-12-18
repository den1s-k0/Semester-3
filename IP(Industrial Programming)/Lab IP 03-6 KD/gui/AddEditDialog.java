package gui;

import cafe_menu.*;
import builders.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class AddEditDialog extends JDialog {
    private CafeMenuPosition position;
    private boolean confirmed = false;

    private JTextField idField;
    private JTextField nameField;
    private JTextField priceField;
    private JTextField caloriesField;
    private JComboBox<String> categoryCombo;

    private JPanel drinkPanel;
    private JTextField volumeField;
    private JCheckBox alcoholicCheck;

    private JPanel mainCoursePanel;
    private JTextField massField1;
    private JCheckBox vegetarianCheck;

    private JPanel dessertPanel;
    private JTextField massField2;
    private JCheckBox sweetCheck;

    private CardLayout cardLayout;
    private JPanel typeSpecificPanel;

    public AddEditDialog(JFrame parent, String title, CafeMenuPosition existingPosition) {
        super(parent, title, true);
        this.position = existingPosition;

        setupDialog();
        createComponents();
        if (existingPosition != null) {
            loadExistingData();
        }

        pack();
        setLocationRelativeTo(parent);
    }

    private void setupDialog() {
        setLayout(new BorderLayout(10, 10));
        setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
        setResizable(false);
    }

    private void createComponents() {
        JPanel mainPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(5, 5, 5, 5);

        gbc.gridx = 0; gbc.gridy = 0;
        mainPanel.add(new JLabel("ID:"), gbc);

        idField = new JTextField(10);
        if (position == null) {
            idField.setText(String.valueOf(generateId()));
        }
        gbc.gridx = 1;
        mainPanel.add(idField, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        mainPanel.add(new JLabel("Название:"), gbc);

        nameField = new JTextField(20);
        gbc.gridx = 1;
        mainPanel.add(nameField, gbc);

        gbc.gridx = 0; gbc.gridy = 2;
        mainPanel.add(new JLabel("Категория:"), gbc);

        categoryCombo = new JComboBox<>(new String[]{"Напитки", "Основные блюда", "Десерты"});
        categoryCombo.addActionListener(e -> updateTypeSpecificPanel());
        gbc.gridx = 1;
        mainPanel.add(categoryCombo, gbc);

        gbc.gridx = 0; gbc.gridy = 3;
        mainPanel.add(new JLabel("Цена:"), gbc);

        priceField = new JTextField(10);
        gbc.gridx = 1;
        mainPanel.add(priceField, gbc);

        gbc.gridx = 0; gbc.gridy = 4;
        mainPanel.add(new JLabel("Калории:"), gbc);

        caloriesField = new JTextField(10);
        gbc.gridx = 1;
        mainPanel.add(caloriesField, gbc);

        cardLayout = new CardLayout();
        typeSpecificPanel = new JPanel(cardLayout);

        createDrinkPanel();
        createMainCoursePanel();
        createDessertPanel();

        typeSpecificPanel.add(drinkPanel, "Напитки");
        typeSpecificPanel.add(mainCoursePanel, "Основные блюда");
        typeSpecificPanel.add(dessertPanel, "Десерты");

        gbc.gridx = 0; gbc.gridy = 5;
        gbc.gridwidth = 2;
        mainPanel.add(typeSpecificPanel, gbc);
        gbc.gridwidth = 1;

        add(mainPanel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        JButton okButton = new JButton("OK");
        JButton cancelButton = new JButton("Отмена");

        okButton.addActionListener(e -> {
            if (validateAndCreate()) {
                confirmed = true;
                dispose();
            }
        });

        cancelButton.addActionListener(e -> dispose());

        buttonPanel.add(okButton);
        buttonPanel.add(cancelButton);

        add(buttonPanel, BorderLayout.SOUTH);
    }

    private void createDrinkPanel() {
        drinkPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(2, 2, 2, 2);

        gbc.gridx = 0; gbc.gridy = 0;
        drinkPanel.add(new JLabel("Объем (мл):"), gbc);

        volumeField = new JTextField(10);
        volumeField.setText("200");
        gbc.gridx = 1;
        drinkPanel.add(volumeField, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        alcoholicCheck = new JCheckBox("Алкогольный");
        gbc.gridwidth = 2;
        drinkPanel.add(alcoholicCheck, gbc);
    }

    private void createMainCoursePanel() {
        mainCoursePanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(2, 2, 2, 2);

        gbc.gridx = 0; gbc.gridy = 0;
        mainCoursePanel.add(new JLabel("Масса (г):"), gbc);

        massField1 = new JTextField(10);
        massField1.setText("300");
        gbc.gridx = 1;
        mainCoursePanel.add(massField1, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        vegetarianCheck = new JCheckBox("Вегетарианское");
        gbc.gridwidth = 2;
        mainCoursePanel.add(vegetarianCheck, gbc);
    }

    private void createDessertPanel() {
        dessertPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(2, 2, 2, 2);

        gbc.gridx = 0; gbc.gridy = 0;
        dessertPanel.add(new JLabel("Масса (г):"), gbc);

        massField2 = new JTextField(10);
        massField2.setText("150");
        gbc.gridx = 1;
        dessertPanel.add(massField2, gbc);

        gbc.gridx = 0; gbc.gridy = 1;
        sweetCheck = new JCheckBox("Сладкий");
        gbc.gridwidth = 2;
        dessertPanel.add(sweetCheck, gbc);
    }

    private void updateTypeSpecificPanel() {
        String selected = (String) categoryCombo.getSelectedItem();
        cardLayout.show(typeSpecificPanel, selected);
    }

    private void loadExistingData() {
        idField.setText(String.valueOf(position.getId()));
        nameField.setText(position.getName());
        categoryCombo.setSelectedItem(position.getCategory());
        priceField.setText(String.valueOf(position.getPrice()));
        caloriesField.setText(String.valueOf(position.getCalories()));

        String category = position.getCategory();
        if (position instanceof Drink) {
            Drink drink = (Drink) position;
            volumeField.setText(String.valueOf(drink.getVolume()));
            alcoholicCheck.setSelected(drink.isAlcoholic());
        } else if (position instanceof MainCourse) {
            MainCourse main = (MainCourse) position;
            massField1.setText(String.valueOf(main.getMass()));
            vegetarianCheck.setSelected(main.isVegetarian());
        } else if (position instanceof Dessert) {
            Dessert dessert = (Dessert) position;
            massField2.setText(String.valueOf(dessert.getMass()));
            sweetCheck.setSelected(dessert.isSweet());
        }

        updateTypeSpecificPanel();
    }

    private boolean validateAndCreate() {
        try {
            int id = Integer.parseInt(idField.getText().trim());
            String name = nameField.getText().trim();
            double price = Double.parseDouble(priceField.getText().trim());
            double calories = Double.parseDouble(caloriesField.getText().trim());
            String category = (String) categoryCombo.getSelectedItem();

            if (id <= 0) {
                showError("ID должен быть положительным числом");
                return false;
            }

            if (name.isEmpty()) {
                showError("Название не может быть пустым");
                return false;
            }

            if (price < 0) {
                showError("Цена не может быть отрицательной");
                return false;
            }

            if (calories < 0) {
                showError("Калории не могут быть отрицательными");
                return false;
            }

            switch (category) {
                case "Напитки":
                    int volume = Integer.parseInt(volumeField.getText().trim());
                    boolean alcoholic = alcoholicCheck.isSelected();
                    if (volume <= 0) {
                        showError("Объем должен быть положительным");
                        return false;
                    }
                    position = new DrinkBuilder()
                            .setId(id)
                            .setName(name)
                            .setPrice(price)
                            .setCategory(category)
                            .setCalories(calories)
                            .setVolume(volume)
                            .setAlcoholic(alcoholic)
                            .build();
                    break;

                case "Основные блюда":
                    int mass1 = Integer.parseInt(massField1.getText().trim());
                    boolean vegetarian = vegetarianCheck.isSelected();
                    if (mass1 <= 0) {
                        showError("Масса должна быть положительной");
                        return false;
                    }
                    position = new MainCourseBuilder()
                            .setId(id)
                            .setName(name)
                            .setPrice(price)
                            .setCategory(category)
                            .setCalories(calories)
                            .setMass(mass1)
                            .setVegetarian(vegetarian)
                            .build();
                    break;

                case "Десерты":
                    int mass2 = Integer.parseInt(massField2.getText().trim());
                    boolean sweet = sweetCheck.isSelected();
                    if (mass2 <= 0) {
                        showError("Масса должна быть положительной");
                        return false;
                    }
                    position = new DessertBuilder()
                            .setId(id)
                            .setName(name)
                            .setPrice(price)
                            .setCategory(category)
                            .setCalories(calories)
                            .setMass(mass2)
                            .setSweet(sweet)
                            .build();
                    break;
            }

            return true;

        } catch (NumberFormatException e) {
            showError("Неверный числовой формат");
            return false;
        } catch (IllegalArgumentException e) {
            showError(e.getMessage());
            return false;
        }
    }

    private void showError(String message) {
        JOptionPane.showMessageDialog(this, message, "Ошибка", JOptionPane.ERROR_MESSAGE);
    }

    private int generateId() {
        return (int) (System.currentTimeMillis() % 10000);
    }

    public boolean isConfirmed() {
        return confirmed;
    }

    public CafeMenuPosition getPosition() {
        return position;
    }
}