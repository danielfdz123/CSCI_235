//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//September 11, 2023
//Project 2

#include <iostream>
#include <string>
#include "Character.hpp"
#ifndef SCOUNDREL_HPP_
#define SCOUNDREL_HPP_

enum Dagger{WOOD, BRONZE, IRON, STEEL, MITHRIL, ADAMANT, RUNE};                     //Possible Dagger types

class Scoundrel : public Character
{
    private:
        Dagger dagger_;
        std::string faction_;
        bool has_disguise_;

    public:
    //Constructor
        Scoundrel();
        
    //P constructor                                                             
        Scoundrel(const std::string& name, const std::string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, 
        std::string dagger = "WOOD", std::string faction = "NONE", bool disguise = false);    
    //Setters
        void setDagger(const std::string& dagger);
        bool setFaction(const std::string& faction);
        void setDisguise(const bool& disguise);
        
    //Getters
        std::string getDagger() const;
        std::string getFaction() const;
        bool hasDisguise() const;
};

#endif