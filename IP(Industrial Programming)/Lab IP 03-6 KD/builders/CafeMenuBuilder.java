package builders;

import cafe_menu.CafeMenuPosition;

public interface CafeMenuBuilder {
    CafeMenuBuilder setId(int id);
    CafeMenuBuilder setName(String name);
    CafeMenuBuilder setPrice(double price);
    CafeMenuBuilder setCategory(String category);
    CafeMenuBuilder setCalories(double calories);
    CafeMenuPosition build();
}