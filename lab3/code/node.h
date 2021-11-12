#pragma once

// Define a node of the tree
template <typename Comparable>
struct BinarySearchTree<Comparable>::Node {
    Comparable element;

    Node* parent;
    Node* left;    // pointer to left sub-tree
    Node* right;   // pointer to right sub-tree

    // Constructors
    Node(const Comparable& theElement, Node* lt = nullptr, Node* rt = nullptr, Node* pt = nullptr)
    : element{theElement}, left{lt}, right{rt}, parent{pt} {
        ++count_nodes;
    }

    //Copy constructors -- disallowed
    Node(const Node&) = delete;

    //Assignement operator -- disallowed
    Node& operator=(const Node&) = delete;

    // Destructor
    ~Node() {
        --count_nodes;
        assert(count_nodes >= 0);  // number of existing nodes can never be negative
    }

    static int count_nodes;  // total number of existing nodes -- to help to detect bugs in the code
};

// Initialize static data member
template <typename Comparable>
int BinarySearchTree<Comparable>::Node::count_nodes = 0;
