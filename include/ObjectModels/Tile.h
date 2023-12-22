#ifndef TILE_H
#define TILE_H

#include "TileCategory.h"
#include "TileHousing.h"

namespace object_models
{
    class Tile
    {
        private:

        object_models::TileCategory _category;
        object_models::TileHousing _housing;

        int _ownerId;

        public:
        
    };

}

#endif // TILE_H