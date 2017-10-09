#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "header.h"
#include "StringManipulator.h"
#include "Database.h"
#include "Profile.h"

class Transaction
{
    public:
        Transaction();
        virtual ~Transaction();
        void run();
        bool setTransactionDetails(string, string, string, string, string, string);

    protected:
        bool withdraw();
        bool deposit();
        bool transfer();
        bool authenticate();
        bool balance();
        string getTransactionDetails();
        string setDepositDetails(string,string,string);
        string setWithdrawalDetails(string,string);
        string setTransferToDetails(string,string,string);
        string setTransferFromDetails(string,string,string);
        string setTime();
        string setDate();

    private:
        string account_no;
        int amount;
        string password;
        string id;

        bool operation;
        Database data;
        Profile person;
        StringManipulator man;
};

#endif // TRANSACTION_H
