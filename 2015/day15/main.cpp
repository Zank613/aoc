#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

#define MAX_TEASPOON 100

class Ingredient {
public:
    string name;
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;

    Ingredient(string name, int capacity, int durability, int flavor, int texture, int calories) :
    name(std::move(name)) ,capacity(capacity), durability(durability), flavor(flavor), texture(texture), calories(calories) {}
};

int bestScore = 0;

void generateRecipes(const vector<Ingredient>& ingredients, vector<int>& teaspoons, int ingredientIndex, int remainingTeaspoons) {
    if (ingredientIndex == ingredients.size() - 1) {
        teaspoons[ingredientIndex] = remainingTeaspoons;

        int capacity = 0;
        int durability = 0;
        int flavor = 0;
        int texture = 0;
        int calories = 0;

        for (int i = 0; i < ingredients.size(); i++) {
            capacity += ingredients[i].capacity * teaspoons[i];
            durability += ingredients[i].durability * teaspoons[i];
            flavor += ingredients[i].flavor * teaspoons[i];
            texture += ingredients[i].texture * teaspoons[i];
            calories += ingredients[i].calories * teaspoons[i];
        }

        if (calories != 500) {
            return;
        }

        capacity = max(0, capacity);
        durability = max(0, durability);
        flavor = max(0, flavor);
        texture = max(0, texture);

        int score = capacity * durability * flavor * texture;

        if (score > bestScore) {
            bestScore = score;
        }

        return;
    }

    for (int amount = 0; amount <= remainingTeaspoons; amount++) {
        teaspoons[ingredientIndex] = amount;
        generateRecipes(ingredients, teaspoons, ingredientIndex + 1, remainingTeaspoons - amount);
    }
}

int main() {
    cout << "AOC 2015 - Day 15" << endl;

    ifstream day15_data("data/2015/day15.txt");

    if (!day15_data) {
        cout << "Could not open file!" << endl;
        return -1;
    }

    vector<Ingredient> ingredients;
    string line;
    while (getline(day15_data, line)) {
        istringstream iss(line);
        string name, property;
        int capacity, durability, flavor, texture, calories;
        char comma;
        iss >> name
        >> property >> capacity >> comma
        >> property >> durability >> comma
        >> property >> flavor >> comma
        >> property >> texture >> comma
        >> property >> calories >> comma;
        ingredients.emplace_back(name.substr(0, name.length()-1), capacity, durability, flavor, texture, calories);
    }

    // for (const Ingredient& i : ingredients) {
    //     cout << i.name << " "
    //          << i.capacity << " "
    //          << i.durability << " "
    //          << i.flavor << " "
    //          << i.texture << " "
    //          << i.calories << endl;
    // }

    vector<int> teaspoons(ingredients.size(), 0);
    generateRecipes(ingredients, teaspoons, 0, MAX_TEASPOON);
    cout << "Best score: " << bestScore << endl;
    return 0;
}