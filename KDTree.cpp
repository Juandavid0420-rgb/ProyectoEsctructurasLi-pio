#include "KDTree.h"
#include <algorithm>
#include <limits>
#include <cmath>

// Node constructor
KDTree::Node::Node(Nodo p) : point(p), left(nullptr), right(nullptr) {}

// Constructor
KDTree::KDTree(const std::vector<Nodo>& points) {
    root = build(points, 0);
}

// Destructor
KDTree::~KDTree() {
    destroyTree(root);
}

// Build the KD-Tree recursively
KDTree::Node* KDTree::build(std::vector<Nodo> points, int depth) {
    if (points.empty()) {
        return nullptr;
    }

    // Select axis based on depth
    int axis = depth % 3;

    // Sort points by the selected axis
    if (axis == 0) {
        std::sort(points.begin(), points.end(), []( Nodo& a,  Nodo& b) { return a.getX() < b.getX(); });
    } else if (axis == 1) {
        std::sort(points.begin(), points.end(), []( Nodo& a,  Nodo& b) { return a.getY() < b.getY(); });
    } else {
        std::sort(points.begin(), points.end(), []( Nodo& a,  Nodo& b) { return a.getZ() < b.getZ(); });
    }

    // Choose median as root
    int median = points.size() / 2;
    Node* node = new Node(points[median]);

    // Recursively build the left and right subtrees
    std::vector<Nodo> leftPoints(points.begin(), points.begin() + median);
    std::vector<Nodo> rightPoints(points.begin() + median + 1, points.end());
    node->left = build(leftPoints, depth + 1);
    node->right = build(rightPoints, depth + 1);

    return node;
}

// Function to destroy the tree
void KDTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Function to find the nearest neighbor
Nodo KDTree::nearestNeighbor( Nodo& target) {
    return nearestNeighbor(root, target, 0, root->point);
}

Nodo KDTree::nearestNeighbor(Node* node,  Nodo& target, int depth, Nodo& best) {
    if (!node) return best;

    double dist = distance(target, node->point);
    double bestDist = distance(target, best);

    // Update best point if current node is closer
    if (dist < bestDist) {
        best = node->point;
    }

    // Determine which side to search first
    int axis = depth % 3;
    Node* nearSide;
    Node* farSide;

    if ((axis == 0 && target.getX() < node->point.getX()) || 
        (axis == 1 && target.getY() < node->point.getY()) || 
        (axis == 2 && target.getZ() < node->point.getZ())) {
        nearSide = node->left;
        farSide = node->right;
    } else {
        nearSide = node->right;
        farSide = node->left;
    }

    // Recursively search the near side
    best = nearestNeighbor(nearSide, target, depth + 1, best);

    // Check if we need to search the far side
    double axisDist;
    if (axis == 0) {
        axisDist = target.getX() - node->point.getX();
    } else if (axis == 1) {
        axisDist = target.getY() - node->point.getY();
    } else {
        axisDist = target.getZ() - node->point.getZ();
    }

    if (std::abs(axisDist) < bestDist) {
        best = nearestNeighbor(farSide, target, depth + 1, best);
    }

    return best;
}

// Function to calculate the distance between two points
double KDTree::distance(Nodo& a, Nodo& b) {
     return std::sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) +
                     (a.getY() - b.getY()) * (a.getY() - b.getY()) +
                     (a.getZ() - b.getZ()) * (a.getZ() - b.getZ()));
}
