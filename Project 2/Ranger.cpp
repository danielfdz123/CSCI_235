//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//September 11, 2023
//Project 2

#include <iostream>
#include <cctype>
#include <vector>
#include "Ranger.hpp"

//Constructor
Ranger::Ranger()
{
    Character();
    arrows_= {};
    affinity_ = {};
    has_companion_ = false;    
}

//Gives the Mage role its deafult stats (P contstructor)
//Get infro from Character.cpp & hpp file
//New variables and values are intorduced to help create the RANGER role
Ranger::Ranger(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy,
const std::vector<Arrows>& arrows, const std::vector<std::string>& affinity, bool companion):
Character(name, race, vitality, armor, level, enemy),
has_companion_{companion}
{
    for(int i = 0; i < arrows.size(); i++)
    {
        addArrows(arrows[i].type_ , arrows[i].quantity_);          //Adds number of arrows depending on quantity and arrow type
    }
    for(int i = 0; i < affinity.size(); i++)
    {
        addAffinity(affinity[i]);                                  //Adds affinity to player depending on its type
    }
}

//Setters
bool Ranger::addAffinity(const std::string& affinity)
{
    std::string ligorio = "";                              //Implement an empty string variable
    for(int i = 0; i < affinity.length(); i++)             //Loops throght each character in the affinity variable
    {
        if(isalpha(affinity[i]))                          
        {
            ligorio = ligorio + char(toupper(affinity[i]));
        }
    }
    if(ligorio == "FIRE" || ligorio == "WATER" || ligorio == "POISON" || ligorio == "BLOOD")
    {
        for(int i = 0; i < affinity_.size(); i++)
        {
            if(affinity_[i] == ligorio)
            {
                return false;                       //Returns false if Affinity doesn't match the current vector slot it's checking
            }
        }
        affinity_.push_back(ligorio);               //Checks next affinity value in the next vector slot
        return true;                                //If affinity matches, then it returns true
    }
    else
    {
        return false;                               //Returns false if all else fails and nothing is satisfied
    }
}

void Ranger::setCompanion(const bool& companion)
{
    has_companion_ = companion;                     //Sets companion value
}

//Arrow stuff
bool Ranger::addArrows(const std::string& arrows_type, int quantity)
{
    std::string beef = "";                                    //Implement an empty string variable
    for(int i = 0; i < arrows_type.length(); i++)             //Loops throght each character in the arrow type variable
    {
        if(!isalpha(arrows_type[i]))                          
        {
            return false;                                     //Returns false if arrow type is unknown or invalid (invalid characters, etc)
        }
        else
        {  
            beef = beef + char(toupper(arrows_type[i]));      //Makes any lowercase letters to uppercase
        }
    }
    for(int i = 0; i < arrows_.size(); i++)
    {
        //If the input string is neither of the 5 or less than 0, then it'll return false since its an invalid input
        if(beef != "WOOD" && beef != "FIRE" && beef != "WATER" && beef != "POISON" && beef != "BLOOD" || quantity <= 0)
        {
            return false;                   
        }
    }
    for(int i = 0; i < arrows_.size(); i++)                 //Loops through each character in the input
    {
        if(beef == arrows_[i].type_)                        //Checks if the string satisfies any of the 5 arrow types
        {
            arrows_[i].quantity_ += quantity;               //If it does, then arrow type is added to the characters inventory and returns true
            return true;
        }
    }
    Arrows a1;
    a1.quantity_ = quantity;
    a1.type_ = beef;
    arrows_.push_back(a1);
    return true;
}

bool Ranger::fireArrow(const std::string& arrows)
{
    std::string ligorio = "";                             //Implement an empty string variable
    for(int i = 0; i < arrows.length(); i++)              //Loops throght each character in the arrows variable
    {
        if(isalpha(arrows[i]))                          
        {
            ligorio = ligorio + char(toupper(arrows[i]));           //Converts the string to all uppercase
        }
    }
    for(int i = 0; i < arrows_.size(); i++)                          
    {
        if(arrows_[i].type_ == ligorio && arrows_[i].quantity_ > 0) 
        {
            arrows_[i].quantity_--;                                 //If arrow type matches and is greater than 0, then 1 arrow is taken from the characters inventory
            return true;
        }
    }
    return false;
}

//Getters
std::vector<std::string> Ranger::getAffinities() const
{
    return affinity_;                                       //Returns affinity when prompted
}

bool Ranger::getCompanion() const
{
    return has_companion_;                                  //Returns companion when prompted
}

std::vector<Arrows> Ranger::getArrows() const
{
    return arrows_;                                         //Returns arrows when prompted
}