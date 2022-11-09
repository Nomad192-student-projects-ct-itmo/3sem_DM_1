#include <iostream>
#include <set>

using namespace std;

size_t code[100000];

size_t n;

size_t exists[100001];

set<size_t> leafs;

// size_t find_min()
// {
//  for(size_t i = 1; i < n; i++)
//  {
//      if(exists[i] == 0)
//          return i;
//  }
//  return 0; ///???
// }

int main()
{
    cin >> n;

    for(size_t i = 0; i < n-2; i++)
    {
        cin >> code[i];
    }

    for(size_t i = 0; i < n + 1; i++)
    {
        exists[i] = 0;
    }
    for(size_t i = 0; i < n-2; i++)
    {
        exists[code[i]]++;
    }
    for(size_t i = 1; i < n + 1; i++)
    {
        if(exists[i] == 0)
            leafs.insert(i);
    }

    for(size_t i = 0; i < n-2; i++)
    {
        size_t u = *leafs.begin();
        size_t v = code[i];
        cout << u << " " << v << "\n";
        leafs.erase(u);
        exists[v]--;
        if(exists[v] == 0)
            leafs.insert(v);
    }

    cout << *leafs.begin() << " " << n << "\n";

    return 0;
}
