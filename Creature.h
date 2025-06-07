/*
Specification for Creature class
*/
#ifndef CREATURE_H
#define CREATURE_H

#include <string>

using std::string;

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
        Creature();
        Creature(string id, string n, string cat, string hist,
                 string hab, string desc, int y);
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
        //.......tbd

};

#endif

