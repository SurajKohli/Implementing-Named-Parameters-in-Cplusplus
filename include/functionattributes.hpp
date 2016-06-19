#ifndef FUNCATTR_H
#define FUNCATTR_H

#include <string>
#include <queue>

/**
 * @brief The FunctAttr class
    * It is a container to store all the
    * attributes and details of a function
 * @author Utkarsh Simha
 */
class FunctAttr
{
    public:
        FunctAttr();
        ~FunctAttr();
        FunctAttr( const FunctAttr& );
        FunctAttr& operator=( const FunctAttr& );
        std::queue< std::pair<std::string, std::string> > *formal_params;
        int m_numNormalArgs;
        int m_numDefArgs;
        bool m_overloaded;
        void setHasDefArgs();
        void setOverloaded();
    private:
        bool m_hasDefArgs;
};

#endif
