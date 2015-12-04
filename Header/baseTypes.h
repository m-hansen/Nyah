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

enum BulletWaveType {
	INVALID_BULLET_WAVE,
	RING,
	SPIRAL,
	ZIGZAG,
	MAX_BULLET_WAVE
};

enum Phase {
	INVALID_PHASE,
	NYAH_ONE,
	NYAH_TWO,
	NYAH_THREE,
	NYAH_FOUR,
	NYAH_FIVE,
	NYAH_SIX,
	NYAH_SEVEN,
	MAX_PHASE
};

typedef struct 
{
    float x;
    float y;
} Coord2D; 

typedef struct 
{
	Coord2D position;
	float_t width;
	float_t height;
} CollisionRectangle;
