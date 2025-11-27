package rolls;

import CafeMenu.CafeMenuPosition;

import java.util.*;
import java.util.stream.Collectors;

public class MapRoll<T extends CafeMenuPosition> extends Rolls<T> {
    private Map<Integer, T> Positions;

    public MapRoll() {
        this.Positions = new LinkedHashMap<>();
    }

    @Override
    public void AddElement(T elem) {
        if (elem != null && !ContainID(elem)) {
            Positions.put(elem.getId(), elem);
            System.out.println("Successfully added.\n");
        } else {
            System.out.println("Already added.\n");
        }
    }

    @Override
    public boolean DeleteElement(T elem) {
        if (elem != null && Positions.containsKey(elem.getId())) {
            Positions.remove(elem.getId());
            return true;
        }
        return false;
    }

    @Override
    public void ReplaceElement(T elem) {
        if (elem != null && ContainID(elem)) {
            Positions.put(elem.getId(), elem);
            System.out.println("Successfully replaced.\n");
        } else {
            System.out.println("Element not found for replacement.\n");
        }
    }

    @Override
    protected boolean ContainID(T elem) {
        return Positions.containsKey(elem.getId());
    }

    @Override
    public T GetElement(int ID, String CATEGORY) {
        T element = Positions.get(ID);
        if (element != null && element.getCategory().equals(CATEGORY)) {
            return element;
        }
        return null;
    }

    @Override
    public List<T> GetAllElements() {
        return new ArrayList<>(Positions.values());
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
        int i = 1;
        for (T position : Positions.values()) {
            System.out.println((i++) + ". " + position);
        }
    }

    @Override
    public void sort(Comparator<T> comparator) {
        List<T> sortedList = Positions.values()
                .stream()
                .sorted(comparator)
                .collect(Collectors.toList());

        Positions.clear();
        for (T item : sortedList) {
            Positions.put(item.getId(), item);
        }
    }
}
