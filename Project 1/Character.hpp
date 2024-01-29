//Daniel Andres Feranndez
//daniel.fernandez16@myhunter.cuny.edu
//August 30, 2023
//Project 1

#include <iostream>
#include <string>
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

enum Race {NONE, HUMAN, ELF, DWARF, LIZARD, UNDEAD};

class Character
{
    private:
        std::string name_;
        Race race_;
        int vitality_;
        int armor_;
        int level_;
        bool enemy_;
    
    public:
    //Constructors
        Character();

    //P Constructors
        Character(std::string name, std::string race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false);

    //setters
        void setName(const std::string& name);
        void setRace(const std::string& race);
        void setVitality(const int& vitality);
        void setArmor(const int& armor);
        void setLevel(const int& level);
        void setEnemy();
        
    //getters
        std::string getRace() const;
        std::string getName() const;
        int getVitality() const;
        int getArmor() const;
        int getLevel() const;
        bool isEnemy() const;
};

#endif