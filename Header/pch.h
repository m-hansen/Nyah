#pragma once
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <io.h>
#include <fcntl.h>
#include <assert.h>
#include <math.h>												// Header File For Math Operations
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <gl/glu.h>												// Header File For The GLu32 Library
#include <gl/glut.h>
#include <stdlib.h>
#include <cstdint>
#include <stdexcept>

#include "fmod.hpp"
#include "fmod_errors.h"

#include "SList.h"
#include "vector.h"
#include "HashMap.h"
#include "Queue.h"

using namespace Library;

#include "DifficultyPreset.h"
#include "glut.h"
#include "baseTypes.h"
#include "openGLFramework.h"
#include "collInfo.h"
#include "Object.h"
#include "Bullet.h"
#include "BulletWave.h"
#include "WavePattern.h"
#include "BulletManager.h"
#include "CollisionHandler.h"
#include "game.h"
#include "gamedefs.h"
#include "GameTime.h"
#include "InputManager.h"
#include "PhaseManager.h"
#include "Player.h"
#include "random.h"
#include "SOIL.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "stateManager.h"
#include "UIManager.h"
#include "HighScores.h"
#include "gameObjects.h"
#include "openGLStuff.h"
