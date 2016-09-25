/* 
 * File:   configIO.h
 * Author: Henrik
 *
 * Created on 13. september 2016, 21:16
 */

#ifndef CONFIGIO_H
#define CONFIGIO_H

#include <iosfwd>  //contains all forward declarations in iostream
#include <string>

#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>

#include "tableEntry.h"

class ConfigIO 
{
    private:
        boost::property_tree::ptree tree { };
        bool configOK;  
        
        // name of mysql_config module in JSON config file
        const std::string mysql_config { "mysql_config" };
        
        // parameter names in mysql_config module
        const std::string host_name { "host_name" };
        const std::string user_name { "user_name" };
        const std::string db_name   { "db_name" };
        const std::string password  { "password" };
        
        // name of sensor module in JSON config file
        const std::string sensors { "sensors" };
        
        // name of table entries in sensor module
        const std::string table_entries { "table_entries" };
        
        
    public:
        // if error loading or parsing config file is encountered, the configOK
        // flag is set to false, otherwise true
        ConfigIO(const std::string& filename);
        
        // host_name, user_name, db_name, password are loaded into space-delimited
        // istringstream in this order. If error is encountered, the 
        // stringstream is returned empty and configOK is set to false
        std::istringstream getDbConfig();
        
        // returns istringstream containing column entry titles for the 
        // table with identified by snesors.sensor_name.table_entries in the 
        // config file
        // If an error is encountered configOK is set to false
        std::istringstream getTableConfig(const std::string& sensor_name);
};

#endif /* CONFIGIO_H */

