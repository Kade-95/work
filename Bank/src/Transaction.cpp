#include "Transaction.h"
#include "Extras.h"

Transaction::Transaction(){
    fflush(stdin);
}

Transaction::~Transaction(){
    fflush(stdin);
}

string Transaction::setTime(){//set the time for the transaction
    time_t now = time(0);
    stringstream oss;
    tm *local = localtime(&now);
    oss << local->tm_hour << "-" << local->tm_min << "-" << local->tm_sec;//concat the sec min and hour
    return oss.str();
}

string Transaction::setDate(){
    time_t now = time(0);
    stringstream oss;
    tm *local = localtime(&now);
    oss << local->tm_year + 1900 << "-" << local->tm_mon + 1 << "-" << local->tm_mday;//same as setTime
    return oss.str();
}

void Transaction::run(){
    system("cls");
    cout << "What type of transaction do you want to do?" << endl;
    cout << "1. Make a deposit" << endl;
    cout << "2. Make a withdrawal" << endl;
    cout << "3. Make a transfer" << endl;
    cout << "4. Check your balance" << endl;
    cout << "5. Check your transaction history" << endl;
    cout << "6. Back to previous menu" << endl;
    cout << "7. Exit the application" << endl;

    Extras extra;
    int option = man.intRestrictor();
    if(option>0 & option<8){
        if(option == 1){
            system("cls");
            deposit();
        }else if(option == 2){
            system("cls");
            withdraw();
        }else if(option == 3){
            system("cls");
            transfer();
        }else if(option == 4){
            system("cls");
            balance();
        }else if(option == 5){
            system("cls");
            getTransactionDetails();
        }else if(option == 6){
            system("cls");
            extra.Display();
        }else if(option == 7){
            system("cls");
            extra.Decide();
        }
    }else{
        cout << "Wrong option, please select again" << endl;
        run();
    }
}

bool Transaction::authenticate(){
    fflush(stdin);
    cout << "Enter the account number: ";
    getline(cin, account_no);
    cout << "Enter the your ID: ";
    getline(cin, id);
    cout << "Enter the your password: ";
    getline(cin, password);

    if(data.authenticate(account_no, id, password)){//authenticate the user using the database
        return true;
    }else{
        return false;
    }
}

bool Transaction::balance(){
    fflush(stdin);
    if(!authenticate()){
        cout << "Account number, ID or Password incorrect, Re-enter";
        return balance();
    }
    int balance = man.strTOin(data.getColumn("customers", "user_id", this->id, 19));//get the balance from the database
    cout << "Your balance is " << balance << endl;
    getchar();
    return true;
}

bool Transaction::withdraw(){
    if(!authenticate()){
        cout << "Account number, ID or Password incorrect, Re-enter";
        return withdraw();
    }
    fflush(stdin);
    cout << "Enter the amount you want to withdraw: ";
    amount = man.intRestrictor();
    int balance = man.strTOin(data.getColumn("customers", "user_id", this->id, 19));
    int value = balance - amount;
    if(value >= 500){//make sure at-least 500 is remaining after every transaction
        string detail[] = {man.intTOstr(value), this->id};
        string query = man.stringReplacer("update customers set balance='%' where user_id='%'", "%", detail);
        string now = setDate() + ":";
        now += setTime();
        if(data.update(query)){
            return setTransactionDetails("withdraw", "self", "null", account_no, now, man.intTOstr(amount));//set the details of the transaction and store in database
        }
    }
    cout << "Transaction not successful" << endl;
    return withdraw();
}

bool Transaction::deposit(){
    cout << "Enter the account number you are depositing to: ";
    fflush(stdin);
    getline(cin, account_no);
    cout << "Enter the account name: ";
    string account_name, depositorName, depositorId;
    getline(cin, account_name);

    if(data.getColumn("customers", "account_no", account_no, 13) == data.getColumn("customers", "account_name", account_name, 13)){
        int balance = man.strTOin(data.getColumn("customers", "account_no", account_no, 19));
        cout << "Enter your name: ";
        fflush(stdin);
        getline(cin, depositorName);
        cout << "Enter your signature: ";
        getline(cin, depositorId);
        cout << "Enter the amount to deposit: ";
        int amount = man.intRestrictor();
        int value_to = amount + balance;

        string detail[] = {man.intTOstr(value_to), account_no};
        string query = man.stringReplacer("update customers set balance='%' where account_no='%'", "%", detail);

        if(data.update(query)){
            string now = setDate() + ":";
            now += setTime();//set the details of the transaction and store it in the database
            return setTransactionDetails("deposit", depositorName, "null", "null", now, man.intTOstr(amount));
        }else{
            cout << "Transaction not successful" << endl;
            return deposit();
        }
    }else{
        cout << "Account number or name is incorrect, check and try again" << endl;
        return deposit();
    }
}

