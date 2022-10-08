#include <iostream>
#include <list>
#include <tuple>
#include<cstdlib>



int getData(std::list<int> data, int stat) {
    /// Returns the data from the list
    auto it = data.begin();
    std::advance(it, stat);
    return *it;
}

int print_stats(const std::list<int>& stats, const std::list<std::string>& nameClass) {
    /// Prints the stats of the class
    std::string name = nameClass.front();
    std::string Class = nameClass.back();

    int strength = getData(stats, 0);
    int dexterity = getData(stats, 1);
    int intelligence = getData(stats, 2);
    int magicpower = getData(stats, 3);
    int health = getData(stats, 4);
    std::cout << "____________________" << std::endl;
    std::cout << "|Name: " << name << std::endl;
    std::cout << "|Class: " << Class << std::endl;
    std::cout << "|Health: " << health << std::endl;
    std::cout << "____________________" << std::endl;
    std::cout << "|Strength: " << strength << std::endl;
    std::cout << "|Dexterity: " << dexterity << std::endl;
    std::cout << "|Intelligence: " << intelligence << std::endl;
    std::cout << "|Magic Power: " << magicpower << std::endl;
    std::cout << "|____________________" << std::endl;




    return 0;



}

std::tuple<std::list<int>, std::list<std::string>> characterCreation() {
    /// Creates the character

    int strength;
    int dexterity;
    int magicpower;
    int intelligence;
    std::string name;
    std::string Class;


    //ask user for input
    std::cout << "What is you name: "<< std::endl;
    std::cin >> name;

    while (true) {
        std::cout << "Swordsman: Has the ability to do critical shot well rounded" << std::endl;
        std::cout << "Mage: Has the ability to stun, but has low health" << std::endl;
        std::cout << "Defender: Has the ability to block, but has low damage" << std::endl;
        std::cout << "________________________________________________________" << std::endl;
        std::cout << "Pick a class (S)wordsman, (M)age, (D)efender:"<< std::endl;
        // explain the classes
        char classChoice;
        std::cin >> classChoice;

        //check if input is valid
        if (classChoice == 'S' || classChoice == 's') {
            Class = "Swordsman";
            strength = 10;
            dexterity = 5;
            magicpower = 1;
            intelligence = 5;
            break;
        } else if (classChoice == 'M' || classChoice == 'm') {
            Class = "Mage";
            strength = 1;
            dexterity = 1;
            magicpower = 10;
            intelligence = 10;
            break;
        } else if (classChoice == 'D' || classChoice == 'd') {
            Class = "Defender";
            strength = 5;
            dexterity = 10;
            magicpower = 1;
            intelligence = 5;
            break;
        } else {
            std::cout << "Invalid class choice!" << std::endl;
        }

    }


    std::list<int> stats = {strength, dexterity, intelligence, magicpower,(dexterity*intelligence)*5};
    std::list<std::string> nameClass = {name, Class};
    // make a tuple of the stats and nameClass
    std::tuple<std::list<int>, std::list<std::string>> character = std::make_tuple(stats, nameClass);
    return character;


}

