/*
CSCI235 Fall 2023
Project 3 - Tavern Class
Georgina Woo
June 20 2023
Tavern.cpp declares the Tavern class along with its private and public members
*/
#include "Tavern.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{     
}

/* Parameterized Constructor */
/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
1. Name: An uppercase string
2. Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
3. Subclass: An uppercase string [BARBARIAN, MAGE, SCOUNDREL, RANGER]
4. Level/Vitality/Armor: A positive integer
5. Enemy: 0 (False) or 1 (True)
6. Main: Uppercase string or strings representing the main weapon (Barbarian and Mage), Dagger type (Scoundrel), or arrows (Ranger). A ranger's arrows are of the form [TYPE] [QUANTITY];[TYPE] [QUANTITY], where each arrow type is separated by a semicolon, and the type and its quantity are separated with a space.
7. Offhand: An uppercase string that is only applicable to Barbarians, and may be NONE if the Barbarian does not have an offhand weapon, or if the character is of a different subclass.
8. School/Faction: Uppercase strings that represent a Mage's school of magic: [ELEMENTAL, NECROMANCY, ILLUSION] or a Scoundrel's faction: [CUTPURSE, SHADOWBLADE, SILVERTONGUE], and NONE where not applicable
9. Summoning: 0 (False) or 1 (True), only applicable to Mages (summoning an Incarnate) and Rangers (Having an Animal Companion)
10. Affinity: Only applicable to Rangers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Ranger with no affinities, or characters of other subclasses.
11. Disguise: 0 (False) or 1 (True), only applicable to Scoundrels, representing if they have a disguise.
12. Enraged: 0 (False) or 1 (True), only applicable to Barbarians, representing if they are enraged.
    @post: Each line of the input file corresponds to a Character subclass and dynamically allocates Character derived objects, adding them to the Tavern.
*/

Tavern::Tavern(const std::string& file)
{
  std::ifstream fin(file);    //file = "characters.csv"
  if(!fin.is_open())
  {
    std::cout << "File cannot be opened" << std::endl;
  }

  //Skips header line
  std::string beef;
  std::getline(fin, beef);

  //Declaring variables for subheadings
    std::string NAME, RACE, SUBCLASS, MAIN, OFFHAND, SCHOOL_FACTION, AFFINITY;
    int LEVEL, VITALITY, ARMOR;
    bool ENEMY, SUMMONING, DISGUISED, ENRAGE;

  //Pointer yippie
  Character* characters = nullptr;
  std::string empty = "";

  while(std::getline(fin, empty))
  {
    //Allowing us to create a stream out of the line
    std::stringstream temp(empty);                   //temp is a stringstream

  //Name, Race, and Class
    getline(temp, NAME, ',');
    getline(temp, RACE, ',');
    getline(temp, SUBCLASS, ',');

  //Level, Vitality, Armor, Enemy
    std::string convert;
    getline(temp, convert, ',');           
      std::istringstream(convert) >> LEVEL;
    getline(temp, convert, ',');
      std::istringstream(convert) >> VITALITY;
    getline(temp, convert, ',');
      std::istringstream(convert) >> ARMOR;
    getline(temp, convert, ',');
      std::istringstream(convert) >> ENEMY;

  //Main weapon
    getline(temp, MAIN, ',');  
    std::vector <Arrows> tempMain;    //Vector that goes through main weapon
    std::istringstream temp2(MAIN);   //temp2 is a stringstream   

    while(std::getline(temp2, convert, ';')) 
    {
      std::istringstream v(convert);     //v = new variable
      std::string ArrType;            //ArrType = Arrow Type
      int ArrQuantity;                //ArrQuantity = Arrow quantity

      v >> ArrType >> ArrQuantity;
      Arrows Arr;
      Arr.type_ = ArrType;
      Arr.quantity_ = ArrQuantity;
      tempMain.push_back(Arr);
    }

  //Secondary Weapon, Faction
    std::getline(temp, OFFHAND, ',');
    std::getline(temp, SCHOOL_FACTION, ',');

  //Summoning
    std::getline(temp, convert, ',');
      std::istringstream(convert) >> SUMMONING;

//Affininty
    getline(temp, AFFINITY, ',');
    std::vector <std::string> tempAffinity;
    std::string empty2 = "";

    if(SUBCLASS == "RANGER")
    {
      std::istringstream a_stream(AFFINITY);
      while(std::getline(a_stream, empty2, ';')) 
      {
        tempAffinity.push_back(empty2); 
      }
    }
    
//Disguise, Enraged
    std::getline(temp, convert, ',');
      std::istringstream(convert) >> DISGUISED;

    std::getline(temp, convert, ',');
      std::istringstream(convert) >> ENRAGE;

//Printing
    if (SUBCLASS == "BARBARIAN") 
    {
      characters = new Barbarian(NAME, RACE, VITALITY, ARMOR, LEVEL, ENEMY, MAIN, OFFHAND, ENRAGE);
    } 
    else if (SUBCLASS == "MAGE") 
    {
      characters = new Mage(NAME, RACE, VITALITY, ARMOR, LEVEL, ENEMY, SCHOOL_FACTION, MAIN, SUMMONING);
    } 
    else if (SUBCLASS == "SCOUNDREL") 
    {
      characters = new Scoundrel(NAME, RACE, VITALITY, ARMOR, LEVEL, ENEMY, MAIN, SCHOOL_FACTION, DISGUISED);
    } 
    else if (SUBCLASS == "RANGER") 
    {
      characters = new Ranger(NAME, RACE, VITALITY, ARMOR, LEVEL, ENEMY, tempMain, tempAffinity, SUMMONING);
    }
    enterTavern(characters);
  }
}

