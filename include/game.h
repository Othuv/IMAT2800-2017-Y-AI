#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <list>

#include "DumbTank.h"
#include "playerTank.h"
#include "obstacle.h"
#include "shell.h"
#include "position.h"
using namespace std;

class Game : public sf::Drawable
{
	private:
		
		static const int posWidth = 38;						// number of x positions the tank can travel 
		static const int posHeight = 27;					// number of y positions the tank can travel
		static const int nNodes = posHeight * posWidth;		// total number of positions the tank can be
		int indexLookup[posWidth][posHeight];				// contains the index value bassed on the x, y coords
		vector<vector<bool>> adjacencyMatrix;				// adjacency matrix [nNodes] [nNodes]
//		vector<vector<Position>> positionMatrix;			// position matrix of size [width] [height], scraped for a calculation

		unsigned short lives;								// number of lives left
		bool debugMode;										// toggle for debug mode
		sf::RectangleShape background;						// Background the playing area
		sf::RectangleShape ammoArea;						// Background where the ammo is drawn
		list<Position> aiPath;
		list<int> lIPath;
		list<Obstacle> obstacles;							// Obstacles in the tanks way
		list<Obstacle> blueBuildings;						// Collection of blue buildings
		list<Obstacle> redBuildings;						// Collection of red buildings
		list<Shell> shells;									// Shells fired from tanks
		void resetNpc();									// Move the NPC after it has been shot
		void resetPlayer();									// Move the player after it has been shot
		void fireShell(Position fp, bool npc);				// Fire a shell
		int redScore;										// Score of red tank
		int blueScore;										// Score of blue tank
    public:
		Game();																					// Constructor
		~Game();																				// Destructor
		int chooseGoal();																		// Select what type of path will be taken
		int makeInitialGoal();																	// Decides the initial position to path find to
		int makeRandomGoal();																	// Creates a random position to path find to
		int makeEnemyTerritoryGoal();															// Creates a position in the enemy (the players) territory
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;				// Draw the game
		void play();																			// Play the game for one timestep
		AITank npc = AITank();																	// Red tank
		PlayerTank player;																		// Blue tank
		void keyPressed(sf::Keyboard::Key key);													// function for processing input
		void keyReleased(sf::Keyboard::Key key);												// function for processing input
		bool gameOver() const;																	// Has the game finished?
		int numBlueBuildings() const;															// Count of blue buildings
		int numRedBuildings() const;															// Count of red buildings

		//The following are functions that have been added to the game to facilitate pathing
		int index(int x, int y);								//return the index for a pair of coords
		list<int> AStarPath(int goal);
		bool reverseIndex(int index, int *x, int *y);			//return the coords for an index
		Position getPos(int x, int y);							//calculate an ingame position from a pair of coords
		Position getPosFromIndex(int index);					//calculates an ingame position based on the index value
		void buildingAdj(int dx, int dy, int yVar, int xVar);	//check if the points on the adjacency matrix collide with a box
		int getNearestIndex(Position currentPos);				//get the closest node to the current position
		list<int> planPathBFS(int goalNode);					//pathing based on a BFS system
		list<int> planPathDFS(int goalNode);					//pathing based on a DFS system
};

class Nodes
{
public:
	float f;
	float g;
	float h;

	int index;
	int parentIndex;
	void Fscore(float parentGScore, int currentX, int currentY, int goalX, int goalY)
	{
		//working out the f score
		float dx, dy;

		g = parentGScore + 1.0f; //parent + 1
		dx = (float)(goalX - currentX); //the x goal position minus the current x postion
		dy = (float)(goalY - currentY); //the y goal position minus the current y postion
		h = sqrt(dx * dx + dy * dy); //The Euclidean distance to the goal 
		f = g + h;

	}
	bool operator<(const Nodes& other)
	{
		return f < other.f;
	}
};
#endif