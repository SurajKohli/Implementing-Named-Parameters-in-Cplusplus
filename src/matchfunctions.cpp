#include "matchfunctions.hpp"

//std::pair<std::string, std::string> matchFunctionDef(const std::string& input)
std::smatch matchFunctionDef(const std::string& input)
{
    std::smatch func_def_match;
	std::regex regex_def("(virtual|friend)?\\s*([[:alpha:]][[:alpha:][:digit:]_]*)\\s+([[:alpha:]][[:alpha:][:digit:]_]*)\\s*\\(\\s*(((.*)\\s*([[:alpha:]][[:alpha:]]*)\\s*[,]\\s*)*(.*)\\s*([[:alpha:]][[:alpha:]]*)*)\\s*\\);");
	if(std::regex_search(input,func_def_match,regex_def)) {
        std::string func_name(func_def_match.str(3)); //Extracting function name
        std::string func_param(func_def_match.str(4)); //Extracting function params
		//return std::pair<std::string, std::string>(func_name,func_param);
        //return func_def_match;
    }
    #if 0
	else
    {
        //return std::pair<std::string, std::string>("","");
        return std::string("");
    }
    #endif
    return func_def_match;
		
}

std::smatch matchObjectFunctionDef(const std::string& input)
{
    std::smatch func_def_match;
    std::regex regex_def("(virtual|friend)?\\s*(.*)\\s+([[:alpha:]][[:alpha:][:digit:]_]*)\\s*\\(\\s*(((.*)\\s*([[:alpha:]][[:alpha:]]*)\\s*[,]\\s*)*(.*)\\s*([[:alpha:]][[:alpha:]]*)*)\\s*\\)");
    if(std::regex_search(input,func_def_match,regex_def)) {
        std::string func_name(func_def_match.str(3)); //Extracting function name
        std::string func_param(func_def_match.str(4)); //Extracting function params
        //return std::pair<std::string, std::string>(func_name,func_param);
        //return func_def_match;
    }
    #if 0
    else
    {
        //return std::pair<std::string, std::string>("","");
        return std::string("");
    }
    #endif
    return func_def_match;
        
}

//std::pair<std::string, std::string> matchFunctionCall(const std::string& input)
std::smatch matchFunctionCall(const std::string& input)
{
    const char *for_const ="for(";
    if(input.rfind(for_const,0)!=0)
    {
        std::smatch func_call_match;
        std::regex regex_call("([[:alpha:]][[:alpha:][:digit:]_]*)\\(\\s*(([[:alpha:]][[:alpha:][:digit:]_]*\\s*:[^:]*\\s*)\\s*(,\\s*[[:alpha:]][[:alpha:][:digit:]_]*\\s*:[^:]*\\s*)*)\\)\\s*");

        if(std::regex_search(input,func_call_match,regex_call)) {
            std::string func_name(func_call_match.str(1)); //Extracting function name
            std::string func_param(func_call_match.str(2)); //Extracting function params
            //return std::pair<std::string, std::string>(func_name,func_param);
            //return func_call_match.str(0);
        }
        #if 0
        else
        {
            return std::string("");
            //return std::pair<std::string, std::string>("","");
        }
        #endif
        return func_call_match;
    }
}

//std::pair<std::string , std::string > matchObjectFunctionCall( const std::string& input )
std::smatch matchObjectFunctionCall( const std::string& input )
{
    std::smatch object_func_call;
    std::regex regex_object_func_call( "([[:alpha:]][[:alpha:][:digit:]_]*)[ ]*(\\.|->)[ ]*([[:alpha:]][[:alpha:][:digit:]_]*\\(\\s*(([[:alpha:]][[:alpha:][:digit:]_]*\\s*:[^:]*\\s*)\\s*(,\\s*[[:alpha:]][[:alpha:][:digit:]_]*\\s*:[^:]*\\s*)*)\\))" );
    if( std::regex_search( input,object_func_call,regex_object_func_call ) )
    {
        std::string object_name = object_func_call.str(1); //Extracting class or object name
        std::string function_call = object_func_call.str(3); //Extracting member function
        //return std::pair< std::string,std::string >(object_name,function_call);
        //return object_func_call.str(0);
    }
    
    #if 0
    else
    {
        return std::string("");
        //return std::pair<std::string, std::string>("","");
    }
    #endif
    return object_func_call;
}

std::smatch matchClassDef( const std::string& input )
{
    std::smatch class_def;
    std::regex regex_class_def( "[ ]*(class|struct)[ ]+([[:alpha:]][[:alpha:][:digit:]_]*)[ ]*((:)(.*))?" );
    if( std::regex_match( input,class_def,regex_class_def ) )
    {
        //std::string object_name = object_func_call.str(1); //Extracting class or object name
        //std::string function_call = object_func_call.str(3); //Extracting member function
        //return std::pair< std::string,std::string >(object_name,function_call);
        //return class_def.str(0);
    }
    #if 0
    else
    {
        return std::string("");
        //return std::pair<std::string, std::string>("","");
    }
    #endif
    return class_def;
}
std::smatch matchObjDeclr( const std::string& input )
{
    std::smatch object_declr;
    std::regex regex_object_declr("([[:alpha:]][[:alpha:][:digit:]_]*)(\\*)?[ ]+(\\*)?([[:alpha:]][[:alpha:][:digit:]_]*)(;)" );
    if( std::regex_search( input,object_declr,regex_object_declr ) )
    {
        //std::string object_name = object_func_call.str(1); //Extracting class or object name
        //std::string function_call = object_func_call.str(3); //Extracting member function
        //return std::pair< std::string,std::string >(object_name,function_call);
        //return object_declr.str(0);
    }
    #if 0
    else
    {
        return std::string("");
        //return std::pair<std::string, std::string>("","");
    }
    #endif
    return object_declr;
}