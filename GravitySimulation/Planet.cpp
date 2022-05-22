#include "main.h"

extern Game* game;


Planet::Planet(double mass, Vector position, Vector velocity, int iNr, double dL2Dist)
{
	this->radius = sqrt(cbrt(mass / DENSITY / PI / 3));
	if (this->radius < 1) this->radius = 1;

	this->acceleration = Vector();
	this->mass = mass;
	this->position = position;
	this->velocity = velocity * sqrt(TIME_STEP);
	this->Momentum = velocity * mass;
	this->iNr = iNr;
	this->dL2Dist = dL2Dist;

	const char* q;
	SDL_Surface* tempSurface;

	if (iNr < 100)
		tempSurface = IMG_Load("planet.png");
	else
		tempSurface = IMG_Load("Marker.png");
	q = SDL_GetError();

	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	q = SDL_GetError();

	SDL_FreeSurface(tempSurface);
}

void Planet::updateVelocity(std::vector<Planet*>& others)
{
	static long unsigned int luiLastIterations = 0;

//	this->acceleration = Vector();
	Vector acceleration;

	double timeStepG = G * TIME_STEP;

	for (int i = 0; i < iNPlanets; i++)
	{
		Planet* other = others[i];

		//don't compute to itself
		if (other == this ) continue;

		Vector posV;
		posV.x = (other->position.x - this->position.x);
		posV.y = (other->position.y - this->position.y);

		double distance2 = (posV.x * posV.x) + (posV.y * posV.y);
		double distance = sqrt(distance2);
		acceleration += posV * (other->mass * timeStepG / (distance2 * distance));
		
		// A bit faster but loses more precision.
		//Vector posV2;
		//posV2.x = (other.position.x - this->position.x);
		//posV2.y = (other.position.y - this->position.y);

		//double distance3 = std::abs(posV2.x * posV2.x * posV2.x) + std::abs(posV2.y * posV2.y * posV2.y);
		//acceleration += posV2 * (other.mass * timeStepG / (distance3));
	}

	this->velocity += acceleration;
	luiIterations++;
}

void Planet::updatePosition()
{
	//EnterCriticalSection(&CriticalSection);
	this->position += this->velocity;
	//LeaveCriticalSection(&CriticalSection);
}

// Render one planet
void Planet::render()
{
	destRect.w = destRect.h = (int)radius * 2;

	destRect.x = (int)(position.x - radius + WIDTH / 2);
	destRect.y = HIGHT - (int)(position.y + radius + HIGHT / 2);			// Y upp, center origo

	if (SDL_RenderCopy(renderer, texture, 0, &destRect) != 0)
	{
		printf("%s\n", SDL_GetError());
		exit(1);		
	}
}
