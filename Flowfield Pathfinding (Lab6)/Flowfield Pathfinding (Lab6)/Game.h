#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"


class Game
{
public:
	Game();
	void run();

private:
	void update(double dt);
	void processEvents();
	void processGameEvents(sf::Event& event);
	void render();
	void initGrid(Tile m_goalTile);
	void closeNeighbours();

protected:
	sf::RenderWindow m_window;

	static const int m_gridSize = 50;
	static const int m_tileSize = 50;
	float m_tileScale = 1;

	Tile *m_tileGrid[m_gridSize][m_gridSize];

	int x = 0;
	int y = 0;

	int m_tilePosX = 0;
	int m_tilePosY = 0;

	sf::Vector2i m_mousePos;

	Tile * m_startTile;
	Tile * m_goalTile;

	bool m_leftPress = false;
	bool m_rightPress = false;
	//Enemy* m_pursue;


};
