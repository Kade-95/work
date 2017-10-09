#include "Profile.h"
#include "Extras.h"

Profile::Profile()
{
    //ctor
}

Profile::~Profile()
{
    //dtor
}

void Profile::run(){
    fflush(stdin);
    system("cls");
    cout << "What do want to do?" << endl;
    cout << "1. Open a new account" << endl;
    cout << "2. Edit your account" << endl;
    cout << "3. Delete an account" << endl;
    cout << "4. Back to previous menu" << endl;
    cout << "5. Exit application" << endl;
    Extras extra;

    int option = man.intRestrictor();
    if(option>0 & option<6){
        if(option == 1){
            system("cls");
            CreatProfile cp;
            cp.makeProfile();
        }else if(option == 2){
            system("cls");
            cout << "This has not been implemented" << endl;
        }else if(option == 3){
            system("cls");
            cout << "This has not been implemented" << endl;
        }else if(option == 4){
            system("cls");
            extra.Display();
        }else if(option == 5){
            system("cls");
            extra.Decide();
        }
    }else{
        cout << "Wrong option, please select again" << endl;
        run();
    }
}

bool Profile::CreatProfile::makeProfile(){
    fflush(stdin);//get all the customer details for the new account
    string user_details[18];
    user_details[0] = setFirstName();
    user_details[1] = setLastName();
    user_details[2] = setOtherName();
    user_details[3] = setDateOfBirth();
    user_details[4] = setSex();
    user_details[5] = setNationality();
    user_details[6] = setStateOfOrigin();
    user_details[7] = setLocalGovArea();
    user_details[8] = setAddress();
    user_details[9] = setMaritalStatus();
    user_details[10] = setOccupation();
    user_details[11] = setAccountType();
    user_details[12] = setId();
    user_details[13] = setPassword();
    user_details[14] = getAccountNo();
    user_details[15] += user_details[0];
    user_details[15] += " ";
    user_details[15] += user_details[1];
    user_details[15] += " ";
    user_details[15] += user_details[2];
    user_details[16] = setEmail();
    user_details[17] = "20000";

    string query = man.stringReplacer("insert into bank.customers(firstname, lastname, othernames, date_of_birth, sex, nationality, state_of_origin, local_gov_area, address, marital_status, occupation, account_type, user_id, password, account_number, account_name, email, date_of_account, balance) values('%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', now(), '%')", "%", user_details);    if(data.write(query)){
        cout << "Account has been created" << endl;
        getchar();
        return true;
    }else{
        cout << "Account was not created due to errors" << endl;
        getchar();
        return false;
    }
}

string Profile::CreatProfile::setEmail(){
    fflush(stdin);
    cout << "Enter email address(Email must be valid): ";
    getline(cin, value);

    if(man.isEmail(value)){
        return value;
    }
    cout << "Not a valid email address" << endl;
    return setEmail();
}

string Profile::CreatProfile::setFirstName(){
    fflush(stdin);
    cout << "Enter first name: ";
    getline(cin, value);
    if(man.isName(value)){
        return value;
    }
    cout << "not a valid name" << endl;
    return setFirstName();
}

string Profile::CreatProfile::setLastName(){
    fflush(stdin);
    cout << "Enter last name: ";
    getline(cin, value);
    if(man.isName(value)){
        return value;
    }
    cout << "not a valid name" << endl;
    return setLastName();
}

string Profile::CreatProfile::setOtherName(){
    fflush(stdin);
    string value;
    cout << "Enter other name: ";
    getline(cin, value);
    if(man.isName(value)){
        return value;
    }
    cout << "not a valid name" << endl;
    return setOtherName();
}

string Profile::CreatProfile::setDateOfBirth(){
    fflush(stdin);
    string value;
    cout << "Enter date of birth: (dd-mm-yyyy)";
    getline(cin, value);
    if(man.isDate(value) & man.isDateValid(value)){
        if(man.isOldEnough(man.isYearValid(value))){
            return value;
        }else{
            cout << "Not old enough to open an account" << endl;
            return setDateOfBirth();
        }
    }
    cout << "not a valid date of birth" << endl;
    return setDateOfBirth();
}

string Profile::CreatProfile::setSex(){
    fflush(stdin);
    string value;
    cout << "Enter gender: (Male, Female)";
    getline(cin, value);
    if(man.isName(value)){
        for(int i=0; i<sizeof(sex); i++){
            if(value == sex[i]){
                return value;
            }
        }
    }
    cout << "not a valid gender" << endl;
    return setSex();
}

