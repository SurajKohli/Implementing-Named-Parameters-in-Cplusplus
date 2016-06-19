#include "symboltable.hpp"

SymbolTable* SymbolTable::instance_ = nullptr;

SymbolTable* SymbolTable::getInstance( std::string file_name )
{
	if( !instance_ )
	{
		instance_ = new SymbolTable(  );
	}
    instance_->getSymbolTable( file_name );
	return instance_;
}

SymbolTable::SymbolTable( )
:symbolTableObjName( new std::unordered_map <  std::string,std::string > ),
symbolTableFuncName( new std::multimap < std::string,classattributes* > ),
class_names()
{

}

SymbolTable::~SymbolTable( )
{
	delete symbolTableObjName;
	for ( auto it : *symbolTableFuncName )
	{
		delete it.second;
	}
	delete symbolTableFuncName;
}

SymbolTable::SymbolTable( const SymbolTable& rhs )
{
	symbolTableObjName = new std::unordered_map < std::string,std::string > ( *rhs.symbolTableObjName );
	symbolTableFuncName = new std::multimap < std::string,classattributes* > ( *rhs.symbolTableFuncName ); //doubt
    class_names = rhs.class_names ;
}

SymbolTable& SymbolTable::operator=( const SymbolTable& rhs )
{
	delete symbolTableObjName;
	for ( auto it : *symbolTableFuncName )
	{
		delete it.second;
	}
	delete symbolTableFuncName;
	symbolTableObjName = new std::unordered_map < std::string,std::string > ( *rhs.symbolTableObjName );
	symbolTableFuncName = new std::multimap < std::string,classattributes* > ( *rhs.symbolTableFuncName ); 
    class_names = rhs.class_names;
}

void SymbolTable::getSymbolTable( std::string file_name )
{   

#if 0
    // std::string line;
    // std::ifstream f( file_name );
    // Done // std::set<std::string> class_names; //Make it into class member
    if( f.is_open() )
    {
        while( std::getline( f, line ) )
        {
            //check if its starts with class some_name or struct some_name
            //if it does check next line is {
        	//then keep taking next line and call the matchfunctiondefintion
        	//till you encounter };
        	//Not reqiured // std::smatch obj_class_match;
        	// Not required // std::smatch obj_name_match;
        	std::regex regex_obj_name_match( "([[:alpha:]][[:alpha:][:digit:]_]*)(\\*)?[ ]+(\\*)?([[:alpha:]][[:alpha:][:digit:]_]*)(;)" );
        	std::regex regex_class_match( "[ ]*(class|struct)[ ]+([[:alpha:]][[:alpha:][:digit:]_]*)[ ]*((:)(.*))?" );
            // const char *ending_brace = "};";
            
        	if( std::regex_search( line,obj_class_match,regex_class_match ) )
        	{
                class_names.insert( obj_class_match.str(2) );
                std::string class_name = obj_class_match.str(2) ;
                std::getline(f,line);
        		if( line == "{" )
        		{

                    classattributes *class_object = new classattributes( );
        			std::multimap< std::string, FunctAttr* >* classFunctDefnition( new std::multimap<std::string, FunctAttr*> );
                    //get the : part for inheretence 
                    //split and get the classes
                    if( obj_class_match.str(3) != "" )
                    {
                        class_object->isInherited_ = true;
                        std::string inhereted_string = obj_class_match.str(3);
                        std::smatch inherted_class;
                        std::regex regex_inhereted( "[ ]*(:)[ ]*(.*)" );
                        if( std::regex_match( inhereted_string,inherted_class,regex_inhereted ) )
                        {
                            inhereted_string = inherted_class.str(2);
                            std::vector< std::string > v;
                            boost::split( v, inhereted_string, boost::is_any_of(","), boost::token_compress_on );
                            if( v.back() == "" )
                                v.pop_back();
                            for( auto &it : v )
                            {
                                std::vector<std::string> param_pair;
                                boost::split( param_pair, it, boost::is_any_of(" "), boost::token_compress_on );
                                auto itm = symbolTableFuncName->find(param_pair[1]); 
                                if( itm != symbolTableFuncName->end() )
                                {
                                    class_object->addInheretedClass( *itm->second );
                                }
                                else
                                {
                                    std::cerr << "Class in Inheretence not declared " << std::endl ;
                                    exit(-1);
                                }
                            }
                        }
                    }
        			while(  std::getline( f,line )  )
        			{
                        if(line.rfind(ending_brace,0) != 0 )
                        {
        				    auto func = matchFunctionDef( line );
        				    if( ( func.first.compare("") != 0 ) && ( func.second.compare("") != 0 ) )
        				    {
        					   FunctAttr *f = new FunctAttr();
        					   insertFormalParameters( func.second, f );
        					   classFunctDefnition->insert( std::pair<std::string, FunctAttr*>( func.first,f ) );
        				    }
                        }
                        else
                        {
                            break;
                        }
        			}

                    class_object->class_func_defs = classFunctDefnition ;
        			symbolTableFuncName->insert( std::pair< std::string,classattributes* >( class_name,class_object ) );
                    // std::cout << "class _name => " << class_name << "\n ";

        		}
        	}
        	else if( std::regex_search( line,obj_name_match,regex_obj_name_match ) && ( class_names.find(obj_name_match.str(1)) != end(class_names)  ) )
        	{
        		symbolTableObjName->insert( std::pair<std::string,std::string>( obj_name_match.str(4),obj_name_match.str(1) ) );
                // std::cout << obj_name_match.str(4) << "\t" << obj_name_match.str(1) << "\n" ;
        	}

        }
        f.close();
    }
    else
    {
        std::cerr << "Cannot open the file" << std::endl;
    }
#endif
}

