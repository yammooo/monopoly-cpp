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

        object_models::TileCategory category() { return _category; }
        object_models::TileHousing housing() { return _housing; }
        void housing(object_models::TileHousing housing) { _housing = housing; }

        int owner_id() { return _ownerId; }
        void set_property(int ownerId) { _ownerId = ownerId; }

        Tile(TileCategory category, TileHousing housing);
        
    };

}

#endif // TILE_H