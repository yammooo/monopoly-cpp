#include "../../include/Client/GameClient.h"

using namespace client;
using namespace engine;
using namespace dependency_injection;

client::GameClient::GameClient()
{
    _context = ServiceProvider::get_service<GameContext>();
}

void client::GameClient::execute()
{
}