bool Transaction::transfer(){
    if(!authenticate()){
        cout << "Account number, ID or Password incorrect, Re-enter" << endl;
        transfer();
    }
    fflush(stdin);
    cout << "Enter the amount you want to transfer: ";
    amount = man.intRestrictor();
    int balance = man.strTOin(data.getColumn("customers", "user_id", this->id, 19));
    int value_from = balance - amount;
    if(value_from >= 500){
        cout << "Enter the account number you are transferring to: ";
        string account_to;
        fflush(stdin);
        getline(cin, account_to);
        cout << "Enter the account name: ";
        string account_name;
        getline(cin, account_name);

        if(data.getColumn("customers", "account_no", account_to, 13) == data.getColumn("customers", "account_name", account_name, 13)){
            balance = man.strTOin(data.getColumn("customers", "account_no", account_to, 19));
            int value_to = amount + balance;

            string detail_from[] = {man.intTOstr(value_from), this->id};
            string query_from = man.stringReplacer("update customers set balance='%' where user_id='%'", "%", detail_from);

            string detail_to[] = {man.intTOstr(value_to), account_to};
            string query_to = man.stringReplacer("update customers set balance='%' where account_no='%'", "%", detail_to);

            if(data.update(query_to)){//update the depositors account and then update the gainers account too
                if(data.update(query_from)){
                    string now = setDate() + ":";
                    now += setTime();
                    return setTransactionDetails("transfer", "self", account_to, account_no, now, man.intTOstr(amount));
                }
            }else{
                cout << "Transaction not successful" << endl;
                return transfer();
            }
        }else{
            cout << "Account number or name is incorrect, check and try again" << endl;
            return transfer();
        }
    }
    cout << "You do not have sufficient balance in your account" << endl;
    return transfer();
}

string Transaction::getTransactionDetails(){
    if(!authenticate()){
        cout << "Account number, ID or Password incorrect, Re-enter" << endl;
        getTransactionDetails();
    }
    string transactionDetail = data.getColumn("customers", "account_no", this->account_no, 20);
    cout << transactionDetail;
    getchar();
    return transactionDetail;
}

string Transaction::setDepositDetails(string ammount, string name, string date){
    string details[] = {name, ammount, date};
    string dDetail = man.stringReplacer("% deposited % to your account on %;", "%", details);
    return dDetail;
}

string Transaction::setWithdrawalDetails(string ammount, string date){
    string details[] = {ammount, date};
    string dDetail = man.stringReplacer("You withdrew % from your account on %;", "%", details);
    return dDetail;
}

string Transaction::setTransferToDetails(string ammount, string account, string date){
    string details[] = {ammount, account, date};
    string dDetail = man.stringReplacer("You transfered % to % on %;", "%", details);
    return dDetail;
}

string Transaction::setTransferFromDetails(string ammount, string account, string date){
    string details[] = {account, ammount, date};
    string dDetail = man.stringReplacer("% transfered % to you on %;", "%", details);
    return dDetail;
}

bool Transaction::setTransactionDetails(string type, string name, string account_to, string account_from, string date, string amount){
    string detail, query;
    string currentDetail;
    fflush(stdin);
    if(type == "deposit"){
        detail = setDepositDetails(amount, name, date);
        currentDetail = data.getColumn("customers", "account_no", account_to, 20);
        currentDetail += detail;
        string details[] = {currentDetail, account_to};
        query = man.stringReplacer("update customers set transaction_details='%' where account_no='%'", "%", details);
        if(data.update(query)){
            cout << "Transaction successful" << endl;
            getchar();
            return true;
        }
    }else if(type == "withdraw"){
        detail = setWithdrawalDetails(amount, date);
        currentDetail = data.getColumn("customers", "account_no", account_from, 20);
        currentDetail += detail;
        string details[] = {currentDetail, account_from};
        query = man.stringReplacer("update customers set transaction_details='%' where account_no='%'", "%", details);
        if(data.update(query)){
            cout << "Transaction successful" << endl;
            getchar();
            return true;
        }
    }else if(type == "transfer"){
        detail = setTransferFromDetails(amount, account_from, date);
        currentDetail = data.getColumn("customers", "account_no", account_to, 20);
        currentDetail += detail;
        string detailsTo[] = {currentDetail, account_to};
        query = man.stringReplacer("update customers set transaction_details='%' where account_no='%'", "%", detailsTo);

        detail = setTransferToDetails(amount, account_to, date);
        currentDetail = data.getColumn("customers", "account_no", account_from, 20);
        currentDetail += detail;
        string detailsFrom[] = {currentDetail, account_from};

        if(data.update(query)){
            query = man.stringReplacer("update customers set transaction_details='%' where account_no='%'", "%", detailsFrom);
            if(data.update(query)){
                cout << "Transaction successful" << endl;
                getchar();
                return true;
            }
        }
    }else{
        cout << "Not a transaction type " << endl;
        setTransactionDetails(type, name, account_to, account_from, date, amount);
    }
}
