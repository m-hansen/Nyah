#include <stdlib.h>
#include "CollisionRectangle.h"
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
	int leftA = rectA->x;
	int rightA = rectA->x + rectA->width;
	int topA = rectA->y;
	int bottomA = rectA->y + rectA->height;

	// Set the bounds for collider B
	int leftB = rectB->x;
	int rightB = rectB->x + rectB->width;
	int topB = rectB->y;
	int bottomB = rectB->y + rectB->height;

	// Check for collision
	// if any of these statements are true we know that there is a gap between 
	// the two colliders on the horizontal or vertical axis
	if ((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB))
	{
		return false;
	}

	// Both the horizontal and vertical coordinates have an overlap
	return true;
}