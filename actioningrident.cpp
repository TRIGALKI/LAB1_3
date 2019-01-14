#include "ingrident.h"
#include "vseotec.h"
#include "actioningrident.h"
ActionIngrident::ActionIngrident() :
    _dur(1.0F),
    _action("ceep calm")
{

}
ActionIngrident::ActionIngrident(std::string action, float dur):
    _dur(dur > 0?dur:1.0F),
    _action(action != ""?action:"ceep calm")
{

}
ActionIngrident::ActionIngrident(ActionIngrident const&inp):
    _dur(inp._dur),
    _action(inp._action)
{

}
ActionIngrident::~ActionIngrident()
{

}
std::string ActionIngrident::getAction() const
{
    return _action;
}
float ActionIngrident::getDur() const
{
    return _dur;
}
void ActionIngrident::changeDur(float newDur)
{
    if(newDur > 0)
    {
        _dur = newDur;

    }
}
void ActionIngrident::changeAction(std::string newAction)
{
    if(newAction != "")
    {
        _action = newAction;
    }

}
bool ActionIngrident::isEqual(Vseotec const & existing) const
{
    const ActionIngrident *p = static_cast<const ActionIngrident*>(&existing);
    return( (this->_action == p->_action) &&
            (this->_dur == p->_dur));
}
bool ActionIngrident::isUnequal(Vseotec const &existing) const
{
    return !(this->isEqual(existing));
}

