#include "AnimalClass.h"
#include <vector>
using namespace std;

class BD {
private:
    vector<Animals> KotikiVec;
    ulongint _NumberOfCats;
public:
void read();
void save();
void edit(uint _id);
void add(Animals);
void Delete(uint _id);
void print();
vector<Animals>search(unsigned int _id, bool _breed, bool _gender, bool _age);
    }