package cafe_menu;

public class MainCourse extends CafeMenuPosition{

    public int getMass() {
        return mass;
    }

    public boolean isVegetarian() {
        return vegetarian;
    }

    public void setMass(int mass) {
        this.mass = mass;
    }

    public void setVegetarian(boolean vegetarian) {
        this.vegetarian = vegetarian;
    }

    private int mass;
    private boolean vegetarian;

    public MainCourse(int ID, String NAME, double PRICE, String CATEGORY, double CALORIES, int MASS, boolean VEGETARIAN) {
        super(ID, NAME, PRICE, CATEGORY, CALORIES);
        this.mass = MASS;
        this.vegetarian = VEGETARIAN;
    }

    @Override
    public String toString(){
        return String.format(
                super.toString() + "Масса: %d мл.\n", mass,
                isVegetarian() ? "Вегетарианский" : "Не вегетарианский"
        );
    }

    public void getInfo(){
        System.out.println("\"ID: " + getId());
        System.out.println("Название: " + getName());
        System.out.println("Категория: " +  getCategory());
        System.out.println(isVegetarian() ? "Вегетарианский" : "Не вегетарианский");
        System.out.println("Цена: " + getPrice());
        System.out.println("Масса" + getMass());
        System.out.println("Калории: " + getCalories());
        System.out.println("Дата добавления: " + getAddedDate());
    }

    @Override
    String getDishType() {
        return (isVegetarian() ? "Вегетарианское" : "Не вегетарианское" + " блюдо ");
    }

}

