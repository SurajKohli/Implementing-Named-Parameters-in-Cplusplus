#include <iostream>
#include "functiondefinitions.hpp"
#include "matchfunctions.hpp"
#include "symboltable.hpp"

std::string replaceFunctionCall( std::pair<std::string,std::string> call );
std::string replaceFunctionCall( std::pair<std::string,std::string> func, auto functionDefns );
std::string replaceObjectFunctionCall( std::pair<std::string,std::string> call , int obj_ptr );
bool replace(std::string& str, const std::string& from, const std::string& to);
void findandreplacefunctioncalls( std::string file_name );
FunctDefn *fd ;
SymbolTable *st ;

void parseFile( FunctDefn *fd, SymbolTable *st, std::string file_name );


int main(int argc, char const *argv[])
{
	if( argc < 2 )
    {
        std::cerr << "Usage : cpp-params [HEADER FILES] [SOURCE FILES] or [SOURCE FILES]" << std::endl;
        return 1;
    }
    #if 0
    std::string src_file = argv[1];
    std::string header_file;
    if( argv[2] == NULL )
    {
        header_file = argv[1];
    }
    else
    {
        header_file = argv[2];
    }
    fd = FunctDefn::getInstance( header_file );
   	st = SymbolTable::getInstance( header_file );
    parseFile( fd, st, header_file );
    //findandreplacefunctioncalls( src_file );
    #endif
    fd = FunctDefn::getInstance(""); //Change to no args -- explicit
    st = SymbolTable::getInstance("");  //Change to no args -- explicit
    int i = 1;
    while( argv[i] != NULL )
    {
        parseFile( fd, st, argv[i] );
        ++i;
    }
	return 0;
}

void parseFile( FunctDefn *fd, SymbolTable *st, std::string file_name )
{
    std::string line;
    std::ifstream f( file_name );
    std::ofstream o("tmp.cpp");
    if( !f.is_open() || !o.is_open() )
    {
        std::cerr << "Cannot open file\n";
        exit(-1);
    }
    while( std::getline( f, line ) )
    {
        std::smatch line_match;
        if( ! ( line_match = matchFunctionDef( line ) ).empty() )
        {
            //std::cout << line << '\n';
            o << line << '\n';
            //std::cout << "Function definition : " << line_match.str(3) << "\t" << line_match.str(4) << '\n';
            fd->insertNormalFunction( line_match.str(3), line_match.str(4) );


        }
        else if( ! ( line_match = matchClassDef( line ) ).empty() )
        {
            //std::cout << "match class dfn :  " << line << '\n';
            o << line << '\n';
            //std::cout << "Class definition : " << line_match.str(2) << "\t" << line_match.str(3) << '\n';
            st->insertClassDefn( f, o, line_match.str(2), line_match.str(3) );

        }
        else if( ! ( line_match = matchObjDeclr( line ) ).empty() )
        {
            //std::cout << line << '\n';
            o << line << '\n';
            //std::cout << "Obj declr : " << line_match.str(4) << "\t" << line_match.str(1) << '\n';
            st->insertObjDeclaration( line_match.str(4), line_match.str(1) );

        }
        else if( ! ( line_match = matchObjectFunctionCall( line ) ).empty() )
        {
            //std::cout << "Object Function call : " << line_match.str(1) << "\t" << line_match.str(3) << '\n';
            int obj_ptr(-1);
            auto func = std::make_pair( line_match.str(1), line_match.str(3) );
            if( line_match.str(2) == "." )
            	obj_ptr = 0;
            else if( line_match.str(2) == "->" )
            	obj_ptr = 1;
            auto res = replaceObjectFunctionCall( func , obj_ptr );
            //std::cout << "replaced function call => " << res << '\n';
            replace( line, line_match.str(0), res );
            //std::cout << line << '\n';
            o << line << '\n';
        }
        else if( ! ( line_match = matchFunctionCall( line ) ).empty() )
        {
            //std::cout << "Normal Function call : " << line_match.str(0) << '\n';
            auto func = std::make_pair( line_match.str(1), line_match.str(2) );
            auto res = replaceFunctionCall( func );
            replace( line, line_match.str(0), res );
            //std::cout << line << '\n';
            o << line << '\n';
            //std::cout << "replaced function call => " << res << '\n';
        }
        else
        {
            //std::cout << line << '\n';
            o << line << '\n';
        }
    }

}

#if 0
void findandreplacefunctioncalls( std::string file_name )
{
	std::string line;
	std::ifstream f( file_name );
	if( f.is_open() )
	{
		while( std::getline( f , line ) )
		{
			auto func = matchObjectFunctionCall( line ); //Get the object name and the funciton name // FIXME: Use better var name
			if( ( func.first.compare("") != 0 ) && ( func.second.compare("") != 0 ) )
			{
                std::cout << "Object function call\n";
				auto res = replaceObjectFunctionCall( func );
				std::cout << "replaced function call => " << res << std::endl;
			}
			else 
			{
				func = matchFunctionCall( line );
				if( ( func.first.compare("") != 0 ) && ( func.second.compare("") != 0 ) )
            	{
                    std::cout << "Normal function call\n";
                	auto res = replaceFunctionCall( func );
                	std::cout << "replaced function call => " << res << std::endl ;
                	
            	}
			}
		}
	}
	else
	{
		std::cerr << "Cannot open File : " << file_name << std::endl;
		exit(-1); 
	}
}
#endif

