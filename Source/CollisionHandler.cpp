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
	int32_t leftA = rectA->position.x;
	int32_t rightA = rectA->position.x + rectA->width;
	int32_t topA = rectA->position.y;
	int32_t bottomA = rectA->position.y + rectA->height;

	// Set the bounds for collider B
	int32_t leftB = rectB->position.x;
	int32_t rightB = rectB->position.x + rectB->width;
	int32_t topB = rectB->position.y;
	int32_t bottomB = rectB->position.y + rectB->height;

	float_t playerPositionX = rectA->position.x - rectA->width / 2;
	float_t playerPositionY = rectA->position.y - rectA->height / 2;
	float_t bulletPositionX = rectB->position.x - rectB->width / 2;
	float_t bulletPositionY = rectB->position.y - rectB->height / 2;

	float_t distance = pow(playerPositionX - bulletPositionX, 2) + pow(playerPositionY - bulletPositionY, 2);
	if (distance <= rectB->width + rectA->width)
	{
		// Overlap occured
		return true;
	}

	// An overlap did not occur
	return false;
}