#ifndef VSEOTEC_H
#define VSEOTEC_H


class Vseotec
{
public:
    virtual ~Vseotec(){}
    virtual bool isEqual(Vseotec const &) const =0;
    virtual bool isUnequal(Vseotec const &) const =0;
    virtual bool whichClass()const=0;
};

#endif // VSEOTEC_H
