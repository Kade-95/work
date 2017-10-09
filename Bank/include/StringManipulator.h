#ifndef STRINGMANIPULATOR_H
#define STRINGMANIPULATOR_H

#include "header.h"

class StringManipulator
{
    public:
        StringManipulator();
        virtual ~StringManipulator();
        string intTOstr(int);
        int strTOin(string);
        char* strTOch(string);
        vector<string> rowTOstring(MYSQL_ROW, MYSQL_RES*);
        bool searchString(string, string);
        string stringReplacer(string, string, string*);
        string stringRestriction();
        bool isSenctence(string);
        bool isName(string);
        bool isAlpha(char);
        bool isDate(string);//dd-mm-yyyy
        bool isNumber(char);
        bool isAlphaNum(string);
        bool isEqual(string, string);
        bool isCapitalAlpha(char);
        bool isSmallAlpha(char);
        bool isSymbol(char);
        int intRestrictor();
        bool isPassValid(string);
        bool isNullString(string);
        bool isNumberString(string);
        bool isSpaceString(string);
        bool isSpace(char);
        bool isEmail(string);
        int isDayValid(string);
        int isMonthValid(string);
        int isYearValid(string);//must not be over the current year and check if the user is old enough
        bool isOldEnough(int);
        bool isLeapYear(int);
        bool isDateValid(string);

    protected:

    private:
        string alpha = "ABCDEFGHIJKLMNOPQRSTUVWSYZabcdefghijklmnopqrstuvwxyz";
        string capAlpha = "ABCDEFGHIJKLMNOPQRSTUVWSYZ";
        string ncapAlpha = "abcdefghijklmnopqrstuvwxyz";
        string number = "1234567890";
        string alphanum = alpha + number;
        string symbol = ",./?'!@#$%^&*()-_+=`~\\| ";
        int num_of_alpha = alpha.length();
        int capAlpha_no = capAlpha.length();
        int ncapAlpha_no = ncapAlpha.length();
        int number_no = number.length();
        int number_of_symbol = symbol.length();
};

#endif // STRINGMANIPULATOR_H
