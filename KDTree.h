#ifndef KDTREE_H
#define KDTREE_H

#include "nodo.h"
#include <vector>

class KDTree {
public:
    struct Node {
        Nodo point;
        Node *left, *right;

        Node(Nodo p);
    };

    KDTree(const std::vector<Nodo>& points);
    ~KDTree();

    Nodo nearestNeighbor( Nodo& target);
    double distance( Nodo& a,  Nodo& b);
    
private:
    Node* root;

    Node* build(std::vector<Nodo> points, int depth);
    void destroyTree(Node* node);
    Nodo nearestNeighbor(Node* node,  Nodo& target, int depth, Nodo& best);
    
};

#endif // KDTREE_H