string Profile::CreatProfile::setNationality(){
    fflush(stdin);
    string value;
    cout << "Enter Nationality: ";
    getline(cin, value);
    if(!man.isNullString(value) & !man.isNumberString(value) & !man.isSpaceString(value)){
        if(man.isCapitalAlpha(value[0])){
            return value;
        }
    }
    cout << "not a valid name of country" << endl;
    return setNationality();
}

string Profile::CreatProfile::setStateOfOrigin(){
    fflush(stdin);
    string value;
    cout << "Enter state of origin: ";
    getline(cin, value);
    if(!man.isNullString(value) & !man.isNumberString(value) & !man.isSpaceString(value)){
        if(man.isCapitalAlpha(value[0])){
            return value;
        }
    }
    cout << "not a valid name of state" << endl;
    return setStateOfOrigin();
}

string Profile::CreatProfile::setLocalGovArea(){
    fflush(stdin);
    string value;
    cout << "Enter Local Government Area: ";
    getline(cin, value);
    if(!man.isNullString(value) & !man.isNumberString(value) & !man.isSpaceString(value)){
        if(man.isCapitalAlpha(value[0])){
            return value;
        }
    }
    cout << "not a valid name of local government area" << endl;
    return setLocalGovArea();
}

string Profile::CreatProfile::setAddress(){
    fflush(stdin);
    string value;
    cout << "Enter Address: ";
    getline(cin, value);
    if(!man.isNullString(value) & !man.isNumberString(value) & !man.isSpaceString(value)){
        return value;
    }
    cout << "not a valid address" << endl;
    return setAddress();
}

string Profile::CreatProfile::setMaritalStatus(){
    fflush(stdin);
    string value;
    cout << "Enter Marital Status: (Married, Single, Engaged)";
    int nMaritalStatus = sizeof(maritalStatus)/sizeof(string);
    getline(cin, value);
    if(man.isName(value)){
        for(int i=0; i<nMaritalStatus; i++){
            if(man.isEqual(value, maritalStatus[i])){
                return maritalStatus[i];
            }
        }
    }
    cout << "not a valid marital status" << endl;
    return setMaritalStatus();
}

string Profile::CreatProfile::setOccupation(){
    fflush(stdin);
    string value;
    cout << "Enter Occupation: ";
    getline(cin, value);
    if(!man.isNullString(value) & !man.isNumberString(value) & !man.isSpaceString(value)){
        if(man.isCapitalAlpha(value[0])){
            return value;
        }
    }
    cout << "not a valid name of occupation" << endl;
    return setOccupation();
}

string Profile::CreatProfile::setAccountType(){
    fflush(stdin);
    string value;
    cout << "Enter Account Type: (Fixed, Savings, Current)";
    int nAccountType = sizeof(accountType)/sizeof(string);
    getline(cin, value);
    if(man.isName(value)){
        for(int i=0; i<nAccountType; i++){
            if(man.isEqual(value, accountType[i])){
                return accountType[i];
            }
        }
    }
    cout << "not a valid account type" << endl;
    return setAccountType();
}

string Profile::CreatProfile::setId(){
    fflush(stdin);
    cout << "Enter ID: ";
    getline(cin, value);
    if(man.isAlphaNum(value)){
        if(!data.check(value, "select * from customers", 13)){
            cout << "ID already in use" << endl;
            return setId();
        }
        return value;
    }
    cout << "not a valid ID" << endl;
    return setId();
}

string Profile::CreatProfile::setPassword(){
    fflush(stdin);
    string value;
    cout << "Enter password: (Password must contain at least one capital letter, small letter, number and symbol and must be more than 8 characters: ";
    getline(cin, value);
    if(man.isPassValid(value)){
        fflush(stdin);
        cout << "re-enter password: ";
        string password;
        getline(cin, password);
        if(man.isPassValid(password)){
            if(password == value){
                return value;
            }else{
                cout << "Password does not match" << endl;
            }
        }
    }
    cout << "not a valid password" << endl;
    return setPassword();
}

string Profile::CreatProfile::getAccountNo(){
    stringstream oss;
    string accountNo;
    string accountArray[5];
    srand(time(NULL));
    int firstParh = rand()%100000 + 10000;//get the first part of the account no
    int secondPart = rand()%100000 + 10000;//get the second part
    oss << firstParh << secondPart;
    value = oss.str();
    oss.str("");

    if(!data.check(value, "select * from customers", 15)){
        return getAccountNo();
    }
    return value;
}
