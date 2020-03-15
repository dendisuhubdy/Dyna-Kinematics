#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "wall.h"
#include "rigid_body_2D.h"

class World
{
public:

   World(const std::vector<Wall>&        walls,
         const std::vector<RigidBody2D>& rigidBodies);

   void           simulate(float deltaTime);

private:

   enum class CollisionState : unsigned int
   {
      penetrating = 0,
      colliding   = 1,
      clear       = 2,
   };

   void           computeForces();
   void           integrate(float deltaTime);
   CollisionState checkForCollisions();
   void           resolveCollisions();

   std::vector<Wall>        mWalls;
   std::vector<RigidBody2D> mRigidBodies;
};

#endif