#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

#include "BinaryTree.h"
#include "Creature.h"

using namespace std;

void buildTreeAndHash(const string& filename, BinaryTree<Creature>& Ctree);
void displayManager(const BinaryTree<Creature>& Ctree);
void searchManager(const BinaryTree<Creature>& Ctree);
void deleteManager(BinaryTree<Creature>& Ctree);
void updateManager(BinaryTree<Creature>& Ctree);

int main() {
    
    string filename;
    BinaryTree<Creature> Ctree;

    cout << "Enter the name of the file containing the creature data: ";
    getline(cin, filename);
    buildTreeAndHash(filename, Ctree); // maybe use a different name or two functions

    displayManager(Ctree); // these functions will do a lot feel free to change it as needed
    searchManager(Ctree);
    deleteManager(Ctree);
    updateManager(Ctree);

}
