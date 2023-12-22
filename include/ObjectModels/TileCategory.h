#ifndef TILE_CATEGORY_H
#define TILE_CATEGORY_H

namespace object_models
{
    enum class TileCategory
    {
        Undefined = 0,
        Start = 1,
        Corner = 2,
        Cheap = 3,
        Standard = 4,
        Luxury = 5
    };
}

#endif // TILE_CATEGORY_H