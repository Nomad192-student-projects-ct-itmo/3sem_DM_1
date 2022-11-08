#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX(a, b) (a > b ? (a) : (b))

struct edge_t
{
    size_t a, b;
};

struct node_t
{
    set<size_t> neighbors;
    bool is_leaf() const noexcept
    {
        return neighbors.size() == 1;
    }
};

constexpr size_t max_nodes_gc = 100000;
constexpr size_t max_edges_gc = max_nodes_gc-1;

node_t nodes[max_nodes_gc];
edge_t edges[max_edges_gc];
size_t Prufers_code[max_nodes_gc - 2];

size_t n_nodes_g;
size_t n_edges_g;

set<size_t> leafs;

int main()
{
    cin >> n_nodes_g;
    n_edges_g = n_nodes_g - 1;
    for(size_t i = 0; i < n_edges_g; i++)
    {
        size_t a, b;
        cin >> a >> b;
        a--; b--;
        //edges[i] = {a-1, b-1};
        nodes[a].neighbors.insert(b);
        nodes[b].neighbors.insert(a);
    }

    for(size_t i = 0; i < n_edges_g; i++)
    {
        if(nodes[i].is_leaf())
            leafs.insert(i);
    }

//    for (const auto &item: leafs) {
//        cout << item << " ";
//    }
//    cout << endl;

    for(size_t i = 0; i < n_nodes_g - 2; i++)
    {
        size_t min_leaf = *leafs.begin();
        leafs.erase(min_leaf);
        size_t neighbor = *(nodes[min_leaf].neighbors.begin());
        Prufers_code[i] = neighbor;
        nodes[neighbor].neighbors.erase(min_leaf);
        if(nodes[neighbor].is_leaf())
            leafs.insert(neighbor);
    }

    for(size_t i = 0; i < n_nodes_g - 2; i++)
    {
        cout << Prufers_code[i] + 1 << " ";
    }
}
