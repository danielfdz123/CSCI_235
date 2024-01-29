//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//September 11, 2023
//Project 2

#include <iostream>
#include <string>
#include <vector>
#include "Character.hpp"
#ifndef RANGER_HPP_
#define RANGER_HPP_

struct Arrows 
{
    std::string type_;
    int quantity_;
};

class Ranger : public Character
{
    private:
        std::vector<Arrows> arrows_;
        std::vector<std::string> affinity_;
        bool has_companion_;

    public:
    //Constructor
        Ranger();
    
    //P Constructor
        Ranger(const std::string& name, const std::string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, 
        const std::vector<Arrows>& arrows = {}, const std::vector<std::string>& affinity = {}, bool companion = false); 

    //Setters
        void setCompanion(const bool& companion);
        bool addAffinity(const std::string& affinity);
    
    //Arrow stuff
        bool addArrows(const std::string& arrow_type, int quantity);
        bool fireArrow(const std::string& arrows);

    //Getters
        std::vector<Arrows> getArrows() const;
        std::vector<std::string> getAffinities() const;
        bool getCompanion() const;
};

#endif