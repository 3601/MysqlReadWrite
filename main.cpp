/* 
 * File:   main.cpp
 * Author: Henrik
 *
 * Created on 28. august 2016, 11:54
 */

#include "mysqlRW.h"
#include <iostream>
#include <string>
#include "tableEntry.h"
#include "configIO.h"
#include <boost/property_tree/ptree.hpp>

int main() 
{

    TableEntry<int,double,std::string> sqlTable("test");
    sqlTable.addEntry("Henrik");
    sqlTable["Tina"] = 2;
    sqlTable["Henrik"] = "stringtest";
    
    sqlTable << "Rasmus" << "Mathias";
    
    for (const auto &indx : sqlTable)
        std::cout << indx.getTitle() << ":  " << indx.getValueStr() << "; ";
    
    std::cout << std::endl;
    
    std::cout << "Call with new title: " << sqlTable["Thomas"].getTitle() << std::endl;
    
    // sqlTable.flush();
    std::cout << "Values after flush: " << std::endl;
    for (const auto &indx : sqlTable)
        std::cout << indx.getTitle() << ": " << indx.getValueStr() << "; ";
    
    std::cout << std::endl << "--- Load of config.json file ---" << std::endl;
    
    ConfigIO cfgFile("C:/Users/Henrik/Programming/Cpp/mysqlReadWrite/mysqlReadWrite/config.json");

    std::istringstream dbConfig = cfgFile.getDbConfig();
    
    std::string host_name, user_name, db_name, password { };
    
    dbConfig >> host_name >> user_name >> db_name >> password;
    
    std::cout << "Mysql settings: " << host_name << ", " << user_name << ", "
              << db_name << ", " << password << std::endl;
    
    std::istringstream tableconfig { };
    
    tableconfig = cfgFile.getTableConfig("sensor1_name");
    
    while (tableconfig >> sqlTable) {};
    
    std::cout << "Table contents after addition of entries from config file" << std::endl;
    
    for (const auto &indx : sqlTable)
        std::cout << indx.getTitle() << ": " << indx.getValueStr() << std::endl;
    
    return 0;

}

