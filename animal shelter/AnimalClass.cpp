#include "AnimalClass.h"

unsigned int Animals::get_Id() const{
    return _id;
}

void Animals::set_Id(const unsigned int &id){
    _id = id;
}

bool Animals::get_Breed() const{
    return _breed;
}

void Animals::set_Breed(const bool &breed){
    _breed = breed;
}

bool Animals::get_Gender() const{
    return _gender;
}

void Animals::set_Gender(const bool &gender){
    _gender = gender;
}

unsigned short int Animals::get_Age() const{
    return _age;
}

void Animals::set_Age(const unsigned short int &age){
    _age = age;
}

bool Animals::get_Status() const{
    return _status;
}

void Animals::set_Status(const bool &status){
    _status = status;
}

std::ostream &operator <<(std::ostream &out, const Animals &r){
    out << "Id: " << r._id << "\nBreed: " << r._breed << "\nGender: " << r._gender <<
           "\nAge: " << r._age << "\nStatus: " << r._status << std::endl;
    return out;
}

std::istream &operator >>(std::istream &in, Animals &r){
    std::cout << "Id: ";
    in >> r._id;
    std::cout << "Breed: ";
    in >> r._breed;
    std::cout << "Gender: ";
    in >> r._gender;
    std::cout << "Age: ";
    in >> r._age;
    return in;
}
