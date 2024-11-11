#include "AnimalClass.h"
#include "bd.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void BD::save() {
        ofstream out;
        out.open("KotikiF", ios_base::binary);
        if (!out.is_open()) {
            cout << "cant open file" << endl;
            return;
        }
        _NumberOfCats = KotikiVec.size();
         out.write(reinterpret_cast<char*>(&_NumberOfCats), sizeof(_NumberOfCats));
         if (_NumberOfCats > 0) {
            out.write(reinterpret_cast<char*>(&KotikiVec[0]), sizeof(Animals) * _NumberOfCats);
        }
    out.close();
    cout << "The data has been successfully saved to a file 'KotikiF'" << endl;
}

void BD::read() {
        ifstream in;
        in.open("KotikiF", ios_base::binary);
        if (!in.is_open()) {
            cout << "cant open file" << endl;
            return;
        }
        in.read(reinterpret_cast<char*>(&_NumberOfCats), sizeof(_NumberOfCats));
        KotikiVec.resize(_NumberOfCats);
        if (_NumberOfCats > 0) {
            in.read(reinterpret_cast<char*>(&KotikiVec[0]), sizeof(Animals) * _NumberOfCats);
        }
    in.close();
    cout << "The data has been successfully downloaded from the file 'KotikiF'" << endl;
    print(); 
}

void BD::add() {
    Animals newAnimal;
    bool breed, gender;
    unsigned short int age;
    unsigned int id = KotikiVec.empty() ? 1 : KotikiVec.back().get_Id() + 1;
    newAnimal.set_Id(id);

    std::cout << "Adding a new animal with ID: " << id << std::endl;

    std::cout << "Does it have a breed? (1 - yes, 0 - no): ";
    std::cin >> breed;
    newAnimal.set_Breed(breed);

    std::cout << "Enter gender (1 - male, 0 - female): ";
    std::cin >> gender;
    newAnimal.set_Gender(gender);

    std::cout << "Enter age: ";
    std::cin >> age;
    newAnimal.set_Age(age);

    newAnimal.set_Status(1);

    KotikiVec.push_back(newAnimal);
    _NumberOfCats = KotikiVec.size();

    std::cout << "New animal added successfully with ID: " << id << " and status in shelter.\n";
}



void BD::print() {
    for (const auto& animal : KotikiVec) {
        cout << animal; 
    }
}

#include <iostream>

void BD::edit(unsigned int _id) {
    for (auto& animal : KotikiVec) {
        if (animal.get_Id() == _id) {
            std::cout << "Editing information for animal with ID " << _id << ":\n";
            
            bool newBreed, newGender, newStatus;
            unsigned short int newAge;

            std::cout << "Does it have a breed? (1 - yes, 0 - no): ";
            std::cin >> newBreed;
            animal.set_Breed(newBreed);

            std::cout << "Enter gender (1 - male, 0 - female): ";
            std::cin >> newGender;
            animal.set_Gender(newGender);

            std::cout << "Enter age: ";
            std::cin >> newAge;
            animal.set_Age(newAge);

            std::cout << "Status (1 for in shelter, 0 for not in shelter): ";
            std::cin >> newStatus;
            animal.set_Status(newStatus);

            std::cout << "Information updated.\n";
            return;
        }
    }
    std::cout << "Animal with ID " << _id << " not found.\n";
}

void BD::Delete(unsigned int _id) {
    for (auto it = KotikiVec.begin(); it != KotikiVec.end(); ++it) {
        if (it->get_Id() == _id) {
            KotikiVec.erase(it);
            _NumberOfCats = KotikiVec.size();
            std::cout << "Animal with ID " << _id << " deleted.\n";
            return;
        }
    }
    std::cout << "Animal with ID " << _id << " not found.\n";
}
