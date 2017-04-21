/** \file aitank,.h **/
#ifndef AITANK_H
#define AITANK_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <list>
#include <math.h>
#include "tank.h"
#include "position.h"

/** \class AITANK \brief Simple AI Tank**/
class AITank : public Tank
{
protected:
	bool visible;
	bool requestingPath = false;
public:
	bool returnRequest();
	void requestAcknowledged();
	bool aimed = false;
	bool fired = true;
	AITank(); //!< Empty construtor
	std::list<Position> path;//!<the path to follow
	Position target = Position(0,0);//!<the current target(Aims at 0,0 by default but the tank doesn't take long to find a new one)
	void setVisible(){visible = true;} //!< Make the AI tank visible to the player
	void setInvisible(){visible = false;} //!< Make the AI tank invisible to the player
	bool isVisible()const {return visible;} //!< Is the tank visiable to the player?

	// FSM public methods, set states and variable
	void reset(); //!< Reset any variables you need to when the tank has been shot
	virtual void move(); //!< Move the tank
	virtual void collided(); //!< Called by the game object when the tank has collided
	virtual void markTarget(Position p /** \param Position of the acquired target */); //!< Called by the game object when a target (enemy building) comes within the tanks visible range
	virtual void markEnemy(Position p /** \param Position of the enemy tank */); //!< Called by the game object when the enemy tank comes within the tanks visible range
	virtual void markBase(Position p /** \param Position of the home building */); //!< Called by the game object when one of you own buildings comes within the tanks visible range
	virtual void markShell(Position p /** \param Position of an enemy shell */); //!< Called by the game object when enemy shell comes within the tanks visible range
	virtual bool isFiring(); //!< Called by the game object each frame.  When this function returns true (and ammo is availbe and loaded) the tank will fire a shell
	virtual void score(int thisScore,int enemyScore);
	void setPath(std::list<Position> nP);
};

#endif