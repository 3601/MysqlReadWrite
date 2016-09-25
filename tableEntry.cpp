/* 
 * File:   tableEntry.cpp
 * Author: Henrik
 * 
 * Created on 28. august 2016, 11:58
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>

#include "tableEntry.h"

template<typename T1, typename T2, typename T3>
bool TableEntry<T1,T2,T3>::addEntry(const std::string& entryTitle)
{
    
    if (entryVec.size() > 0) // test if entryTitle already exists
    {
        for (auto &idx : entryVec)
            if (idx.ColumnEntry<T1,T2,T3>::getTitle() == entryTitle)
                return false;
    }   
    
    entryVec.push_back(ColumnEntry<T1,T2,T3>(entryTitle));
    // std::cout << "ColumnEntry no " << entryVec.size() << " added to table: " << tableTitle << ". The title is: " 
    //           << entryVec[entryVec.size()-1].ColumnEntry<T1,T2,T3>::getTitle()
    //           << std::endl;
    return true;            
}

template<typename T1, typename T2, typename T3>
ColumnEntry<T1,T2,T3>& TableEntry<T1,T2,T3>::operator[](const std::string& entryTitle)
{
    
    std::cout << "This is a call to the overloaded [] operator with string: " << entryTitle << std::endl;    
    
    if (entryVec.size() > 0)
        for (auto &idx : entryVec)
        {
            // std::cout << "Range-based loop search for: " << entryTitle << "; Current entry is: " << idx.ColumnEntry<T1,T2,T3>::getTitle() << std::endl;
            if (idx.ColumnEntry<T1,T2,T3>::getTitle() == entryTitle)
                return idx;
        } 
    
    entryVec.push_back(ColumnEntry<T1,T2,T3>(entryTitle));
    // std::cout << "No entry with title: " << entryTitle << " was found. New entry created. No of entries is " << entryVec.size() << std::endl;
    return entryVec[entryVec.size()-1];
   
}

template<typename T1, typename T2, typename T3>
ColumnEntry<T1,T2,T3>& TableEntry<T1,T2,T3>::operator[](const int& index)
{
    return entryVec.at(index);  //throws std::out_of_range if index is out of range
}

template<typename T1, typename T2, typename T3>
void TableEntry<T1,T2,T3>::flush()
{
    for (auto &indx : entryVec)
        indx.flush();
}

template<typename T1, typename T2, typename T3>
int TableEntry<T1,T2,T3>::getSize() const
{
    return entryVec.size();
}

template<typename T1, typename T2, typename T3>
std::string TableEntry<T1,T2,T3>::getTitle() const
{
    return tableTitle;
}


/*
 *  TableEntry friend functions
 */

template <typename T4, typename T5, typename T6>
TableEntry<T4,T5,T6>& operator<< (TableEntry<T4,T5,T6>& table, 
                                  const std::string& entryTitle)
{

    table.addEntry(entryTitle);
    return table;
}


template <typename charT, typename traits, typename T4, typename T5, typename T6>
std::basic_istream<charT,traits>& operator>> 
    (std::basic_istream<charT,traits>& istr, TableEntry<T4,T5,T6>& table)
{
    std::string tmpstr { };
    if (istr >> tmpstr)
        table.addEntry(tmpstr);
    return istr;
}



