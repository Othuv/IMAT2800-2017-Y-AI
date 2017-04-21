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
{//stop the tank and any turret rotation and then look for more targets by rotating the turret left
	stop();
	stopTurret();
	turretGoLeft();
	requestingPath = true;
}

void AITank::move()
{
	stop(); //make sure the tank isn't moving if it has nowhere to go
	aimed = false; //a reset so the tank checks its aim each time
	float nTH; //new true heading
	float nTR = 0; //new true rotation (For the turret)
	if (path.size() != 0)
	{
		//work out the new true heading based on its position and the front of path
		nTH = RAD2DEG(atan2f((pos.getY()-path.front().getY()), (pos.getX() - path.front().getX())))+180;

		while (nTH < 0.99f)
		{
			nTH += 360;//while new true heading is below 0 add 360, this makes it so any negative numbers are corrected to degrees
		}
		while (nTH > 360.0f)
		{
			nTH -= 360;//while new true heading is above 360 subtract 360, this makes it so any way too many large numbers are corrected to degrees
		}

		if (pos.getTh() <= nTH + 1.5f && pos.getTh() >= nTH - 1.5f)
		{//if the current heading is within tolerances then stop any turning motion and move forward
			stop();
			goForward();
		}
		else
		{
			if (pos.getTh() > nTH)
			{//if the new heading is left of the current heading then turn left
				stop();
				goLeft();
			}
			if (pos.getTh() < nTH)
			{// if the new heading is right then turn right
				stop();
				goRight();
			}
		}
		if (path.front().getX() < (pos.getX() +2.f) && path.front().getY() < (pos.getY() +2.f) && path.front().getX() > (pos.getX() - 1.5f) && path.front().getY() > (pos.getY() - 1.5f))
		{//if position is at the path position then stop and pop it from the path (This moving to the next if it exists)
			stop();
			path.pop_front();
		}
	}
	else
	{
		requestingPath = true;//if no path then request one for the next call
	}

	nTR = RAD2DEG(atan2f(pos.getY() - target.getY(), pos.getX() - target.getX())) + 180;
	//work out the new turret rotation based on a stored target

	if (turretTh < nTR + 1.25f && turretTh > nTR - 1.25f)
	{//if the turrets direction is within tolerance then stop and let the game know its aimed at a target
		stopTurret();
		aimed = true;
	}
	else if (turretTh < nTR)
	{//if the target is to the right turn the turret right
		turretGoRight();
	}
	else if (turretTh > nTR)
	{//if the target is to the left turn to the left
		turretGoLeft();
	}

	//test code that helped us debug pathing/tankmovemet issues
	/*std::cout << "pathx: " << path.front().getX() << " pathy: " << path.front().getY() << std::endl << "currentX: " << pos.getX() << " CurrentY: " << pos.getY() << std::endl;
	std::cout << "nTH: " << nTH << " nTR: " << nTR << std::endl << "tankH: " << pos.getTh() << " TurretH: " << turretTh << std::endl;*/
}

void AITank::collided()
{//if collided then stop and move backward (Stop rests certain values)
	stop();
	goBackward();
}

void AITank::markTarget(Position p)
{//a target has been found set it and let the tank fire when aimed
	target = p;
	fired = false;
}

void AITank::markBase(Position p)
{
	//the tank shouldn't try to aim at its own base and so we didn't do anything for this
}

void AITank::markEnemy(Position p)
{//set target to an emeny (The order this is in means that the AI prioritises the player)
	target = p;
	fired = false;
}

void AITank::markShell(Position p)
{
	//The ai takes no shells into account (its only defined to stop errors but also as we aren't allowed to change funcitonality we didn't comment them out
}

bool AITank::isFiring()
{//works out if the tank can fire
	return (aimed && !fired);
}

void AITank::score(int thisScore, int enemyScore)
{
	//the tank doesn't take into account the score as it prioritizes the player anyway
}

void AITank::setPath(std::list<Position> nP)
{//copies new path (nP) to the internal path storage.
	for (int i = 0; i < path.size(); i++)
	{
		path.pop_front();
	}

	for (int i = 0; i < nP.size(); i++)
	{
		path.insert(path.end(), nP.front());
		nP.pop_front();
	}
}

bool AITank::returnRequest()
{//returns if the tank is requesting a path
	return requestingPath;
}

void AITank::requestAcknowledged()
{//and if it gives a path it stops the tank from requesting a new one
	requestingPath = false;
}