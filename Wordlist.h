#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

class AVLTreeNode {
public:
	// Should have attributes named:
	// parent - pointer to parent
	// left - pointer to left child
	// right - pointer to right child
	// word - node's string data
	// count - number of times the word appears
	// height - node's height

	AVLTreeNode* parent;
	AVLTreeNode* left;
	AVLTreeNode* right;
	string word;
	int count;
	int height;

	// Constructors ...
	AVLTreeNode (const string& word){
		this->word = word;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
		this->count = 1;
		this->height = 0;
	}
};

// Wordlist class
class Wordlist
{
private:
	// Class attributes go here
	// Your class MUST have a root node named root (below)
	AVLTreeNode* root; // DO NOT REMOVE
	unsigned int size;
	
	// Helper functions
	AVLTreeNode* insertHelper(AVLTreeNode* node, const string& word);
    AVLTreeNode* removeHelper(AVLTreeNode* node, const string& word);
    AVLTreeNode* findMin(AVLTreeNode* node) const;
    AVLTreeNode* balance(AVLTreeNode* node);
    int height(AVLTreeNode* node) const;
    int getBalanceFactor(AVLTreeNode* node) const;
    AVLTreeNode* rotateLeft(AVLTreeNode* node);
    AVLTreeNode* rotateRight(AVLTreeNode* node);
    void destroyTree(AVLTreeNode* node);
    void copyTree(AVLTreeNode*& thisNode, AVLTreeNode* otherNode, AVLTreeNode* parent);
    void printWordsHelper(AVLTreeNode* node, int& index) const;
    void mostFrequentHelper(AVLTreeNode* node, string& word, unsigned int& maxCount) const;
    int countSingletons(AVLTreeNode* node) const;
	int totalWordsHelper(AVLTreeNode* node) const;

public:
	// public methods go here

	// Default Constructor
	Wordlist();

	// File constructor
	Wordlist(const string& filename);

	// Copy Constructor
	Wordlist(const Wordlist& other);

	// Default Operator
	Wordlist& operator=(const Wordlist& other);

	// Destructor
	~Wordlist();

	// Insert method
	void insert(const string& word);

	// Remove method
	bool remove(const string& word);

	// getCount method
	int getCount(const string& word);

	// contains method
	bool contains(const string& word);

	// differentWords method
	int differentWords() const;

	// mostFrequent method
	string mostFrequent() const;

	// singletons method
	int singletons() const;

	// totalWords method
	int totalWords() const;

	// Prints useful statistics about the word list
	void printStatistics() const;

	void printWords() const;

	// Returns the root of the AVL tree
	AVLTreeNode* getRoot() const { return root; }; // DO NOT REMOVE

	void printTree(AVLTreeNode* node) const;
};