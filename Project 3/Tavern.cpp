//CSCI 235 - Fall 2023
//Project 3: The Tavern
//Daniel Andres Fernandez
//September 26, 2023
//Tavern.cpp

#include "Tavern.hpp"

//Constructor
Tavern::Tavern():lvl_sum{0}, enemy_count{0} 
{}

//Enter/Exit Tavern
bool Tavern::enterTavern(const Character& enter)
{
    if(add(enter)) 
    {
        lvl_sum += enter.getLevel();
        if(enter.isEnemy()) 
        {
            enemy_count++;
        }
        return true;
    }
    return false;
}
bool Tavern::exitTavern(const Character& exit)
{
    if (remove(exit)) 
    {
        lvl_sum -= exit.getLevel();
        if (exit.isEnemy()) 
        {
            enemy_count--;
        }
        return true;
    }
    return false;
}

//Getters and Calculation Stuff
int Tavern::getLevelSum() const
{
    return lvl_sum;
}
int Tavern::calculateAvgLevel() const
{
    double sum = lvl_sum;
    return std::round(sum/item_count_);
}
int Tavern::getEnemyCount() const
{
    return enemy_count;
}
double Tavern::calculateEnemyPercentage() const
{
    double a = enemy_count;
    double percentage = std::round((a/item_count_)*10000)/100.0;
    return percentage;
}

//Reports
int Tavern::tallyRace(const std::string& race) const
{
    int ligorio = 0;
    for(int i = 0; i < getCurrentSize(); i++)
    {
        if(items_[i].getRace() == race)
        {
            ligorio++;
        }
    }
    return ligorio;
}
void Tavern::tavernReport() const
{
//Character Report
    std::cout << "Humans: " << tallyRace("HUMAN") << "\n";
    std::cout << "Elves: " << tallyRace("ELF") << "\n";
    std::cout << "Dwarves: " << tallyRace("DWARF") << "\n";
    std::cout << "Lizards: " << tallyRace("LIZARD") << "\n";
    std::cout << "Undead: " << tallyRace("UNDEAD") << "\n";

//Averages
    std::cout << "The average level is: " << calculateAvgLevel() << "\n";
    std::cout << calculateEnemyPercentage() << "%" << " are enemies.\n";
}