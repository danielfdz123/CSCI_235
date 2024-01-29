#include "Tavern.hpp"

int main()
{
    Tavern bar("characters.csv");  // Tavern object - parameterized constructor taking in a csv file name
    bar.displayCharacters();
}