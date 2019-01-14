#include "vseotec.h"
#include "assert.h"
#include <iostream>
#include "ingrident.h"
Ingrident::Ingrident() :
    _number(1),
    _value("grams"),
    _name("Meat")
{

}
Ingrident::Ingrident(std::string name, std::string value, int number):
    _name(name != ""?name:"Meat"),
    _value(value != ""?value:"grams"),
    _number(number > 0?number:1)
{

}
Ingrident::Ingrident(Ingrident &inp):
    _name(inp._name),
    _value(inp._value),
    _number(inp._number)
{
}
Ingrident::~Ingrident()
{

}
std::string Ingrident::getName() const
{
    return _name;
}
std::string Ingrident::getValue() const
{
    return _value;
}
int Ingrident::getNumber() const
{
    return _number;
}
void Ingrident::changeNumber(int newNumber)
{
    if(newNumber > 0)
    {
        _number = newNumber;

    }
}
void Ingrident::changeName(std::string newName)
{
    if(newName != "")
    {
        _name = newName;
    }

}
void Ingrident::changeValue(std::string newValue)
{
    if(newValue != "")
    {
        _value = newValue;
    }

}
bool Ingrident::isEqual(Vseotec const &existing) const
{
    const Ingrident *p = static_cast<const Ingrident*>(&existing);
    return((this->getName() == (p->_name))&&(this->getNumber() == (p->_number))
           &&(this->getValue() == (p->_value)));
}
bool Ingrident::isUnequal(Vseotec const &existing) const
{
    return !(this->isEqual(existing));
}


