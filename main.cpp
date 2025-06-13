#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

#include "BinaryTree.h"
#include "Creature.h"

using namespace std;

void printWelcome(string &);
void buildCreatureList(HashTable<Creature> &, BinaryTree<Creature> &, string<Creature> &);
void runMainMenu(HashTable<Creature> &, BinaryTree<creature> &);
void printGoodbye();

int main() {
    
    string filename;
    BinaryTree<Creature> Ctree;
    HashTable<Creature> Ctable;

    printWelcome();
    buildCreatureList(Ctable, Ctree, filename);
    runMainMenu(Ctable, Ctree);
    printGoodbye();
    // cout << "Enter the name of the file containing the creature data: ";
    // getline(cin, filename);
  

}
