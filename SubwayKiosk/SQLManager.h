#ifndef SQL_MAANGER_H
#define SQL_MAANGER_H
#include "Singleton.h"

class SQLManager : public Singleton<SQLManager> {
    friend class Singleton<SQLManager>;
private:
    SQLManager();
public:
};
#endif