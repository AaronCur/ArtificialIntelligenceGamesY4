#include "Player.h"
Player::Player() :
	m_position(100, 100),
	m_velocity(0,0),
	shape(100.0),
	m_rotation(0),
	m_maxSpeed(250),
	m_speed(0),
	m_heading(0,0)

{
	if (!m_texture.loadFromFile("Player.png")) {
		//do something
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.3, 0.3);
	m_sprite.setRotation(90);
	m_sprite.setOrigin(m_position.x  + (m_sprite.getTextureRect().width / 2), m_position.y  + (m_sprite.getTextureRect().height / 2));
	DEG_TO_RAD = 3.14 / 180;
	
}
Player::~Player()
{

}
void Player::getNewOrientation()
{
	m_heading.x = cos(m_rotation * (3.14 / 180));
	m_heading.y = sin(m_rotation * (3.14 / 180));

}
void Player::speedUp()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += 1;
	}
}
void Player::speedDown()
{
	if (m_speed > 0)
	{
		m_speed -= 1;
	}
}
void Player::increaseRotation()
{

	m_rotation += 1.0f;
}
void Player::decreaseRotation()
{
	
	if (m_rotation != 0.00f)
	{
		m_rotation -= 1.0f;
	}
	else
	{
		m_rotation = 359.0f;
	}
	
	
}

void Player::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//right key is pressed: move our character
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// up key is pressed: move our character
		speedUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//down key is pressed: move our character
		speedDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//space key is pressed: move our character
		m_velocity.x = 0;
		m_velocity.y = 0;
	}

	getNewOrientation();
	m_sprite.setPosition(m_sprite.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_sprite.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_sprite.setRotation(m_rotation);

	//m_position = m_position + m_velocity;
	//m_sprite.setPosition(m_position);
	

	respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);

	


}

void Player::respawn(float x, float y)
{
	if (y >= 1000 + 100)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, -200);
	}

	else if (y < -200)
	{
		m_sprite.setPosition(m_sprite.getPosition().x,1100);
	}
	else if (x < -200)
	{
		m_sprite.setPosition(2100, m_sprite.getPosition().y);
	}
	else if (x >= 2100)
	{
		m_sprite.setPosition(200, m_sprite.getPosition().y);
	}
}

void Player::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}