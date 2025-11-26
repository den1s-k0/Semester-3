package rolls;

import CafeMenu.CafeMenuPosition;

import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class MapRoll<T extends CafeMenuPosition> extends Rolls{
    private Map<String, T> Positions;

    public MapRoll() {
        this.Positions = new LinkedHashMap<>();
    }

    @Override
    public void AddElement(CafeMenuPosition elem) {

    }

    @Override
    public boolean DeleteElement(CafeMenuPosition elem) {
        return false;
    }

    @Override
    public void ReplaceElement(CafeMenuPosition elem) {

    }

    @Override
    protected boolean ContainID(CafeMenuPosition elem) {
        return false;
    }

    @Override
    public CafeMenuPosition GetElement(int ID, String CATEGORY) {
        return null;
    }

    @Override
    public List GetAllElements() {
        return List.of();
    }

    @Override
    public int GetSize() {
        return 0;
    }

    @Override
    public void Clear() {

    }

    @Override
    public void PrintList() {

    }

    @Override
    public void sort(Comparator comparator) {

    }
}
