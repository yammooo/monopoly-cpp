#include <iostream>
#include <memory>
#include <typeinfo>

#include "../include/Engine/GameContext.h"
#include "../include/ObjectModels/GameBoard.h"
#include "../include/ObjectModels/Player.h"
#include "../include/ObjectModels/Tile.h"
#include "../include/DependencyInjection/ServiceProvider.h"

using namespace dependency_injection;
using namespace object_models;
using namespace engine;

int main(int argc, char** argv)
{
    GameBoard board {};

    //std::cout << typeid(&board).name() << std::endl;
    //std::cout << object_models::GameBoard::name() << std::endl;

    //dependency_injection::ServiceProvider::register_service<object_models::GameBoard>();
    //dependency_injection::ServiceProvider::register_service<object_models::GameBoard>();

    ServiceProvider::register_service<GameContext>(10);

    auto t = ServiceProvider::get_service<GameContext>();

    std::cout << t.getA() << std::endl;

    //std::cout << t.get() << std::endl;

//    dependency_injection::ServiceProvider::register_service("serv", ptr);

//    auto result = dependency_injection::ServiceProvider::get_service<int>("serv");

//    std::cout << result.get()[10] << std::endl;

    return 0;
}