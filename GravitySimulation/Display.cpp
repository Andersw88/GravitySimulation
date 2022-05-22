
#include "Main.h"

// Run rendering in a separate thread at 60/100 fps

SDL_Thread* pRThread;

static int fRThread(void* pv)
{
	Display cDisplay;
	cDisplay.fRender();
	return 0;
}

//**********************************

//void Display::Init()
void InitDisplayThread()
{
	pRThread = SDL_CreateThread( fRThread, "RThread", (void*)NULL);
	if (!pRThread) {
		printf("%s\n", SDL_GetError());
		exit(1);		// Error return
	}
}

//**********************************

#if 1
// Render planets, present new universe
int Display::fRender()
{
#if 1

	static int iCnt = 0;
	static SDL_Texture* tOldImage = NULL;
	SDL_Surface* sOldImage = NULL;
	static int i = 0;

	Planet* pPlanet = game->universe.planets.at(1);  // For use with L2 and L4, always related to planet 1
	Planet* pLagrange = game->universe.planets.back();  // For use with L2 and L4

	for (;; ) {

		if (SDL_RenderClear(renderer) != 0)
			break;
#if TRACKS
		if (tOldImage) {
			if (SDL_SetTextureBlendMode(tOldImage, SDL_BLENDMODE_BLEND) != 0)
				break;
			if (SDL_SetTextureAlphaMod(tOldImage, TRACKLEN ) != 0)
				break;
			if (SDL_RenderCopy(renderer, tOldImage, NULL, NULL) != 0)
				break;
			SDL_DestroyTexture(tOldImage);

		}
#endif
		SDL_Delay( FRAMEDELAY );

		//EnterCriticalSection(&CriticalSection);
#if LOGL4
		pLagrange->position = pPlanet->position;		// L4
		pLagrange->position.Rotate(pi2 * -60 / 360);
#endif
#if LOGL2
		pLagrange->position = pPlanet->position;
		pLagrange->position.Extend(pLagrange->dL2Dist);
#endif
		//LeaveCriticalSection(&CriticalSection);

		// render all new stuff
		for (auto& planet : game->universe.planets) {
			planet->render();
		}
//		LeaveCriticalSection(&CriticalSection);   // seems like it is not needed here   why ??

#if TRACKS
		{
			SDL_Surface* saveSurface = NULL;
			SDL_Surface* infoSurface = NULL;

			infoSurface = SDL_GetWindowSurface(window);
			if (infoSurface == NULL) {
				break;
			}

			int nBytes = infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel;
			unsigned char* pixels = new unsigned char[nBytes];
			if (infoSurface == NULL) {
				break;
			}

			if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format,
				pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				break;
			}

			saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h,
				infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask,
				infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
			if (saveSurface == NULL) {
				break;
			}

			tOldImage = SDL_CreateTextureFromSurface( renderer, saveSurface);
			if (!tOldImage) {
				break;
			}
			//*/
			delete[] pixels;
			SDL_FreeSurface(sOldImage);
			SDL_FreeSurface(infoSurface);
		}
#endif
		SDL_RenderPresent(renderer);
	}
	printf("%s\n", SDL_GetError());
	#endif
	exit(1);		// Error return
}
#endif
