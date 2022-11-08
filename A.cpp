#include <cstdio>
#include <cinttypes>
#include <list>

using namespace std;

typedef uint_fast16_t mtype;
#define SP_M_TYPE SCNuFAST16

mtype n;
bool Adjacency_matrix[4000][4000];

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
            } while (!(path(at(0), *iter) && path(at(1), *next(iter))));

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


//int main() {
//    scan_Adjacency_matrix();
//    //print_Adjacency_matrix();
//
//    for (size_t i = 0; i < n; i++)
//        Hamiltonian_path.push_back(i);
//
//    for (size_t i = 0; i < n* (n - 1); i++) {
//        mtype cur = Hamiltonian_path.front();
//        Hamiltonian_path.pop_front();
//        Hamiltonian_path.push_back(cur);
//
//        //printf("back: %" SP_M_TYPE "\n", Hamiltonian_path.back() + 1);
//
//        if (path(Hamiltonian_path.front(), Hamiltonian_path.back()))
//            continue;
//
//        auto iter = Hamiltonian_path.begin();
//
//        //printf("elb: %" SP_M_TYPE "\n", *iter + 1);
//
//        do {
//            iter++;
//        } while (!(path(Hamiltonian_path.back(), *iter) && path(Hamiltonian_path.front(), *next(iter))));
//
//        //printf("ela: %" SP_M_TYPE "\n", *iter + 1);
//
//        //print_list();
//
//        auto iter2 = Hamiltonian_path.begin();
//        while (iter != iter2 && next(iter) != iter2) {
//            //printf("swap: %" SP_M_TYPE " %" SP_M_TYPE "\n", *iter + 1, *iter2 + 1);
//
//            mtype a = *iter2;
//            mtype b = *iter;
//            *iter2 = b;
//            *iter = a;
//            //printf("after swap: %" SP_M_TYPE " %" SP_M_TYPE "\n", *iter + 1, *iter2 + 1);
//            iter2++;
//            iter--;
//            //printf("next iter: %" SP_M_TYPE " %" SP_M_TYPE "\n", *iter + 1, (*next(iter)) + 1);
//            //print_list();
//        }
//    }
//
//    print_list();
//
//    return 0;
//}


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
