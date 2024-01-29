//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//September 11, 2023
//Project 2

#include <iostream>
#include <cctype>
#include "Mage.hpp"

//Constructor
Mage::Mage()
{
    Character();
    school_of_magic_ = "NONE";
    weapon_ = "NONE";
}

//Gives the Mage role its deafult stats (P contstructor)
//Get infro from Character.cpp & hpp file
//New variables and values are intorduced to help create the Mage role
Mage::Mage(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy,
const std::string& school, const std::string& weapon, bool summon):                      
Character(name, race, vitality, armor, level, enemy), 
can_summon_incarnate_{summon}
{
    if(!setSchool(school))
    {
        school_of_magic_ = "NONE";                          //School of Magic is set to none by default
    }

    if(!setCastingWeapon(weapon))
    {
        weapon_ = "NONE";                                   //Weapon is set to none by default
    }
}

//SETTERS
bool Mage::setSchool(const std::string& school)
{
    std::string ligorio = "";                           //Implement an empty string variable
    for(int i = 0; i < school.length(); i++)            //Loops throght each character in the school variable
    {
        if(isalpha(school[i]))                          
        {
            ligorio = ligorio + char(toupper(school[i]));
        }
    }

    //If the characters match any of the 3 conditions, then the school is assigned to its corresponding part (Elemental, Necromancy, or Illusion)
    //Otherwise, boolean value is set to false, which sets the school to NONE
    if(ligorio == "ELEMENTAL" || ligorio == "NECROMANCY" || ligorio == "ILLUSION")
    {
        school_of_magic_ = school;                                         
        return true;
    }
    else
    {
        return false;
    }
}

bool Mage::setCastingWeapon(const std::string& weapon)
{
    std::string ligorio = "";                           //Implement an empty string variable
    for(int i = 0; i < weapon.length(); i++)            //Loops throght each character in the weapon variable
    {
        if(isalpha(weapon[i]))                          
        {
            ligorio = ligorio + char(toupper(weapon[i]));
        }
    }

    //If the characters match any of the 2 conditions, then the weapon is assigned to its corresponding part (Wind or Staff)
    //Otherwise, boolean value is set to false, which sets the weapon value to NONE
    if(ligorio == "WAND" || ligorio == "STAFF")
    {
        weapon_ = weapon;                                         
        return true;
    }
    else
    {
        return false;
    }
}

void Mage::setIncarnateSummon(const bool& summon)
{
    can_summon_incarnate_ = summon;         //Sets default summoning ability
}

//GETTERS
std::string Mage::getSchool() const
{
    return school_of_magic_;                //Returns the Mage's school when prompted
}

std::string Mage::getCastingWeapon() const
{
    return weapon_;                         //Returns the Mage's weapon when prompted
}

bool Mage::hasIncarnateSummon() const
{
    return can_summon_incarnate_;           //Returns the Mage's summon ability as TRUE or FALSE
}