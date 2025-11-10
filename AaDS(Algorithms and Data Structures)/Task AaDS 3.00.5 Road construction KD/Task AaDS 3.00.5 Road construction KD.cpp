#include <iostream>
#include <fstream>

using namespace std;

int FindSet(int* mas, int x) {
    int ind = x;
    while (mas[ind] > 0)
        ind = mas[ind];
    return ind;
}

int FindSetRec(int* mas, int x) {
    int ind = x;
    if (mas[ind] > 0)
        mas[ind] = FindSet(mas, mas[ind]);
    return ind;
}

int Union(int* mas, int x, int y, int& count) {
    int new_r = FindSet(mas, x), old_r = FindSet(mas, y);
    if (new_r == old_r)
        return count;
    if (mas[new_r] > mas[old_r])
        swap(new_r, old_r);
    mas[new_r] += mas[old_r];
    mas[old_r] = new_r;
    count--;
    return count;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    if (!in.is_open() || !out.is_open())
        return 1;
    int size, roads, a, b, count;
    in >> size >> roads;
    count = size;
    int* cities = new int[size + 1];

    for (int i = 0; i < size; i++)
        cities[i] = -1;

    for (int i = 0; i < roads; i++) {
        in >> a >> b;
        out << Union(cities, a, b, count) << endl;
    }

    in.close();
    out.close();

    delete[] cities;
    return 0;
}