std::string replaceFunctionCall( std::pair<std::string,std::string> func )
{
    //std::cout << "Replace function call\n";
    std::vector< std::string > values;
    //std::cout << "Replace function call\n";
    std::string func_name = func.first; //Function Name
    auto actualParams = insertActualParameters( func.second );
    //auto p = fd->functionDefns->find( it.first );
    auto iter_pair = fd->functionDefns->equal_range( func_name );
    if( iter_pair.first == iter_pair.second )
    {
        std::cerr << "Function Definition : " << func_name << " not found\n";
        exit(EXIT_FAILURE);
    }
    for( auto iter = iter_pair.first; iter != iter_pair.second; ++iter )
    {
        if( ( iter->second->m_numNormalArgs == actualParams.size() ) 
                || ( ( actualParams.size() > iter->second->m_numNormalArgs ) 
                    && ( actualParams.size() <= iter->second->m_numNormalArgs + iter->second->m_numDefArgs ) ) )
        {
            //std::cout << "Function : " << iter->first;
            //std::cout << ( iter->second->m_overloaded ? " (Overloaded)\n" : "\n" );
            std::queue<std::pair<std::string,std::string>> params( *(iter->second->formal_params) );
            while( !params.empty() )
            {
                auto param_arg_pair = params.front();
                auto param_name = param_arg_pair.first;
                auto def_arg = param_arg_pair.second;
                std::string val("");
                auto q = actualParams.find( param_name );
                if( q == actualParams.end() )
                {
                    //Check for default args
                    if( ! def_arg.empty() )
                    {
                        //std::cout << param_name << " : " << def_arg << " (Default arg)" << std::endl;
                        val = def_arg;
                    }
                    else
                    {
                        std::cerr << "Param : " << param_name  << " in function " << func_name << " not found\n";
                        break;
                    }
                }
                else
                {
                    //std::cout << param_name << " : " << q->second << std::endl;
                    val = q->second;
                }
                params.pop();
                values.push_back(val);
            }
            std::string res = func_name;
            res += "(";
            for( auto &param_val : values )
            {
                res += param_val;
                res += ",";
            }
            res.pop_back();
            res+= ")";
            return res;
        }
    }
    return std::string("");
    /*std::cout << line << std::endl;
    std::string final_func_call = replaceFuncCall( line, values );
    std::cout << final_func_call <<std::endl;
    std::cout << "-----------" << std::endl;*/

    //functionCalls->insert( std::pair<std::string, std::unordered_map<std::string, std::string>>( func.first, actualParams ) );
#if 0
    std::cout << "Replace function call\n";
    std::string res = call.first + "(";
    auto actualParams = insertActualParameters( call.second );
    auto p = fd->functionDefns->find( call.first );
    if( p == fd->functionDefns->end() )
    {
        std::cerr << "Function " << call.first << " not found\n";
        exit(EXIT_FAILURE);
    }

    auto iter_pair = fd->functionDefns->equal_range( call.first );
    if( iter_pair.first == iter_pair.second )
    {
        std::cerr << "Function Definition : " << it.first << " not found\n";
        exit(-1);
    }
    for( auto iter = iter_pair.first; iter != iter_pair.second; ++iter )
    {
        if( ( iter->second->m_numNormalArgs == call.second.size() ) 
                || ( ( it.second.size() > iter->second->m_numNormalArgs ) 
                    && ( it.second.size() <= iter->second->m_numNormalArgs + iter->second->m_numDefArgs ) ) )
        {

        }
    }
#endif
#if 0
    while( !p->second->formal_params->empty() )
    {
        auto param_arg_pair = p->second->formal_params->front();
        auto param_name = param_arg_pair.first;
        auto def_arg = param_arg_pair.second;
        auto q = actualParams.find( param_name );
        if( q == actualParams.end() )
        {
            //Check for default args
            if( ! def_arg.empty() )
            {
                if( p ->second->formal_params->size() == 1 )
                    res = res + def_arg ;
                else
                    res = res + def_arg + " , ";
                std::cout << param_name << " : " << def_arg << " (Default arg)" << std::endl;
            }
            else
            {
                std::cerr << "Param : " << param_name  << " in function " << call.first << " not found\n";
                exit(-1);
            }
        }
        else
        {
            if( p ->second->formal_params->size() == 1 )
                res = res + q->second ;
            else
                res = res + q->second + " , ";
            std::cout << param_name << " : " << q->second << std::endl;
        }
        p->second->formal_params->pop();
    }
    return res + ")";
#endif
}

