#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

#define MAX(x, y) x > y ? (x) : (y)

struct edge_t
{
    size_t u, v;
};

struct node_t
{
    //set<size_t> contractions;
    set<size_t> neighbors;
//    bool is_leaf() const noexcept
//    {
//        return neighbors.size() == 1;
//    }
};

struct graph_t
{
    node_t nodes[10];

public:
    size_t n;
    size_t m;
    explicit graph_t(size_t n, size_t m) : n(n), m(m) {}

//    void set(size_t other_n, size_t other_m)
//    {
//        this->n = other_n;
//        this->m = other_m;
//    }

    bool find_edge(edge_t* res)
    {
        size_t i = 0;
        for(; i < 10; i++)
        {
            if(nodes[i].neighbors.size() > 0)
                break;
        }
        if(i >= 10)
            return false;

        res->u = i;
        res->v = *nodes[i].neighbors.begin();
        return true;
    }

private:
    void edge_del_p(size_t a, size_t b)
    {
        nodes[a].neighbors.erase(b);
        nodes[b].neighbors.erase(a);
        m--;
    }

public:
    bool edge_contraction()
    {
        edge_t res;
        bool result_b = find_edge(&res);
        if(!result_b)
            return false;

        size_t a = res.u, b = res.v;
        edge_del_p(a, b);
//        nodes[a].contractions.insert(b);
//        nodes[b].contractions.insert(a);

        set<size_t> new_neighbors = nodes[a].neighbors;

        for (const auto &item: nodes[b].neighbors) {
            new_neighbors.insert(item);
        }

        for (const auto &item: nodes[b].neighbors) {
            nodes[item].neighbors.erase(b);
            nodes[item].neighbors.insert(a);
        }

        nodes[a].neighbors = new_neighbors;
        nodes[b].neighbors.clear();

        n--;

        assert(n > 0);
        return true;
    }

    bool edge_del()
    {
        edge_t res;
        bool result_b = find_edge(&res);
        if(!result_b)
            return false;

        size_t a = res.u, b = res.v;
        nodes[a].neighbors.erase(b);
        nodes[b].neighbors.erase(a);
        //m--;
        return true;
    }

    bool is_empty()
    {
        edge_t res;
        return !find_edge(&res);
    }
};

size_t n_nodes_g;

class polynomial_t
{
    size_t n;
    long long *coefficients;
public:
    explicit polynomial_t(size_t n) : n(n), coefficients(new long long[n]) {}

    polynomial_t(const polynomial_t &other) : n(other.n), coefficients(new long long[other.n])
    {
        for(size_t i = 0; i < n; i++)
        {
            coefficients[i] = other[i];
        }
    }

    polynomial_t& operator=(const polynomial_t& other)
    {
        if(this == &other)
            return *this;

        delete[] coefficients;

        n = other.n;
        coefficients =  new long long[other.n];

        for(size_t i = 0; i < n; i++)
        {
            coefficients[i] = other[i];
        }

        return *this;
    }

    void swap(polynomial_t &other)
    {
        std::swap(n, other.n);
        std::swap(coefficients, other.coefficients);
    }

    long long& operator[](size_t i) const
    {
        return coefficients[i];
    }

    size_t size() const
    {
        return n;
    }

    ~polynomial_t()
    {
        delete[] coefficients;
    }
};

void swap(polynomial_t &a, polynomial_t &b)
{
    a.swap(b);
}

class chromatic_polynomial_t
{
    polynomial_t polynomial;

public:
    explicit chromatic_polynomial_t(size_t n) : polynomial(n + 1)
    {
        polynomial[n] = 1;
        for(size_t i = 0; i < n; i++)
        {
            polynomial[i] = 0;
        }
    }

    explicit chromatic_polynomial_t(size_t n, size_t m) : polynomial(n + 1)
    {
        polynomial[n] = 1;
        polynomial[n - 1] = -m;
        polynomial[0] = 0;
    }

    size_t size() const
    {
        return polynomial.size();
    }

    long long& operator[](size_t i) const
    {
        return polynomial[i];
    }

    chromatic_polynomial_t& operator-(const chromatic_polynomial_t &other)
    {
        size_t max_size = MAX(size(), other.size());
        polynomial_t result(max_size);

        for(size_t i = 0; i < max_size; i++)
            result[i] = 0;

        for(size_t i = 0; i < size(); i++)
            result[i] += polynomial[i];

        for(size_t i = 0; i < other.size(); i++)
            result[i] -= other[i];

        swap(polynomial, result);

        return *this;
    }
};

std::ostream& operator << (std::ostream &os, const chromatic_polynomial_t &p)
{
    for(size_t i = p.size(); i--;)
    {
        os << p[i] << " ";
    }

    return os;
}

chromatic_polynomial_t Chromatic_polynomial(graph_t g)
{
    if(g.is_empty())
    {
        chromatic_polynomial_t result(g.n);
        return result;
    }

    graph_t g_del = g;
    graph_t g_cont = g;
    g_del.edge_del();
    g_cont.edge_contraction();

    return Chromatic_polynomial(g_del) - Chromatic_polynomial(g_cont);
}

int main()
{
    size_t m;
    cin >> n_nodes_g >> m;

    graph_t start(n_nodes_g, m);

    for(size_t i = 0; i < m; i++)
    {
        size_t a, b;
        cin >> a >> b;
        a--; b--;
        start.nodes[a].neighbors.insert(b);
        start.nodes[b].neighbors.insert(a);
    }



    cout << n_nodes_g << "\n";
    cout << Chromatic_polynomial(start);

}


/*

4 5
1 2
1 3
2 3
2 4
3 4

 */