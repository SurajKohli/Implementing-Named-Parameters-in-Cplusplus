#include "insertparams.hpp"

std::unordered_map<std::string, std::string> insertActualParameters( std::string call_string )
{
    std::unordered_map<std::string,std::string> actual_parameters;
    std::vector<std::string> params;
    boost::split( params, call_string, boost::is_any_of(" ,"), boost::token_compress_on );
    params.erase( std::remove( begin(params), end(params), " " ), end(params) );
    params.erase( std::remove_if( begin(params), end(params), 
                                   []( std::string x ) { return x.empty(); } ), end(params) );
    for( auto &it : params ) {
        std::vector<std::string> param_pair;
        boost::split( param_pair, it, boost::is_any_of(" :"), boost::token_compress_on );
        param_pair.erase( std::remove( begin(param_pair), end(param_pair), " " ), end(param_pair) );
        param_pair.erase( std::remove_if( begin(param_pair), end(param_pair), 
                                       []( std::string x ) { return x.empty(); } ), end(param_pair) );
        std::pair<std::string, std::string> p(param_pair[0],param_pair[1]);
        actual_parameters.insert( p );
    }
    return actual_parameters;
}

void insertFormalParameters( std::string declr_string, FunctAttr *f )
{
    std::vector<std::string> params;
    boost::split( params, declr_string, boost::is_any_of(","), boost::token_compress_on );
    params.erase( std::remove( begin(params), end(params), " " ), end(params) );
    params.erase( std::remove_if( begin(params), end(params), 
                                   []( std::string x ) { return x.empty(); } ), end(params) );
    for( auto &it : params )
    {
        std::vector<std::string> param_declr;
        std::smatch m;
        if( regex_search( it, m, std::regex("(.*)[ ]?(=[ ]?(.*))" )) ) //See if the param has a default argument
        {
            f->setHasDefArgs();
            std::string param_type_name = m.str(1); //Type and param name
            boost::split( param_declr, param_type_name,  boost::is_any_of(" "), boost::token_compress_on );
            param_declr.erase( std::remove( begin(param_declr), end(param_declr), " " ), end(param_declr) );
            param_declr.erase( std::remove_if( begin(param_declr), end(param_declr), 
                               []( std::string x ) { return x.empty(); } ), end(param_declr) );
            std::string param_name = param_declr.back();
            std::string def_value = m.str(3); //Default args
            auto p = std::make_pair( param_name, def_value );
            f->formal_params->push( p );
            ++(f->m_numDefArgs);
        }
        else
        {
            boost::split( param_declr, it,  boost::is_any_of(" "), boost::token_compress_on );
            param_declr.erase( std::remove( begin(param_declr), end(param_declr), " " ), end(param_declr) );
            param_declr.erase( std::remove_if( begin(param_declr), end(param_declr), 
                        []( std::string x ) { return x.empty(); } ), end(param_declr) );
            std::string param_name = param_declr.back();
            std::string def_value;
            auto p = std::make_pair( param_name, def_value );
            f->formal_params->push( p );
            ++(f->m_numNormalArgs);
        }
    }
}
