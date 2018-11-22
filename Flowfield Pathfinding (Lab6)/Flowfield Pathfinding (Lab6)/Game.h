#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "Button.h"


class Game
{
public:
	Game();
	void run();

private:
	void update();
	void processEvents();
	void processGameEvents(sf::Event& event);
	void render();
	void reset();
	void initGrid(int posX, int posY);
	void getPath(Tile m_startTile);

protected:
	sf::RenderWindow m_window;

	static const int m_gridSize = 30;
	static const int m_tileSize = 60;
	float m_tileScale = 1;

	Tile *m_tileGrid[m_gridSize][m_gridSize];

	int x = 0;
	int y = 0;

	int m_tilePosX = 0;
	int m_tilePosY = 0;

	sf::Vector2i m_mousePos;

	Tile * m_startTile;
	Tile * m_goalTile;
	sf::Font m_font;

	Button *m_button;
	Button *m_vecButton;
	Button *m_costButton;
	Button *m_clearButton;

	bool m_leftPress = false;
	bool m_rightPress = false;
	//Enemy* m_pursue;


	sf::Text m_startText;

	sf::Text m_goalText;

	sf::Text m_obstacleText;

	sf::Text m_pathText;
	
	sf::RectangleShape m_startRec;
	sf::RectangleShape m_goalRec;
	sf::RectangleShape m_obstacleRec;
	sf::RectangleShape m_pathRec;

};
