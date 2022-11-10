#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

constexpr size_t max_n_gc = 1000;
bool Adjacency_matrix[max_n_gc][max_n_gc];

size_t n_g;

#define MAX(a, b) (a > b) ? (a) : (b)
#define MIN(a, b) (a < b) ? (a) : (b)

bool path(size_t a, size_t b) {
    if (a == b)
        return false;
    if(a > b)
        return Adjacency_matrix[a][b];
    /// b > a
    return !Adjacency_matrix[b][a];
}

void scan_Adjacency_matrix() {
    char buf;
    scanf("%zu%c", &n_g, &buf);   /// buf == "\n"
    for (size_t i = 0; i < n_g; i++) {
        for (size_t j = 0; j < i; j++) {
            scanf("%c", &buf);
            Adjacency_matrix[i][j] = (buf - '0');
        }
        scanf("%c", &buf);   /// buf == "\n"
    }
}

int main()
{
    scan_Adjacency_matrix();

    vector<size_t> Hamiltonian_path(n_g);

    for(size_t i = 0; i < n_g; i++)
        Hamiltonian_path[i] = i;

    do
    {
        shuffle(Hamiltonian_path.begin(), Hamiltonian_path.begin(), std::mt19937(std::random_device()()));
        stable_sort(Hamiltonian_path.begin(), Hamiltonian_path.end(), path);
    } while (path(Hamiltonian_path[0], Hamiltonian_path[Hamiltonian_path.size()-1]));


    for (const auto &item: Hamiltonian_path) {
        cout << item + 1 << " ";
    }

    return 0;
}

/**

3

1
01

**/
