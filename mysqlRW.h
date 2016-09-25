/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mysqlRW.h
 * Author: Henrik
 *
 * Created on 4. september 2016, 13:38
 */

#ifndef MYSQLRW_H
#define MYSQLRW_H

#include <my_global.h>  //important that this is included as the first header
#include <mysql.h>

#include <cstdlib>
#include <iosfwd>  //contains all forward declarations of iostream
#include <string>
#include <cstring>

#include <boost/property_tree/ptree.hpp>

#include "tableEntry.h"

class MysqlRW {
private:

    std::string host_name;
    std::string user_name;
    std::string password;
    std::string db_name;
    unsigned int port_num = 0;
    const char* socket_name = NULL;
    unsigned int flags = 0;

    MYSQL *conn;

    // how to make sure that only one instance of this class exists?

public:
    // Exception is thrown (-1) if error is encountered during initialization
    // or establishment of mySQL connection
    MysqlRW(const std::string& host_name, const std::string& user_name,
            const std::string& db_name, const std::string& password);

    // accepts istringstream containing space-delimited sequence of:
    // host_name user_name db_name password
    // provided by the configIO class from the config file
    MysqlRW(std::istringstream& istr);
};

#endif /* MYSQLRW_H */

