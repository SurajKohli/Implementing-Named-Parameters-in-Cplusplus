 #ifndef MATCH_FUNCTIONS_H
#define MATCH_FUNCTIONS_H
#include <regex>
#include <string>
#include <iostream>
//std::pair<std::string, std::string> matchFunctionDef(const std::string& input);
//std::pair<std::string, std::string> matchFunctionCall(const std::string& input);
//std::pair<std::string , std::string > matchObjectFunctionCall( const std::string& input );
std::smatch matchFunctionDef(const std::string& input) ;
std::smatch matchObjectFunctionDef( const std::string& input ) ;
std::smatch matchFunctionCall(const std::string& input) ;
std::smatch matchObjectFunctionCall( const std::string& input ) ;
std::smatch matchClassDef( const std::string& input ) ;
std::smatch matchObjDeclr( const std::string& input ) ;
#endif
