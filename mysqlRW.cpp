/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mysqlRW.cpp
 * Author: Henrik
 * 
 * Created on 4. september 2016, 13:39
 */

#include <my_global.h>  //important that this is included as the first header
#include <mysql.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "tableEntry.h"

#include "mysqlRW.h"

MysqlRW::MysqlRW(const std::string& host_name, const std::string& user_name, 
                 const std::string& db_name, const std::string& password)  
                 : host_name(host_name), user_name(user_name),
                   db_name(db_name), password(password)
{
    conn = mysql_init(NULL); 
    
    if (conn == NULL)
    {
        std::cout << "Error initializing mySQL connection" << std::endl;
        throw -1;
    }
    
    if (!mysql_real_connect(conn, host_name.c_str(), user_name.c_str(), 
                                  password.c_str(), db_name.c_str(), 
                                  port_num, socket_name, flags))
    {
        std::cout << "Could not connect to mySQL database" << std::endl;
        std::cout << "Error code: " << mysql_errno(conn) << ", " 
                  << mysql_sqlstate(conn) << ", " << mysql_error(conn) 
                  << std::endl;
        mysql_close(conn);
        throw -1;
    } 
    
}

MysqlRW::MysqlRW(std::istringstream& istr)
{
    if (istr >> host_name >> user_name >> db_name >> password)
    {
        conn = mysql_init(NULL);
        
        if (conn == NULL)
        {
            std::cout << "Error initializing mySQL connection" << std::endl;
            throw -1;
        }
        
        if (!mysql_real_connect(conn, host_name.c_str(), user_name.c_str(), 
                                      password.c_str(), db_name.c_str(), 
                                      port_num, socket_name, flags))
        {
            std::cout << "could not connect\n" << std::endl;
            std::cout << "Error code: " << mysql_errno(conn) << ", " 
                      << mysql_sqlstate(conn) << ", " << mysql_error(conn) 
                      << std::endl;
            mysql_close(conn);
            throw -1;
        } 
    }
}


