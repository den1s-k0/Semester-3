import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class CurrencyConverter extends JFrame {
    private final Properties exchangeRates = new Properties();
    private JComboBox<String> fromCurrencyComboBox;
    private JComboBox<String> toCurrencyComboBox;
    private JTextField amountTextField;
    private JButton convertButton;
    private JLabel resultLabel;
    private final ExecutorService executorService = Executors.newSingleThreadExecutor();

    private static final String[] CURRENCIES = {"USD", "EUR", "RUB"};

    public CurrencyConverter() {
        setTitle("Конвертер валют");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 250);
        setLocationRelativeTo(null);

        loadExchangeRates();
        initUI();
    }

    private void loadExchangeRates() {
        InputStream input = null;
        try {
            File projectDir = new File(".").getAbsoluteFile().getParentFile();
            if (projectDir != null) {
                File file = new File(projectDir, "rates.properties");
                if (file.exists()) {
                    input = new FileInputStream(file);
                    System.out.println("Файл найден: " + file.getAbsolutePath());
                }
            }
            exchangeRates.load(input);
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Ошибка загрузки курсов валют: " + e.getMessage(),
                    "Ошибка", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void initUI() {
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;

        gbc.gridx = 0;
        gbc.gridy = 0;
        add(new JLabel("Введите сумму для конвертации:"), gbc);

        gbc.gridx = 1;
        amountTextField = new JTextField(10);
        add(amountTextField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        add(new JLabel("Конвертировать из валюты:"), gbc);

        gbc.gridx = 1;
        fromCurrencyComboBox = new JComboBox<>(CURRENCIES);
        add(fromCurrencyComboBox, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        add(new JLabel("Конвертировать в валюту:"), gbc);

        gbc.gridx = 1;
        toCurrencyComboBox = new JComboBox<>(CURRENCIES);
        toCurrencyComboBox.setSelectedIndex(1);
        add(toCurrencyComboBox, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 2;
        convertButton = new JButton("Конвертировать");
        add(convertButton, gbc);

        gbc.gridy = 4;
        resultLabel = new JLabel("Результат: ");
        resultLabel.setFont(new Font("Arial", Font.BOLD, 14));
        resultLabel.setHorizontalAlignment(SwingConstants.CENTER);
        add(resultLabel, gbc);

        convertButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                convertCurrency();
            }
        });
    }

    private void convertCurrency() {
        String fromCurrency = (String) fromCurrencyComboBox.getSelectedItem();
        String toCurrency = (String) toCurrencyComboBox.getSelectedItem();
        String amountText = amountTextField.getText().trim();

        if (amountText.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Введите сумму для конвертации",
                    "Ошибка", JOptionPane.WARNING_MESSAGE);
            return;
        }

        double amount;
        try {
            amount = Double.parseDouble(amountText);
            if (amount <= 0) {
                JOptionPane.showMessageDialog(this, "Сумма должна быть больше 0",
                        "Ошибка", JOptionPane.WARNING_MESSAGE);
                return;
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Введите корректное число",
                    "Ошибка", JOptionPane.WARNING_MESSAGE);
            return;
        }

        if (fromCurrency.equals(toCurrency)) {
            resultLabel.setText(String.format("Результат: %.2f %s", amount, toCurrency));
            return;
        }

        convertButton.setEnabled(false);
        resultLabel.setText("Конвертация...");

        executorService.submit(new ConversionTask(fromCurrency, toCurrency, amount));
    }

    private class ConversionTask implements Runnable {
        private final String fromCurrency;
        private final String toCurrency;
        private final double amount;

        public ConversionTask(String fromCurrency, String toCurrency, double amount) {
            this.fromCurrency = fromCurrency;
            this.toCurrency = toCurrency;
            this.amount = amount;
        }

        @Override
        public void run() {
            try {
                Thread.sleep(1000);

                double result = performConversion(fromCurrency, toCurrency, amount);

                SwingUtilities.invokeLater(() -> {
                    resultLabel.setText(String.format("Результат: %.2f %s", result, toCurrency));
                    convertButton.setEnabled(true);
                });

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                SwingUtilities.invokeLater(() -> {
                    resultLabel.setText("Ошибка: операция прервана");
                    convertButton.setEnabled(true);
                });
            } catch (Exception e) {
                SwingUtilities.invokeLater(() -> {
                    resultLabel.setText("Ошибка конвертации");
                    convertButton.setEnabled(true);
                    JOptionPane.showMessageDialog(CurrencyConverter.this,
                            "Курс для конвертации " + fromCurrency + " -> " + toCurrency + " не найден",
                            "Ошибка", JOptionPane.ERROR_MESSAGE);
                });
            }
        }

        private double performConversion(String from, String to, double amount) {
            Double rate = findConversionRate(from, to);

            if (rate != null) {
                return amount * rate;
            }

            throw new IllegalArgumentException("Курс для конвертации " + from + " -> " + to + " не найден");
        }

        private Double findConversionRate(String from, String to) {
            String directKey = from + "_TO_" + to;
            if (exchangeRates.containsKey(directKey)) {
                return Double.parseDouble(exchangeRates.getProperty(directKey));
            }

            String reverseKey = to + "_TO_" + from;
            if (exchangeRates.containsKey(reverseKey)) {
                return 1.0 / Double.parseDouble(exchangeRates.getProperty(reverseKey));
            }

            for (String intermediate : CURRENCIES) {
                if (!intermediate.equals(from) && !intermediate.equals(to)) {
                    Double rate1 = findDirectOrReverseRate(from, intermediate);
                    Double rate2 = findDirectOrReverseRate(intermediate, to);

                    if (rate1 != null && rate2 != null) {
                        return rate1 * rate2;
                    }
                }
            }

            return null;
        }

        private Double findDirectOrReverseRate(String from, String to) {
            String directKey = from + "_TO_" + to;
            if (exchangeRates.containsKey(directKey)) {
                return Double.parseDouble(exchangeRates.getProperty(directKey));
            }

            String reverseKey = to + "_TO_" + from;
            if (exchangeRates.containsKey(reverseKey)) {
                return 1.0 / Double.parseDouble(exchangeRates.getProperty(reverseKey));
            }

            return null;
        }
    }

    @Override
    public void dispose() {
        executorService.shutdown();
        super.dispose();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            CurrencyConverter converter = new CurrencyConverter();
            converter.setVisible(true);
        });
    }
}