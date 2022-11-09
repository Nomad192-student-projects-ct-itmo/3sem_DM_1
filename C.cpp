#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

size_t k = 0;

bool comp(size_t a, size_t b)
{
    if(k++ > 10000)
        return false;

    cout << "1 " << a << " " << b << endl;

    string answer;
    cin >> answer;

    return answer == "YES";
}

int main()
{
    size_t n;
    cin >> n;

    vector<size_t> l(n);

    for(size_t i = 0; i < n; i++)
        l[i] = i + 1;


    stable_sort(l.begin(), l.end(), comp);

    cout << "0" << " ";
    if(k > 10000)
        for(size_t i = 0; i < n; i++)
            cout << "0" << " ";
    else
        for(auto v: l)
            cout << v << " ";

    return 0;
}
