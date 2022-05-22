#pragma once

#define ELIPTIC false
#define LOGL4 false
#define LOGL2 true
#define MANY false
#define SYSTEM false
#define TWOPLANETS false
#define SUNMOON false

#define TRACKS true
#define TRACKLEN 252

#include <Windows.h>
#include <time.h>
#include <cmath>
#include "Vector.h"
#include <vector>
#include <condition_variable>
#include <thread>
#include <chrono>
#include "SDL.h"
#include "SDL_image.h"
#include "planet.h"
#include "Game.h"
#include "Display.h"
#include "Universe.h"


extern long unsigned int luiIterations;
extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern Game* game;
extern void InitDisplayThread();
extern CRITICAL_SECTION CriticalSection;
extern int iNPlanets;


//#define FPS 60
#define FPS 200
#define FRAMEDELAY ( 1000 / FPS )

#define HIGHT 900
#define WIDTH 900
#define PI 3.14159
#define DENSITY 1.0

#if MANY 
#define G (4.0)
#define TIME_STEP ( 1.0 / 0x10000000 )

#elif LOGL2
#define G (1.0 / 128.0)
#define TIME_STEP ( 1.0 / 0x1000000000 )

#else
#define G (1.0 / 128)
#define TIME_STEP ( 1.0 / 0x100000000 )

#endif

#define MOUSE 100000.0
#define pi2 ( PI * 2)

