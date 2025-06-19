# Screen Manager: Ye Zhang


I am student-4 in our group. I am in charge of the screen output manager. Specifically, I implemented (further cordinated by others) printWelcom (i.e., menuPrompt), buildDataStructure, insertManager, searchManager, deleteManager, undoDeleteManager, statisticsManager, print options (iDisplay, hDisplay, vPrintCreature() in hashtable).

**printWelcom (i.e., menuPrompt)**: 

the main menu for user to option, including 
```
Main Menu:
  [L] - Load data file
  [A] - Add data
  [S] - Search data (Primary key: creature_id)
  [D] - Delete data
  [U] - Undo delete
  [P] - Print data
  [T] - Show statistics
  [W] - Write to file
  [H] - Help
  [Q] - Quit
  (hidden option) [N] - Print indented tree
```

**buildDataStructure**

Load data from a file (one data per line). Read each line and insert to HashTable and BST. In our project, HashTable (with chaining technique for collision) is the main data structure to store all item information, BST is to store primary key and index in HashTable. So the first step is to insert an item in hashTable and return the hash index. Then insert primary key and hash index to BST

**insertManager**

The main logic of insert an item is the same as *buildDataStructure*, the only difference is this is for manually input a new item with required features (e.g., creature_id, name, history...). If the input key is aleady in our database, then prompt to user to re-enter the new item.

**searchManager**

Search an item by an input primary key (i.e., creature_id). If found, display the found item (all attributes printed vertically with vPrintCreature() in HashTable.cpp), otherwise, print "Creature ### not found""

**deleteManager**

First search if the item to delete is in our datastructure. If yes, remove the item from HashTable and BST, otherwise "CANNOT delete creature ###"

**undoDeleteManager**

Use a stack to temporarly store the item after delete. When user aims to undo delete, pop the top item in the stack and re-insert to our database. This function allow users undo delete continuously until all deleted items are poped (i.e., stack is empty). Note that when user write the data (with potential munipulations), this stack is clearned which means user cannot undo delete (prompt to user).

**statisticsManager**

Call HashTable function to get statistics, e.g., load factore, longest chain (hash key collision), empty bucket, and etc..

**[hidden] indentedTree**

Call BST printTree() function to print indented tree (wiht primary key for stored data). This is a hidden option.

# Binary Search Tree & File I/O: Shunyao Jin

I am student-3 in our group. I am in charge of the Binary Search Tree and File I/O modules. Specifically, I implemented the core BST data structure (for indexing creature IDs) and a `FileIO` class (for loading, managing, and persisting creature data). Below is a summary of my contributions.

## Binary Search Tree

**BinaryNode Class**:

Defines the node type for the BST, storing a `key` (creature ID) and an `index` (position in the hash table), as well as pointers to left and right children.

**insert (BST)**:

Wrapper for recursive insertion of a `(key, index)` pair. Prevents duplicates by first searching the tree, then inserts a new `BinaryNode` and increments the node count on success.

**search (BST)**:

Wrapper for recursive lookup of a creature ID. Returns `true` and outputs the corresponding hash-table index if found, or `false` otherwise.

**remove (BST)**:

Wrapper for deletion by key. Uses in-order successor when the node has two children, updates subtree links, and decrements the node count on success.

**findSmallest & findLargest (BST)**:

Public methods to retrieve the hash-table index of the smallest or largest key in the BST, respectively.

**setIndex (BST)**:

Allows updating the stored index for a given key, used during hash-table rehashing to keep the BST in sync.

**printTree (BST)**:

Inherited from `BinaryTree`, this method prints the tree as an indented list of keys with their levels, used for debugging and display.

## File I/O

**init (FileIO)**:

Opens the input file, counts lines to choose an initial prime-sized table, constructs the hash table, and calls `loadData` to populate both structures.

**loadData (FileIO)**:

Reads each line, parses into a `Record`, constructs a `Creature` object, inserts it into the hash table, then into the BST; triggers `rehash` if load factor exceeds 0.75.

**insert (FileIO)**:

At runtime, inserts a new `Creature`: checks for duplicates via `search`, appends to `hashTable` (with rehashing as needed), then updates the BST.

**search (FileIO)**:

Delegates to `bst.search` to test for the presence of a given creature ID.

**del (FileIO)**:

Deletes a creature ID from both the BST and the hash table.

**saveData (FileIO)**:

Writes all creatures from `hashTable` back to a text file in the original semicolon-delimited format, overwriting or creating as specified.

**getHashTableSize (FileIO)**:

Returns the current number of buckets in the hash table.

**getHashTableloadFactor (FileIO)**:

Returns the current load factor of the hash table.

**getHashTableLongestChain (FileIO)**:

Returns the length of the longest collision chain in the hash table.

**getHashTableEmptyBuckets (FileIO)**:

Returns the number of empty buckets in the hash table.

**inOrder (FileIO)**:

Exposes an in-order traversal over BST keys for display purposes.

**indentedTree (FileIO)**:

Calls `bst.printTree()` to display the BST’s structure as an indented list.

**getCreature (FileIO)**:

Retrieves a `Creature` object by ID: looks up the index via `bst.search` then fetches from `hashTable`.

**is_ready (FileIO)**:

Checks whether the input file stream is open and ready for I/O.

**rehash, isPrime & nextPrime (FileIO)**:

Implements dynamic resizing: when `hashTable.loadFactor()` > 0.75, `rehash` allocates a larger prime-sized table, reinserts all creatures, and updates BST indexes via `setIndex`.

**setFileName & Destructor (FileIO)**:

Allows changing the target filename and ensures proper cleanup of `hashTable` and file streams.