// class_name - str(2) ; inherited_string - str(3)
void SymbolTable::insertClassDefn( std::ifstream &f, std::ofstream &o, std::string class_name, std::string inherited_string )
{
    std::string line;
    const char *ending_brace = "};";
    class_names.insert( class_name ); //Insert class name
    std::getline(f,line);
    o << line << '\n';
    if( line == "{" )
    {

        classattributes *class_object = new classattributes( ); //Storing attributes of class
        std::multimap< std::string, FunctAttr* >* classFunctDefnition( new std::multimap<std::string, FunctAttr*> );
        //get the : part for inheretence 
        //split and get the classes
        if( inherited_string != "" ) //Class inherits
        {
            class_object->isInherited_ = true;
            std::smatch inherted_class;
            std::regex regex_inhereted( "[ ]*(:)[ ]*(.*)" );
            if( std::regex_match( inherited_string,inherted_class,regex_inhereted ) )
            {
                inherited_string = inherted_class.str(2); //Discard access specifier
                std::vector< std::string > v; // FIXME: Use a more intuitive name than 'v'
                boost::split( v, inherited_string, boost::is_any_of(","), boost::token_compress_on );
                if( v.back() == "" )
                    v.pop_back();
                for( auto &it : v )
                {
                    std::vector<std::string> param_pair;
                    boost::split( param_pair, it, boost::is_any_of(" "), boost::token_compress_on );
                    auto itm = symbolTableFuncName->find(param_pair[1]); 
                    // std::cout << "Inhertited class : " << param_pair[1] << "\n" ;
                    if( itm != symbolTableFuncName->end() )
                    {
                        class_object->addInheretedClass( *itm->second );
                    }
                    else
                    {
                        std::cerr << "Class in Inheretence not defined\n";
                        exit(-1);
                    }
                }
            }
        }
        while(  std::getline( f,line )  )
        {
            o << line << '\n';
            if(line.rfind(ending_brace,0) != 0 )
            {
                std::smatch func_match = matchObjectFunctionDef( line );
                if( ! func_match.empty() )
                {
                    //std::cout << "Member function definition : " << func_match.str(0) << '\n';
                    std::string funcName = func_match.str(3);
                    std::string funcParams = func_match.str(4);
                    FunctAttr *f = new FunctAttr();
                    insertFormalParameters( funcParams, f );
                    classFunctDefnition->insert( std::make_pair( funcName,f ) );
                }
            }
            else
            {
                break;
            }
        }

        class_object->class_func_defs = classFunctDefnition ;
        symbolTableFuncName->insert( std::make_pair( class_name,class_object ) );
        // std::cout << "class _name => " << class_name << "\n ";

    }
}

//objName - str(4) ; className - str(1)
void SymbolTable::insertObjDeclaration( std::string objName, std::string className )
{
    if( class_names.find( className ) != class_names.end() )
    {
        symbolTableObjName->insert( std::make_pair( objName, className ) );
    }
}