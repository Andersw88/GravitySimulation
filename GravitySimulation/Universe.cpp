#include "main.h"

void Universe::addPlanet(Planet* planet)
{
	planets.push_back(planet);
}

void Universe::update()
{
	for( int i = 0; i < iNPlanets; i++ )
	{
		planets[i]->updateVelocity( planets );
	}

	for (int i = 0; i < iNPlanets; i++)
	{
		planets[i]->updatePosition();
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

		// This is probably a bug?
		TotMomentum = TotMomentum / (dMyMassQ * dTotalMass);

		Vector VelocityAdjust = TotMomentum; // TotMomentum / (dMyMassQ * dTotalMass);
		planet->velocity -= VelocityAdjust;
	}
}

