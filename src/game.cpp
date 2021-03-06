#include "game.h"


Game::Game() // Constructor
{

	//Set position and adjacency matrix
	
	/*
	// position matrix contains the locations of each node
	positionMatrix.resize(posWidth);
	for (int i = 0; i < posWidth; i++) {
		positionMatrix[i].resize(posHeight);
	}
	

	for (int i = 0; i < posWidth - 1; i++) {
		for (int j = 0; j < posHeight - 1; j++) {
			Position newPos = Position(20 * i + 20, 20 * j + 20);
			positionMatrix[i][j] = newPos;
		}
	}
	*/

	// Allocate adjacency matrix
	adjacencyMatrix.resize(nNodes);				//resize the adjacency matrix based on the number of nodes
	for (int i = 0; i<nNodes; i++) {			
		adjacencyMatrix[i].resize(nNodes);
	}

	// Populate index lookup table
	for (int i = 0; i<posWidth; i++) {			
		for (int j = 0; j<posHeight; j++) {
			indexLookup[i][j] = j * posWidth + i;
		}
	}
	// initialize all of the adjacency points to false
	for (int i = 0; i<nNodes; i++) {
		for (int j = 0; j<nNodes; j++) {
			adjacencyMatrix[i][j] = 0;
		}
	}

	// loop through all the available positions
	for (int i = 0; i < posHeight - 1; i++)
	{
		for (int j = 0; j < posWidth - 1; j++)
		{
			//calculate current position
			int position = posWidth * i + j;			
			
			// adjacent squares
			//left is fine if not on far left
			if (j > 0) adjacencyMatrix[position][position - 1] = 1;

			//right is fine if not on far right
			if (j < posWidth - 1) adjacencyMatrix[position][position + 1] = 1;

			//up is fine if not on top row
			if (i > 0) adjacencyMatrix[position][position - posWidth] = 1;

			//down is fine is not on bottom row
			if (i < posHeight - 1) adjacencyMatrix[position][position + posWidth] = 1;
			

			// handling for diagonals
			//top row 
			if (i == 0) {
				if (j == 0)					//top left corner
				{
					adjacencyMatrix[position][position + posWidth + 1] = 1; // down and right is true
				}
				else if (j == posWidth - 1) // top right corner
				{
					adjacencyMatrix[position][position + posWidth - 1] = 1;	//down and left is true
				}
				else                        // anything else on top row
				{
					adjacencyMatrix[position][position + posWidth + 1] = 1;
					adjacencyMatrix[position][position + posWidth - 1] = 1;
				}
			}

			//bottom row
			else if (i == posHeight - 1) {
				if (j == 0)						//bottom left corner
				{
					adjacencyMatrix[position][position - posWidth + 1] = 1; //up and right is true
				}
				else if (j == posWidth - 1)		//bottom right corner
				{
					adjacencyMatrix[position][position - posWidth - 1] = 1;	//up and left is true
				}
				else                            //anything else on the bottom row, both are true
				{
					adjacencyMatrix[position][position - posWidth + 1] = 1;	
					adjacencyMatrix[position][position - posWidth - 1] = 1;
				}
			}

			//left column
			if (j == 0) {
				if (i != 0 && i != posHeight - 1)	//not a corner (handled above)
				{
					adjacencyMatrix[position][position - posWidth + 1] = 1;	//up and right
					adjacencyMatrix[position][position + posWidth + 1] = 1;	//down and right
				}
			}

			//right column
			else if (j == posWidth - 1) {
				if (i != 0 && i != posHeight - 1)	//not a corner (handled above)
				{
					adjacencyMatrix[position][position - posWidth - 1] = 1;	//up and left 
					adjacencyMatrix[position][position + posWidth - 1] = 1;	//down and left
				}
			}	
		}
	}
	
	// Set Backgound
	background.setSize(sf::Vector2f(780.0f,570.0f));
	background.setFillColor(sf::Color(40,70,20));
	background.setPosition(10.0f,10.0f);

	ammoArea.setSize(sf::Vector2f(800.0f,20.0f));
	ammoArea.setFillColor(sf::Color(140,90,60));
	ammoArea.setPosition(0.0f,580.0f);

	// Seed pseudorandom num gen
	srand ( (int) time(NULL) );

	// Set debug mode to off
	debugMode = false;

	// Borders
	obstacles.push_back(Obstacle(0.f,0.f,10.f,580.f,sf::Color(100,100,100)));
	obstacles.push_back(Obstacle(0.f,0.f,800.f,10.f,sf::Color(100,100,100)));
	obstacles.push_back(Obstacle(0.f,570.f,800.f,580.f,sf::Color(100,100,100)));
	obstacles.push_back(Obstacle(790.f,0.f,800.f,580.f,sf::Color(100,100,100)));

	float dx, dy;
	// Top right
	dx = (float) (rand() % 340 + 400);
	dy = (float) (rand() % 200 + 10);

	redBuildings.push_back(Obstacle(dx,dy,dx+20.f,dy+20.f,sf::Color(170,60,60)));
	redBuildings.push_back(Obstacle(dx+20.f,dy,dx+40.f,dy+20.f,sf::Color(170,40,40)));
	redBuildings.push_back(Obstacle(dx,dy+20.f,dx+20.f,dy+40.f,sf::Color(170,40,40)));
	redBuildings.push_back(Obstacle(dx+20.f,dy+20.f,dx+40.f,dy+40.f,sf::Color(170,60,60)));
	redBuildings.push_back(Obstacle(dx,dy+40.f,dx+20.f,dy+60.f,sf::Color(170,60,60)));
	redBuildings.push_back(Obstacle(dx+20.f,dy+40.f,dx+40.f,dy+60.f,sf::Color(170,40,40)));

	Game::buildingAdj(dx, dy, 60, 40);

	// Bottom right
	dx = (float) (rand() % 340 + 400);
	dy = (float) (rand() % 200 + 280);

	redBuildings.push_back(Obstacle(dx,dy,dx+20.f,dy+20.f,sf::Color(170,60,60)));
	redBuildings.push_back(Obstacle(dx+20.f,dy,dx+40.f,dy+20.f,sf::Color(170,40,40)));
	redBuildings.push_back(Obstacle(dx,dy+20.f,dx+20.f,dy+40.f,sf::Color(170,40,40)));
	redBuildings.push_back(Obstacle(dx+20.f,dy+20.f,dx+40.f,dy+40.f,sf::Color(170,60,60)));

	Game::buildingAdj(dx, dy, 40, 40);

	// Top left
	dx = (float) (rand() % 340 + 10);
	dy = (float) (rand() % 200 + 10);

	blueBuildings.push_back(Obstacle(dx,dy,dx+20,dy+20,sf::Color(60,60,170)));
	blueBuildings.push_back(Obstacle(dx+20,dy,dx+40,dy+20,sf::Color(40,40,170)));
	blueBuildings.push_back(Obstacle(dx,dy+20,dx+20,dy+40,sf::Color(40,40,170)));
	blueBuildings.push_back(Obstacle(dx+20,dy+20,dx+40,dy+40,sf::Color(60,60,170)));

	Game::buildingAdj(dx, dy, 40, 40);
	// Bottom left
	dx = (float) (rand() % 340 + 10);
	dy = (float) (rand() % 200 + 280);

	blueBuildings.push_back(Obstacle(dx,dy,dx+20,dy+20,sf::Color(60,60,170)));
	blueBuildings.push_back(Obstacle(dx+20,dy,dx+40,dy+20,sf::Color(40,40,170)));
	blueBuildings.push_back(Obstacle(dx,dy+20,dx+20,dy+40,sf::Color(40,40,170)));
	blueBuildings.push_back(Obstacle(dx+20,dy+20,dx+40,dy+40,sf::Color(60,60,170)));
	blueBuildings.push_back(Obstacle(dx,dy+40,dx+20,dy+60,sf::Color(60,60,170)));
	blueBuildings.push_back(Obstacle(dx+20,dy+40,dx+40,dy+60,sf::Color(40,40,170)));

	Game::buildingAdj(dx, dy, 60, 40);

	resetNpc();
	resetPlayer();

	redScore = 0;
	blueScore = 0;

	
	lIPath = AStarPath(makeInitialGoal());								//Creates and intital path of index values
	for (int i = 0; i < lIPath.size(); i++)								//goes through the path of index values and converts them to position values
	{
		aiPath.insert(aiPath.end(), getPosFromIndex(lIPath.front()));	
		lIPath.pop_front();
	}
	npc.setPath(aiPath);												//send the path to the npc
	}

