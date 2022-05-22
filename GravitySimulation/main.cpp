#include "main.h"

#include "SDL.h"
#include "Game.h"
#include <Windows.h>

/*
 "high Speed" gravity simulation.
 On my system I get ~15000000 iteration/revolution on a 2 planet system. Revolution time: ~12 S, CPU load ~13%
 Your mileage may vary. Change TIME_STEP in planet.h to change speed.
 You need SDL2.lib, SDL2main.lib, zlib1.dll, libpng16-16.dll, SDL2.dll, SDL2_image.dll,
 and SDL-includes to run this when using VS2019

 Corrent config is a test of L2

 Just modified code from GitHub/Feeeeddmmmeee
*/


Game* game = NULL;
long unsigned int luiIterations = 0;;
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
CRITICAL_SECTION CriticalSection;
int iNPlanets = 0;

int main(int argc, char* argv[])
{
	Uint32 uiNow = 0;
	Uint32 uiTimeStart = 0;
	Uint32 luiTimeStart = 0;
	InitializeCriticalSection(&CriticalSection);

	game = new Game();
	game->init("Gravity Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HIGHT, false);


	//ShowWindow(GetConsoleWindow(), SW_HIDE);
//	::Init()

	//int uiNow = 0;
	while (game->running())
	{
		
		static int i = 0;

		//uiNow = SDL_GetTicks();
		if (uiNow % 100 == 0)
		{
			game->handleEvents();
		}
		game->update();

		if (uiNow >= uiTimeStart + FRAMEDELAY)
		{
			uiTimeStart = uiNow + FRAMEDELAY;
			//game->render();
		}
		if (uiNow >= luiTimeStart + 10000)
		{
			printf(":%ld\n", luiIterations );
			luiTimeStart += 10000;
		}
		uiNow++;
	}

	//ShowWindow(GetConsoleWindow(), SW_RESTORE);
	game->clean();

	return 0;
}