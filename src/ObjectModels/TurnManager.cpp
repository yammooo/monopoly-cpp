#include "../../include/ObjectModels/TurnManager.h"

using namespace object_models;
using namespace std;

TurnManager::TurnManager(vector<int> turns)
{
    _playerTurns = queue<int>();

    for (auto turn : turns)
    {
        _playerTurns.push(turn);
    }
}

void TurnManager::remove_player(int player_index)
{
    queue<int> new_queue = queue<int>();
    
    while (_playerTurns.size() > 0)
    {
        int index = _playerTurns.front();
        _playerTurns.pop();

        if (index != player_index)
        {
            new_queue.push(index);
        }
    }

    _playerTurns = new_queue;
}

int TurnManager::get_next_player_index()
{
    int index = _playerTurns.front();
    _playerTurns.pop();

    _playerTurns.push(index);

    return index;
}

int TurnManager::get_current_player_index()
{
    int index = _playerTurns.front();
    return index;
}