/**
    @post: For every character in the tavern, displays each character's information
*/

void Tavern::displayCharacters()
{
  for(int i = 0; i < getCurrentSize(); i++)
  {
    items_[i] -> display();
  }
}

/**
    @param: a string reference to a race
    @post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information

*/

void Tavern::displayRace(const std::string& race)
{
  for(int i = 0; i < getCurrentSize(); i++)
  {
    if(items_[i] -> getRace() == race)
    {
      items_[i] -> display();
    }
  }
}

/**
    @post: Every character in the tavern eats a tainted stew.
*/

void Tavern::taintedStew()
{
  for(int i = 0; i < getCurrentSize(); i++)
  {
    items_[i] -> eatTaintedStew();
  }
}

/** 
    @param:   A reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to items_, false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/

bool Tavern::enterTavern(Character* a_character)
{
  if(add(a_character))
  {
    level_sum_ += a_character -> getLevel();
    if(a_character -> isEnemy())
      num_enemies_++;
     
    return true;
  }
  else
  {
    return false;
  }
}

/** @param:   A reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from items_, false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::exitTavern(Character* a_character)
{
  if(remove(a_character))
  {
    level_sum_ -= a_character -> getLevel();
    if(a_character -> isEnemy())
      num_enemies_--;
      
    return true;
  }
  return false;
}



/** 
    @return:  The integer level count of all the characters currently in the Tavern
    **/
    int Tavern::getLevelSum()
    {
      return level_sum_;
    }



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
   return (level_sum_>0) ? round(double(level_sum_) / item_count_) : 0.0;

}



/** 

    @return:  The integer enemy count of the Tavern
    **/
    int Tavern::getEnemyCount()
    {
      return num_enemies_;
    }

/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
  double enemy_percent = (num_enemies_>0) ?  (double(num_enemies_) / item_count_) * 100: 0.0;
  return std::ceil(enemy_percent*100.0) / 100.0; //round up to to decimal places
 
}


/** 
    @param:   A string reference to a race 
    @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index] -> getRace() == race)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}



/**
  @post:    Outputs a report of the characters currently in the tavern in the form:
  "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"

  Example output: 
  Humans: 5
  Elves: 8
  Dwarves: 3
  Lizards: 7
  Undead: 2

  The average level is: 16
  24% are enemies.
*/
void Tavern::tavernReport()
{
  int humans = tallyRace("HUMAN");
  int elves = tallyRace("ELF");
  int dwarves = tallyRace("DWARF");
  int lizards = tallyRace("LIZARD");
  int undead = tallyRace("UNDEAD");
  
  std::cout << "Humans: " << humans << std::endl;
  std::cout << "Elves: " << elves << std::endl;
  std::cout << "Dwarves: " << dwarves << std::endl;
  std::cout << "Lizards: " << lizards << std::endl;
  std::cout << "Undead: " << undead << std::endl;
  std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
  std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}