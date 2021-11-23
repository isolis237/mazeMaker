/* Your code here! */
#include <iostream>
#include "dsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        set.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (set[elem] < 0)
        return elem;
    set[elem] = find(set[elem]);
    return set[elem];
}

void DisjointSets::setunion(int a, int b) {
    int a_root = find(a);
    int b_root = find(b);

    if (a_root < b_root) { //a > b 
        set[a_root] = set[a_root] + set[b_root];
        set[b_root] = a_root;
    } else {
        set[b_root] = set[a_root] + set[b_root];
        set[a_root] = b_root;
    }
}

int DisjointSets::size(int elem) {
    int idx = find(elem);
    return -1 * set[idx];
}