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
	stop();
	//right = false;
	//left = false;
	//backward = false;
	//forward = false;
	float nTH;
	float nTR = 0;
	if (path.size() != 0)
	{
		
		nTH = RAD2DEG(atan2f((pos.getY()-path.front().getY()), (pos.getX() - path.front().getX())))+180;

		while (nTH < 0.0f)
		{
			nTH += 360;
		}
		while (nTH > 360.0f)
		{
			nTH -= 360;
		}

		if (pos.getTh() <= nTH + 1.5f && pos.getTh() >= nTH - 1.5f)
		{
			stop();
			goForward();
		}
		else
		{
			if (pos.getTh() > nTH)
			{
				stop();
				goLeft();
			}
			if (pos.getTh() < nTH)
			{
				stop();
				goRight();
			}
		}
		if (path.front().getX() <= (pos.getX() +1.5f) && path.front().getY() <= (pos.getY() +1.5f) && path.front().getX() >= (pos.getX() - 1.5f) && path.front().getY() >= (pos.getY() - 1.5f))
		{
			stop();
			path.pop_front();
		}
	}
	nTR = RAD2DEG(atan2f(pos.getY() - target.getY(), pos.getX() - target.getX())) + 180;

	if (turretTh <= nTR + 1.25f && turretTh >= nTR - 1.25f)
	{
		stopTurret();
	}
	else if (turretTh < nTR)
	{
		turretGoRight();
	}
	else if (turretTh > nTR)
	{
		turretGoLeft();
	}

	std::cout << "nTH: " << nTH << " nTR: " << nTR << std::endl << "tankH: " << pos.getTh() << " TurretH: " << turretTh << std::endl;
}

void AITank::collided()
{
	stop();
	goBackward();
}

void AITank::markTarget(Position p)
{
	target = p;
}

void AITank::markBase(Position p)
{
	target = p;
}

void AITank::markEnemy(Position p)
{
	target = p;
}

void AITank::markShell(Position p)
{
}

bool AITank::isFiring()
{
	return true;
}

void AITank::score(int thisScore, int enemyScore)
{
}

void AITank::setPath(std::list<Position> nP)
{
	for (int i = 0; i < nP.size(); i++)
	{
		path.insert(path.end(), nP.front());
		nP.pop_front();
	}
}