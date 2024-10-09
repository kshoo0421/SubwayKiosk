#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
: serverManager(ServerManager::Instance()), sqlManager(SQLManager::Instance()) {};

