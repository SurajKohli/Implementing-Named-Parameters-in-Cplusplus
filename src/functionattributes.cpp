#include "functionattributes.hpp"

FunctAttr::FunctAttr()
: m_overloaded(false),m_hasDefArgs(false),m_numNormalArgs(0),m_numDefArgs(0),
formal_params( new std::queue< std::pair< std::string, std::string > > )
{
}
FunctAttr::~FunctAttr()
{
    delete formal_params;
}

FunctAttr::FunctAttr( const FunctAttr& rhs )
{
    formal_params = new std::queue< std::pair< std::string, std::string > >(*rhs.formal_params);
    m_overloaded = rhs.m_overloaded;
    m_hasDefArgs = rhs.m_hasDefArgs;
    m_numNormalArgs = rhs.m_numNormalArgs;
    m_numDefArgs = rhs.m_numDefArgs;
}

FunctAttr& FunctAttr::operator=( const FunctAttr& rhs )
{
    delete formal_params;
    formal_params = new std::queue< std::pair< std::string, std::string > >(*rhs.formal_params);
    m_overloaded = rhs.m_overloaded;
    m_hasDefArgs = rhs.m_hasDefArgs;
    m_numNormalArgs = rhs.m_numNormalArgs;
    m_numDefArgs = rhs.m_numDefArgs;
}

void FunctAttr::setOverloaded()
{
    m_overloaded = true;
}

void FunctAttr::setHasDefArgs()
{
    m_hasDefArgs = true;
}

