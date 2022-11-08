#include <iostream>
#include <vector>

using namespace std;

struct node_t
{
    vector<size_t> neighbors;
    bool is_leaf() const noexcept
    {
        return neighbors.size() == 1;
    }
};

struct graph_t
{
    node_t nodes[10];
} start;

size_t n_nodes_g;

long long Chromatic_polynomial[11];

class polynomial_t
{
    size_t n;
    long long *coefficients;
public:
    explicit polynomial_t(size_t n) : n(n), coefficients(new long long[n]) {}

    long long& operator[](size_t i)
    {
        return coefficients[i];
    }

    ~polynomial_t()
    {
        delete[] coefficients;
    }
};

class chromatic_polynomial_t
{
    polynomial_t polynomial;
    explicit chromatic_polynomial_t(size_t n, size_t m) : polynomial(n + 1)
    {
        polynomial[n] = 1;
        polynomial[n - 1] = -m;
        polynomial[0] = 0;
    }
};


int main()
{
    size_t m;
    cin >> n_nodes_g >> m;

    for(size_t i = 0; i < m; i++)
    {
        size_t a, b;
        cin >> a >> b;
        a--; b--;
        start.nodes[a].neighbors.push_back(b);
        start.nodes[b].neighbors.push_back(a);
    }

    Chromatic_polynomial[n_nodes_g] = 1;
    Chromatic_polynomial[n_nodes_g-1] = -m;
    Chromatic_polynomial[0] = 0;

    for(size_t i = n_nodes_g - 2; i > 0; i--)
    {

    }

    cout << n_nodes_g << "\n";
    for (size_t i = n_nodes_g + 1; i--;) {
        cout << Chromatic_polynomial[i] << " ";
    }
}
