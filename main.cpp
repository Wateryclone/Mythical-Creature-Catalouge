#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

#include "BinaryTree.h"
#include "Creature.h"

using namespace std;

void printWelcome();
void buildCreatureList();
void runMainMenu();
void printGoodbye();

int main() {
    
    string filename;
    BinaryTree<Creature> Ctree;

    printWelcome();
    buildCreatureList();
    runMainMenu();
    printGoodbye();
    // cout << "Enter the name of the file containing the creature data: ";
    // getline(cin, filename);
  

}
