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
    out << " ____________________________\n";
    out << "|     CAT WITH ID: " << r._id << "         |\n";
    out << "|============================|\n";
    out << "|        BREED: " << r._breed << "            |\n";
    out << "|         SEX: " << r._gender << "             |\n"; 
    out << "|         AGE: " << r._age << "             |\n";
    out << "|============================|\n";
    return out;
    return out;
}

std::istream &operator >>(std::istream &in, Animals &r){
    std::cout<<"_____________________"<<endl;
    std::cout<<"|       BREED       |               ,/|         _.--''^``-...___.._.,;"<<endl;
    std::cout<<"|===================|              /, |'.     _-'          ,--,,,--'''"<<endl;
    std::cout<<"| 0 - THOROUGHBRED  |             { |    `_-''       '    /}"<<endl;
    std::cout<<"| 1 - NOT PUREBRED  |              `;;'            ;   ; ;"<<endl;
    std::cout<<"|                   |          ._.--''     ._,,, _..'  .;.'"<<endl;
    std::cout<<"|===================|           (,_....----'''     (,..--''"<<endl;
    std::cout<<"|_____ENTER_KEY_____|"<<endl;
    in >> r._breed;
    std::cout<<"_____________________"<<endl;
    std::cout<<"|        SEX        |             ||__|,|   (`)        "<<endl;
    std::cout<<"|===================|             |_ _  |.--.) )       "<<endl;
    std::cout<<"|    0 - FEMALE     |             ( T   )     |        "<<endl;
    std::cout<<"|     1 - MALE      |            (((^_(((/(((_>        "<<endl;
    std::cout<<"|                   |                                 "<<endl;
    std::cout<<"|===================|                                "<<endl;
    std::cout<<"|_____ENTER_KEY_____|"<<endl;
    in >> r._gender;
    std::cout << "_____________________" << std::endl;
    std::cout << "|        AGE        |   //___// " << std::endl;
    std::cout << "|===================|  ( o   o )" << std::endl;
    std::cout << "|   0 - < 1 YEAR    |  (  =^=  )" << std::endl;
    std::cout << "|   1 - > 1 YEAR    |  (        )" << std::endl;
    std::cout << "|                   |  (         )"<< std::endl;
    std::cout << "|===================|  (__________)))))))))))" << std::endl;
    std::cout << "|_____ENTER_KEY_____|  " << std::endl;
    in >> r._age;
    return in;
}
