#include "Arrive.h"

Arrive::Arrive(float max, float posX, float posY) :
	m_position(posX, posY),
	m_velocity(0, 0),
	shape(100.0f),
	m_maxSpeed(2.0f),
	m_maxRotation(20.0f),
	m_timeToTarget(max),
	m_behaviour(1),
	m_threshold(30.0f),
	m_radius(250.0f)
	
{

	if (!m_texture.loadFromFile("Enemy.png")) {
		//do something
	}

	if (!m_font.loadFromFile("Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	m_label.setFont(m_font);
	m_label.setCharacterSize(40);
	m_label.setString("Arrive");
	m_label.setFillColor(sf::Color(127, 127, 127));
	m_sprite.setOrigin((m_sprite.getTextureRect().width / 2), (m_sprite.getTextureRect().height / 2));
	
	

	//m_rect.setTexture(&m_texture);
	//m_rect.setSize(sf::Vector2f(m_texture.getSize().x / 3, m_texture.getSize().y / 3));
	//m_rect.setPosition(m_position);

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.1, 0.1);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);
	//shape.setFillColor(sf::Color::Green);

	//m_sprite.setOrigin(m_position.x , m_position.y);
	m_sprite.setOrigin((m_sprite.getTextureRect().width / 2), (m_sprite.getTextureRect().height / 2));


}


Arrive::~Arrive()
{

}
sf::Vector2f Arrive::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Arrive::getVelocity()
{
	return m_velocity;
}
int Arrive::getId()
{
	return id;
}
void Arrive::kinematicFlee(sf::Vector2f enemyPosition)
{
	m_velocity = m_position - enemyPosition;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//m_velocityF = m_velocityF * m_maxSpeed;
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	std::cout << m_velocity.x << std::endl;;
	m_orientation = getNewOrientation(m_orientation, m_velocityF);
}
void Arrive::collisionAvoidance(std::vector<Enemy*> enemies) {

	for (int i = 0; i < enemies.size(); i++)//
	{
		if (enemies[i]->getPosition() != m_position)
		{
			//Vector player to enemy
			m_direction = enemies[i]->getPosition() - m_position;
			m_distance = std::sqrt(m_direction.x*m_direction.x + m_direction.y* m_direction.y);



			if (m_distance <= m_radius)
			{
				float dot = (m_velocity.x * m_direction.x) + (m_velocity.y * m_direction.y);
				float det = (m_velocity.x * m_direction.y) - (m_velocity.y * m_direction.x);

				float angle = atan2(det, dot);
				angle = (180 / 3.14) * angle;

				if (angle >= -m_threshold && angle <= m_threshold)
				{
					m_behaviour = 2;
					kinematicFlee(enemies[i]->getPosition());
					std::cout << "Collided Arrive" << std::endl;

				}

			}
			if (m_behaviour == 2 && m_distance > m_radius * 2)
			{
				m_behaviour = 1;
			}



		}
	}

}
float Arrive::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}
void Arrive::respawn(float x, float y)
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

float Arrive::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}

void Arrive::kinematicArrive(sf::Vector2f playerPosition)
{
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	m_velocity = playerPosition - m_position;

	//if (m_velocityF < 0)
	//{
	//return m_velocityF;
	//}
	if (m_velocityF >= 0)
	{
		m_velocity = m_velocity / m_timeToTarget;

		if (m_velocityF > m_maxSpeed) {

			//Normalize vector
			m_velocity.x = m_velocity.x / m_velocityF;
			m_velocity.y = m_velocity.y / m_velocityF;

			m_velocity = m_velocity* m_maxSpeed;

		}

		m_orientation = getNewOrientation(m_orientation, m_velocityF);
	}

}

void Arrive::update(sf::Vector2f playerPosition, sf::Vector2f playerVelocity)
{
	if (m_behaviour == 1)
	{
		kinematicArrive(playerPosition);
	}
	

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);
	m_label.setPosition(m_sprite.getPosition().x - 50, m_sprite.getPosition().y - 130);
}


void Arrive::render(sf::RenderWindow & window)
{

	window.draw(m_sprite);
	window.draw(m_label);
}