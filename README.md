# Wordlist Class - AVL Tree-Based Word Frequency Counter

## **Objective**

The Wordlist class is designed to efficiently count word frequencies from a text file using an AVL Tree, a self-balancing binary search tree. This project demonstrates advanced data structures to handle word frequency analysis and provides key statistics, such as the total number of words, most frequent words, and singletons.

---

## **Features**

1. **AVL Tree Implementation**
   - **Self-Balancing:** Maintains \(O(\log n)\) time complexity for insertions, deletions, and lookups using rotations.
   - **Custom Node Structure:** Each node stores:
     - **`word`:** The word being tracked.
     - **`wordCount`:** Frequency of the word.
     - **`height`:** Height of the node in the tree.
     - **Pointers:** Links to parent, left, and right child nodes.

2. **Wordlist Class**
   - **File Input:** Reads text files and inserts words into the AVL Tree.
   - **Statistics:**
     - **Unique Words:** Total count of different words in the file.
     - **Total Word Count:** Sum of all word frequencies.
     - **Most Frequent Word:** Identifies the word with the highest frequency.
     - **Singletons:** Counts words that appear only once, along with the percentage of singletons.
   - **Operations:**
     - Insert and remove words, ensuring AVL Tree balance.
     - Retrieve word frequencies and check if a word exists.
   - **Output:** 
     - Print word frequencies in ascending order.
     - Display comprehensive statistics.

---

## **Code Overview**

1. **Wordlist.h**
   - Defines the `Wordlist` class and the `AVLTreeNode` structure.
   - Key Components:
     - Helper methods for AVL Tree operations, such as rotations, balancing, and traversals.
     - Public methods for word insertion, deletion, frequency retrieval, and statistical analysis.

2. **Wordlist.cpp**
   - Implements the methods declared in `Wordlist.h`.
   - Highlights:
     - **Insert:** Adds a word to the AVL Tree or increments its frequency.
     - **Remove:** Deletes a word while preserving AVL balance.
     - **Statistics:** Uses recursive functions for efficient word counting and finding the most frequent word.
     - **Printing:** Outputs word frequencies in sorted order and displays key statistics.

---

## **How It Works**

1. **Word Insertion**
   - Words are inserted into the AVL Tree, either as new nodes or by incrementing the frequency of existing nodes.
   - The tree automatically balances itself using rotations (left, right, or combinations) to maintain optimal performance.

2. **Word Removal**
   - Deletes a word by finding its node, replacing it if necessary, and rebalancing the tree.

3. **Statistical Analysis**
   - Computes:
     - **Unique Words:** Number of distinct nodes in the tree.
     - **Total Words:** Sum of word frequencies across all nodes.
     - **Most Frequent Word:** Identifies the word with the maximum frequency using an in-order traversal.
     - **Singletons:** Counts nodes with a frequency of 1.

4. **Output**
   - Provides a sorted list of words with their frequencies.
   - Displays statistical summaries, including singleton percentages.

---

## **How to Use**

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/wordlist-avl.git
   cd wordlist-avl
   ```

2. **Include the Files:**
   - Add `Wordlist.h` and `Wordlist.cpp` to your project.

3. **Example Usage:**
   ```cpp
   #include "Wordlist.h"

   int main() {
       Wordlist wl("sample.txt");

       wl.printWords();         // Print all words in ascending order with frequencies.
       wl.printStatistics();    // Display statistics (unique words, singletons, etc.).

       if (wl.contains("example")) {
           cout << "The word 'example' appears " << wl.getCount("example") << " times." << endl;
       }

       return 0;
   }
   ```

---

## **Key Features of the AVL Tree**

- **Rotations for Balancing:**
  - Single and double rotations to ensure tree balance after every modification.
- **Efficiency:** 
  - Ensures optimal time complexity for word insertions and lookups, even with large datasets.

---

## **Conclusion**

This project showcases an efficient and robust implementation of an AVL Tree for word frequency analysis. The Wordlist class offers advanced functionality, such as statistical insights and efficient data management, making it a practical tool for text processing tasks.
