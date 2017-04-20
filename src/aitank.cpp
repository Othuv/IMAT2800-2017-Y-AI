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
	if (path.size() != 0)
	{
		
		nTH = atan2f((pos.getY()-path.front().getY()), (pos.getX() - path.front().getX()))*360;
		std::cout << nTH << std::endl;
		if (nTH < 0)
		{
			nTH += 360;
		}
		if (pos.getTh() != nTH)
		{
			goLeft();
		}
		if (pos.getTh() <= nTH + 20 && pos.getTh() >= nTH - 20)
		{
			stop();
			goForward();
		}
		if (path.front().getX() == pos.getX() && path.front().getY() == pos.getY())
		{
			stop();
			path.pop_front();
		}
	}
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