#ifndef INGRIDENT_H
#define INGRIDENT_H

#include <iostream>
#include <string>
#include "vseotec.h"
class Ingrident:public Vseotec
{
public:
    Ingrident();
    Ingrident(std::string name,std::string  value, int number);
    Ingrident(Ingrident &inp);
    virtual ~Ingrident() override;
    //cелектор
    std::string getName() const;
    int getNumber() const;
    std:: string getValue() const;
    //модификатор
    void changeNumber(int newNumber);
    void changeValue(std::string newValue);
    void changeName(std::string newName);
    bool isEqual (Vseotec const&) const override;
    bool isUnequal (Vseotec const&) const override;
    bool whichClass()const override {return true;}
private:
    std::string _name,  _value;
    int _number;


};

#endif // INGRIDENT_H
