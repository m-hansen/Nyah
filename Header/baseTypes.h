typedef struct 
{
    float x;
    float y;
}Coord2D;

typedef float float_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef char char8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int bool8_t;

enum BulletColor {
	INVALID_COLOR,
	RED,
	BLUE,
	MAX_COLOR,
};
enum BulletAnimationState {
	INVALID_ANIM_STATE,
	GLOWING,
	SHRINKING,
	MAX_ANIM_STATE
};
