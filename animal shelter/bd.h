#include "AnimalClass.h"
#include <vector>

class BD {
private:
    std::vector<Animals> KotikiVec = {};
    unsigned long int _NumberOfCats = {};
public:
    void read();
    void save();
    void edit(unsigned long int _id);
    void add(Animals animal);
    void Delete(unsigned long int _id);
    void print();
    int search(short int _breed, short int _gender, short int _age, std::vector<Animals>* retAnim);
    unsigned long int size();
    Animals takeCat(unsigned long int id);
};