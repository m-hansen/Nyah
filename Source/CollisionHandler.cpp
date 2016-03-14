#include "pch.h"

CollisionHandlerC* CollisionHandlerC::sInstance = NULL;

CollisionHandlerC* CollisionHandlerC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new CollisionHandlerC(); }
	return sInstance;
}

bool CollisionHandlerC::CollisionOccuredRect(CollisionRectangle* rectA, CollisionRectangle* rectB)
{
	int32_t leftA = rectA->position.x;
	int32_t rightA = rectA->position.x + rectA->width;
	int32_t bottomA = rectA->position.y;
	int32_t topA = rectA->position.y + rectA->height;

	// Set the bounds for collider B
	int32_t leftB = rectB->position.x;
	int32_t rightB = rectB->position.x + rectB->width;
	int32_t bottomB = rectB->position.y;
	int32_t topB = rectB->position.y + rectB->height;

	if (leftA < rightB &&
		rightA > leftB &&
		bottomA < topB &&
		topA > bottomB) {
		return true;
	}

	return false;

}