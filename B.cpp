#include <cstdio>
#include <cinttypes>
#include <list>

using namespace std;

typedef uint_fast16_t mtype;
#define SP_M_TYPE SCNuFAST16

mtype n;
bool Adjacency_matrix[100][100];

void print_Adjacency_matrix() {
    printf("============================================\n");
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            printf("%d", Adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    printf("============================================\n");
}

void scan_Adjacency_matrix() {
    char buf;
    scanf("%" SP_M_TYPE "%c", &n, &buf);   /// buf == "\n"
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            scanf("%c", &buf);
            //printf("i = %d, j = %d: %d\n", i, j, buf);
            Adjacency_matrix[i][j] = (buf - '0');
        }
        scanf("%c", &buf);   /// buf == "\n"
        //printf("i = %d: %d\n", i, buf);
    }
}

#define MAX(a, b) (a > b) ? (a) : (b)
#define MIN(a, b) (a < b) ? (a) : (b)

bool path(mtype a, mtype b) {
    if (a == b)
        return false;

    return Adjacency_matrix[MAX(a, b)][MIN(a, b)];
}

list<mtype> Hamiltonian_path;

list<mtype>::iterator next(list<mtype>::iterator iter) {
    return ++iter;
}

list<mtype>::iterator prev(list<mtype>::iterator iter) {
    return --iter;
}

mtype& at(size_t i)
{
    auto iter = Hamiltonian_path.begin();
    for(size_t j = 0; j < i; j++)
        iter++;
    return *iter;
}

void print_list() {
    for (auto e: Hamiltonian_path)
        printf("%" SP_M_TYPE " ", e + 1);
    printf("\n");
}

void mass_swap(list<mtype>::iterator beg, list<mtype>::iterator end)
{
    while (beg != end && next(end) != beg) {
        mtype a = *beg;
        mtype b = *end;
        *beg = b;
        *end = a;

        beg++;
        end--;
    }
}

int main() {
    scan_Adjacency_matrix();
    //print_Adjacency_matrix();

    for (size_t i = 0; i < n; i++)
        Hamiltonian_path.push_back(i);

    for (size_t k = 0, p = 0; k < n*(n-1) && p < n; k++) {
        if(!path(at(0), at(1)))
        {
            auto iter = next(Hamiltonian_path.begin());
            do {
                iter++;
            } while (iter != Hamiltonian_path.end() && !(path(at(0), *iter) && path(at(1), *next(iter))));

            if(iter == Hamiltonian_path.end())
            {
                iter = next(Hamiltonian_path.begin());
                do {
                    iter++;
                } while (!(path(at(0), *iter)));
            }

            mass_swap(next(Hamiltonian_path.begin()), iter);
            p = 0;
        }
        else
        {
            p++;
        }
        Hamiltonian_path.push_back(Hamiltonian_path.front());
        Hamiltonian_path.pop_front();
    }

    print_list();

    return 0;
}

/**
4

1
11
101

**/


/**
4

1
10
011

**/
