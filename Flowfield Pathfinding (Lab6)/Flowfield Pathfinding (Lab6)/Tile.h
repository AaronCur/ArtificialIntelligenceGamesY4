#pragma once
#include <SFML\Graphics.hpp>
#include <sstream>


enum Draw
{
	FLOW,
	COST,
	BOTH,
	CLEAR
};
enum State
{
	NONE,
	START,
	GOAL,
	OBSTACLE,
	PATH
};


class Tile
{
public:
	Tile(float x, float y, int tileSize, float m_tileScale, int xPos, int yPos, sf::Font &font);
	~Tile();

	void update();
	void mouseDetection(sf::Vector2i mousePos, int val);
	void setRotation(float rot);
	void setCost(int cost);
	void setPrevious(int x, int y);
	int getCost();

	void setDrawState(Draw ds);
	Draw getDrawState();
	
	void render(sf::RenderWindow &window);

	void setCurrentState(State s);
	State getCurrentState();



	sf::Vector2f m_position;
	sf::RectangleShape rectangle;
	sf::Font m_font;
	sf::Text m_costText;
	sf::String m_costString;

	sf::Text m_heuristictext;
	sf::String m_heuristicString;

	State m_currentState = NONE;
	Draw m_drawState = CLEAR;
	int m_tileSize;
	float m_tileScale;
	
    int m_cost = 0;
	bool checked = false;

	int m_xPos;
	int m_yPos;

	float m_rotation = 0;

	sf::RectangleShape vector;

	std::pair < int, int> m_previous;

private:

};