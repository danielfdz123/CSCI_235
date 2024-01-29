//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//September 11, 2023
//Project 2

#include <iostream>
#include <string>
#include "Character.hpp"
#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

class Barbarian : public Character
{
    private:
        std::string main_weapon_;
        std::string secondary_weapon_;
        bool enraged_;

    public:
    //Constructor
        Barbarian();

    //P Constructor
        Barbarian(std::string name, std::string race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false,        
        std::string weapon1 = "NONE", std::string weapon2 = "NONE", bool enraged = false);

    //Setters
        bool setMainWeapon(const std::string& weapon1);
        bool setSecondaryWeapon(const std::string& weapon2);
        void setEnrage(const bool& enraged);

    //Getters
        std::string getMainWeapon() const;
        std::string getSecondaryWeapon() const;
        bool getEnrage() const;

    //Neither?
        void toggleEnrage();
};

#endif