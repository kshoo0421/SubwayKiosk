#ifndef SERVER_MANGER_H
#define SERVER_MANGER_H
#include "Singleton.h"

class ServerManager : public Singleton<ServerManager> {
    friend class Singleton<ServerManager>;
private:
    ServerManager();
public:

};

#endif