#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <windows.h>

using namespace std;

enum class Status
{
    NotVisited = 0,
    Current = 1,
    Visited = 2
};

bool dfs(int u,
    const vector<vector<int>>& matrix,
    vector<Status>& status,
    vector<int>& order)
{
    status[u] = Status::Current;

    const int n = static_cast<int>(matrix.size());
    for (int v = 0; v < n; ++v) {
        if (matrix[u][v] == 0) continue;

        if (status[v] == Status::Current)
            return false;                       // цикл

        if (status[v] == Status::NotVisited) {
            if (!dfs(v, matrix, status, order))
                return false;                   // цикл
        }
    }

    status[u] = Status::Visited;
    order.push_back(u);
    return true;
}

vector<int> topologicalSortDFS(int n, const vector<vector<int>>& matrix)
{
    vector<Status> status(n, Status::NotVisited);
    vector<int> order;

    for (int i = 0; i < n; ++i) {
        if (status[i] == Status::NotVisited) {
            if (!dfs(i, matrix, status, order))
                return {};
        }
    }

    reverse(order.begin(), order.end());
    return order;
}

bool read_from_file(const string& filename,
    int& n,
    vector<vector<int>>& matrix)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cerr << "Не удалось открыть файл: " << filename << '\n';
        return false;
    }

    if (!(fin >> n) || n <= 0)
    {
        cerr << "Не удалось прочитать количество вершин\n";
        return false;
    }

    matrix.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (!(fin >> matrix[i][j]))
            {
                cerr << "Ошибка чтения элемента [" << i << "][" << j << "]\n";
                return false;
            }

    return true;
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n = 0;
    vector<vector<int>> matrix;

    if (!read_from_file("input.txt", n, matrix))
        return 1;

    vector<int> order = topologicalSortDFS(n, matrix);

    if (order.empty())
        cout << "В графе есть цикл — топологическая сортировка невозможна.\n";
    else {
        cout << "Топологический порядок вершин: ";
        for (int v : order) cout << v << ' ';
        cout << '\n';
    }
    return 0;
}