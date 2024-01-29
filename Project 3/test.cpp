#include <cmath>
#include <iostream>
#include "Tavern.hpp"
#include "Character.hpp"

int main() {
    Character Maryash;
    Maryash.setName("Ishowmeat");
    Maryash.setRace("ELF");
    Maryash.setLevel(31);

    Character Joe;
    Joe.setName("VeefBeffer");
    Joe.setRace("DWARF");
    Joe.setEnemy();
    Joe.setLevel(10000);

    Tavern jail;
    jail.enterTavern(Maryash);
    jail.enterTavern(Joe);
    jail.tavernReport();

    Character Deez;
    Deez.setName("Kevin");
    Deez.setRace("UNDEAD");
    Deez.setLevel(32);
    jail.enterTavern(Deez);
    jail.tavernReport();


    Character bonk;
    bonk.setName("Kobin");
    bonk.setRace("DWARF");
    bonk.setLevel(13);
    bonk.setEnemy();
    jail.enterTavern(bonk);
    jail.tavernReport();


    Character mwin;
    mwin.setName("Cable");
    mwin.setRace("HUMAN");
    mwin.setLevel(8);
    mwin.setEnemy();
    jail.enterTavern(mwin);
    jail.tavernReport();


    Character beef;
    beef.setName("Kevin");
    beef.setRace("NONE");
    beef.setLevel(9);
    jail.enterTavern(beef);
    jail.tavernReport();

    jail.exitTavern(Joe);
    jail.tavernReport();
    jail.exitTavern(beef);
    jail.tavernReport();

    return 0;

}