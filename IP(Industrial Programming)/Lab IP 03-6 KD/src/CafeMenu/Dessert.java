package CafeMenu;

public class Dessert extends CafeMenuPosition{

    public int getMass() {
        return mass;
    }

    public boolean isSweet() {
        return sweet;
    }

    public void setSweet(boolean sweet) {
        this.sweet = sweet;
    }

    public void setMass(int mass) {
        this.mass = mass;
    }

    private int mass;
    private boolean sweet;

    public Dessert(int ID, String NAME, double PRICE, String CATEGORY, double CALORIES, int MASS, boolean SWEET) {
        super(ID, NAME, PRICE, CATEGORY, CALORIES);
        this.mass= MASS;
        this.sweet = SWEET;
    }

    @Override
    public String toString(){
        return String.format(
                super.toString() + "Масса: %d мл.\n", mass,
                isSweet() ? "Сладкий" : "Кислый"
        );
    }

    public void getInfo(){
        System.out.println("\"ID: " + getId());
        System.out.println("Название: " + getName());
        System.out.println("Категория: " +  getCategory());
        System.out.println(isSweet() ? "Сладкий" : "Кислый");
        System.out.println("Цена: " + getPrice());
        System.out.println("Масса" + getMass());
        System.out.println("Калории: " + getCalories());
        System.out.println("Дата добавления: " + getAddedDate());
    }

    @Override
    String getDishType() {
        return (isSweet() ? "Сладкий" : "Кислый") + " десерт ";
    }
}
