//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//August 30, 2023
//Project 1 

#include <iostream>
#include <string>
#include <cctype>
#include "Character.hpp"

//Gives character its default stats n stuff (P constructor)
Character::Character(std::string name, std::string race, int vitality, int armor, int level, bool enemy):
    name_{name}, vitality_{vitality}, armor_{armor}, level_{level}, enemy_{enemy}
  {
    setName(name);
    setRace(race);
    enemy_ = enemy;

    if (armor >= 0)         //Checks if armor is positive, if it is then nothing is done. Otherwise set to 0
    {
        armor_ = armor;
    } 
    else 
    {
        armor_ = 0;
    }

    if (vitality >= 0)      //Checks if vitality is positive, if it is then nothing is done. Otherwise set to 0
    {
        vitality_ = vitality;
    } 
    else 
    {
        vitality_ = 0;
    }

    if (level >= 0)         //Checks if level is positive, if it is then nothing is done. Otherwise set to 0
    {
        level_ = level;
    } 
    else 
    {
        level_ = 0;
    }
}

//Constructor gives default values to the variables
Character::Character()
{
    name_ = "NAMELESS";
    race_ = NONE;
    vitality_ = 0;
    armor_ = 0;
    level_ = 0;
    enemy_ = false;
}

//SETTERS
void Character::setName(const std::string& name)
{
    std::string ligorio = "";                         //Implement an empty string variable
    for(int i = 0; i < name.length(); i++)            //Loops throght each character in the name variable
    {
        if(isalpha(name[i]))                          
        {
            ligorio = ligorio + char(toupper(name[i]));
        }
    }
    if(ligorio == "")                                //If the string is empty, then the name is set to "NAMELESS" by default
    {                                                //Otherwise, name_ is set equal to the string variable
        name_ = "NAMELESS";
    }
    else
    {
        name_ = ligorio;
    }
}
void Character::setRace(const std::string& race)
{
    //Race stuff woo 
    if(race == "HUMAN")                              //The race is set to HUMAN if the race is human
    {
        race_ = HUMAN;
    }
    else if(race == "ELF")                           //The race is set ELF if the race is elf
    {
        race_ = ELF;
    } 
    else if(race == "DWARF")                         //The race is set to DWARF if the race is dwarf
    {
        race_ = DWARF;
    }
    else if(race == "LIZARD")                        //The race is set to LIZARD if the race is lizard
    {
        race_ = LIZARD;
    }
    else if(race == "UNDEAD")                        //The race is set to UNDEAD if the race is undead
    {
        race_ = UNDEAD;
    }
    else                                             //If nothing is satisfied, then the race is set to NONE
    {
        race_ = NONE;
    }
}
void Character::setVitality(const int& vitality)
{
    if(vitality >= 0)                                //Sets default vitality value if its 0 or greater
    {
        vitality_ = vitality;
    }
}
void Character::setArmor(const int& armor)    
{
    if(armor >= 0)                                  //Sets default armor value if its 0 or greater
    {
        armor_ = armor;
    }
}
void Character::setLevel(const int& level)         
{
    if(level >= 0)                                  //Sets default level value if its 0 or greater
    {
        level_ = level;
    }
}
void Character::setEnemy()
{
    enemy_ = true;                                  //Default value for the enemy is true
}

//GETTERS
std::string Character::getName() const
{
    return name_;                                   //Returns the name if prompted
}
std::string Character::getRace() const
{
    if(race_ == HUMAN)                              //Loops through all different possibilities for race, and returns the one that is satisfied
    {
        return "HUMAN";                             //If satisfied, race is returned as HUMAN
    }
    else if(race_ == ELF)
    {
        return "ELF";                               //If satisfied, race is returned as ELF
    } 
    else if(race_ == DWARF)
    {
        return "DWARF";                             //If satisfied, race is returned as DWARF
    }
    else if(race_ == LIZARD)
    {
        return "LIZARD";                            //If satisfied, race is returned as LIZARD
    }
    else if(race_ == UNDEAD)
    {
        return "UNDEAD";                            //If satisfied, race is returned as UNDEAD
    }
    else
    {
        return "NONE";                              //Otherwise, race is returned as NONE
    }
}
int Character::getVitality() const
{
    return vitality_;                              //Returns vitality value
}
int Character::getArmor() const
{
    return armor_;                                 //Returns armor value
}
int Character::getLevel() const
{
    return level_;                                 //Returns level value
}
bool Character::isEnemy() const
{
    return enemy_;                                 //Returns enemy status as TRUE or FALSE
}