int enterDungeon(const std::string& Class ,int health ,int strength, int dexterity, int intelligence, int magicpower) {
    int upgradeCrystals = 0;   // number of upgrade crystals
    bool stun = false;         // if the monster is stunned
    int cursedchance = rand() % 100 + 1; // chance of a cursed monster appearing
    bool cursed;     // if the monster is cursed
    int monsterHealth; // health of the monster
    int monsterDamage; // damage of the monster
    std::cout << "You enter the dungeon" << std::endl;

    if (cursedchance == 1) {
        cursed = true;
    } else {
        cursed = false;
    }

    if(cursed){
        std::cout << "You have encountered a CURSED monster!" << std::endl;

        monsterHealth = health*1.5;
    }
    else{
        std::cout << "You have encountered a monster!" << std::endl;
        monsterHealth = rand() % health/1.5 + 1;
    }




    std::cout << "Monster Health: " << monsterHealth << std::endl;
    std::cout << "_____________________" << std::endl;
    std::cout << "What do you do? (A)ttack, (R)un: "<< std::endl;
    char action;
    std::cin >> action;
    while (0 <= monsterHealth) {
        if (action == 'A' || action == 'a') {
            int chance = rand() % 10 + 1;
            if (Class == "Swordsman" && chance == 1){
                int damage = (rand() % ((strength * magicpower)*2)+ 10)*2;
                std::cout << "CRITICAL" << std::endl;
                std::cout << "You deal " << damage << " damage!" << std::endl;
                monsterHealth -= damage;
                }
            else if (Class == "Mage" && chance == 1){
                 stun = true;
            }

            int damage = (rand() % ((strength * magicpower)*2)+ 10);
            monsterHealth -= damage;
            std::cout << "You hit the monster for " << damage << " damage" << std::endl;
            if (monsterHealth<0)
            {
                if (cursed){
                    upgradeCrystals += 20;
                }
                else{
                    upgradeCrystals += 1;
                }
                std::cout << "You killed the monster!" << std::endl;
                std::cout << "You got " << upgradeCrystals << " upgrade crystal(s)" << std::endl;
                break;


            }
            std::cout << "Monster Health: " << monsterHealth << std::endl;
            if (cursed){
                monsterDamage = rand() % (((dexterity * intelligence)*5)/2) + 1;
            }
            else{
                monsterDamage = rand() % (((dexterity * intelligence)*5)/4) + 1;
            }
            if (Class == "Defender" && chance == 1){
                std::cout << "You blocked the attack" << std::endl;
                monsterDamage = 0;
            }
            if (stun){
                std::cout << "Monster are stunned" << std::endl;
                monsterDamage = 0;
                stun = false;
            }

            health -= monsterDamage;
            std::cout << "The monster did " << monsterDamage << " damage!" << std::endl;


            health -= monsterDamage;
            if (health <= 0) {
                std::cout << "You died!" << std::endl;
                return -1;

            }
            std::cout << "Your health: " << health << std::endl;
            std::cout << "_____________________" << std::endl;



            std::cout << "What do you do? (A)ttack, (R)un: "<< std::endl;
            std::cin >> action;
        } else if (action == 'R' || action == 'r') {
            std::cout << "You ran away!" << std::endl;
            break;
        } else {
            std::cout << "Invalid action!" << std::endl;
            std::cout << "What do you do? (A)ttack, (R)un: "<< std::endl;
            std::cin >> action;
        }
    }
    return upgradeCrystals;
}

int main() {
    std::cout << "Welcome to the {C++ Dungeons}!" << std::endl;
    std::cout << "Created by: https://github.com/Flow-Glow" << std::endl;
    std::tuple<std::list<int>, std::list<std::string>> character = characterCreation();
    std::list<int> stats = std::get<0>(character);
    std::list<std::string> nameClass = std::get<1>(character);
    std::string name = nameClass.front();
    std::string Class = nameClass.back();
    int upgradeCrystals = 0;
    int strength = getData(stats, 0);
    int dexterity = getData(stats, 1);
    int intelligence = getData(stats, 2);
    int magicpower = getData(stats, 3);
    int health = getData(stats, 4);
    print_stats(stats, nameClass);
    bool life = true;
    int TotalCrystals = 0;
    TotalCrystals += upgradeCrystals;
    //ask user if they want to enter a dungeon
    while (life) {
        std::cout << "Do you want to enter a dungeon? (Y/N): "<< std::endl;
        char dungeonChoice;
        std::cin >> dungeonChoice;
        if (dungeonChoice == 'Y' || dungeonChoice == 'y') {
            int upgradeCrystal = enterDungeon(Class,health,strength, dexterity, intelligence, magicpower);
            if (upgradeCrystal == -1) {
                life = false;
            } else {
                upgradeCrystals += upgradeCrystal;
            }
        } else if (dungeonChoice == 'N' || dungeonChoice == 'n') {
            std::cout << "You leave the dungeon!" << std::endl;
            // print health
            std::cout << "Your health: " << health << std::endl;
            // print upgrade crystals
            std::cout << "Upgrade Crystals: " << upgradeCrystals << std::endl;
            if(upgradeCrystals > 0){
                std::cout << "You can upgrade your stats!" << std::endl;
                std::cout << "Do you want to upgrade your stats? (Y/N): ";
                char upgradeChoice;
                std::cin >> upgradeChoice;
                if(upgradeChoice == 'Y' || upgradeChoice == 'y'){
                    std::cout << "You upgrade your stats!" << std::endl;
                    strength += upgradeCrystals;
                    dexterity += upgradeCrystals;
                    intelligence += upgradeCrystals;
                    magicpower += upgradeCrystals;
                    health += upgradeCrystals*5;
                    stats = {strength, dexterity, intelligence, magicpower, health};
                    print_stats(stats, nameClass);
                    upgradeCrystals = 0;
                } else if(upgradeChoice == 'N' || upgradeChoice == 'n'){
                    std::cout << "You don't upgrade your stats!" << std::endl;
                } else {
                    std::cout << "Invalid choice!" << std::endl;
                }
            }
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }

    std::cout << "You got " << TotalCrystals << " upgrade crystal(s)" << std::endl;
    std::cout << "Your stats: " << std::endl;
    print_stats(stats, nameClass);
    std::cout << "Thanks for playing!" << std::endl;
    // wait for user to press enter
    std::cin.ignore();
    std::cin.get();



    return 0;
}
