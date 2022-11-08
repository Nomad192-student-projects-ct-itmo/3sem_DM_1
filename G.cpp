#include <iostream>
#include <vector>

using namespace std;

#define MAX(a, b) (a > b ? (a) : (b))

struct node_t
{
    vector<size_t> neighbors;
    size_t color = 0;
};

node_t nodes[10000];

size_t max_color;

void paint(size_t v)
{
    if(nodes[v].color)
        return;
    {
        bool *colors = new bool[max_color+1];

        for(size_t i = 0; i < max_color+1; i++)
            colors[i] = false;

        for(auto v : nodes[v].neighbors)
            if(nodes[v].color)
                colors[nodes[v].color] = true;

        for(size_t i = 1; i < max_color+1; i++)
            if(colors[i] == false)
            {
                nodes[v].color = i;
                break;
            }

        delete[] colors;
    }


    for(auto v : nodes[v].neighbors)
        paint(v);

    return;
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    size_t max_g = 0;
    for(size_t i = 0; i < m; i++)
    {
        size_t a, b;
        cin >> a >> b;
        a--;
        b--;
        //cout << a << b << endl;
        nodes[a].neighbors.push_back(b);
        nodes[b].neighbors.push_back(a);
        size_t g = MAX(nodes[a].neighbors.size(), nodes[b].neighbors.size());
        if(g > max_g)
            max_g = g;
    }
    max_color = max_g + (max_g%2 == 0);
    paint(0);
    cout << max_color << "\n";
    for(size_t i=0; i < n; i++)
    {
        cout << nodes[i].color << "\n";
    }
}
