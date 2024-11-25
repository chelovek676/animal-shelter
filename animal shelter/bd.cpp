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

void BD::add(const Animals& newAnimal) {
    KotikiVec.push_back(newAnimal);
    _NumberOfCats = KotikiVec.size();

    cout << "New animal added successfully with ID: " << id << " and status in shelter.\n";
}



void BD::print() {
    for (const auto& animal : KotikiVec) {
        cout << animal; 
    }
}


void BD::edit(unsigned int _id) {
    for (auto& animal : KotikiVec) {
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

void BD::Delete(unsigned int _id) {
    for (auto it = KotikiVec.begin(); it != KotikiVec.end(); ++it) {
        if (it->get_Id() == _id) {
            KotikiVec.erase(it);
            _NumberOfCats = KotikiVec.size();
            cout << "Animal with ID " << _id << " deleted.\n";
            return;
        }
    }
    cout << "Animal with ID " << _id << " not found.\n";
}

vector<Animals> BD::search(unsigned int _id, bool _breed, bool _gender, bool _age) {
    vector<Animals> FilteredVec;
    for (auto it = KotikiVec.begin(); it != KotikiVec.end(); ++it) {
        if (it->get_Id() == _id and it->get_Breed() == _breed and it->get_Gender() == _gender and it->get_Age() == _age) {
            FilteredVec.push_back(it);
        }
    }
    return FilteredVec;
}
