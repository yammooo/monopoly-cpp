#include "../../include/Engine/GameProcessor.h"

using namespace object_models;
using namespace dependency_injection;

GameInfo engine::GameProcessor::process(GameData* game, ActionInfo action)
{

    return GameInfo(game->id());
}

object_models::GameInfo init_game(object_models::GameData* game)
{
    int playerNumber = game->configuration().playerNumber();

    std::map<int, int> pointsByPlayer;

    for (int i=0; i<playerNumber; i++){
        pointsByPlayer[i] = 0;
    }

    do {
        


    } while ();
};

engine::GameProcessor::GameProcessor()
{
    _random = ServiceProvider::get_service<RandomContext>();
}