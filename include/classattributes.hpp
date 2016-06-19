#ifndef CLASSATTRIBUTES_H
#define CLASSATTRIBUTES_H

#include "functionattributes.hpp"
#include <string>
#include <vector>
#include <map>

class classattributes
{
public:
	classattributes();
	~classattributes();
	classattributes( const classattributes& rhs );
	classattributes& operator=( const classattributes& rhs );
	bool isInherited_;
	std::multimap < std::string, FunctAttr* >* class_func_defs ;
	std::vector< classattributes* > *inherited_class;
	void addInheretedClass( classattributes& elem );
	
};

#endif