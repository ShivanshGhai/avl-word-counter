#include "Wordlist.h"

// Helper Functions

// Returns the height of an AVL tree node.
// If the node is null, the height is -1.
int Wordlist::height(AVLTreeNode* node) const {
    if (!node) { // Check if the node is empty.
        return -1;
    } else { // Return the stored height of the node.
        return node->height;
    }
}

// Returns the balance factor of a node in the AVL tree.
// The balance factor is the height difference between the left and right subtrees.
int Wordlist::getBalanceFactor(AVLTreeNode* node) const {
    if (!node) { // Check if the node is empty.
        return 0;
    } else { // Compute and return the balance factor.
        return height(node->left) - height(node->right);
    }
}

// Performs a left rotation to balance the AVL tree.
// The provided node becomes the left child of its right child.
AVLTreeNode* Wordlist::rotateLeft(AVLTreeNode* node) {
    AVLTreeNode* newRoot = node->right; // The new root is the right child.
    node->right = newRoot->left; // Update the right child.
    if (newRoot->left) { // Update the parent pointer if left child exists.
        newRoot->left->parent = node;
    }
    newRoot->left = node; // Perform the rotation.
    newRoot->parent = node->parent; // Update parent pointer for the new root.
    node->parent = newRoot;

    // Update heights of the rotated nodes.
    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot; // Return the new root.
}

// Performs a right rotation to balance the AVL tree.
// The provided node becomes the right child of its left child.
AVLTreeNode* Wordlist::rotateRight(AVLTreeNode* node) {
    AVLTreeNode* newRoot = node->left; // The new root is the left child.
    node->left = newRoot->right; // Update the left child.
    if (newRoot->right) { // Update the parent pointer if right child exists.
        newRoot->right->parent = node;
    }
    newRoot->right = node; // Perform the rotation.
    newRoot->parent = node->parent; // Update parent pointer for the new root.
    node->parent = newRoot;

    // Update heights of the rotated nodes.
    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot; // Return the new root.
}

// Balances the AVL tree at the given node to maintain the AVL property.
AVLTreeNode* Wordlist::balance(AVLTreeNode* node) {
    if (!node) { // Check if the node is empty.
        return nullptr;
    }

    int balanceFactor = getBalanceFactor(node); // Compute balance factor.

    // Left-heavy case: Perform a right rotation.
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) { // Check for left-right case.
            node->left = rotateLeft(node->left); // Perform left rotation first.
        }
        return rotateRight(node); // Perform right rotation.
    }

    // Right-heavy case: Perform a left rotation.
    else if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) { // Check for right-left case.
            node->right = rotateRight(node->right); // Perform right rotation first.
        }
        return rotateLeft(node); // Perform left rotation.
    }

    return node; // Node is already balanced.
}

// Finds the node with the minimum value in the subtree rooted at the given node.
AVLTreeNode* Wordlist::findMin(AVLTreeNode* node) const {
    while (node && node->left) { // Traverse left until the smallest node is reached.
        node = node->left;
    }
    return node;
}

// Recursively destroys all nodes in the AVL tree starting from the given node.
void Wordlist::destroyTree(AVLTreeNode* node) {
    if (node) { // If the node is not null, recursively delete its children.
        destroyTree(node->left);
        destroyTree(node->right);
        delete node; // Delete the current node.
    }
}

// Recursively copies the AVL tree from another tree.
void Wordlist::copyTree(AVLTreeNode*& newNode, AVLTreeNode* originalNode, AVLTreeNode* parent) {
    if (originalNode == nullptr) { // Base case: null node.
        newNode = nullptr;
        return;
    }

    // Create a new node with the same data as the original.
    newNode = new AVLTreeNode(originalNode->word);
    newNode->count = originalNode->count;
    newNode->parent = parent; // Set the parent pointer.
    newNode->height = originalNode->height;

    // Recursively copy the left and right subtrees.
    copyTree(newNode->left, originalNode->left, newNode);
    copyTree(newNode->right, originalNode->right, newNode);
}

// Public Methods

// Default constructor: initializes an empty word list.
Wordlist::Wordlist() {
    root = nullptr;
    size = 0;
}

// Constructor: builds the word list from a file.
Wordlist::Wordlist(const string& filename) {
    root = nullptr;
    size = 0;
    ifstream myFile(filename);
    string word;
    while (myFile >> word) { // Read words from file
        insert(word);        // Insert each word into the tree
    }
    myFile.close();
}

// Copy constructor: creates a deep copy of the given word list.
Wordlist::Wordlist(const Wordlist& other) {
    root = nullptr;
    size = 0;
    copyTree(root, other.root, nullptr); // Copy the AVL tree
}

// Assignment operator: deep copies another word list.
Wordlist& Wordlist::operator=(const Wordlist& other) {
    if (this != &other) {       // Avoid self-assignment
        destroyTree(root);      // Clear the existing tree
        root = nullptr;
        size = 0;
        copyTree(root, other.root, nullptr); // Copy the AVL tree
    }
    return *this;
}

