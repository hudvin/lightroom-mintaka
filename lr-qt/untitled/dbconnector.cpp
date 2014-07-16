#include <dbconnector.h>

bool Singleton::instance_exists;
Singleton* Singleton::_theOnlyInstance;

Singleton::Singleton()  {}

Singleton::~Singleton() {
    instance_exists = false;
}

Singleton* Singleton::getInstance()  {
    if(!instance_exists)    {
        _theOnlyInstance = new Singleton();
        instance_exists = true;
        return _theOnlyInstance;
    }   else    {
        return _theOnlyInstance;
    }
}

DBWrapper Singleton::getDBWrapper()    {
    return dbWrapper;
}

