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