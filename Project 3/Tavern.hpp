//CSCI 235 - Fall 2023
//Project 3: The Tavern
//Daniel Andres Fernandez
//September 26, 2023
//Tavern.hpp

#include <iostream>
#include <string>
#include <cmath>
#include "ArrayBag.hpp"
#include "Character.hpp"
#ifndef TAVERN_HPP_
#define TAVERN_HPP_

class Tavern: public ArrayBag<Character> 
{
    private:
        int lvl_sum;
        int enemy_count;

    public:
    //Constructor
        Tavern();

    //Enter/Exit Tavern
        bool enterTavern(const Character& Maryash);
        bool exitTavern(const Character& Maryash);

    //Getters & Calculations
        int getLevelSum() const;
        int calculateAvgLevel() const;
        int getEnemyCount() const;
        double calculateEnemyPercentage() const;
    
    //Reports
        int tallyRace(const std::string& race) const; 
        void tavernReport() const;
};
#endif