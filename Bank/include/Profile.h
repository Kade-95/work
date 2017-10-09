#ifndef PROFILE_H
#define PROFILE_H

#include "header.h"
#include "StringManipulator.h"
#include "Database.h"

class Profile
{
    public:
        Profile();
        virtual ~Profile();
        void run();

    protected:
        StringManipulator man;

    private:

    class CreatProfile{//create profile class
        public:
            bool makeProfile();

        protected:
            string setFirstName();
            string setLastName();
            string setOtherName();
            string setDateOfBirth();
            string setSex();
            string setNationality();
            string setStateOfOrigin();
            string setLocalGovArea();
            string setAddress();
            string setMaritalStatus();
            string setOccupation();
            string setAccountType();
            string setId();
            string setPassword();
            string getAccountNo();
            string setEmail();

        private:
            int balance;
            Database data;
            StringManipulator man;
            string value;
            string maritalStatus[3] = {"Single", "Married", "Engaged"};
            string sex[2] = {"Male", "Female"};
            string accountType[4] = {"Fixed", "Savings", "Current"};
    };

    class EditProfile{
    public:

    protected:

    private:
        bool updateProfile();

    };
};

#endif // PROFILE_H
