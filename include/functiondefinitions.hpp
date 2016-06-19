#ifndef FUNCTDEFN_H
#define FUNCTDEFN_H

#include <map>
#include "functionattributes.hpp"
#include "matchfunctions.hpp"
#include "insertparams.hpp"
#include <fstream>
#include <iostream>

/**
 * @brief The FunctDefn class
    * It is used to get all the function
    * defintions, and create FunctAttr objects
    * for each function definition 
 * @author Utkarsh Simha
 */
class FunctDefn
{
    private:
        FunctDefn();

        ~FunctDefn();

        FunctDefn( const FunctDefn& rhs );

        FunctDefn& operator=( const FunctDefn& rhs );

        /**
         * @brief Get the funciton definitions from the
         * header file and then populate the multimap.
         * It also inserts the formal parameters into 
         * a queue
         */
        void getFunctionDefns( std::string file_name );

        static FunctDefn *instance_;

    public:
        static FunctDefn* getInstance( std::string file_name );
        static void deleteInstance();

        void insertNormalFunction( std::string funcName, std::string funcArgs );

        //Multimap which maintains function names and maps them
        //to an object of the FunctAttr class which holds
        //the attributes of the function
        std::multimap<std::string, FunctAttr*> *functionDefns;
};
#endif
