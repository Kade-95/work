#include "Database.h"

Database::Database(){
    //ctor
    man = new StringManipulator();
    CreateDB();
}

Database::~Database(){
    mysql_close(con);
    delete(con);
    delete(man);
    //dtor
}

bool Database::connectHost(){
    con = mysql_init(0);
    if(!con){
        return false;
    }else{
        con = mysql_real_connect(con, dbHost, dbUser, dbPass, NULL, 0, NULL, 0);
        if(con){
            return true;
        }else{
            cout << "Connection error";
        }
    }
    return false;
}

vector<string> Database::read(string query, int column){
    vector<string> value;
    int i;
    if(connectHost()){
        qvalue = mysql_query(con, query.c_str());
        if(!qvalue){
            res = mysql_store_result(con);
            i = mysql_num_fields(res);
            if(i>column){
                while(row = mysql_fetch_row(res)){
                    value.push_back(man->rowTOstring(row, res).at(column));
                }
            }else{
                value.push_back("Hey not accessible");
            }
        }else{
            value.push_back("Query Error");
        }
    }else{
        value.push_back("Connection Error");
    }
    return value;
}

bool Database::write(string query){
    if(connectHost()){
        qvalue = mysql_query(con, query.c_str());
        if(!qvalue){
            return true;
        }
    }
    return false;
}

bool Database::check(string value, string query, int column){
    int len = read(query, column).size();
    for(int i=0; i<len; i++){
        if(value == read(query, column).at(i)){
            return false;
        }
    }
    return true;
}

bool Database::authenticate(string account_no, string id, string password){
    string detail[1] = {account_no};
    if(connectHost()){
        string query = man->stringReplacer("select * from customers where account_no='%'", "%", detail);
        qvalue = mysql_query(con, query.c_str());
        if(!qvalue){
            res = mysql_store_result(con);
            while(row = mysql_fetch_row(res)){
                if(id == row[13] & password == row[14]){
                    return true;
                }
            }
        }
    }
    return false;
}

string Database::getColumn(string table, string column, string value, int rValue){
    string detail[3] = {table, column, value};
    if(connectHost()){
        string query = man->stringReplacer("select * from % where %='%'", "%", detail);
        qvalue = mysql_query(con, query.c_str());
        if(!qvalue){
            int i=0;
            res = mysql_store_result(con);
            while(row = mysql_fetch_row(res)){
                return row[rValue];
            }
        }
    }
    return "Not Found";
}

bool Database::update(string query){
    if(connectHost()){
        qvalue = mysql_query(con, query.c_str());
        if(!qvalue){
            return true;
        }
    }
    return false;
}

bool Database::del(string query){
    if(connectHost()){
        qvalue = mysql_query(con, query.c_str());
        if(!qvalue){
            return true;
        }
    }
    return false;
}

void Database::CreateDB(){
    if(connectHost()){
        string details[] = {"bank"};
        string query = man->stringReplacer("CREATE DATABASE IF NOT EXISTS %", "%", details);
        qvalue = mysql_query(con, query.c_str());
        if(!qvalue){
            if(!CreateCustomerTable()){
                cout << "Customer table could not be created" << endl;
                exit(-1);
            }
        }
    }
}

bool Database::CreateCustomerTable(){
    if(con){
        qvalue = mysql_query(con, "CREATE TABLE IF NOT EXISTS bank.customers(id int PRIMARY KEY NOT NULL AUTO_INCREMENT, firstname varchar(225), lastname varchar(225), othernames varchar(225), date_of_birth varchar(225), sex varchar(225), nationality varchar(225), state_of_origin varchar(225), local_gov_area varchar(225), address varchar(225), marital_status varchar(225), occupation varchar(225), account_type varchar(225), user_id varchar(225), password varchar(225), account_number varchar(225), account_name varchar(225), email varchar(225), date_of_account date, balance int(100), transaction_details text)");
        if(!qvalue){
            return true;
        }
    }
    return false;
}
