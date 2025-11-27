package cafe_menu;

public class Drink extends CafeMenuPosition{

    public int getVolume() {
        return volume;
    }

    public boolean isAlcoholic() {
        return alcoholic;
    }

    public void setVolume(int volume) {
        this.volume = volume;
    }

    public void setAlcoholic(boolean alcoholic) {
        this.alcoholic = alcoholic;
    }

    private int volume;
    private boolean alcoholic;

    public Drink(int ID, String NAME, double PRICE, String CATEGORY, double CALORIES, int VOLUME, boolean ALCOHOLIC) {
        super(ID, NAME, PRICE, CATEGORY, CALORIES);
        this.volume = VOLUME;
        this.alcoholic = ALCOHOLIC;
    }

    @Override
    public String toString(){
        return String.format(
           super.toString() + "Объем: %d мл.\n", volume,
                isAlcoholic() ? "Алкогольный" : "Безалкогольный"
        );
    }

    public void getInfo(){
        System.out.println("\"ID: " + getId());
        System.out.println("Название: " + getName());
        System.out.println("Категория: " +  getCategory());
        System.out.println(isAlcoholic() ? "Алкогольный" : "Безалкогольный");
        System.out.println("Цена: " + getPrice());
        System.out.println("Объем" + volume);
        System.out.println("Калории: " + getCalories());
        System.out.println("Дата добавления: " + getAddedDate());
    }

    @Override
    String getDishType() {
        return (isAlcoholic() ? "Алкогольный" : "Безалкогольный") + " напиток ";
    }
}
