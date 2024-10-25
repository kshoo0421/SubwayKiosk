#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
: serverManager(ServerManager::Instance()), sqlManager(SQLManager::Instance()) {};

int DatabaseManager::SendCartToServer(const Cart& cart) {
    return serverManager.SendCartToServer(cart);
}
