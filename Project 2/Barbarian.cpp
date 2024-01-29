//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//September 11, 2023
//Project 2

#include <iostream>
#include <cctype>
#include "Barbarian.hpp"

//Constructor
Barbarian::Barbarian()
{
    Character();
    main_weapon_ = "NONE";
    secondary_weapon_ = "NONE";
    enraged_ = false;
}

//P Constructor
//Implements variables from Character.cpp & character.hpp
//Implements variables to help build the Barbarian role from Barbarian.hpp
Barbarian::Barbarian(std::string name, std::string race, int vitality, int armor, int level, bool enemy,
std::string weapon1, std::string weapon2, bool enraged):
Character(name, race, vitality, armor, level, enemy), 
main_weapon_{weapon1},
secondary_weapon_{weapon2},
enraged_{enraged}
{
    setMainWeapon(weapon1);
    setSecondaryWeapon(weapon2);
}

//Setters
bool Barbarian::setMainWeapon(const std::string& weapon1)
{
    std::string ligorio = "";                            //Implement an empty string variable
    for(int i = 0; i < weapon1.length(); i++)            //Loops throght each character in the weapon1 variable
    {
        if(isalpha(weapon1[i]))                          
        {
            ligorio = ligorio + char(toupper(weapon1[i]));       //Makes the characters UPPERCASE
        }
    }
    if(ligorio != "")                       //If the string is not empty, then wepon1 exists and is set to true
    {
        main_weapon_ = ligorio;
        return true;
    }
    else                                    //If string is empty, then weapon1 is set to false (doesn't exist or is invalid)
    {
        return false;
    }
}

bool Barbarian::setSecondaryWeapon(const std::string& weapon2)
{
    std::string ligorio = "";                            //Implement an empty string variable
    for(int i = 0; i < weapon2.length(); i++)            //Loops throght each character in the weapon2 variable
    {
        if(isalpha(weapon2[i]))                          
        {
            ligorio = ligorio + char(toupper(weapon2[i]));          //Makes the characters UPPERCASE
        }
    }
    if(ligorio != "")                                   //If the string is not empty, then wepon2 exists and is set to true
    {
        secondary_weapon_ = ligorio;
        return true;
    }
    else                                                //If string is empty, then weapon2 is set to false (doesn't exist or is invalid)
    {
        return false;
    }
}

void Barbarian::setEnrage(const bool& enraged)
{
    enraged_ = enraged;                                 //Sets enraged value
}

//Getters
std::string Barbarian::getMainWeapon() const
{
    return main_weapon_;                                //Returns primary weapon when called
}

std::string Barbarian::getSecondaryWeapon() const
{
    return secondary_weapon_;                           //Returns secondary weapon when called
}

bool Barbarian::getEnrage() const
{
    return enraged_;                                    //Returns if barbarian is enraged or not
}

void Barbarian::toggleEnrage()
{
    if(enraged_ == true)                                //Negates the enraged status (True -> False // False -> True)
    {
        enraged_ = false;
    }
    else
    {
        enraged_ = true;
    }
}