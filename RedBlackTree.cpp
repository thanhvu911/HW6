#include <iostream>
#include <string>
using namespace std;

#include "RedBlackTree.h"

RedBlackTree::~RedBlackTree()
{
    DestructorHelper(root);
}

RedBlackTree::RedBlackTree() {
}
// Copy constructor details from https://www.cplusplus.com/articles/y8hv0pDG/
RedBlackTree::RedBlackTree(const RedBlackTree &other) {
    root = CopyRecur(nullptr, other.root);
    numItems = other.Size();
}

// Insertion logic based on the Red-Black Tree properties
// Insertion method adapted from zyBook section 16.3.1 and https://www.youtube.com/watch?v=UaLIHuR1t8Q (Red-Black Tree Insertion video @ 5:30)
// Collected 3700000 ID numbers in 3.14336 seconds.
//Added ID 19566413 in 1e-06 seconds.
//Added ID 36803526 in 2e-06 seconds.
//Added ID 5776091 in 2e-06 seconds.
//Added ID 18268980 in 2e-06 seconds.
//Added ID 24759956 in 2e-06 seconds.
void RedBlackTree::Insert(int value) {
    if (Contains(value)) {
        throw invalid_argument("Node is already inside the tree");
    }
    RBTNode *node = new RBTNode(value, COLOR_RED);  // Ensure node initialization includes setting data and color.
    root = insertBST(root, node);
    numItems++;
    fixAfterInsertion(node);
}


// Search function to check if a value is in the tree
bool RedBlackTree::Contains(int value) {
    return searchTree(root, value);
}

// Removed ID 3595368 in 1.6e-05 seconds.
// Removed ID 3465782 in 4e-06 seconds.
// Removed ID 133069 in 8e-06 seconds.
// Removed ID 1798315 in 1e-05 seconds.
// Removed ID 3664370 in 2e-06 seconds.
void RedBlackTree::Remove(int data) {
    if (!Contains(data)) {
        throw invalid_argument("Node does not exist in the tree");
    }
    root = removeBST(root, data); 
    numItems--;
}

const int RedBlackTree::GetMin() const {
    RBTNode *currentNode = root;
    while (currentNode->left) currentNode = currentNode->left;
    return currentNode->data;
}

const int RedBlackTree::GetMax() const {
    RBTNode *currentNode = root;
    while (currentNode->right) currentNode = currentNode->right;
    return currentNode->data;
}


size_t RedBlackTree::Size() const {
    return numItems;
}

RBTNode *RedBlackTree::CopyRecur(RBTNode *parent, RBTNode *sourceNode) {
    if (!sourceNode) return nullptr;
    RBTNode *clonedNode = new RBTNode(sourceNode->data, sourceNode->color);
    clonedNode->left = CopyRecur(clonedNode, sourceNode->left);
    clonedNode->right = CopyRecur(clonedNode, sourceNode->right);
    return clonedNode;
}


void RedBlackTree::DestructorHelper(RBTNode *node) {
    if (!node) return; 
    // Recursive case: delete both subtrees.
    DestructorHelper(node->left);
    DestructorHelper(node->right);
    delete node; 
}

// In-order printing
string RedBlackTree::ToInfixString(RBTNode *root) const {
    if (!root) return "";
    return ToInfixString(root->left) + printNode(root) + ToInfixString(root->right);
}

// Post-order printing
string RedBlackTree::ToPostfixString(RBTNode *root) const {
    if (!root) return "";
    return ToPostfixString(root->left) + ToPostfixString(root->right) + printNode(root);
}

// Pre-order printing
string RedBlackTree::ToPrefixString(RBTNode *node) const {
    if (!node) return "";
    return printNode(node) + ToPrefixString(node->left) + ToPrefixString(node->right);
}

string RedBlackTree::printNode(RBTNode *node) const {
    return (node->color == COLOR_BLACK ? " B" : " R") + to_string(node->data) + " ";
}

RBTNode* RedBlackTree::find_parent(RBTNode* rootNode, RBTNode* node) {
    // Base case: rootNode is nullptr or node is the rootNode itself.
    if (rootNode == nullptr || rootNode == node) {
        return nullptr;
    }
    // Check if the current rootNode is the direct parent of the node.
    if (rootNode->left == node || rootNode->right == node) {
        return rootNode;
    }
    // Recursively search the appropriate subtree based on the node's data.
    if (node->data < rootNode->data) {
        return find_parent(rootNode->left, node);
    } else {
        return find_parent(rootNode->right, node);
    }
}

