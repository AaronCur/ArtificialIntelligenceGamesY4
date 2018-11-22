#include "Button.h"
#include <iostream>
Button::Button(sf::Font font, sf::String string, float posX, float posY) :
	m_position(posX, posY),
	m_size(400, 200),
	m_button1(string),
	m_font(font)
{

	m_name.setFont(m_font);
	m_name.setCharacterSize(90);
	m_name.setString(m_button1);
	m_name.setPosition(m_position.x + 5, m_position.y + 2);

}

Button::~Button()
{

}

void Button::update()
{

}
void Button::mouseDetection(sf::Vector2i mousePos)
{

	if ((m_position.x < mousePos.x) &&
		(m_position.x + m_size.x > mousePos.x) &&
		(m_position.y + m_size.y > mousePos.y) &&
		(m_position.y < mousePos.y))
	{

			selected = true;
	}
	
}



void Button::render(sf::RenderWindow &window)
{

	button.setFillColor(sf::Color(127, 127, 127));

	button.setOutlineThickness(5);
	button.setOutlineColor(sf::Color(0, 0, 0));
	button.setPosition(m_position);
	button.setSize(m_size);
	m_name.setPosition(m_position.x + (200 / 4), m_position.y + (100 / 4));
	m_name.setFillColor(sf::Color::White);
	window.draw(button);
	window.draw(m_name);


}