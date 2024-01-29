//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//September 11, 2023
//Project 2

#include <iostream>
#include <cctype>
#include "Scoundrel.hpp"

//Constructor gives default calues to variables
Scoundrel::Scoundrel()
{
    Character();
    faction_ = "NONE";
    dagger_ = WOOD; 
    has_disguise_ = false;   
}

//Gives the Scoundrel role its default stats (P Constructor)
//Get infro from Character.cpp & hpp file
//New variables and values are intorduced to help create the SCOUNDREL role
Scoundrel::Scoundrel(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy, 
std::string dagger, std::string faction, bool disguise):
Character(name, race, vitality, armor, level, enemy),
faction_{faction},
has_disguise_{disguise}
{
    setDagger(dagger);
    if(!setFaction(faction))
    {
        faction_ = "NONE";                  //Faction is set to none if there's an invalid input (also the default value)
    }
}

//SETTERS
void Scoundrel::setDagger(const std::string& dagger)
{
    std::string ligorio = "";                             //Implement an empty string variable
    for(int i = 0; i < dagger.length(); i++)              //Loops throght each character in the dagger variable
    {
        if(isalpha(dagger[i]))                          
        {
            ligorio = ligorio + char(toupper(dagger[i]));           //Converts lowercase letetrs to uppercase
        }
    }
    if(ligorio == "BRONZE")
    {
        dagger_ = BRONZE;                               //Dagger is set to BRONZE if satisfied
    }
    else if(ligorio == "IRON")
    {
        dagger_ = IRON;                                 //Dagger is set to IRON if satisfied
    }
    else if(ligorio == "STEEL")
    {
        dagger_ = STEEL;                                //Dagger is set to STEEL if satisfied
    }
    else if(ligorio == "MITHRIL")
    {
        dagger_ = MITHRIL;                              //Dagger is set to MITHRIL if satisfied
    }
    else if(ligorio == "ADAMANT")
    {
        dagger_ = ADAMANT;                              //Dagger is set to ADAMANT if satisfied
    }
    else if(ligorio == "RUNE")
    {
        dagger_ = RUNE;                                 //Dagger is set to RUNE if satisfied
    }
    else
    {
        dagger_ = WOOD;                                 //Dagger is set to WOOD if satisfied
    }
}

bool Scoundrel::setFaction(const std::string& faction)
{
    std::string ligorio = "";                             //Implement an empty string variable
    for(int i = 0; i < faction.length(); i++)             //Loops throght each character in the faction variable
    {
        if(isalpha(faction[i]))                          
        {
            ligorio = ligorio + char(toupper(faction[i]));              //Converts characters to uppercase from lowercase
        }
    }
    if(ligorio == "NONE" || ligorio == "CUTPURSE" || ligorio == "SHADOWBLADE" || ligorio == "SILVERTONGUE")    //If the string is empty, then the name is set to "NAMELESS" by default
    {
        faction_ = ligorio;                 //Faction is set to true and is set equal to the variable from the private member section (also returns true)
        return true;
    }
    else
    {
        return false;                      //Returns false if nothing is satisfied
    }
}

void Scoundrel::setDisguise(const bool& disguise)
{
    has_disguise_ = disguise;              //Sets disguise to true or false (False is the default value)
}

//GETTERS
std::string Scoundrel::getDagger() const
{
    if(dagger_ == BRONZE)
    {
        return "BRONZE";                     //Returns a BRONZE Dagger 
    }
    else if(dagger_ == IRON)
    {
        return "IRON";                       //Returns an IRON Dagger 
    }
    else if(dagger_ == STEEL)
    {
        return "STEEL";                      //Returns a STEEL Dagger 
    }
    else if(dagger_ == MITHRIL)
    {
        return "MITHRIL";                    //Returns a MITHRIL Dagger 
    }
    else if(dagger_ == ADAMANT)
    {
        return "ADAMANT";                    //Returns an ADAMANT Dagger 
    }
    else if(dagger_ == RUNE)
    {
        return "RUNE";                      //Returns a RUNE Dagger 
    }
    else if(dagger_ == WOOD)
    {
        return "WOOD";                      //Returns a WOODEN Dagger 
    }
    else
    {
        return "NONE";                      //Returns a Dagger... oh wait there IS NO DAGGER. So the character doesnt have a dagger 
    }
}

std::string Scoundrel::getFaction() const
{
    return faction_;                        //Returns the faction value when prompted
}

bool Scoundrel::hasDisguise() const
{
    return has_disguise_;                   //Returns if the character has a disguise or not
}