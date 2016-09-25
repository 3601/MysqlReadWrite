/* 
 * File:   configIO.cpp
 * Author: Henrik
 * 
 * Created on 13. september 2016, 21:16
 */

#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "tableEntry.h"

#include "configIO.h"


ConfigIO::ConfigIO(const std::string& filename)
{
    try
    {
       boost::property_tree::read_json(filename, tree); 
       configOK = true;
    }
    catch(...)
    {
        std::cout << "Error loading or parsing of config file" << std::endl;
        configOK = false;
    }
}

std::istringstream ConfigIO::getDbConfig()
{
    std::istringstream tmpstream { };
    
    if (configOK)
    {
        try
        {
            const std::string host_name_path { mysql_config + "." + host_name };
            const std::string user_name_path { mysql_config + "." + user_name };
            const std::string db_name_path   { mysql_config + "." + db_name };
            const std::string password_path  { mysql_config + "." + password };
            
            tmpstream.str(tree.get<std::string>(host_name_path) + " " +
                          tree.get<std::string>(user_name_path) + " " +
                          tree.get<std::string>(db_name_path) + " " +
                          tree.get<std::string>(password_path));
            
                      
            return tmpstream;
        }
        catch (...)
        {
            std::cout << "Error reading >" << mysql_config 
                      << "< module in config file" << std::endl;
            configOK = false;
            tmpstream.str(std::string());
            return tmpstream; //empty stringstream return upon error
        }
    } else return tmpstream; //empty stringstream return if configOK is false
}

std::istringstream ConfigIO::getTableConfig(const std::string& sensor_name)
{
    
    std::istringstream tmpstream { };
    const std::string sensorModulePath { sensors + "." + sensor_name + "." + table_entries };
    
    if (configOK)
    {
        try
        {
            tmpstream.str(tree.get<std::string>(sensorModulePath));
            return tmpstream;
        }
        catch (...)
        {
            std::cout << "Error reading from >" << sensorModulePath 
                      << "< in config file" << std::endl;
            configOK = false;
            tmpstream.str(std::string());
            return tmpstream; //empty istringstream returned upon error
        }
    } else return tmpstream;  //empty istringstream returned if configOK is false
}


