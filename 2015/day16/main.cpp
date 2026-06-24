#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Aunt {
public:
    int id = -1;
    int children = -1;
    int cats = -1;
    int samoyeds = -1;
    int pomeranians = -1;
    int akitas = -1;
    int vizslas = -1;
    int goldfish = -1;
    int trees = -1;
    int cars = -1;
    int perfumes = -1;

    bool isMatch_p1(const Aunt& other) const {
        if (other.children != -1 && other.children != this->children) {return false;}
        if (other.cats != -1 && other.cats != this->cats) {return false;}
        if (other.samoyeds != -1 && other.samoyeds != this->samoyeds) {return false;}
        if (other.pomeranians != -1 && other.pomeranians != this->pomeranians) {return false;}
        if (other.akitas != -1 && other.akitas != this->akitas) {return false;}
        if (other.vizslas != -1 && other.vizslas != this->vizslas) {return false;}
        if (other.goldfish != -1 && other.goldfish != this->goldfish) {return false;}
        if (other.trees != -1 && other.trees != this->trees) {return false;}
        if (other.cars != -1 && other.cars != this->cars) {return false;}
        if (other.perfumes != -1 && other.perfumes != this->perfumes) {return false;}

        return true;
    }

    bool isMatch_p2(const Aunt& other) const {
        if (other.children != -1 && other.children != this->children) {return false;}
        if (other.cats != -1 && other.cats <= this->cats) {return false;}
        if (other.samoyeds != -1 && other.samoyeds != this->samoyeds) {return false;}
        if (other.pomeranians != -1 && other.pomeranians >= this->pomeranians) {return false;}
        if (other.akitas != -1 && other.akitas != this->akitas) {return false;}
        if (other.vizslas != -1 && other.vizslas != this->vizslas) {return false;}
        if (other.goldfish != -1 && other.goldfish >= this->goldfish) {return false;}
        if (other.trees != -1 && other.trees <= this->trees) {return false;}
        if (other.cars != -1 && other.cars != this->cars) {return false;}
        if (other.perfumes != -1 && other.perfumes != this->perfumes) {return false;}

        return true;
    }
};

void setAuntValue(Aunt& aunt, const string& field, const int value) {
    if (field == "children") {aunt.children = value;}
    else if (field == "cats") {aunt.cats = value;}
    else if (field == "samoyeds") {aunt.samoyeds = value;}
    else if (field == "pomeranians") {aunt.pomeranians = value;}
    else if (field == "akitas") {aunt.akitas = value;}
    else if (field == "vizslas") {aunt.vizslas = value;}
    else if (field == "goldfish") {aunt.goldfish = value;}
    else if (field == "trees") {aunt.trees = value;}
    else if (field == "cars") {aunt.cars = value;}
    else if (field == "perfumes") {aunt.perfumes = value;}
}

int main() {
    cout << "Day 16 - AOC 2015" << endl;

    ifstream day16_data("data/2015/day16.txt");
    if (!day16_data) {
        cout << "Could not open file!";
        return -1;
    }

    Aunt known;
    known.children = 3;
    known.cats = 7;
    known.samoyeds = 2;
    known.pomeranians = 3;
    known.akitas = 0;
    known.vizslas = 0;
    known.goldfish = 5;
    known.trees = 3;
    known.cars = 2;
    known.perfumes = 1;

    vector<Aunt> passedAunts;
    string line;

    while (getline(day16_data, line)) {
        Aunt candidate;
        istringstream iss(line);

        string sueText, idText;
        iss >> sueText >> idText;

        idText.pop_back();
        candidate.id = stoi(idText);

        for (int count = 0; count < 3; count++) {
            string field;
            int value;

            iss >> field >> value;

            field.pop_back();

            setAuntValue(candidate, field, value);

            if (iss.peek() == ',') {
                iss.ignore();
            }

            if (iss.peek() == ' ') {
                iss.ignore();
            }
        }

        if (known.isMatch_p1(candidate)) {
            passedAunts.push_back(candidate);
        }

        if (known.isMatch_p2(candidate)) {
            passedAunts.push_back(candidate);
        }
    }

    for (const Aunt& aunt : passedAunts) {
        cout << "Possible Aunt Sue: " << aunt.id << endl;
    }

    return 0;
}