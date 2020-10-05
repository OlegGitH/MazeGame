#include "Collision.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    return SDL_HasIntersection(&rectA, &rectB);
}


bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
    if (AABB(colA.collider, colB.collider))
    {
        //std::cout << colA.tag << "hit: " << colB.tag << std::endl;
        return true;
    }
    else {

        return false;

    }
}
