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

enum PatternType {
	INVALID_PATTERN = -1,

	EASY_BEGIN = 0,
	SINGLE_RING_1,
	SINGLE_RING_2,
	SINGLE_RING_3,
	SINGLE_RING_4,
	ALTERNATOR_EASY_1,
	ALTERNATOR_EASY_2,
	SEQUENTIAL_EASY_1,
	SEQUENTIAL_EASY_2,
	EASY_END,

	MEDIUM_BEGIN,
	ALTERNATOR_MEDIUM_1,
	ALTERNATOR_MEDIUM_2,
	SEQUENTIAL_MEDIUM_1,
	SEQUENTIAL_MEDIUM_2,
	FLIP_MEDIUM_1,
	FLIP_MEDIUM_2,
	SPIRAL_MEDIUM_1,
	SPIRAL_MEDIUM_2,
	MEDIUM_END,

	HARD_BEGIN,
	ALTERNATOR_HARD_1,
	ALTERNATOR_HARD_2,
	SEQUENTIAL_HARD_1,
	SEQUENTIAL_HARD_2,
	FLIP_HARD_1,
	FLIP_HARD_2,
	SPIRAL_HARD_1,
	SPIRAL_HARD_2,
	FLURRY_HARD_1,
	HARD_END
};

enum BulletWaveType {
	INVALID_BULLET_WAVE = -1,
	RING_00_DEG = 0,
	RING_90_DEG = 1,
	RING_180_DEG = 2,
	RING_270_DEG = 3,
	CRES_0_DEG = 4,
	CRES_30_DEG = 5,
	CRES_60_DEG = 6,
	CRES_90_DEG = 7,
	CRES_120_DEG = 8,
	CRES_150_DEG = 9,
	CRES_180_DEG = 10,
	CRES_210_DEG = 11,
	CRES_240_DEG = 12,
	CRES_270_DEG = 13,
	CRES_300_DEG = 14,
	CRES_330_DEG = 15,
	SPIRAL_CLOCK = 16,
	SPIRAL_CNT_CLOCK = 17,
	MAX_BULLET_WAVE = 18
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
	float x;
	float y;
	float z;
} Coord3D;

typedef struct 
{
	Coord2D position;
	float_t width;
	float_t height;
} CollisionRectangle;