Game::~Game(){}  // Destructor

// Set a random Position which does not collide with anything
void Game::resetNpc()
{
	bool collision = true;
	while(collision)
	{
		float x = (float) (rand() % 360 + 400);
		float y = (float) (rand() % 580 + 10);
		float th = (float) (rand() % 359);
		float tth = th;
		npc.resetTank(x,y,th,tth);
		npc.reset();

		collision = false;
		for (list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
		{
			if(npc.bb.collision(it->bb))
			{
				collision = true;
				break;
			}
		}
		for (list<Obstacle>::iterator it = blueBuildings.begin(); it != blueBuildings.end(); ++it)
		{
			if(npc.bb.collision(it->bb))
			{
				collision = true;
				break;
			}
		}
		for (list<Obstacle>::iterator it = redBuildings.begin(); it != redBuildings.end(); ++it)
		{
			if(npc.bb.collision(it->bb))
			{
				collision = true;
				break;
			}
		}
		if(npc.bb.collision(player.bb)) collision = true;
	}
}

// Set a random Position which does not collide with anything
void Game::resetPlayer()
{
	bool collision = true;
	while(collision)
	{
		float x = (float) (rand() % 380 + 10);
		float y = (float) (rand() % 580 + 10);
		float th =(float) ( rand() % 359);
		float tth = th;
		player.resetTank(x,y,th,tth);
		player.reset();

		collision = false;
		for (list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
		{
			if(player.bb.collision(it->bb))
			{
				collision = true;
				break;
			}
		}
		for (list<Obstacle>::iterator it = blueBuildings.begin(); it != blueBuildings.end(); ++it)
		{
			if(player.bb.collision(it->bb))
			{
				collision = true;
				break;
			}
		}
		for (list<Obstacle>::iterator it = redBuildings.begin(); it != redBuildings.end(); ++it)
		{
			if(player.bb.collision(it->bb))
			{
				collision = true;
				break;
			}
		}
		if(player.bb.collision(npc.bb)) collision = true;
	}
}

void Game::play()// Play the game for one timestep
{
	// Move tank
	player.markPos();
	player.move();

	// Check for collisions
	//initialize collisions as false
	bool collision = false;
	//check if colliding with any obsacles
	for (list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		if(player.bb.collision(it->bb))
		{
			collision = true;
			break;
		}
	}

	//check if colliding with blue buildings
	for (list<Obstacle>::iterator it = blueBuildings.begin(); it != blueBuildings.end(); ++it)
	{
		if(player.bb.collision(it->bb))
		{
			collision = true;
			break;
		}
	}

	//check if colliding with red buildings
	for (list<Obstacle>::iterator it = redBuildings.begin(); it != redBuildings.end(); ++it)
	{
		if(player.bb.collision(it->bb))
		{
			collision = true;
			break;
		}
	}
	//check if colliding with the npc
	if(player.bb.collision(npc.bb)) collision = true;

	//if so, push back to its previous position
	if(collision)player.recallPos();

	// Move AI tank
	npc.markPos();
	npc.move();
	npc.implementMove();
	if(npc.isFiring()){fireShell(npc.firingPosition(), true);}

	// Check for collisions, same as with the player
	collision = false;
	for (list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		if(npc.bb.collision(it->bb))
		{
			collision = true;
			break;
		}
	}
	for (list<Obstacle>::iterator it = blueBuildings.begin(); it != blueBuildings.end(); ++it)
	{
		if(npc.bb.collision(it->bb))
		{
			collision = true;
			break;
		}
	}
	for (list<Obstacle>::iterator it = redBuildings.begin(); it != redBuildings.end(); ++it)
	{
		if(npc.bb.collision(it->bb))
		{
			collision = true;
			break;
		}
	}
	if(npc.bb.collision(player.bb)) collision = true;

	if(collision)
	{
		npc.recallPos();
		npc.collided();
	}

	// Check if AI Tank can see anything
	// red buildings
    for (list<Obstacle>::iterator it = redBuildings.begin(); it != redBuildings.end(); ++it)
    {
	  if(npc.canSee(it->bb)) npc.markBase(Position((it->bb.getX1() + it->bb.getX2()) / 2.0f, (it->bb.getY1() + it->bb.getY2()) / 2.0f));
    }

	//blue buildings
    for (list<Obstacle>::iterator it = blueBuildings.begin(); it != blueBuildings.end(); ++it)
    {
	  if(npc.canSee(it->bb)) npc.markTarget(Position((it->bb.getX1() + it->bb.getX2()) / 2.0f, (it->bb.getY1() + it->bb.getY2()) / 2.0f));
    }

	//bullets
    for (list<Shell>::iterator it = shells.begin(); it != shells.end(); ++it)
    {
	  if(npc.canSee(it->bb) && !it->isNpc()) npc.markShell(Position((it->bb.getX1() + it->bb.getX2()) / 2.0f, (it->bb.getY1() + it->bb.getY2()) / 2.0f));
    }

	//player
	if(npc.canSee(player.bb)) npc.markEnemy(Position((player.bb.getX1() + player.bb.getX2()) / 2.0f, (player.bb.getY1() + player.bb.getY2()) / 2.0f ));

	// Move shells
	for (list<Shell>::iterator it = shells.begin(); it != shells.end(); ++it){it->move();}

	// Check if shells have hit anything

	// Have shells hit edges
	for (list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		for (list<Shell>::iterator it2 = shells.begin(); it2 != shells.end(); it2++)
	    {
		  if(it->bb.collision(it2->bb))
		  {
			shells.erase(it2);
			break;
		  }
		}
	}
	// Second check
	for (list<Shell>::iterator it2 = shells.begin(); it2 != shells.end(); it2++)
	{
		if(fabs(it2->getY()) > 1000)
		{
		shells.erase(it2);
		break;
		}
		if(fabs(it2->getX()) > 1200)
		{
		shells.erase(it2);
		break;
		}
	}

	// Have shells hit red buildings
	bool stop = false;
	list<Obstacle>::iterator it = redBuildings.begin();
	while (!(stop || it == redBuildings.end()))
	{
		
		list<Shell>::iterator it2 = shells.begin();
		while(!(stop || it2 == shells.end()))
		{
			if(it->bb.collision(it2->bb) && (it2->couldSeeWhenFired(it->bb) || it->isVisible()) )
			{
				shells.erase(it2);
				redBuildings.erase(it);
				blueScore += 10;
				npc.score(redScore, blueScore);
				stop = true;
			}
			else it2++;
		}
		
		if(!stop)++it;
	}

	// Have shells hit blue buildings
	stop = false;
	it = blueBuildings.begin();
	while (!(stop || it == blueBuildings.end()))
	{

		list<Shell>::iterator it2 = shells.begin();
		while(!(stop || it2 == shells.end()))
		{
			if(it->bb.collision(it2->bb) && (it2->couldSeeWhenFired(it->bb) || it->isVisible()))
			{
				shells.erase(it2);
				blueBuildings.erase(it);
				redScore += 10;
				npc.score(redScore, blueScore);
				stop = true;
			}
			else it2++;
		}

		if(!stop)++it;
	}

	// Have shells hit red tank
	stop = false;
	list<Shell>::iterator it2 = shells.begin();
	while(!(stop || it2 == shells.end()))
	{
		if(it2->couldSeeWhenFired(npc.bb) && npc.bb.collision(it2->bb))
		{
			shells.erase(it2);
			resetNpc();
			blueScore += 25;
			npc.score(redScore, blueScore);
			stop = true;
		}
		else it2++;
	}


	// Have shells hit BLUE tank
	stop = false;

	it2 = shells.begin();
	while(!(stop || it2 == shells.end()))
	{
		if(it2->couldSeeWhenFired(player.bb) && player.bb.collision(it2->bb))
		{
			shells.erase(it2);
			resetPlayer();
			redScore += 25;
			npc.score(redScore, blueScore);
			stop = true;
		}
		else it2++;
	}

	//have builings with object permanance
	for (list<Obstacle>::iterator it = redBuildings.begin(); it != redBuildings.end(); ++it)
	{
		if(player.canSee(it->bb)) it->setVisible();
	}

	for (list<Obstacle>::iterator it = blueBuildings.begin(); it != blueBuildings.end(); ++it)
	{
		if(player.canSee(it->bb)) it->setVisible();
	}

	//check if the player can see the enemy
	if(player.canSee(npc.bb)) {npc.setVisible();}
	else {npc.setInvisible();}

	for (list<Shell>::iterator it = shells.begin(); it != shells.end(); ++it)
	{
		if(player.canSee(it->bb)) it->setVisible();
	}


	if (npc.returnRequest())														//if the npc currently requires a new path
	{
		lIPath = AStarPath(chooseGoal());											//calculate one based off of its current location and priority, if it's running away go anywhere, if not go into enemy territory
		for (int i = 0; i < lIPath.size(); i++)										//go through the path of index values
		{
			aiPath.insert(aiPath.end(), getPosFromIndex(lIPath.front()));			//convert them into position values
			lIPath.pop_front();
		}
		npc.setPath(aiPath);														//send the npc the new path 
		npc.requestAcknowledged();													//set the npc to stop asking for a new one
	}
}

void Game::fireShell(Position fp, bool isNpc)
{
   Position shellPos = fp;
   Shell newShell(fp, isNpc);
   bool ai = false;
   bool tank = false;
   bool canFire = false;
   // Sort out visibility
   if(isNpc)					//If the one trying to fire is the npc
   {
		if(npc.canFire())		//check if it has ammo
		{
			npc.fireShell();	//fire 
			npc.fired = true;
			canFire = true;		//set can fire to true
		}
   }
   else
   {
	    if(player.canFire())
		{
			player.fireShell();
			canFire = true;
		}
   }

   if(canFire)shells.push_back(newShell);
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const// Draw the game
{
	//draw background
	target.draw(background);
	//draw the underlay for the ammo
	target.draw(ammoArea);

	// Draw shells
	for (list<Shell>::const_iterator it = shells.begin(); it != shells.end(); ++it)
	{
		if(it->isVisible() || debugMode)  target.draw(*it);
	}

	// Draw obstacles
	for (list<Obstacle>::const_iterator it = obstacles.begin(); it != obstacles.end(); ++it) 
	{
		target.draw(*it);
	}

	// Draw Red Buildings
	for (list<Obstacle>::const_iterator it = redBuildings.begin(); it != redBuildings.end(); ++it)
	{
		if(it->isVisible() || debugMode) target.draw(*it);
	}

	// Draw blue buildings
	for (list<Obstacle>::const_iterator it = blueBuildings.begin(); it != blueBuildings.end(); ++it)
	{
		if(it->isVisible()  || debugMode) target.draw(*it);
	}

	// Draw AITank
	if (npc.isVisible() || debugMode) target.draw(npc);

	// Draw Player
	target.draw(player);
	
	// Draw ammo count at the bottom
	sf::RectangleShape ammo(sf::Vector2f(5,10));
	ammo.setFillColor(sf::Color(0,0,255));

	//for the player
	for(int i=0;i<player.getNumberOfShells();i++)
	{
		ammo.setPosition((float)i*15+10, 585.f);
		target.draw(ammo);
	}

	//for the npc
	ammo.setFillColor(sf::Color(255,0,0));
	for(int i=0;i<npc.getNumberOfShells();i++)
	{
		ammo.setPosition((float)790-i*15, 585.f);
		target.draw(ammo);
	}

	// Draw scores
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	char msg[255];
	sprintf_s(msg,"%d", blueScore);
	sf::Text drawingText(sf::String(msg),font,18);
	drawingText.setColor(sf::Color::White);

	drawingText.setPosition(250,577);
	target.draw(drawingText);

	sprintf_s(msg,"%d", redScore);
	drawingText.setString(sf::String(msg));
	drawingText.setPosition(550,577);
	target.draw(drawingText);

	// Draw game over
	if(gameOver())
	{
		//game over message
		sprintf_s(msg,"GAME OVER", blueScore);
		sf::Text drawingText(sf::String(msg),font,42);
		drawingText.setPosition(300, 140);
		target.draw(drawingText);
		drawingText.setPosition(300, 240);

		//if statements determining the winner
		//red
		if(redScore > blueScore)
		{
			sprintf_s(msg,"RED WINS!", blueScore);
			drawingText.setString(sf::String(msg));
		}
		//blue 
		if(redScore < blueScore)
		{
			sprintf_s(msg,"BLUE WINS!", blueScore);
			drawingText.setString(sf::String(msg));
		}
		//draw
		if(redScore == blueScore)
		{
			sprintf_s(msg,"MATCH DRAW!", blueScore);
			drawingText.setString(sf::String(msg));
		}
		target.draw(drawingText);
	}
}
     

//reactions to key presses
void Game::keyPressed(sf::Keyboard::Key key)
{
	switch(key)
	{
		//tab will toggle debug
	   case	sf::Keyboard::Tab :
		   debugMode = !debugMode;
		   player.toggleDebugMode();
		   npc.toggleDebugMode();
		   for (list<Shell>::iterator it = shells.begin(); it != shells.end(); ++it){it->toggleDebugMode();}
		   break;
		   //W: moves player forward
	   case  sf::Keyboard::W : 
		   player.goForward();
		   break;

		   //A: turns player to its left
	   case  sf::Keyboard::A : 
		   player.goLeft();
		   break;

		   //S: moves player backwards
	   case  sf::Keyboard::S : 
		   player.goBackward();
		   break;

		   //D: Turns player to its right
	   case  sf::Keyboard::D : 
		   player.goRight();
		   break;

		   //space will cause the player attempt to fire
	   case	sf::Keyboard::Space :
		   if(player.canFire())
		   {
			player.fire();
			fireShell(player.firingPosition(), false);
		   }
		   break;
			
		   //Left: moves the turret left independant of the player
	   case  sf::Keyboard::Left:
		   player.turretGoLeft();
		   break;

		   //Right: moves the turret right independant of the player
	   case  sf::Keyboard::Right:
		   player.turretGoRight();
		   break;
	}
}

void Game::keyReleased(sf::Keyboard::Key key)
{
	switch(key)
	{
		//W, A, S, D: stops the player when the key is released
	   case  sf::Keyboard::W : 
		   player.stop();
		   break;
	   case  sf::Keyboard::A : 
		   player.stop();
		   break;
	   case  sf::Keyboard::S : 
		   player.stop();
		   break;
	   case  sf::Keyboard::D : 
		   player.stop();
		   break;

		//Left, Right: stops moving the turret when the key is released
	   case  sf::Keyboard::Left:
		   player.stopTurret();
		   break;
	   case  sf::Keyboard::Right:
		   player.stopTurret();
		   break;
	}
}

bool Game::gameOver() const
{
	//ends the game if either side has no buildings left or neither party has ammo and there are no more shells on the screen
	return numBlueBuildings() == 0 || numRedBuildings() == 0 || (!(player.hasAmmo() || npc.hasAmmo()) && shells.empty());
}

int Game::numBlueBuildings() const
{
	//returns the number of blue buildings
	return blueBuildings.size();
}

int Game::numRedBuildings() const
{
	//returns the number of red buildings
	return redBuildings.size();
}

list<int> Game::AStarPath(int goal)
{
	list<int> path;						//The path
	list<Nodes> open;					//list of nodes that have been visited
	list<Nodes> closed;					//list of nodes that haven't been visited

	int currentIndex = getNearestIndex(Position(npc.getX(), npc.getY()));;		//set the current index to the closest point
	int currentX, currentY;														//the x and y coords of the index
	Nodes currentNode;															//the current node being used

	int goalIndex = goal;														//the index we want to reach
	int goalX, goalY;															//that nodes x and y coords
	reverseIndex(goalIndex, &goalX, &goalY);

	// Set the base of the index, Parent index and the score
	currentNode.index = currentIndex;
	currentNode.parentIndex = -1;
	reverseIndex(currentIndex, &currentX, &currentY);
	currentNode.Fscore(0.0, currentX, currentY, goalX, goalY);

	open.push_back(currentNode);

	while (currentIndex != goalIndex) // while the tank has not reached the goal (the current index is not equal to the goal index)
	{
		//sort through the list of possible nodes and then resort them by taking some off the list
		// and set the new current index to proceed...
		open.sort();

		currentNode = open.front();
		open.pop_front();
		closed.push_back(currentNode);
		currentIndex = currentNode.index;

		//Look for connectiosn to other nodes
		for (int otherIndex = 0; otherIndex < nNodes; otherIndex++)
		{
			if (adjacencyMatrix[currentIndex][otherIndex])
			{
				list<Nodes>::iterator graphListIter;
				bool onClosed = false;
				bool onOpen = false;

				for (graphListIter = closed.begin(); graphListIter != closed.end(); ++graphListIter)
				{
					//check if its on the closed list
					if ((*graphListIter).index == otherIndex)
					{
						// if it has been found on the closed list, check the current g value to the one...
						// found on the closed list and then update the node
						onClosed = true;
						if (currentNode.g + 1.0 < (*graphListIter).g)
						{
							(*graphListIter).parentIndex = currentIndex;
						}
					}
				}

				if (!onClosed)
				{
					//check to see if its on the open list
					for (graphListIter = open.begin(); graphListIter != open.end(); ++graphListIter)
					{
						if ((*graphListIter).index == otherIndex)
						{
							onOpen = true;
							if (currentNode.g + 1.0 < (*graphListIter).g)
							{
								(*graphListIter).parentIndex = currentIndex;
							}
						}
					}
				}

				if (!onClosed && !onOpen)
				{
					Nodes tmpNode;														// not on open or the closed list...
					tmpNode.parentIndex = currentIndex;									// set the parent node to the present node
					tmpNode.index = otherIndex;											//set the node index to the other index
					reverseIndex(otherIndex, &currentX, &currentY);						//find the X and Y position of the node
					tmpNode.Fscore(currentNode.g, currentX, currentY, goalX, goalY);	//node score
					open.push_back(tmpNode);											// add to the open list
				}
			}
		}
	}

	// Now that the goal/ shortest path has been found, work its way backwords from the goal...
	//back to the first node
	int parent;
	list<Nodes>::iterator graphListIter;

	//set up the new nodes & remove current node from the closed list
	currentNode = closed.back();
	parent = currentNode.parentIndex;
	path.push_front(currentIndex);
	closed.pop_back();

	for (graphListIter = closed.end(), graphListIter--; graphListIter != closed.begin(); --graphListIter)
	{
		currentNode = *graphListIter;
		if (currentNode.index == parent)
		{
			path.push_front(parent);					// add to path
			parent = currentNode.parentIndex;			//new parent node
			closed.erase(graphListIter);				// remove from closed list
			graphListIter = closed.end();				//work its way backward
		}
	}
	return path;
}

int Game::index(int x, int y)			//Takes an x and y coordinate and returns the index node number
{
	return indexLookup[x - 1 ][y - 1];	//Reduces x and y first as to not cause catastrphic vector errors
}

bool Game::reverseIndex(int index, int *x, int *y)
{
	if (index > nNodes) { return false; }	//if the index is outside the number of nodes return false 

	else									//otherwise calculate the x y coords using this
	{
		*x = index % posWidth;
		*y = index / posWidth;
		return true;
	}
}

Position Game::getPos(int x, int y)				//Takes an x and y value and calculates its actual possition on the map
{
	return Position(20 * x + 40, 20 * y + 40);	//calculate the position of a set of coords
}

Position Game::getPosFromIndex(int index)		//Takes an index and  calculates its actual possition on the map
{
	int x = index % posWidth;					//converts the index to x and y positions
	int y = index / posWidth;					

	return Position(20 * x + 40, 20 * y + 40);	//calculate the position of a set of coords
}

void Game::buildingAdj(int dx, int dy, int yVar, int xVar)
{
	for (int i = 0; i < posHeight - 1; i++)										//For each node
	{
		for (int j = 0; j < posWidth - 1; j++)
		{
			Position currentPos = Game::getPos(i, j);							//calculate the nodes position
			int currentIndex = index(i, j);										//calculate its index
			if (currentPos.getX() > dx && currentPos.getX() < dx + xVar)		//check if it lies within the blocks x coords
			{
				if (currentPos.getY() > dy && currentPos.getY() < dx + yVar)	//check if it lies within the blocks y coords
				{
					for (int k = 0; k < nNodes - 1; k++)						//make sure the node is seen as inaccessable
					{
						adjacencyMatrix[k][currentIndex] = 0;
						adjacencyMatrix[currentIndex][k] = 0;
					}
				}
			}
		}
	}
}

int Game::getNearestIndex(Position currentPos)
{
	float currentMinDist = 1000;												//Large number initialized in order to prevent errors
	int currentMinNode = 0;														//arbitrary, needs to be initialized to prevent errors
	for (int i = 0; i < posHeight - 1; i++)										//loop through each node
	{
		for (int j = 0; j < posWidth - 1; j++)
		{
			Position nodePos = Game::getPos(i, j);								//calculate the nodes possition
			
			float diffX = (currentPos.getX() - nodePos.getX());					//calculate the difference in x
			float diffY = (currentPos.getY() - nodePos.getY());					//calculate the difference in y
			float currentDist = (diffY * diffY) + (diffX * diffX);				//calculate the distance between the npc and the node

			if (currentDist < currentMinDist) currentMinNode = index(i, j);		//check if it is closer than the current closest node, if so, replace it
		}
	}
	return currentMinNode;														//returns the node closest to the npc, this will be treated as the players position when path finding
}

list<int> Game::planPathBFS(int goalNode)
{
	int currentNode = getNearestIndex(Position(npc.getX(), npc.getY()));		//treat the node closest to the npc as its current node

	list<int> path;								// Final path to be constructed
	bool visited[nNodes];						// Has the node been visit
	list<list<int>> nodeQueue;					// Queue of nodes, implemented using a list

	for (int i = 0; i<nNodes; i++) visited[i] = false;

	path.push_back(currentNode);			    //add the initial node
	nodeQueue.push_back(path);				    //add this path to the list
	visited[currentNode] = true;			    //set the first node to visited
	if (currentNode == goalNode) return path;   //if the first node was the goal node then return it	

	while (!nodeQueue.empty())				    //while the node queue isn't empty	
	{
		path = nodeQueue.front();			    //Take the oldest stored path
		nodeQueue.pop_front();				    //Take that path off of the queue
		currentNode = path.back();			    //Set the current node to the last node on the path

		for (int i = 0; i<nNodes; i++)		    //for every node
		{
			if (adjacencyMatrix[currentNode][i] && !visited[i])    //check if it's adjacent to the current one and hasn't yet been visited
			{
				path.push_back(i);				//add the node to the current path
				nodeQueue.push_back(path);		//add this path to the list
				visited[i] = true;				//and set the node to visited
				if (i == goalNode)				//if the last element was the goal node
				{
					path.pop_front();			//take off the first element (don't know why but it's needed)
					return path;				//return the final path
				}
				path.pop_back();				//take that node back off of the list
			}
		}
	}
}

list<int> Game::planPathDFS(int goalNode)
{
	int currentNode = getNearestIndex(Position(npc.getX(), npc.getY()));

	list<int> path;								// Final path to be constructed
	bool visited[nNodes];						// Has the node been visit
	list<list<int>> nodeQueue;					// Queue of nodes, implemented using a list

	for (int i = 0; i<nNodes; i++) visited[i] = false;

	path.push_back(currentNode);			    //add the initial node
	nodeQueue.push_back(path);				    //add this path to the list
	visited[currentNode] = true;			    //set the first node to visited
	if (currentNode == goalNode) return path;   //if the first node was the goal node then return it	

	while (!nodeQueue.empty())				    //while the node queue isn't empty	
	{
		path = nodeQueue.back();			    //Take the newest stored path
		nodeQueue.pop_back();				    //Take that path off of the queue
		currentNode = path.back();			    //Set the current node to the last node on the path

		for (int i = 0; i<nNodes; i++)		    //for every node
		{
			if (adjacencyMatrix[currentNode][i] && !visited[i])    //check if it's adjacent to the current one and hasn't yet been visited
			{
				path.push_back(i);				//add the node to the current path
				nodeQueue.push_back(path);		//add this path to the list
				visited[i] = true;				//and set the node to visited
				if (i == goalNode)
				{
					path.pop_front();
					return path;				//if the node is the one we want to reach, return the current path
				}
			}
		}
	}
}

int Game::chooseGoal()							//determines the goal node based on the current number of shells the npc can fire
{
	if (npc.getNumberOfShells() > 0)			//checks if there are any shells left
	{
		return makeEnemyTerritoryGoal();		//Select a new a goal node in enemy territory
	}

	else										//If there are no shells left
	{
		return makeRandomGoal();				//Make a goal anywhere, to try and run away
	}
}

int Game::makeInitialGoal()						//Makes a goal node in the upper left of the map
{
	int dx = (float)(rand() % 10) + 1;			//Randomize the x between 1 and 10
	int dy = (float)(rand() % 30) + 1;			//Randomize the y between 1 and 30

	return index(dx, dy);						//Calculate the index of the point
}

int Game::makeRandomGoal()						//Makes an entirely random goal node
{
	int dx = (float)(rand() % posWidth-1)+1;		//Randomizes between 1 and posWidth
	int dy = (float)(rand() % posHeight-1)+1;		//Randomizes between 1 and posHeight

	return index(dx, dy);						//Calculate the index of the point
}

int Game::makeEnemyTerritoryGoal()				//Makes a goal node in enemy territory
{
	int dx = (float)(rand() % posWidth / 2)+1;	//Randomizes between 1 and half of the posWidth
	int dy = (float)(rand() % posHeight-1)+1;		//Randomizes between 1 and posHeight

	return index(dx, dy);						//Calculate the index of the point
}

