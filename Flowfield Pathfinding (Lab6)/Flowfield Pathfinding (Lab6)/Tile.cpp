#include "Tile.h"
#include <iostream>
Tile::Tile(float x, float y, int tileSize, float tileScale, int xPos, int yPos) :
	m_position(x, y),
	m_tileSize(tileSize),
	m_tileScale(tileScale),
	m_xPos(xPos),
	m_yPos(yPos)
{

	if (!m_font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	m_costText.setFont(m_font);
	m_costText.setString(std::to_string(m_cost));
	//m_costText.setFillColor(sf::Color::Black);
	m_costText.setPosition(m_position);
	rectangle.setSize(sf::Vector2f(m_tileSize * m_tileScale, m_tileSize * m_tileScale));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color::Blue);
	rectangle.setPosition(x, y);

}

Tile::~Tile()
{

}

void Tile::setCurrentState(State s)
{
	m_currentState = s;
}

State Tile::getCurrentState()
{
	return m_currentState;
}

void Tile::update()
{

	switch (m_currentState)
	{
	case NONE:
		rectangle.setFillColor(sf::Color::White);
		break;
	case START:
		rectangle.setFillColor(sf::Color::Green);
		break;
	case GOAL:
		rectangle.setFillColor(sf::Color::Red);
		break;
	case OBSTACLE:
		rectangle.setFillColor(sf::Color::Black);
		break;
	default:
		break;
	}
}
void Tile::mouseDetection(sf::Vector2i mousePos, int val)
{
	
	if ((m_position.x < mousePos.x) &&
		(m_position.x + (m_tileSize * m_tileScale) > mousePos.x) &&
		(m_position.y + (m_tileSize * m_tileScale) > mousePos.y) &&
		(m_position.y < mousePos.y))
	{
		if (val == 1) {
			setCurrentState(START);
		}
		else if (val == 2)
		{
			setCurrentState(GOAL);
		}
	}
	
}

void Tile::setCost(int cost)
{
	m_cost = cost;
	m_costText.setString(std::to_string(m_cost));
}
int Tile::getCost()
{
	return m_cost;
}

void Tile::render(sf::RenderWindow &window)
{
	window.draw(rectangle);
	window.draw(m_costText);
}