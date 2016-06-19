#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H 

#include <map>
#include "functionattributes.hpp"
#include "matchfunctions.hpp"
#include "insertparams.hpp"
#include "classattributes.hpp"
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

class SymbolTable
{
private:

	SymbolTable( );

	~SymbolTable( );

	SymbolTable( const SymbolTable& rhs );

	SymbolTable& operator=( const SymbolTable& rhs );

	void getSymbolTable( std::string file_name );

	static SymbolTable *instance_;

	std::set<std::string> class_names;

public:

	std::unordered_map< std::string,std::string > *symbolTableObjName;

	std::multimap< std::string,classattributes* > *symbolTableFuncName;

	static SymbolTable* getInstance( std::string file_name );

	void insertClassDefn( std::ifstream &f, std::ofstream &o, std::string class_name, std::string inherited_string );

	void insertObjDeclaration( std::string objName, std::string className );

	//static void deleteInstance();
	
};

#endif
