#include "StringManipulator.h"

StringManipulator::StringManipulator(){
    //ctor
}

StringManipulator::~StringManipulator(){
    //dtor
}

bool StringManipulator::isOldEnough(int year){
    time_t now = time(0);
    tm *local = localtime(&now);
    int currentYear = local->tm_year + 1900;
    if((currentYear - year) > 18){
        return true;
    }
    return false;
}

int StringManipulator::isYearValid(string value){
    string s;
    time_t now = time(0);
    tm *local = localtime(&now);
    int currentYear = local->tm_year + 1900;
    for(int i=0; i<4; i++){
        s += value[6+i];
    }
    int year = atoi(s.c_str());
    if(year){
        if(year<=currentYear){
            return year;
        }
    }
    return 0;
}

int StringManipulator::isMonthValid(string value){
    string s;
    for(int i=0; i<2; i++){
        s += value[3+i];
    }
    int month = atoi(s.c_str());
    if(month){
        if(month<=12){
            return month;
        }
    }
    return 0;
}

bool StringManipulator::isLeapYear(int year){
    if(year%4 == 0){
        if((year%100 == 0) & (year%400 != 0)){
            return false;
        }
        return true;
    }
    return false;
}

int StringManipulator::isDayValid(string value){
    string s;
    time_t now = time(0);
    tm *local = localtime(&now);
    for(int i=0; i<2; i++){
        s += value[0+i];
    }
    int day = atoi(s.c_str());
    int limit = 0;
    int month = isMonthValid(value);
    if(month == 1){//jan
        limit = 31;
    }else if(month == 2){//feb
        if(isLeapYear(isYearValid(value))){
            limit = 29;
        }else{
            limit = 28;
        }
    }else if(month == 3){//mar
        limit = 31;
    }else if(month == 4){//apr
        limit = 30;
    }else if(month == 5){//may
        limit = 31;
    }else if(month == 6){//jun
        limit = 30;
    }else if(month == 7){//jul
        limit = 31;
    }else if(month == 8){//aug
        limit = 31;
    }else if(month == 9){//sep
        limit = 30;
    }else if(month == 10){//oct
        limit = 31;
    }else if(month == 11){//nov
        limit = 30;
    }else if(month == 12){//dec
        limit = 31;
    }

    if(day){
        if(day<=limit){
            return day;
        }
    }
    return 0;
}

int StringManipulator::strTOin(string value){
    int rValue= atoi(value.c_str());
    return rValue;
}

string StringManipulator::intTOstr(int value){
    stringstream oss;
    oss << value;
    return oss.str();
}

char *StringManipulator::strTOch(string s){
        vector<char> c(s.length() + 1);
        strcpy(&c[0], s.c_str());

    char *rc = &c[0];
}

string StringManipulator::stringReplacer(string value, string from, string *to){
    size_t pos = 0;
    int i = 0;
    while((pos = value.find(from, pos)) != string::npos){
        value.replace(pos, from.length(), to[i]);
        pos += to[i].length();
        i++;
    }
    return value;
}

bool StringManipulator::searchString(string value, string toFind){
    char *pc = strstr(value.c_str(), toFind.c_str());
    if(pc == NULL){
        return false;
    }else{
        return true;
    }
}

vector<string> StringManipulator::rowTOstring(MYSQL_ROW row, MYSQL_RES *res){
    vector<string> value;
    stringstream oss;
    int num = mysql_num_fields(res);
    for(int i=0; i<num; i++){
        oss << row[i];
        value.push_back(oss.str());
        oss.str("");
    }
    return value;
}

bool StringManipulator::isSenctence(string value){
    char *cValue = strTOch(capAlpha);
    char *cAlpha = strTOch(capAlpha);
    for(int j=0; j<capAlpha_no; j++){
        if(cValue[0] == cAlpha[j]){
            return true;
        }
    }
    return false;
}

int StringManipulator::intRestrictor(){
    int value;
    if(!(cin >> value)){
        cin.clear();
        string error;
        getline(cin, error);
        cout << "Only numbers are required here:" << endl;
        return intRestrictor();
    }

    return value;
}

