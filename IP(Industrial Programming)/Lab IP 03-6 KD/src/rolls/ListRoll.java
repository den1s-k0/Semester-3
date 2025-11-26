package rolls;

import CafeMenu.CafeMenuPosition;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class ListRoll<T extends CafeMenuPosition> extends Rolls<T>{
    private List<T> Positions;

    public ListRoll(){
        this.Positions = new ArrayList<>();
    }

    @Override
    public void AddElement(T elem) {
        if (elem != null && !ContainID(elem)) {
            Positions.add(elem);
            System.out.println("Successfully added.\n");
        }
        else
            System.out.println("Already added.\n");
    }

    @Override
    public boolean DeleteElement(T elem) {
            return Positions.removeIf(obj -> obj.getId() == elem.getId() &&
                    obj.getCategory().equals(elem.getCategory()));
    }

    @Override
    public void ReplaceElement(T elem) {
        if (elem != null && !ContainID(elem)) {
            Positions.add(elem);
            System.out.println("Successfully added.\n");
        }
        else
            System.out.println("Already added.\n");
    }

    @Override
    protected boolean ContainID(T elem){
        return Positions.stream().anyMatch(obj -> obj.getId() == elem.getId() &&
                obj.getCategory().equals(elem.getCategory()));
    }


    @Override
    public T GetElement(int ID, String CATEGORY) {
        return Positions.stream()
                .filter(obj -> obj.getId() == ID &&
                        obj.getCategory().equals(CATEGORY))
                .findFirst()
                .orElse(null);
    }

    @Override
    public List<T> GetAllElements() {
        return new ArrayList<>(Positions);
    }

    @Override
    public int GetSize() {
        return Positions.size();
    }

    @Override
    public void Clear() {
        Positions.clear();
    }

    @Override
    public void PrintList() {
        if (Positions.isEmpty()) {
            System.out.println("Список пуст.");
            return;
        }
        System.out.println("Список позиций:");
        for (int i = 0; i < Positions.size(); i++) {
            System.out.println((i + 1) + ". " + Positions.get(i));
        }
    }

    @Override
    public void sort(Comparator<T> comparator) {
        Positions.sort(comparator);
    }
}
