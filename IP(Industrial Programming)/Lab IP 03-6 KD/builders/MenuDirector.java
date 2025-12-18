package builders;

import cafe_menu.CafeMenuPosition;

public class MenuDirector {

    public CafeMenuPosition fromFileString(String fileString) {
        if (fileString.startsWith("DRINK;")) {
            String[] parts = fileString.split(";");
            return new DrinkBuilder()
                    .setId(Integer.parseInt(parts[1]))
                    .setName(parts[2])
                    .setPrice(Double.parseDouble(parts[3].replace(',', '.')))
                    .setCategory(parts[4])
                    .setCalories(Double.parseDouble(parts[5].replace(',', '.')))
                    .setVolume(Integer.parseInt(parts[7]))
                    .setAlcoholic(Boolean.parseBoolean(parts[8]))
                    .setAddedDate(parts[6])
                    .build();
        } else if (fileString.startsWith("MAIN_COURSE;")) {
            String[] parts = fileString.split(";");
            return new MainCourseBuilder()
                    .setId(Integer.parseInt(parts[1]))
                    .setName(parts[2])
                    .setPrice(Double.parseDouble(parts[3].replace(',', '.')))
                    .setCategory(parts[4])
                    .setCalories(Double.parseDouble(parts[5].replace(',', '.')))
                    .setMass(Integer.parseInt(parts[7]))
                    .setVegetarian(Boolean.parseBoolean(parts[8]))
                    .setAddedDate(parts[6])
                    .build();
        } else if (fileString.startsWith("DESSERT;")) {
            String[] parts = fileString.split(";");
            return new DessertBuilder()
                    .setId(Integer.parseInt(parts[1]))
                    .setName(parts[2])
                    .setPrice(Double.parseDouble(parts[3].replace(',', '.')))
                    .setCategory(parts[4])
                    .setCalories(Double.parseDouble(parts[5].replace(',', '.')))
                    .setMass(Integer.parseInt(parts[7]))
                    .setSweet(Boolean.parseBoolean(parts[8]))
                    .setAddedDate(parts[6])
                    .build();
        }
        throw new IllegalArgumentException("Unknown menu position type: " + fileString);
    }
}