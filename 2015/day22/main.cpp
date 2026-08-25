#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Entity {
    int health;
    int damage;
    int armor;

    Entity(const int h, const int d, const int a)
    : health(h), damage(d), armor(a) {}
};

struct Player {
    int health;
    int mana;
    int armor;

    Player(const int h, const int m, const int a)
    : health(h), mana(m), armor(a) {}
};

struct Effects {
    int shield;
    int poison;
    int recharge;

    Effects(const int s, const int p, const int r)
    : shield(s), poison(p), recharge(r) {}
};

int minimumMana = 1000000;

void applyEffects(Player& player, Entity& boss, Effects& effects) {
    player.armor = 0;

    if (effects.shield > 0) {
        player.armor = 7;
        effects.shield--;
    }

    if (effects.poison > 0) {
        boss.health -= 3;
        effects.poison--;
    }

    if (effects.recharge > 0) {
        player.mana += 101;
        effects.recharge--;
    }
}

void fight(Player player, Entity boss, Effects effects,
           int manaSpent, bool playerTurn, bool hardMode) {

    if (manaSpent >= minimumMana) {
        return;
    }

    // Hard mode penalty happens BEFORE effects
    if (hardMode && playerTurn) {
        player.health--;

        if (player.health <= 0) {
            return;
        }
    }

    applyEffects(player, boss, effects);

    if (boss.health <= 0) {
        minimumMana = min(minimumMana, manaSpent);
        return;
    }

    if (playerTurn) {
        bool canCastSpell = false;

        // Magic Missile
        if (player.mana >= 53) {
            canCastSpell = true;

            Player newPlayer = player;
            Entity newBoss = boss;
            Effects newEffects = effects;

            newPlayer.mana -= 53;
            newBoss.health -= 4;

            if (newBoss.health <= 0) {
                minimumMana = min(minimumMana, manaSpent + 53);
            }
            else {
                fight(
                    newPlayer,
                    newBoss,
                    newEffects,
                    manaSpent + 53,
                    false,
                    hardMode
                );
            }
        }

        // Drain
        if (player.mana >= 73) {
            canCastSpell = true;

            Player newPlayer = player;
            Entity newBoss = boss;
            Effects newEffects = effects;

            newPlayer.mana -= 73;
            newBoss.health -= 2;
            newPlayer.health += 2;

            if (newBoss.health <= 0) {
                minimumMana = min(minimumMana, manaSpent + 73);
            }
            else {
                fight(
                    newPlayer,
                    newBoss,
                    newEffects,
                    manaSpent + 73,
                    false,
                    hardMode
                );
            }
        }

        // Shield
        if (player.mana >= 113 && effects.shield == 0) {
            canCastSpell = true;

            Player newPlayer = player;
            Entity newBoss = boss;
            Effects newEffects = effects;

            newPlayer.mana -= 113;
            newEffects.shield = 6;

            fight(
                newPlayer,
                newBoss,
                newEffects,
                manaSpent + 113,
                false,
                hardMode
            );
        }

        // Poison
        if (player.mana >= 173 && effects.poison == 0) {
            canCastSpell = true;

            Player newPlayer = player;
            Entity newBoss = boss;
            Effects newEffects = effects;

            newPlayer.mana -= 173;
            newEffects.poison = 6;

            fight(
                newPlayer,
                newBoss,
                newEffects,
                manaSpent + 173,
                false,
                hardMode
            );
        }

        // Recharge
        if (player.mana >= 229 && effects.recharge == 0) {
            canCastSpell = true;

            Player newPlayer = player;
            Entity newBoss = boss;
            Effects newEffects = effects;

            newPlayer.mana -= 229;
            newEffects.recharge = 5;

            fight(
                newPlayer,
                newBoss,
                newEffects,
                manaSpent + 229,
                false,
                hardMode
            );
        }

        if (!canCastSpell) {
            return;
        }
    }
    else {
        int bossDamage = max(1, boss.damage - player.armor);

        player.health -= bossDamage;

        if (player.health <= 0) {
            return;
        }

        fight(
            player,
            boss,
            effects,
            manaSpent,
            true,
            hardMode
        );
    }
}

int main() {
    cout << "AOC 2015 - Day 22" << endl;

    ifstream day22_data("data/2015/day22.txt");
    if (!day22_data) {
        cout << "Could not open file!";
        return -1;
    }

    Entity firstBoss(58, 9, 0);

    Player player(50, 500, 0);
    Effects effects(0, 0, 0);

    // Part 1
    minimumMana = 1000000;

    fight(
        player,
        firstBoss,
        effects,
        0,
        true,
        false
    );

    cout << "Part 1: " << minimumMana << endl;

    // Part 2
    minimumMana = 1000000;

    fight(
        player,
        firstBoss,
        effects,
        0,
        true,
        true
    );

    cout << "Part 2: " << minimumMana << endl;

    return 0;
}