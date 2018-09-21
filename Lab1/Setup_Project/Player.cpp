

#include "Player.h"
Player::Player() :
	m_position(100, 100),
	m_velocity(0,0),
	shape(100.0)

{
	if (!m_texture.loadFromFile("Player.png")) {
		//do something
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.3, 0.3);
	
}
Player::~Player()
{

}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		m_velocity.x = m_velocity.x + 0.2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		m_velocity.x = m_velocity.x - 0.2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// left key is pressed: move our character
		m_velocity.y = m_velocity.y - 0.2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// left key is pressed: move our character
		m_velocity.y = m_velocity.y + 0.2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// left key is pressed: move our character
		m_velocity.x = 0;
		m_velocity.y = 0;
	}

	m_position = m_position + m_velocity;
	m_sprite.setPosition(m_position);

	respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);

	


}

void Player::respawn(float x, float y)
{
	if (y >= 1000 + 100)
	{
		m_position.y = -200;
	}

	else if (y < -200)
	{
		m_position.y = 1100;
	}
	else if (x < -200)
	{
		m_position.x = 2100;
	}
	else if (x >= 2100)
	{
		m_position.x = -200;
	}
}

void Player::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}