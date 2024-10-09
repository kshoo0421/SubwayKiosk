#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#include "Singleton.h"
#include "ServerManager.h"
#include "SQLManager.h"

class DatabaseManager : public Singleton<DatabaseManager> {
    friend class Singleton<DatabaseManager>;
private:
    DatabaseManager();
    ServerManager& serverManager;
    SQLManager& sqlManager;
public:

};
#endif