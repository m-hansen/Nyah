#include <stdlib.h>
#include <math.h>
#include "baseTypes.h"
#include "CollisionHandler.h"

CollisionHandlerC* CollisionHandlerC::sInstance = NULL;

CollisionHandlerC* CollisionHandlerC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new CollisionHandlerC(); }
	return sInstance;
}

bool CollisionHandlerC::CollisionOccuredRect(CollisionRectangle* rectA, CollisionRectangle* rectB)
{
	// Set the bounds for collider A
	int leftA = rectA->position.x;
	int rightA = rectA->position.x + rectA->width;
	int topA = rectA->position.y;
	int bottomA = rectA->position.y + rectA->height;

	// Set the bounds for collider B
	int leftB = rectB->position.x;
	int rightB = rectB->position.x + rectB->width;
	int topB = rectB->position.y;
	int bottomB = rectB->position.y + rectB->height;

	// Check for collision
	// if any of these statements are true we know that there is a gap between 
	// the two colliders on the horizontal or vertical axis
	/*if ((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB))
	{
		return false;
	}*/

	float player_x = rectA->position.x - rectA->width / 2;
	float player_y = rectA->position.y - rectA->height / 2;
	float bullet_x = rectB->position.x - rectB->width / 2;
	float bullet_y = rectB->position.y - rectB->height / 2;

	float distance = pow(player_x - bullet_x, 2) + pow(player_y - bullet_y, 2);
	if (distance <= rectB->width + rectA->width)
	{
		return true;
	}

	// An overlap did not occur
	return false;
}