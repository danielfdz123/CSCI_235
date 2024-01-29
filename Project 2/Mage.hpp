//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//September 11, 2023
//Project 2

#include <iostream>
#include <string>
#include "Character.hpp"
#ifndef MAGE_HPP_
#define MAGE_HPP_

class Mage : public Character
{
    private:
        std::string school_of_magic_;
        std::string weapon_;
        bool can_summon_incarnate_;

    public:
    //Constructor
        Mage();

    //P Constructor
        Mage(const std::string& name, const std::string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, 
        const std::string& school = "NONE", const std::string& weapon = "NONE", bool summon = false);
    
    //Setters
        bool setSchool(const std::string& school);
        bool setCastingWeapon(const std::string& weapon);
        void setIncarnateSummon(const bool& summon);

    //Getters
        std::string getSchool() const;
        std::string getCastingWeapon() const;
        bool hasIncarnateSummon() const;
};

#endif