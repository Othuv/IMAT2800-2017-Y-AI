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
		
		static const int posWidth = 39;
		static const int posHeight = 28;
		
		static const int nNodes = posHeight * posWidth;
		
		int indexLookup[posWidth][posHeight];

		vector<vector<bool>> adjacencyMatrix;	// adjacency matrix [nNodes] [nNodes]
		vector<vector<Position>> positionMatrix; // position matrix of size [width] [height]

		unsigned short lives; // number of lives left
		bool debugMode; // toggle for debug mode
		sf::RectangleShape background; // Background the playing area
		sf::RectangleShape ammoArea; // Background where the ammo is drawn
		list<Obstacle> obstacles; // Obstacles in the tanks way
		list<Obstacle> blueBuildings; // Collection of blue buildings
		list<Obstacle> redBuildings; // Collection of red buildings
		list<Shell> shells; // Shells fired from tanks
		void resetNpc(); // Move the NPC after it has been shot
		void resetPlayer(); // Move the player after it has been shot
		void fireShell(Position fp, bool npc); // Fire a shell
		int redScore; // Score of red tank
		int blueScore; // Score of blue tank
    public:
		Game(); // Constructor
		~Game(); // Destructor
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; // Draw the game
		void play(); // Play the game for one timestep
		DumbTank npc; // Red tank
		PlayerTank player; // Blue tank
		void keyPressed(sf::Keyboard::Key key); // function for processing input
		void keyReleased(sf::Keyboard::Key key); // function for processing input
		bool gameOver() const; // Has the game finished?
		int numBlueBuildings() const; // Count of blue buildings
		int numRedBuildings() const; // Count of red buildings
		int getIndex(int x, int y);
		bool reverseIndex(int index, int *x, int *y);
		Position getPos(int x, int y);
		void buildingAdj(int dx, int dy, int yVar, int xVar);
		int getNearestIndex(Position currentPos);
		list<int> planPathBFS(int goalNode);
		list<int> planPathDFS(int goalNode);
};
#endif