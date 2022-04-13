#include "Universe.h"

void Universe::addPlanet(Planet* planet)
{
	this->planets.push_back(planet);
}

void Universe::update()
{
	for (auto& planet : planets)
	{
		planet->updateVelocity(planets);
	}

	for (auto& planet : planets)
	{
		planet->updatePosition();
	}

}

// Render all planets
void Universe::render(SDL_Renderer* renderer)
{
	for (auto& planet : planets)
	{
		planet->render(renderer);
	}
}

void Universe::MomentumAdjust()
{
	double dTotalMass = 0;
	double dMyMassQ = 0;
	Vector TotMomentum(0.0, 0.0);

	for (auto& planet : planets)
	{
		TotMomentum += planet->Momentum;
		dTotalMass += planet->mass;
	}

	for (auto& planet : planets) {
		dMyMassQ = planet->mass / dTotalMass;
		Vector VelocityAdjust = TotMomentum / (dMyMassQ * dTotalMass);
		planet->velocity -= VelocityAdjust;
	}
}

