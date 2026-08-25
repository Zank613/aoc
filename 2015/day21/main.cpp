#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Entity {
    int health;
    int damage;
    int armor;

    Entity(const int h, const int d, const int a)
    : health(h), damage(d), armor(a) {}
};

struct Item {
    int cost;
    int damage;
    int armor;

    Item(const int c, const int d, const int a)
    : cost(c), damage(d), armor(a) {}
};

bool fight(Entity player, Entity boss) {
    while (player.health > 0 && boss.health > 0) {
        int playerDamage = max(1, player.damage - boss.armor);
        boss.health -= playerDamage;

        if (boss.health <= 0) {
            return true;
        }

        int bossDamage = max(1, boss.damage - player.armor);
        player.health -= bossDamage;
    }

    return false;
}

int main() {
    cout << "AOC 2015 - Day 21" << endl;

    ifstream day21_data("data/2015/day21.txt");
    if (!day21_data) {
        cout << "Could not open file!";
        return -1;
    }

    Entity firstBoss(104, 8, 1);

    vector<Item> weapons = {
        Item(8, 4, 0),
        Item(10, 5, 0),
        Item(25, 6, 0),
        Item(40, 7, 0),
        Item(74, 8, 0)
    };

    vector<Item> armors = {
        Item(0, 0, 0),
        Item(13, 0, 1),
        Item(31, 0, 2),
        Item(53, 0, 3),
        Item(75, 0, 4),
        Item(102, 0, 5)
    };

    vector<Item> rings = {
        Item(25, 1, 0),
        Item(50, 2, 0),
        Item(100, 3, 0),
        Item(20, 0, 1),
        Item(40, 0, 2),
        Item(80, 0, 3)
    };

    int minimumCost = 1000000;
    int maximumCost = 0;

    for (int weapon = 0; weapon < weapons.size(); weapon++) {
        for (int armor = 0; armor < armors.size(); armor++) {

            // No rings
            {
                int cost = weapons[weapon].cost + armors[armor].cost;
                int damage = weapons[weapon].damage + armors[armor].damage;
                int defense = weapons[weapon].armor + armors[armor].armor;

                Entity player(100, damage, defense);

                if (fight(player, firstBoss)) {
                    minimumCost = min(minimumCost, cost);
                }
                else {
                    maximumCost = max(maximumCost, cost);
                }
            }

            // One ring
            for (int ring = 0; ring < rings.size(); ring++) {
                int cost =
                    weapons[weapon].cost +
                    armors[armor].cost +
                    rings[ring].cost;

                int damage =
                    weapons[weapon].damage +
                    armors[armor].damage +
                    rings[ring].damage;

                int defense =
                    weapons[weapon].armor +
                    armors[armor].armor +
                    rings[ring].armor;

                Entity player(100, damage, defense);


                if (fight(player, firstBoss)) {
                    minimumCost = min(minimumCost, cost);
                }
                else {
                    maximumCost = max(maximumCost, cost);
                }
            }

            // Two rings
            for (int firstRing = 0; firstRing < rings.size(); firstRing++) {
                for (int secondRing = firstRing + 1; secondRing < rings.size(); secondRing++) {
                    int cost =
                        weapons[weapon].cost +
                        armors[armor].cost +
                        rings[firstRing].cost +
                        rings[secondRing].cost;

                    int damage =
                        weapons[weapon].damage +
                        armors[armor].damage +
                        rings[firstRing].damage +
                        rings[secondRing].damage;

                    int defense =
                        weapons[weapon].armor +
                        armors[armor].armor +
                        rings[firstRing].armor +
                        rings[secondRing].armor;

                    Entity player(100, damage, defense);

                    if (fight(player, firstBoss)) {
                        minimumCost = min(minimumCost, cost);
                    }
                    else {
                        maximumCost = max(maximumCost, cost);
                    }
                }
            }
        }
    }

    cout << "Part 1: " << minimumCost << endl;
    cout << "Part 2: " << maximumCost << endl;

    return 0;
}