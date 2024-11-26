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
    void search(unsigned long int _id, bool _breed, bool _gender, bool _age, std::vector<Animals>* retAnim);
};