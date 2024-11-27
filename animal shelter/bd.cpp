#include "AnimalClass.h"
#include <vector>
#include "bd.h"

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
}

void BD::add(Animals newAnimal) {
    newAnimal.set_Id(KotikiVec.size());
    KotikiVec.push_back(newAnimal);
    _NumberOfCats = KotikiVec.size();
    save();

    //cout << "New animal added successfully with ID: " << id << " and status in shelter.\n";
}



void BD::print() {
    for (Animals animal : KotikiVec) {
        cout << animal; 
    }
}


void BD::edit(unsigned long int _id) {
    for (Animals animal : KotikiVec) {
        if (animal.get_Id() == _id) {
            cout << "Editing information for animal with ID " << _id << ":\n";
            
            bool newBreed, newGender, newStatus;
            unsigned short int newAge;

            cout << "Does it have a breed? (1 - yes, 0 - no): ";
            cin >> newBreed;
            animal.set_Breed(newBreed);

            cout << "Enter gender (1 - male, 0 - female): ";
            cin >> newGender;
            animal.set_Gender(newGender);

            cout << "Enter age: ";
            cin >> newAge;
            animal.set_Age(newAge);

            cout << "Status (1 for in shelter, 0 for not in shelter): ";
            cin >> newStatus;
            animal.set_Status(newStatus);

            cout << "Information updated.\n";
            return;
        }
    }
    cout << "Animal with ID " << _id << " not found.\n";
}

void BD::Delete(unsigned long int _id) {
    for (int i = 0; i < KotikiVec.size(); i++) {
        if (KotikiVec[i].get_Id() == _id) {
            KotikiVec.erase(KotikiVec.begin()+i);
            _NumberOfCats = KotikiVec.size();
            cout << "Animal with ID " << _id << " deleted.\n";
            return;
        }
    }
    cout << "Animal with ID " << _id << " not found.\n";
}

int BD::search(short int breed, short int gender, short int age, vector<Animals>* retAnim) {
    int count = 0;
    for (Animals kot : KotikiVec) {
        if (!kot.get_Status())
            continue;
        if ((breed < 2 and breed != kot.get_Breed()) and (gender < 2 and gender != kot.get_Gender())) {
            continue;
        }
        if (age < 2) {
            if (age == 0 and kot.get_Age() != 0) {
                continue;
            }
            else if (age == 1 and kot.get_Age() == 0) {
                continue;
            }
        }
        retAnim->push_back(kot);
        count++;
    }
    return count;
}

unsigned long int BD::size() {
    return KotikiVec.size();
}

Animals BD::takeCat(unsigned long int id) {
    unsigned long int it = {};
    for (int i = 0; i < KotikiVec.size(); i++) {
        if (KotikiVec[i].get_Id() == id) {
            it = i;
            break;
        }
    }
    KotikiVec[it].set_Status(false);
    save();
    return KotikiVec[it];
}
