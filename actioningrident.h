#ifndef ACTIONINGRIDENT_H
#define ACTIONINGRIDENT_H
#include "vseotec.h"
#include <iostream>
class ActionIngrident:public Vseotec
{
public:
    ActionIngrident();
    ActionIngrident(std::string action,float dur);
    ActionIngrident(ActionIngrident const &np);
    virtual ~ActionIngrident() override;
    //селекторы и модификаторы
    std::string getAction()const;
    void changeAction(std::string newAction);
    float getDur()const;
    void changeDur(float newDur);
    bool isEqual(Vseotec const &)const override;
    bool isUnequal (Vseotec const &)const override;
    bool whichClass()const override {return false;}
private:
    float _dur;
    std::string _action;


};

#endif // ACTIONINGRIDENT_H
