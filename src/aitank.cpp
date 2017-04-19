#include "AITank.h"

AITank::AITank() // Constructor
{
	bodyTex.loadFromFile("assets\\redTank.png");
	body.setTexture(bodyTex);
	body.setOrigin(100,100);
	body.setScale(0.2f,0.2f);

	turretTex.loadFromFile("assets\\redTankTurret.png");
	turret.setTexture(turretTex);
	turret.setOrigin(46,44);
	turret.setScale(0.2f,0.2f);
	
	numberOfShells = 15;
}

void AITank::reset()
{

}

void AITank::move()
{

}

void AITank::collided()
{

}

void AITank::markTarget(Position p)
{

}

void AITank::markBase(Position p)
{

}

void AITank::markEnemy(Position p)
{

}

void AITank::markShell(Position p)
{

}

bool AITank::isFiring()
{

}

void AITank::score(int thisScore, int enemyScore)
{

}