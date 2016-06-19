#include "functiondefinitions.hpp"

FunctDefn* FunctDefn::instance_ = nullptr;

FunctDefn* FunctDefn::getInstance( std::string file_name )
{
    if( !instance_ )
    {
        instance_ = new FunctDefn( );
    }
    instance_->getFunctionDefns( file_name );
    return instance_;
}

void FunctDefn::deleteInstance()
{
    delete instance_;
}

FunctDefn::FunctDefn()
: functionDefns( new std::multimap<std::string, FunctAttr*> )
{
}

FunctDefn::~FunctDefn()
{
    for( auto it : *functionDefns )
    {
        delete it.second;
    }
    delete functionDefns;
}

FunctDefn::FunctDefn( const FunctDefn& rhs )
{
    functionDefns = new std::multimap<std::string, FunctAttr*>( *rhs.functionDefns );
}

FunctDefn& FunctDefn::operator=( const FunctDefn& rhs )
{
    delete functionDefns;
    functionDefns = new std::multimap<std::string, FunctAttr*>( *rhs.functionDefns );
}


void FunctDefn::getFunctionDefns( std::string file_name )
{
    #if 0
    std::string line;
    std::ifstream f( file_name );
    if( f.is_open() )
    {
        while( std::getline( f, line ) )
        {
            // To be modified and called in caller // auto func = matchFunctionDef( line );
            if( ( func.first.compare("") != 0 ) && ( func.second.compare("") != 0 ) ) 
            {
                
                FunctAttr *f = new FunctAttr();
                auto overloaded_func = functionDefns->find( func.first );
                if( overloaded_func != end(*functionDefns) )
                {
                    f->setOverloaded();
                    overloaded_func->second->setOverloaded();
                }
                insertFormalParameters( func.second, f );
                functionDefns->insert(std::pair<std::string, FunctAttr*>(func.first, f));
                
            }
        }
        f.close();
    }
    else
    {
        std::cerr << "Cannot open the file" << std::endl;
    }
    f.close();
    #endif
}

void FunctDefn::insertNormalFunction( std::string funcName, std::string funcArgs )
{
    FunctAttr *f = new FunctAttr();
    auto overloaded_func = functionDefns->find( funcName );
    if( overloaded_func != end(*functionDefns) )
    {
        f->setOverloaded();
        overloaded_func->second->setOverloaded();
    }
    insertFormalParameters( funcArgs, f );
    functionDefns->insert(std::make_pair(funcName, f));

}