// Standard BST insert before applying RBT properties
RBTNode *RedBlackTree::insertBST(RBTNode *root, RBTNode *node) {
    if (root == nullptr) {
        return node;  // New node becomes root of the subtree.
    }
    if (node->data < root->data) {
        root->left = insertBST(root->left, node);
        root->left->parent = root;  // Set parent pointer.
    } else {
        root->right = insertBST(root->right, node);
        root->right->parent = root;  // Set parent pointer.
    }
    return root;
}

// Recursive search logic https://levelup.gitconnected.com/binary-search-trees-and-recursion-f99ce7eb647b
bool RedBlackTree::searchTree(RBTNode *root, int value) {
    if (root == nullptr) {
        return false;
    }
    else if (root->data == value) {
        return true;
    }
    else if (value < root->data) {
        return searchTree(root->left, value);
    }
    else {
        return searchTree(root->right, value);
    }
}

// Getter for node color
int RedBlackTree::getColor(RBTNode *node) {
    if (node == nullptr){
        return COLOR_BLACK;
    }
    return node->color;
}

// Setter for node color
void RedBlackTree::setColor(RBTNode *node, int color) {
    if (node == nullptr)
        return;
    node->color = color;
}

void RedBlackTree::rotateLeft(RBTNode *node) {
    RBTNode *rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    
    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(RBTNode *node) {
    RBTNode *leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    
    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

// Fixing tree after insertion to maintain Red-Black properties
void RedBlackTree::fixAfterInsertion(RBTNode *node) {
    // Process up the tree until we reach the root or a black parent node
    while (node != root && node->parent->color == COLOR_RED) {
        RBTNode *parent = node->parent;
        RBTNode *grandparent = parent->parent;
        if (grandparent == nullptr) {
            break;
        }
        // Determine if the parent is a left or right child
        bool isLeftChild = (parent == grandparent->left);
        RBTNode *uncle = isLeftChild ? grandparent->right : grandparent->left;
        // Recoloring if the uncle is red
        if (uncle && uncle->color == COLOR_RED) {
            parent->color = COLOR_BLACK;
            uncle->color = COLOR_BLACK;
            grandparent->color = COLOR_RED;
            node = grandparent;
            continue;
        }
        // Rotate and recolor if the uncle is black
        if (isLeftChild) {
            if (node == parent->right) {
                // Left-Right Case: Rotate left at parent before rotating right at grandparent
                rotateLeft(parent);
                node = parent;
                parent = node->parent;
            }
            // Left-Left Case: Rotate right at grandparent and swap colors
            rotateRight(grandparent);
        } else {
            if (node == parent->left) {
                // Right-Left Case: Rotate right at parent before rotating left at grandparent
                rotateRight(parent);
                node = parent;
                parent = node->parent;
            }
            // Right-Right Case: Rotate left at grandparent and swap colors
            rotateLeft(grandparent);
        }
        parent->color = COLOR_BLACK;
        grandparent->color = COLOR_RED;
        break;
    }
    // Ensure the root is always black (to maintain property 2)
    root->color = COLOR_BLACK;
}

//helper function for remove Binary Search Tree https://www.geeksforgeeks.org/deletion-in-binary-search-tree/
RBTNode *RedBlackTree::removeBST(RBTNode *node, int data) {
    if (node == nullptr) {
        return nullptr;
    }
    if (data < node->data) {
        node->left = removeBST(node->left, data);
    } else if (data > node->data) {
        node->right = removeBST(node->right, data);
    } else {
        // Node to be deleted is found
        if (node->left == nullptr || node->right == nullptr) {
            RBTNode *child = nullptr;
            if (node->left != nullptr) {
                child = node->left;
            } else {
                child = node->right;
            }
            if (child == nullptr) {
                // No child case
                child = node;  // To keep a reference for fixing double black
                node = nullptr;
            } else {
                // Node has one child. Replace node with its child
                *node = *child;
            }
            delete child;
            // If the node was black and replaced by a black child, fix double black
            if (node != nullptr && node->color == COLOR_BLACK) {
                adjustDoubleBlack(node);
            } else if (node != nullptr) {
                node->color = COLOR_BLACK;  // Ensure the replacement child is black
            }
        } else {
            // Two children: Get the inorder successor
            RBTNode *temp = inorderSuccessor(node);
            if (temp == nullptr) {
                throw runtime_error("Inorder successor should not be nullptr here");
            }
            // Replace node data with successor data
            node->data = temp->data;
            // Remove the inorder successor
            node->right = removeBST(node->right, temp->data);
        }
    }
    return node;
}

// Find the smallest node in the right subtree of the given node, i.e., its inorder successor.
RBTNode* RedBlackTree::inorderSuccessor(RBTNode* targetNode) {
    if (targetNode == nullptr || targetNode->right == nullptr) {
        return nullptr; // No right subtree means no inorder successor.
    }

    RBTNode* successor = targetNode->right;
    // Move to the leftmost node of the right subtree.
    while (successor->left != nullptr) {
        successor = successor->left;
    }
    return successor;
}


// Helper function to handle the removal process, particularly fixing tree properties after node deletion
void RedBlackTree::removeBST(RBTNode *targetNode) {
    // Nothing to do if the node is null.
    if (!targetNode) {
        return;  
    }
    // If the node to remove is the root and has no children, simply remove it.
    if (targetNode == root) {
        delete root;
        root = nullptr;
        return;
    }
    // Check if the node or one of its children is red.
    bool isRed = getColor(targetNode) == COLOR_RED || 
                 getColor(targetNode->left) == COLOR_RED ||
                 getColor(targetNode->right) == COLOR_RED;
    if (isRed) {
        RBTNode* replacement = targetNode->left ? targetNode->left : targetNode->right;
        // Link the replacement node to the parent of the node to be deleted.
        RBTNode* parentNode = find_parent(root, targetNode);
        if (parentNode->left == targetNode) {
            parentNode->left = replacement;
        } else {
            parentNode->right = replacement;
        }
        if (replacement) {
            // Set the parent pointer.
            replacement->parent = parentNode; 
            // Ensure the replacement is black.
            setColor(replacement, COLOR_BLACK); 
        }
        delete targetNode; 
    } else {
        // Handle double black situation
        adjustDoubleBlack(targetNode);
    }
}

// Method to resolve double black issues after node deletion
void RedBlackTree::adjustDoubleBlack(RBTNode *affectedNode) {
    if (affectedNode == root) {
        // If the double black node is the root, simply change it to black
        setColor(affectedNode, COLOR_BLACK);
        return;
    }

    RBTNode *sibling;
    RBTNode *currentNode = affectedNode;
    setColor(currentNode, DOUBLE_BLACK); // Set double black to handle extra black violation.

    while (currentNode != root && getColor(currentNode) == DOUBLE_BLACK) {
        RBTNode *parent = find_parent(root, currentNode);
        bool isLeft = (currentNode == parent->left);
        sibling = isLeft ? parent->right : parent->left;

        if (getColor(sibling) == COLOR_RED) {
            // Case 1: Red sibling
            setColor(sibling, COLOR_BLACK);
            setColor(parent, COLOR_RED);
            isLeft ? rotateLeft(parent) : rotateRight(parent);
            sibling = isLeft ? parent->right : parent->left; // Refresh sibling reference post-rotation
        }

        if (areBothChildrenBlack(sibling)) {
            // Case 2: Both children of sibling are black
            setColor(sibling, COLOR_RED);
            if (getColor(parent) == COLOR_RED) {
                setColor(parent, COLOR_BLACK);
            } else {
                setColor(parent, DOUBLE_BLACK);
                currentNode = parent; // Move to the parent to handle next level
                continue;
            }
        } else {
            // Case 3: At least one red child of sibling
            if (isLeft && getColor(sibling->right) == COLOR_BLACK) {
                setColor(sibling->left, COLOR_BLACK);
                setColor(sibling, COLOR_RED);
                rotateRight(sibling);
                sibling = parent->right;
            } else if (!isLeft && getColor(sibling->left) == COLOR_BLACK) {
                setColor(sibling->right, COLOR_BLACK);
                setColor(sibling, COLOR_RED);
                rotateLeft(sibling);
                sibling = parent->left;
            }

            setColor(sibling, getColor(parent));
            setColor(parent, COLOR_BLACK);
            isLeft ? rotateLeft(parent) : rotateRight(parent);
            break;
        }
    }
    setColor(currentNode, COLOR_BLACK); 
}

// Helper to check if both children of a node are black
bool RedBlackTree::areBothChildrenBlack(RBTNode *node) {
    return getColor(node->left) == COLOR_BLACK && getColor(node->right) == COLOR_BLACK;
}


