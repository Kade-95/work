#ifndef DATABASE_H
#define DATABASE_H

#include "header.h"
#include "StringManipulator.h"

class Database
{
    public:
        Database();
        virtual ~Database();
        bool connectHost();
        vector<string> read(string, int);
        bool write(string);
        bool update(string);
        bool del(string);
        bool check(string, string, int);
        bool authenticate(string, string, string);
        string getColumn(string, string, string, int);

        void CreateDB();
        bool CreateCustomerTable();

    protected:

    private:
        MYSQL *con;
        MYSQL_RES *res;
        MYSQL_ROW row;
        int qvalue;
        StringManipulator *man;
};

#endif // DATABASE_H
