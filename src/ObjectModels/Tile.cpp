#include "../../include/ObjectModels/Tile.h"

object_models::Tile::Tile(TileCategory category, TileHousing housing)
    : _category(category), _housing(housing), _ownerId(-1) {}