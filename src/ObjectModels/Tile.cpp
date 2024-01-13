// Author: Martina Naldoni

#include "../../include/ObjectModels/Tile.h"

object_models::Tile::Tile(TileCategory category, TileHousing housing)
    : _category(category), _housing(housing), _ownerId(-1) {}

object_models::Tile::Tile(TileCategory category, TileHousing housing, std::string name, int position)
    : _category(category), _housing(housing), _ownerId(-1), _name(name), _position(position) {}