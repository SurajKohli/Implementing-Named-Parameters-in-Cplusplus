#include "classattributes.hpp"

classattributes::classattributes( )
:isInherited_(false) , class_func_defs( new std::multimap < std::string, FunctAttr* >() ),inherited_class( new std::vector<classattributes*>( ) )
{

}

classattributes::~classattributes( )
{
	delete inherited_class;
	for ( auto it : *class_func_defs )
	{
		delete it.second;
	}
	delete class_func_defs;
}

classattributes::classattributes( const classattributes& rhs )
{
	isInherited_ = rhs.isInherited_ ;
	class_func_defs = rhs.class_func_defs ;
	inherited_class = rhs.inherited_class ;
}

classattributes& classattributes::operator=( const classattributes& rhs )
{
	isInherited_ = rhs.isInherited_ ;
	for ( auto it : *class_func_defs )
	{
		delete it.second ;
	}
	delete class_func_defs ;
	class_func_defs = rhs.class_func_defs ;
	delete inherited_class ;
	inherited_class = rhs.inherited_class ;
}

void classattributes::addInheretedClass(  classattributes& elem )
{
	inherited_class->push_back( &elem );
}