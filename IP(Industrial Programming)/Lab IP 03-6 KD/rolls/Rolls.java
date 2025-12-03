package rolls;

import cafe_menu.CafeMenuPosition;

import java.util.Comparator;
import java.util.List;

public abstract class Rolls<T extends CafeMenuPosition> {
    public abstract void AddElement(T elem);

    public abstract boolean DeleteElement(T elem);

    public abstract void ReplaceElement(T elem);

    protected abstract boolean ContainID(T elem);

    public abstract T GetElement(int ID, String CATEGORY);

    public abstract List<T> GetAllElements();

    public abstract int GetSize();

    public abstract void Clear();

    public abstract void PrintList();

    public abstract void sort(Comparator<T> comparator);
}

