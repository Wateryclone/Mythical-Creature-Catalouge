/*
Specification for Creature class
*/
#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Creature 
{
    private:
        string creatureID; // Primary key eg. "FNKS-BD"
        string name; // eg. "Phoenix"
        string category; // eg. "Bird"
        string history; // famous legend or myth associated with the creature 
                //eg."A mythical bird that cyclically regenerates or is reborn from its ashes, known in Greek, Egyptian, and Persian traditions."
        string habitat; // eg. "Deserts and mountains"
        string description; // eg. "Fiery bird with radiant plumage, capable of resurrection through immolation and rebirth."
        int releventYear; // year of first mention in history

    public:
        // Constructors
        Creature()
        {
            creatureID = "dummy";
            name = "dummy";
            category = "dummy";
            history = "dummy";
            habitat = "dummy";
            description = "dummy";
            releventYear = 0;
        }
        Creature(string id, string n, string cat, string hist,
                 string hab, string desc, int y)
                 {
                    creatureID = id;
                    name = n;
                    category = cat;
                    history = hist;
                    habitat = hab;
                    description = desc;
                    releventYear = y;
                 }
        // Setters
        void setCreatureID(const string& id) { creatureID = id; }
        void setName(const string& n) { name = n; }
        void setCategory(const string& cat) { category = cat; }
        void setHistory(const string& hist) { history = hist; }
        void setHabitat(const string& hab) { habitat = hab; }
        void setDescription(const string& desc) { description = desc; }
        void setReleventYear(int y) { releventYear = y; }

        // Getters
        string getCreatureID() const { return creatureID; }
        string getName() const { return name; }
        string getCategory() const { return category; }
        string getHistory() const { return history; }
        string getHabitat() const { return habitat; }
        string getDescription() const { return description; }
        int getReleventYear() const { return releventYear; }

        // Other methods
        // print a creature
        void vPrintCreature() const;
            
        // friend std::ostream& operator<<(std::ostream& os, const Creature& creature) 
        // {
        //     // you can use vPrintCreature, or custom print fields here
        //     os << "ID: " << creature.getCreatureID() << "\n";
        //     os << "Name: " << creature.getName() << "\n";
        //     // add the rest of the fields
        //     return os;
        // }

};

// vertical print a creature
inline void Creature::vPrintCreature() const
{
    cout << "Creature ID: " << creatureID << endl;
    cout << "Name: " << name << endl;
    cout << "Category: " << category << endl;
    cout << "History: " << history << endl;
    cout << "Habitat: " << habitat << endl;
    cout << "Description: " << description << endl;
    cout << "Year: " << releventYear << endl;
}

#endif