// Destructor: frees memory by destroying the AVL tree.
Wordlist::~Wordlist() {
    destroyTree(root);
}

// Inserts a word into the word list, balancing the AVL tree as necessary.
void Wordlist::insert(const string& word) {
    root = insertHelper(root, word);}

AVLTreeNode* Wordlist::insertHelper(AVLTreeNode* node, const string& word) {
    // Check if the node is empty
    if (!node) {
        size++;
        return new AVLTreeNode(word);
    }
    // Check if the word is smaller than the parent: insert left
    if (word < node->word) {
        node->left = insertHelper(node->left, word);
        node->left->parent = node;
    }
    // Check if the word is greater than the parent: insert right
    else if (word > node->word) {
        node->right = insertHelper(node->right, word);
        node->right->parent = node;
    } else {
        node->count++;
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    return balance(node);
}

bool Wordlist::remove(const string& word) {
    if (!contains(word)){
        return false;}
    root = removeHelper(root, word);
    return true;
}

AVLTreeNode* Wordlist::removeHelper(AVLTreeNode* node, const string& word) {
    // Check if the node is empty
    if (!node) {
        return nullptr;
    }
    // Check if the word is smaller than the parent: remove left
    if (word < node->word) {
        node->left = removeHelper(node->left, word);
    }
    // Check if the word is greater than the parent: remove right 
    else if (word > node->word) {
        node->right = removeHelper(node->right, word);
    } else {
        if (!node->left || !node->right) {
            AVLTreeNode* temp;
            if (node->left) {
                temp = node->left;
            } 
            else {
                temp = node->right;
            }

            if (temp) {
                temp->parent = node->parent;
            }
            delete node;
            size--;
            return temp;
        } else {
            AVLTreeNode* minNode = findMin(node->right);
            node->word = minNode->word;
            node->count = minNode->count;
            node->right = removeHelper(node->right, minNode->word);
        }
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    return balance(node);
}

int Wordlist::getCount(const string& word) {
    AVLTreeNode* current = root;
    while (current) {
        if (word < current->word){
            current = current->left;
        }
        else if (word > current->word){
            current = current->right;
        }
        else{
            return current->count;
        }
    }
    return 0;
}

bool Wordlist::contains(const string& word) {
    AVLTreeNode* current = root;
    while (current) {
        if (word < current->word){
            current = current->left;
        }
        else if (word > current->word){
            current = current->right;
        }
        else{
            return true;
        }
    }
    return false;
}

int Wordlist::differentWords() const {
    return size;
}

int Wordlist::totalWords() const {
    return totalWordsHelper(root);
}

int Wordlist::totalWordsHelper(AVLTreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    // Sum the counts of the left and right subtrees and the current node's count
    return node->count + totalWordsHelper(node->left) + totalWordsHelper(node->right);
}


string Wordlist::mostFrequent() const {
    // Throw an exception if the word list is empty
    if (!root) {
        throw std::invalid_argument("The word list is empty.");
    }

    string mostFrequentWord;
    unsigned int maxCount = 0;

    mostFrequentHelper(root, mostFrequentWord, maxCount);
    return mostFrequentWord + " " + to_string(maxCount);
}

void Wordlist::mostFrequentHelper(AVLTreeNode* node, string& word, unsigned int& maxCount) const {
    if (!node) return;

    // Check the current node
    if (node->count > maxCount) {
        maxCount = node->count;
        word = node->word;
    }

    // Recurse on left and right subtrees
    mostFrequentHelper(node->left, word, maxCount);
    mostFrequentHelper(node->right, word, maxCount);
}

void Wordlist::printWords() const {
    if (!root) {
        cout << "The word list is empty." << endl;
        return;
    }

    int index = 1; // To keep track of word indices for printing
    printWordsHelper(root, index);
}

void Wordlist::printWordsHelper(AVLTreeNode* node, int& index) const {
    if (!node){
        return;
    }

    // Recurse on the left subtree
    printWordsHelper(node->left, index);

    // Print the current node's word and count
    cout << index++ << ". " << setw(25) << left << node->word << node->count << endl;

    // Recurse on the right subtree
    printWordsHelper(node->right, index);
}

int Wordlist::singletons() const {
    return countSingletons(root);
}

// Helper function
int Wordlist::countSingletons(AVLTreeNode* node) const {
    if (node == nullptr)
        return 0;

    int count = 0;
    if (node->count == 1)  // Node is a singleton
        count = 1;

    // Recur on left and right children
    return count + countSingletons(node->left) + countSingletons(node->right);
}

// Prints useful statistics about the word list
void Wordlist::printStatistics() const
{
	cout << "Number of different words: " << differentWords() << endl;
	cout << "    Total number of words: " << totalWords() << endl;
	cout << "       Most frequent word: " << mostFrequent() << endl;
	cout << "     Number of singletons: " << singletons()
		<< setprecision(0) << fixed
		<< " (" << 100.0 * singletons() / differentWords() << "%)"
		<< endl;
}