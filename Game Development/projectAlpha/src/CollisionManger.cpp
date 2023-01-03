#include "CollisionManager.h"

const std::string CollisionManager::ghostIsland = "ghostIsland";
const std::string CollisionManager::miniIsland = "miniIsland";
const std::string CollisionManager::villageIsland = "villageIsland";
const std::string CollisionManager::japaneseIsland = "japaneseIsland";
const std::string CollisionManager::storeIsland = "storeIsland";

CollisionManager::CollisionManager()
{

}

//SDL_bool SDL_IntersectRect(const SDL_Rect* A, const SDL_Rect* B, SDL_Rect* result)
//{
//    int Amin, Amax, Bmin, Bmax;
//
//    /* Horizontal intersection */
//    Amin = A->x;
//    Amax = Amin + A->w;
//    Bmin = B->x;
//    Bmax = Bmin + B->w;
//    if (Bmin > Amin)
//        Amin = Bmin;
//    result->x = Amin;
//    if (Bmax < Amax)
//        Amax = Bmax;
//    result->w = Amax - Amin > 0 ? Amax - Amin : 0;
//
//    /* Vertical intersection */
//    Amin = A->y;
//    Amax = Amin + A->h;
//    Bmin = B->y;
//    Bmax = Bmin + B->h;
//    if (Bmin > Amin)
//        Amin = Bmin;
//    result->y = Amin;
//    if (Bmax < Amax)
//        Amax = Bmax;
//    result->h = Amax - Amin > 0 ? Amax - Amin : 0;
//
//    return (result->w && result->h);
//}
