#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#define DOUBLE_BLACK 0
#define COLOR_RED 1 
#define COLOR_BLACK 0

#include <iostream>
#include <vector>

using namespace std;

// video lecture 9 
struct RBTNode {
    int data;
    unsigned short int color;
    RBTNode *left = nullptr;
    RBTNode *right = nullptr;
    RBTNode *parent = nullptr;  // Include parent pointer in the struct
    bool IsNullNode = false;    // Default to false for normal nodes

    // Constructor to initialize a node conveniently
    RBTNode(int d = 0, unsigned short int c = COLOR_RED, RBTNode *p = nullptr, RBTNode *l = nullptr, RBTNode *r = nullptr)
    : data(d), color(c), left(l), right(r), parent(p), IsNullNode(false) {}
};

class RedBlackTree {
    public: 
        RedBlackTree();
        ~RedBlackTree();
        RedBlackTree(const RedBlackTree &other); // Copy constructor
        void Insert(int value);
        bool Contains(int value); // True if integer is in the tree
        void Remove(int data);
        const int GetMin() const;
        const int GetMax() const;
        size_t Size() const;
        string ToInfixString() const {return ToInfixString(root);};
        string ToPrefixString() const { return ToPrefixString(root);};
        string ToPostfixString() const { return ToPostfixString(root);};

    private:
        unsigned long long int numItems = 0;
        RBTNode *root = nullptr;
        RBTNode *CopyRecur(RBTNode *thisRoot, RBTNode *rootCp);
        void DestructorHelper(RBTNode *node);

        //Private printing method
        string ToInfixString(RBTNode *root) const;
        string ToPrefixString(RBTNode *root) const;
        string ToPostfixString(RBTNode *root) const;
        string printNode(RBTNode *root) const;

        //Helper method for BST
        RBTNode* find_parent(RBTNode *rootNode, RBTNode *node);
        RBTNode *insertBST(RBTNode *root, RBTNode *node);
        bool searchTree(RBTNode *root, int value);

        //Private color method
        int getColor(RBTNode *node);
        void setColor(RBTNode *node, int color);

        //Helper method for insert
        void rotateLeft(RBTNode *node);
        void rotateRight(RBTNode *node);
        void fixAfterInsertion(RBTNode *node);

        //Helper method for remove
        RBTNode *removeBST(RBTNode *root, int data);
        RBTNode *inorderSuccessor(RBTNode *node);
        void removeBST(RBTNode *targetNode);
        void adjustDoubleBlack(RBTNode *affectedNode);
        bool areBothChildrenBlack(RBTNode *node);
        void cleanupParentReference(RBTNode *root, RBTNode *node);

};
#endif
