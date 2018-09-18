#include "Player.h"
Player::Player() :
	m_position(500, 800)

{
	

}
Player::~Player()
{

}

void Player::update( float x, float y)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		m_velocity.x = m_velocity.x + 0.002;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		m_velocity.x = m_velocity.x - 0.002;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// left key is pressed: move our character
		m_velocity.y = m_velocity.y - 0.002;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// left key is pressed: move our character
		m_velocity.y = m_velocity.y + 0.002;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// left key is pressed: move our character
		m_velocity.x = 0;
		m_velocity.y = 0;
	}

	m_position = m_position + m_velocity;

	shape.setPosition(m_position);


}

void Player::respawn(float x, float y)
{
	if (shape.getPosition().y >= 1000 + 100)
	{
		m_position.y = -200;
	}

	else if (shape.getPosition().y < -200)
	{
		m_position.y = 1100;
	}
	else if (shape.getPosition().x < -200)
	{
		m_position.x = 2100;
	}
	else if (shape.getPosition().x >= 2100)
	{
		m_position.x = -200;
	}
}

void Player::render(sf::RenderWindow &window)
{
	window.clear();
	window.draw(shape);
	window.display();
}