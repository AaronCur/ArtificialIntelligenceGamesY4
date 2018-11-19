#pragma once
#include <SFML\Graphics.hpp>
#include <sstream>

enum State
{
	NONE,
	START,
	GOAL,
	OBSTACLE
};

class Tile
{
public:
	Tile(float x, float y, int tileSize, float m_tileScale, int xPos, int yPos);
	~Tile();

	void update();
	void mouseDetection(sf::Vector2i mousePos, int val);
	void setCost(int cost);
	void render(sf::RenderWindow &window);

	void setCurrentState(State s);
	State getCurrentState();
	sf::Vector2f m_position;
	sf::RectangleShape rectangle;
	sf::Font m_font;
	sf::Text m_name;
	sf::String m_nameText;

	sf::Text m_heuristictext;
	sf::String m_heuristicString;

	State m_currentState = NONE;
	int m_tileSize;
	float m_tileScale;
	int m_cost = 0;

	int m_xPos;
	int m_yPos;

private:

};