bool StringManipulator::isName(string value){
    int len_of_value = value.length();
    char *cValue = strTOch(value);
    if(isNullString(value)){
        return false;
    }else{
        for(int i=0; i<len_of_value; i++){
            if(isCapitalAlpha(value[0])){
                if(isAlpha(cValue[i])){
                    continue;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
    }
    return true;
}

bool StringManipulator::isAlpha(char value){
    char *cAlpha = strTOch(alpha);
    for(int i=0; i<num_of_alpha; i++){
        if(value == cAlpha[i]){
            return true;
        }
    }
    return false;
}

bool StringManipulator::isDate(string value){
    int len = value.length();
    if(len == 10){
        char *cValue = strTOch(value);
        for(int i=0; i<len; i++){
            if(isNumber(cValue[i])){
                continue;
            }else{
                if(i==2 | i==5){
                    if(cValue[i] == '-'){
                        continue;
                    }else{
                        return false;
                    }
                }else if(i == 0){

                }
            }
        }
    }else{
        return false;
    }
    return true;
}

bool StringManipulator::isDateValid(string value){
    if(isYearValid(value)){
        if(isMonthValid(value)){
            if(isDayValid(value)){
                return true;
            }
        }
    }
    return false;
}

bool StringManipulator::isSpaceString(string value){
    for(int i=0; i<value.length(); i++){
        if(!isspace(value[i])){
            return false;
        }
    }
    return true;
}

bool StringManipulator::isSpace(char value){
    if(value == ' '){
        return true;
    }
    return false;
}

bool StringManipulator::isEqual(string value, string check){
    if(value.length() != check.length()){
        return false;
    }
    for(int i=0; i<value.length(); i++){
        if(tolower(value[i]) != tolower(check[i])){
            return false;
        }
    }
    return true;
}

bool StringManipulator::isPassValid(string value){
    //must contain one cap alpha, small alpha, number and symbols //and must be more than 10 characters
    int nValue = value.length();
    if(nValue >= 8){
        for(int i=0; i<nValue; i++){
            if(isSymbol(value[i])){
                for(int j=0; j<nValue; j++){
                    if(isCapitalAlpha(value[j])){
                        for(int k=0; k<nValue; k++){
                            if(isSmallAlpha(value[k])){
                                for(int l=0; l<number_no; l++){
                                    if(isNumber(value[l])){
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool StringManipulator::isCapitalAlpha(char value){
    for(int i=0; i<capAlpha_no; i++){
        if(value == capAlpha[i]){
            return true;
        }
    }
    return false;
}

bool StringManipulator::isSmallAlpha(char value){
    for(int i=0; i<ncapAlpha_no; i++){
        if(value == ncapAlpha[i]){
            return true;
        }
    }
    return false;
}

bool StringManipulator::isAlphaNum(string value){
    int len = value.length();
    for(int i=0; i<len; i++){
        if(!(isAlpha(value[i]) | isNumber(value[i]))){
            return false;
        }
    }
    return true;
}

bool StringManipulator::isNullString(string value){
    if(value == ""){
        return true;
    }
    return false;
}

bool StringManipulator::isSymbol(char value){
    for(int i=0; i<number_of_symbol; i++){
        if(value == symbol[i]){
            return true;
        }
    }
    return false;
}

bool StringManipulator::isNumber(char value){
    char *cNumber = strTOch(number);
    for(int i=0; i<number_no; i++){
        if(value == cNumber[i]){
            return true;
        }
    }
    return false;
}

bool StringManipulator::isEmail(string value){
    int len = value.length();
    int dotPos = len - 4;
    int atPos;
    for(int i=0; i<len; i++){
        if(value[i] == '@' & i != 0){
            atPos = i;
            for(int j=atPos; j<len; j++){
                if(value[j] == '.' & j == dotPos){
                    return true;
                }
            }
        }
    }
    return false;
}

bool StringManipulator::isNumberString(string value){
    for(int i=0; i<value.length(); i++){
        if(!isNumber(value[i])){
            return false;
        }
    }
    return true;
}
