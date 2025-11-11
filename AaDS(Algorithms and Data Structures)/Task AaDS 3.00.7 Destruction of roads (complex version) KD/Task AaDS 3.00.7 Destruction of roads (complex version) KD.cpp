#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int FindSet(int* mas, int x) {
    int r = x, next;
    while (r != mas[r])
        r = mas[r];

    while (x != r) {
        next = mas[x];
        mas[x] = r;
        x = next;
    }
    return r;
}

int Union(int* mas, int* size, int x, int y, int& count) {
    int new_r = FindSet(mas, x), old_r = FindSet(mas, y);
    if (new_r == old_r)
        return count;

    if (size[new_r] < size[old_r])
        swap(new_r, old_r);
    mas[old_r] = new_r;
    size[new_r] += size[old_r];
    count--;
    return count;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in.is_open() || !out.is_open())
        return 1;

    int n, m, q;
    in >> n >> m >> q;
    if (n == 1) {
        for (int i = 0; i < q; i++)
            out << 1;
        return 0;
    }

    int* cities = new int[n + 1];
    int* size = new int[n + 1];
    for (int i = 0; i < n + 1; i++) {
        cities[i] = i;
        size[i] = 1;
    }

    int* road1 = new int[m + 1];
    int* road2 = new int[m + 1];
    bool* droads = new bool[m + 1];
    for (int i = 1; i < m + 1; i++) {
        in >> road1[i] >> road2[i];
        droads[i] = true;
    }

    int* earthquakes = new int[q];
    for (int i = 0; i < q; i++)
        in >> earthquakes[i];

    for (int i = 0; i < q; i++)
        droads[earthquakes[i]] = false;

    int count = n;
    for (int i = 1; i < m + 1; i++) {
        if (!droads[i])
            continue;
        Union(cities, size, road1[i], road2[i], count);
    }

    int* answer = new int[q];

    for (int i = q - 1; i >= 0; i--) {
        if (count != 1) {
            answer[i] = 0;
            count = Union(cities, size, road1[earthquakes[i]], road2[earthquakes[i]], count);
        }
        else {
            answer[i] = 1;
        }
    }
    for(int i = 0; i < q; i++)
        out << answer[i];

    in.close();
    out.close();
    delete[] cities;
    delete[] size;
    delete[] road1;
    delete[] road2;
    delete[] droads;
    delete[] earthquakes;
    delete[] answer;
    return 0;
}