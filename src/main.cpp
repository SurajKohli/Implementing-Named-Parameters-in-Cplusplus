#include <iostream>
#include "functiondefinitions.hpp"
#include "finding_function_calls.h"

std::multimap<std::string, std::unordered_map<std::string,std::string>>* getFunctionCalls( std::string src_file );
int main( int argc, char *argv[] )
{
    if( argc < 3 )
    {
        std::cerr << "Usage : cpp-params [SOURCE FILE] [HEADER FILE]" << std::endl;
        exit(-1);
    }
    std::string src_file = argv[1];
    std::string header_file = argv[2];
    FunctDefn fd( header_file );
    auto funcCalls = getFunctionCalls( src_file );
    for( const auto &it : *funcCalls )
    {
        auto p = fd.functionDefns->find( it.first );
        if( p == fd.functionDefns->end() )
        {
            std::cout << "Function Definition : " << it.first << " not found\n";
            continue;
        }
        while( !p->second->formal_params->empty() )
        {
            auto val = p->second->formal_params->front();
            auto q = it.second.find( val );
            if( q == it.second.end() )
            {
                std::cout << "Param : " << val << " in function " << it.first << " not found\n";
                break;
            }
            std::cout << val << " : " << q->second << std::endl;
            p->second->formal_params->pop();
        }
        delete p->second;
    }
    delete funcCalls;

    return 0;
}

std::multimap<std::string, std::unordered_map<std::string,std::string>>* getFunctionCalls( std::string src_file )
{
    auto *functionCalls = new std::multimap<std::string, std::unordered_map<std::string,std::string>>(); 
    std::string line;
    std::ifstream f( src_file  );
    if( f.is_open() )
    {
        while( std::getline( f, line ) )
        {
            auto func = matchFunctionCall( line );
            if( ( func.first.compare("") != 0 ) && ( func.second.compare("") != 0 ) )
            {
                auto actualParams = insertActualParameters( func.second );
                functionCalls->insert( std::pair<std::string, std::unordered_map<std::string, std::string>>( func.first, actualParams ) );
            }
        }
    }
    else
    {
        std::cerr << "Cannot open file" << std::endl;
    }
    return functionCalls;
}
