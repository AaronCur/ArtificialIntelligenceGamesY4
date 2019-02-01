#include "Wander.h"

Wander::Wander() :
	m_position(100, 800),
	m_velocity(0, 0),
	shape(100.0f),
	m_maxSpeed(2.0f),
	m_maxRotation(20.0f),
	m_radius(250.0f),
	m_threshold(30.0f),
	m_behaviour(1)
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
	m_label.setString("Wander");
	m_label.setPosition(m_sprite.getPosition());
	m_label.setFillColor(sf::Color(127, 127, 127));
	
    //m_rect.setTexture(&m_texture);
	//m_rect.setSize(sf::Vector2f(m_texture.getSize().x / 3, m_texture.getSize().y / 3));
	//m_rect.setPosition(m_position);
	
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.1, 0.1);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);
	//shape.setFillColor(sf::Color::Green);

	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2,m_sprite.getTextureRect().height / 2);

	std::cout << m_sprite.getTextureRect().width << std::endl;
	std::cout << m_sprite.getTextureRect().height << std::endl;
	
}



Wander::~Wander()
{

}

sf::Vector2f Wander::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Wander::getVelocity()
{
	return m_velocity;
}
int Wander::getId()
{
	return id;
}
void Wander::kinematicFlee(sf::Vector2f enemyPosition)
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


	m_orientation = getNewOrientation(m_orientation, m_velocityF);

}
void Wander::collisionAvoidance(std::vector<Enemy*> enemies) {


	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->getId() != id)
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
					std::cout << "Collided Wander" << std::endl;

				}

			}
			if (m_behaviour == 2 && m_distance > m_radius * 2)
			{
				m_behaviour = 1;
			}



		}
	}

}
float Wander::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}
void Wander::respawn(float x, float y)
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

float Wander::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}

void Wander::kinematicWander(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//m_velocityF = m_velocityF * m_maxSpeed;
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	std::cout << m_velocity.x << std::endl;;
	m_orientation = getNewOrientation(m_orientation, m_velocityF);
	m_orientation = m_orientation + m_maxRotation * getRandom(2, -1);
	m_velocity.x = (-sin(m_orientation)) * m_maxSpeed;
	m_velocity.y = cos(m_orientation) * m_maxSpeed;
}

void Wander::update(sf::Vector2f playerPostion, sf::Vector2f playerVelocity)
{
	if (m_behaviour == 1)
	{
		kinematicWander(playerPostion);
	}
	

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);
	m_label.setPosition(m_sprite.getPosition().x - 50, m_sprite.getPosition().y - 130);
}


void Wander::render(sf::RenderWindow & window)
{
	
	window.draw(m_sprite);
	window.draw(m_label);
}