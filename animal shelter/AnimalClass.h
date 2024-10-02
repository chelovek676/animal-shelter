#ifndef ANIMALCLASS_H
#define ANIMALCLASS_H

#include <iostream>

class Animals{
private:
    unsigned int _id;
    bool _breed;
    bool _gender;
    unsigned short int _age;
    bool _status; //В приюте?
public:
    unsigned int get_Id() const;
    void set_Id(const unsigned int &id);
    bool get_Breed() const;
    void set_Breed(const bool &breed);
    bool get_Gender() const;
    void set_Gender(const bool &gender);
    unsigned short int get_Age() const;
    void set_Age(const unsigned short int &age);
    bool get_Status() const;
    void set_Status(const bool &status);
    friend std::ostream &operator <<(std::ostream &out, const Animals &r);
    friend std::istream &operator >>(std::istream &in, Animals &r);
};

#endif // ANIMALCLASS_H
