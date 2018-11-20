#include "Tile.h"
#include <iostream>
Tile::Tile(float x, float y, int tileSize, float tileScale, int xPos, int yPos, sf::Font &font) :
	m_position(x, y),
	m_tileSize(tileSize),
	m_tileScale(tileScale),
	m_xPos(xPos),
	m_yPos(yPos),
	m_font(font)
{

	

	m_costText.setFont(m_font);
	m_costText.setString(std::to_string(m_cost));
	m_costText.setFillColor(sf::Color::Black);
	m_costText.setPosition(m_position);
	rectangle.setSize(sf::Vector2f(m_tileSize * m_tileScale, m_tileSize * m_tileScale));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(200, 200, 200));
	rectangle.setPosition(x, y);


	vector.setSize(sf::Vector2f(25, 1));
	vector.setFillColor(sf::Color::Red);
	vector.setOutlineColor(sf::Color::Red);
	vector.setOutlineThickness(1);
	vector.setPosition(m_position.x + ((m_tileSize * m_tileScale) / 2), m_position.y + ((m_tileSize * m_tileScale) / 2));
	vector.setRotation(m_rotation);
}

Tile::~Tile()
{

}

void Tile::setRotation(float rot)
{
	m_rotation = rot;
	vector.setRotation(m_rotation);
}


void Tile::setCurrentState(State s)
{
	m_currentState = s;
}


State Tile::getCurrentState()
{
	return m_currentState;
}

void Tile::setDrawState(Draw ds) {

	m_drawState = ds;
}
Draw Tile::getDrawState() {
	return m_drawState;
}

//void Tile::setCurrentDrawState(DrawState s)
//{
//	m_currentDrawState = s;
//}
//
//
//DrawState Tile::getCurrentDrawState()
//{
//	return m_currentDrawState;
//}
//

void Tile::update()
{
	

	switch (m_currentState)
	{
	case NONE:
		rectangle.setFillColor(sf::Color(255 - (m_cost * 2.3), 255 - (m_cost * 2.3),255 - (m_cost * 2.3)));
		break;
	case START:
		rectangle.setFillColor(sf::Color::Green);
		break;
	case GOAL:
		rectangle.setFillColor(sf::Color::Red);
		break;
	case OBSTACLE:
		rectangle.setFillColor(sf::Color(45,45,45));
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
	
	switch (m_drawState)
	{
	case FLOW:
		if (m_currentState == NONE)
		window.draw(vector);
		break;
	case COST:
		if (m_currentState == NONE)
		window.draw(m_costText);
		break;
	case BOTH:
		if (m_currentState == NONE)
		window.draw(vector);
		window.draw(m_costText);
		break;
	default:
		break;
	}
	
}