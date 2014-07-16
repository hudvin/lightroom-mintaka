#include <dbwrapper.h>

#ifndef SINGLETON_H
#define SINGLETON_H
class Singleton
{
public:
    static Singleton* getInstance();
    ~Singleton();
    DBWrapper getDBWrapper();
private:
    DBWrapper dbWrapper;
    Singleton();
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    static bool instance_exists;
    static Singleton* _theOnlyInstance;
};
#endif // SINGLETON_H
