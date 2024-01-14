// Author: Martina Naldoni

/*
Here is how we decided to represent a tile of the Monopoly board:
- it has a Category (Luxury, Standar, Cheap, Start, Corner)
- it has a housing status (Undefined, Land (bare ownership), House, Hotel )
- it has a name (eg. H6)
- it has a position (its index in the vactor of tiles that is kept in the gameboard )
- it has an Owner id (that is -1 when not owned by anyone)

*/

#ifndef TILE_H
#define TILE_H

#include <string>

#include "TileCategory.h"
#include "TileHousing.h"

namespace object_models
{
    class Tile
    {
        private:

        object_models::TileCategory _category;
        object_models::TileHousing _housing;

        std::string _name;
        int _position;

        int _ownerId;

        public:

        object_models::TileCategory category() { return _category; }
        object_models::TileHousing housing() { return _housing; }
        void housing(object_models::TileHousing housing) { _housing = housing; }

        void name(std::string name) { _name = name; }
        std::string name() { return _name; }
        
        void position(int position) { _position = position; }
        int position() { return _position; }
        
        int owner_id() { return _ownerId; }
        void set_property(int ownerId) { _ownerId = ownerId; }

        Tile(TileCategory category, TileHousing housing);
        Tile(TileCategory category, TileHousing housing, std::string name, int position);
        
    };

}

#endif // TILE_H