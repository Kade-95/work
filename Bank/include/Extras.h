#ifndef EXTRAS_H
#define EXTRAS_H

#include "header.h"
#include "StringManipulator.h"
#include "Profile.h"
#include "Transaction.h"

class Extras
{
    public:
        Extras();
        virtual ~Extras();
        void Display();
        void Decide();
        StringManipulator man;
        Transaction operate;
        Profile person;


    protected:

    private:
};

#endif // EXTRAS_H