std::string replaceFunctionCall( std::pair<std::string,std::string> func, auto functionDefns )
{
    std::vector< std::string > values;
    //std::cout << "Replace function call\n";
    std::string func_name = func.first; //Function Name
    auto actualParams = insertActualParameters( func.second );
    //auto p = fd->functionDefns->find( it.first );
    auto iter_pair = functionDefns->equal_range( func_name );
    for( auto iter = iter_pair.first; iter != iter_pair.second; ++iter )
    {
        if( ( iter->second->m_numNormalArgs == actualParams.size() ) 
                || ( ( actualParams.size() > iter->second->m_numNormalArgs ) 
                    && ( actualParams.size() <= iter->second->m_numNormalArgs + iter->second->m_numDefArgs ) ) )
        {
            //std::cout << "Function : " << iter->first;
            //std::cout << ( iter->second->m_overloaded ? " (Overloaded)\n" : "\n" );
            std::queue<std::pair<std::string,std::string>> params( *(iter->second->formal_params) );
            while( !params.empty() )
            {
                auto param_arg_pair = params.front();
                auto param_name = param_arg_pair.first;
                auto def_arg = param_arg_pair.second;
                std::string val("");
                auto q = actualParams.find( param_name );
                if( q == actualParams.end() )
                {
                    //Check for default args
                    if( ! def_arg.empty() )
                    {
                        //std::cout << param_name << " : " << def_arg << " (Default arg)" << std::endl;
                        val = def_arg;
                    }
                    else
                    {
                        std::cerr << "Param : " << param_name  << " in function " << func_name << " not found\n";
                        break;
                    }
                }
                else
                {
                    //std::cout << param_name << " : " << q->second << std::endl;
                    val = q->second;
                }
                params.pop();
                values.push_back(val);
            }
            std::string res = func_name;
            res += "(";
            for( auto &param_val : values )
            {
                res += param_val;
                res += ",";
            }
            res.pop_back();
            res+= ")";
            return res;
        }
    }
    return std::string("");
}

std::string replaceObjectFunctionCall( std::pair<std::string,std::string> call , int obj_ptr )
{
    //std::cout << "Replace object function call\n";
    std::string res = call.first ;
    if( obj_ptr == 0 )
		res = res + "." ; //TODO: have to account for pointers
	else if ( obj_ptr == 1)
		res = res + "->" ;
	std::string function_call = "" ;
    std::string funcName;
    std::string funcArgs;
	auto func_match = matchFunctionCall( call.second ); //Get the function name and arg list
	/*if( ( func.first.compare("") != 0 ) && ( func.second.compare("") != 0 ) )
	{
		auto actualParams = insertActualParameters( func.second );
		function_call = func.first ; //Function name
		// res  = res + func.first + " ( ";
	}*/
    if( !func_match.empty() )
    {
        funcName = func_match.str(1);
        funcArgs = func_match.str(2);
        auto actualParams = insertActualParameters( funcArgs );
        function_call = funcName ; //Function name
    }
	auto class_name = st->symbolTableObjName->find( call.first ); //Obtain class name from symbol table referncing via object name
	if( class_name == st->symbolTableObjName->end() )
    {
    	std::cerr << "Wrong object name " << call.first << " used for calling function : " << call.second << std::endl;
        exit(EXIT_FAILURE);
    }
    auto function_set = st->symbolTableFuncName->find( class_name->second );
    if( function_set == st->symbolTableFuncName->end() )
    {
    	//should not happen generally
    	std::cerr << "No matching class for the object named : " << call.first << std::endl ;
        exit(EXIT_FAILURE);
    }
    //function_set->second is my class attribute object

    auto classattribute_func_name_set = function_set->second->class_func_defs;
    bool funcFound = false ; 
    /*for ( auto i : *classattribute_func_name_set )
    {
    	if( i.first == function_call )
    	{
    		res += replaceFunctionCall( std::make_pair( funcName, funcArgs ) );
    		funcFound = true;
    	}
    }*/
    std::string res_func_call;
    if( ( res_func_call = replaceFunctionCall( std::make_pair( funcName, funcArgs ), classattribute_func_name_set ) ).compare("") != 0 )
    {
        funcFound = true;
        //Extract string
        res += res_func_call;
    }
    if( !funcFound ) //Function not found. Check base class
    {
    	auto inhereted = function_set->second->isInherited_ ;
    	if( inhereted )
    	{
    		//check for base class
    		for( auto it : *function_set->second->inherited_class )
    		{
    			auto classattribute_func_name_set = it->class_func_defs;
    			/*for ( auto i : *classattribute_func_name_set )
    			{
    				if( i.first == function_call ) //Function found in base class
    				{
    					res += replaceFunctionCall(std::make_pair( funcName, funcArgs ));
    					funcFound = true ;
    					break;
    				}

    			}*/
                if( ( res_func_call = replaceFunctionCall( std::make_pair( funcName, funcArgs ), classattribute_func_name_set ) ).compare("") != 0 )
                {
                    funcFound = true;
                    res += res_func_call;
                    break;
                }
    	    }
    		if( !funcFound )
    		{
    			std::cerr << "No such function named "<< function_call << " present in the class : " << class_name->second<<std::endl ;
                exit(EXIT_FAILURE);
    		}
    	}
    	else
    	{
    		std::cerr << "No such function named "<< function_call << " present in the class : " << class_name->second<<std::endl ;
            exit(EXIT_FAILURE);
    	}
    }

	return res ;
}

bool replace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
