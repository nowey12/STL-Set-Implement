#include <iostream>

using namespace std;

struct Node {
    int key, height, subtreeSize;
    Node *left, *right;
};

typedef Node *NodePointer;

class AVLTree {
private:
    NodePointer root;
    int sizeOfTree;

public:
    AVLTree() {
        root = nullptr;
        sizeOfTree = 0;
    };

    int empty();

    int size();

    int minimum(int key);

    int maximum(int key);

    Node *find(int key);

    Node *findWithoutPrint(int key);

    void *insert(int key);

    void rank(int key);

    pair<int, int> rankAndDepth(Node *root, int key, int currentDepth, int currentRank);

    void erase(int key);

    const NodePointer getRoot() const;
};

int AVLTree::size() {
    cout << sizeOfTree << '\n';
    return sizeOfTree;
}

int AVLTree::empty() {
    if (sizeOfTree == 0) {
        cout << 1 << '\n';
        return 1;
    } else {
        cout << 0 << '\n';
        return 0;
    }
}

Node *AVLTree::findWithoutPrint(int key) {
    NodePointer current_node = root;

    while (current_node != nullptr) {
        if (current_node->key == key) {
            return current_node;
        } else if (current_node->key > key) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    return current_node;
}

int AVLTree::minimum(int key) {
    NodePointer currentNode = findWithoutPrint(key);

    while (currentNode->left != nullptr) {
        currentNode = currentNode->left;
    }

    std::cout << currentNode->key << " ";
    find(currentNode->key);
    return currentNode->key;
}

int AVLTree::maximum(int key) {
    NodePointer currentNode = findWithoutPrint(key);

    while (currentNode->right != nullptr) {
        currentNode = currentNode->right;
    }

    std::cout << currentNode->key << " ";
    find(currentNode->key);
    return currentNode->key;
}


int getHeight(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int getBalanceFactor(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->subtreeSize = 1;
    return node;
}

int getSubtreeSize(Node *node) {
    return node != nullptr ? node->subtreeSize : 0;
}

Node *rightRotate(Node *currentRoot) {
    Node *newRoot = currentRoot->left;
    Node *subtree = newRoot->right;

    newRoot->right = currentRoot;
    currentRoot->left = subtree;

    currentRoot->height = max(getHeight(currentRoot->left), getHeight(currentRoot->right)) + 1;
    currentRoot->subtreeSize = 1 + getSubtreeSize(currentRoot->left) + getSubtreeSize(currentRoot->right);

    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    newRoot->subtreeSize = 1 + getSubtreeSize(newRoot->left) + getSubtreeSize(newRoot->right);

    return newRoot;
}

Node *leftRotate(Node *currentRoot) {
    Node *newRoot = currentRoot->right;
    Node *subtree = newRoot->left;

    newRoot->left = currentRoot;
    currentRoot->right = subtree;

    currentRoot->height = max(getHeight(currentRoot->left), getHeight(currentRoot->right)) + 1;
    currentRoot->subtreeSize = 1 + getSubtreeSize(currentRoot->left) + getSubtreeSize(currentRoot->right);

    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    newRoot->subtreeSize = 1 + getSubtreeSize(newRoot->left) + getSubtreeSize(newRoot->right);

    return newRoot;
}

Node *insertNode(Node *node, int key) {
    if (node == nullptr) {
        return (newNode(key));
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    node->subtreeSize = 1 + getSubtreeSize(node->left) + getSubtreeSize(node->right);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        } else if (key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return leftRotate(node);
        } else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

void *AVLTree::insert(int key) {
    root = insertNode(root, key);
    find(key);
    sizeOfTree++;
}

Node *AVLTree::find(int key) {
    int depth = 0;
    NodePointer current_node = root;

    while (current_node != nullptr) {
        if (current_node->key == key) {
            cout << depth << '\n';
            return current_node;
        } else if (current_node->key > key) {
            depth += 1;
            current_node = current_node->left;
        } else {
            depth += 1;
            current_node = current_node->right;
        }
    }

    cout << 0 << '\n';
    return current_node;
}

pair<int, int> AVLTree::rankAndDepth(Node *root, int key, int currentDepth, int currentRank) {
    if (root == nullptr) {
        return {0, 0};
    }

    int left = getSubtreeSize(root->left);
    if (key == root->key) {
        return {currentRank + left + 1, currentDepth};
    } else if (key < root->key) {
        return rankAndDepth(root->left, key, currentDepth + 1, currentRank);
    } else {
        return rankAndDepth(root->right, key, currentDepth + 1, currentRank + left + 1);
    }
}

Node *getMinimumNodeOfSubTree(Node *node) {
    Node *current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node *eraseNode(Node *root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->key) {
        root->left = eraseNode(root->left, key);
    } else if (key > root->key) {
        root->right = eraseNode(root->right, key);
    } else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            Node *temp = getMinimumNodeOfSubTree(root->right);
            root->key = temp->key;
            root->right = eraseNode(root->right, temp->key);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root->subtreeSize = 1 + getSubtreeSize(root->left) + getSubtreeSize(root->right);

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

void AVLTree::erase(int key) {
    if (findWithoutPrint(key) == nullptr) {
        cout << 0 << '\n';
        return;
    }
    find(key);
    sizeOfTree--;
    root = eraseNode(root, key);
}

void AVLTree::rank(int key) {
    if (findWithoutPrint(key) == nullptr) {
        cout << 0 << '\n';
        return;
    }
    auto result = rankAndDepth(root, key, 0, 0);
    cout << result.second << " " << result.first << '\n';
}

const NodePointer AVLTree::getRoot() const {
    return root;
}

