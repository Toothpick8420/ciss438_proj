#ifndef DB_H
#define DB_H
#include <iostream>
#include <fstream>
#include <bitset>
#include <functional>
#include <sqlite3.h>
#include <string>
#include <vector>

static int login_callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    //std::cout << "in login" << std::endl;
    std::vector<std::string> * row_data = (std::vector<std::string> *)data;
    //std::cout << "converted" << std::endl;
    for(i = 0; i < int(argc); ++i)
    {
        (*row_data).push_back(std::string(argv[i]));
    }
    std::cout << std::endl;
    //std::cout << "In Login " << (*row_data).size() << std::endl;
    return 0;
}

//Insert Sql into db. For Creating profiles
static void insert_sql(std::string username, std::string pass, sqlite3* DB)
{
    char* messageError;
    std::string sql = "INSERT INTO USER (USERNAME, PASSWORD, HIGHSCORE, WINS, LOSSES) VALUES ('";
    sql = sql + username + "',";
    sql = sql + "'" + pass + "',0,0,0);";
    //std::cout << sql.c_str() << std::endl;
    sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);
    //std::cout << "DONE INSERTING" <<std::endl;
    return;
}

//Done on first time startup
int initDB(sqlite3* DB)
{
    int exit = 0;
    char* messaggeError;
    std::string create = (std::string("CREATE TABLE USER(")+
                          "USERNAME           VARCHAR(25)    NOT NULL, "+
                          "PASSWORD        VARCHAR(25)     NOT NULL, "+
                          "HIGHSCORE            INT, "+
                          "WINS        INT, "+
                          "LOSSES INT);");
    
    exit = sqlite3_exec(DB, create.c_str(), NULL, NULL, &messaggeError);
    return exit;
}

void registerUser(sqlite3 * DB)
{
    std::string UN;
    std::string pw;
    std::vector<std::string> data;
    std::cout << "Username: ";
    std::cin >> UN;
    std::cout << "Password: ";
    std::cin >> pw;
    insert_sql(UN, pw, DB); 
}

void print_sql(std::vector<std::string> data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        std::cout << data[i] << ' ';
        if ((i + 1) % 5 == 0)
            std::cout << '\n';
    }
}

    
void showAll(sqlite3* DB)
{
    std::cout << "All users in Database: " << std::endl;
    std::vector<std::string> data;
    std::string select = "SELECT * from USER;";
    int exit = sqlite3_exec(DB, select.c_str(), login_callback, (&data), NULL);
    
    print_sql(data);
    
}
std::string selectUser(sqlite3 * DB)
{
    std::string UN;
    std::string PW;
    std::vector<std::string> data;
        
    std::cout << "Username: ";
    std::cin >> UN;
    std::cout << "Password: ";
    std::cin >> PW;
    
    std::string login = "Select USERNAME from User where USERNAME = ";
    login = login + "'" + UN + "' and PASSWORD = '" + PW + "';";
    int exit = sqlite3_exec(DB, login.c_str(), login_callback, (&data), NULL);
    if (data.size() > 0)
        return data[0];
    //Login not found
    return "";
    
}

#endif
