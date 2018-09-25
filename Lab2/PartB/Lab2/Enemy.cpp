#include "Enemy.h"


Enemy::Enemy() :
	m_position(100, 500),
	m_velocity(0, 0),
	shape(100.0f),
	m_maxSpeed(10.0f)
{
	if (!m_texture.loadFromFile("Enemy.png")) {
		//do something
	}

	
    //m_rect.setTexture(&m_texture);
	//m_rect.setSize(sf::Vector2f(m_texture.getSize().x / 3, m_texture.getSize().y / 3));
	//m_rect.setPosition(m_position);
	
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.3, 0.3);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);
	shape.setFillColor(sf::Color::Green);

	m_sprite.setOrigin(m_position.x - (m_sprite.getTextureRect().width / 2), m_position.y - (m_sprite.getTextureRect().height / 2));

	std::cout << m_sprite.getTextureRect().width << std::endl;
	std::cout << m_sprite.getTextureRect().height << std::endl;
	
}


Enemy::~Enemy()
{
}
float Enemy::getNewOrientation(float currentOrientation, float velocity)
{
	//if (velocity >0)
	//{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	//}
	//else {
		///return currentOrientation;
	//}

}
void Enemy::respawn(float x, float y)
{
	

	if (x > 2020)
	{
		m_position.x = -200;
		m_velocity.x = getRandom(10, 1);
		m_velocity.y = getRandom(21, -10);
	}
	if (x < -200)
	{
		m_position.x = 1920;
		m_velocity.x = getRandom(-10, -1);
		m_velocity.y = getRandom(21, -10);
	}
	if (y < -200)
	{
		m_position.y = 1080;
		m_velocity.x = getRandom(21, -10);
		m_velocity.y = getRandom(-10, -1);
	}
	if (y > 1180)
	{
		m_position.y = -200;
		m_velocity.x = getRandom(21, -10);
		m_velocity.y = getRandom(10, 1);
	}

}

float Enemy::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}

void Enemy::update(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	m_velocityF = m_velocityF * m_maxSpeed;
	m_orientation = getNewOrientation(m_orientation, m_velocityF);


	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);
}


void Enemy::render(sf::RenderWindow & window)
{
	
	window.draw(m_sprite);
}