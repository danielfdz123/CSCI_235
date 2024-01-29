#include "Tavern.hpp"
#include "Character.hpp"
#include <iostream>

int main()
{
    Tavern tavern("enemies.csv");
    tavern.createCombatQueue("NONE");
    Character* test1 = new Character("Amy", "ELF", 3, 5, 3, 0);
    tavern.setMainCharacter(test1);
    tavern.actionSelection();
}