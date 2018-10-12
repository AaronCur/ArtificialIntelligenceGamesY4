#include "Pursue.h"

Pursue::Pursue() :
	m_position(300, 500),
	m_velocity(0, 0),
	m_relVelocity(0,0),
	shape(100.0f),
	m_maxSpeed(1.0f),
	m_maxRotation(20.0f),
	m_timeToTarget(80.0f),
	m_maxTimePrediction(10.0f),
	m_relSpeed(0.0f),
	m_radius(300.0f),
	m_threshold (30.0f),
	m_behaviour(1)
{

	if (!m_texture.loadFromFile("EnemySeek.png")) {
		//do something
	}

	if (!m_font.loadFromFile("Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	m_label.setFont(m_font);
	m_label.setCharacterSize(40);
	m_label.setString("Pursue");
	m_label.setPosition(m_sprite.getPosition());
	m_label.setFillColor(sf::Color(127,127,127,127));
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(m_texture.getSize().x / 3, m_texture.getSize().y / 3));
	m_rect.setPosition(m_position);

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.3, 0.3);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);
	//shape.setFillColor(sf::Color::Green);

	m_sprite.setOrigin((m_sprite.getTextureRect().width / 2), (m_sprite.getTextureRect().height / 2));

	

}


Pursue::~Pursue()
{

}
sf::Vector2f Pursue::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Pursue::getVelocity()
{
	return m_velocity;
}
int Pursue::getId()
{
	return id;
}
float Pursue::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}
void Pursue::respawn(float x, float y)
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

float Pursue::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}

void Pursue::collisionAvoidance(std::vector<Enemy*> enemies) {

///Closest approach

	//ShortestTime = infinity
	//firstTarget = None /// target tht will collide first
	//firstMinSeperation, firstDistance, firstRelativePos, firstRelativeVel
	//Radius // Collision radius

	//for target in targets:
		//relativePos = target.position - charachter.position
		//relativeVel = target.velocity - charachter.velocity
		//relativeSpeed = relativeVel.length
		//timeToCollision = (relativePos.RelativeVel) / (relativeSpeed*relativespeed)
		//distance = relativePos.length()
		//minSeperation = distance - relativeSpeed * shortestTime
		
		//If mineperation > 2 *radius : continue
		//If timeToCollision > 0 and timeToCollision < shortestTime:
			//shortestTime = timeToCollision
			//firstTarger

	//for (int i = 0; i < enemies.size(); i++)
	//{
	//	if (enemies[i]->getId() != id)
	//	{
	//		m_relPosition = enemies[i]->getPosition() - m_position;
	//		m_relVelocity = enemies[i]->getVelocity() - m_velocity;
	//		m_relSpeed = std::sqrt(m_relVelocity.x*m_relVelocity.x + m_relVelocity.y* m_relVelocity.y);
	//		m_timeToCollision = ((m_relPosition.x * m_relVelocity.x) + (m_relPosition.y * m_relVelocity.y)) / (m_relSpeed * m_relSpeed);

	//		m_distance = std::sqrt(m_relPosition.x*m_relPosition.x + m_relPosition.y* m_relPosition.y);

	//		m_minSeperation = m_distance - (m_relSpeed * m_shortestTime);

	//		if (m_minSeperation <= 2 * m_radius)
	//		{
	//			break;
	//		}

	//		if (m_timeToCollision > 0 && m_timeToCollision < m_shortestTime)
	//		{
	//			m_shortestTime = m_timeToCollision;
	//			m_firstTarget = enemies[i]->getPosition();
	//			m_firstMinSeperation = m_minSeperation;
	//			m_firstDistance = m_distance;
	//			m_firstRelativePos = m_relPosition;
	//			m_firstRelativeVel = m_relVelocity;
	//		}
	//		
	//	}
	//}

	//if (m_firstMinSeperation <= 0 || m_distance < 2 * m_radius) //colliding
	//{
	//	m_relPosition = m_firstTarget - m_position;
	//}
	//else
	//{
	//	m_relPosition = m_firstRelativePos + m_firstRelativeVel * m_shortestTime;
	//}





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
					m_velocity = -m_velocity;
					m_orientation = -m_orientation;
					std::cout << "Collided Pursue" << std::endl;
					
				}
				

			}
			if (m_behaviour == 2 && m_distance > m_radius * 2)
			{
				m_behaviour = 1;
			}

		

		}
	}

}
void Pursue::kinematicSeek(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
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
void Pursue::kinematicFlee(sf::Vector2f enemyPosition)
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
void Pursue::kinematicArrive(sf::Vector2f playerPosition)
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

			m_velocity = m_velocity * m_maxSpeed;

		}

		m_orientation = getNewOrientation(m_orientation, m_velocityF);
	}

}
void Pursue::pursue(sf::Vector2f playerPosition, sf::Vector2f playerVelocity) {
	//direction = target.positon - my.position
	//distance = direction.length
	//speed = my.velocity.length

	//if speed <= distance / maxTimePrediction:
		//timePrediction = maxTimeprediction
	//else:
		//timePrediciton = distance/speed
	//NewTarget.position = target.position + target.velocity * timePrediction
	//return seek(me, newTarget)

	m_direction = playerPosition - m_position;
	
	
	m_distance = std::sqrt(m_direction.x*m_direction.x + m_direction.y* m_direction.y);

	
	m_speed = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	
	if (m_speed <= m_distance / m_maxTimePrediction) {
		
		m_timePrediction = m_maxTimePrediction;
	}
	else {
		m_timePrediction = m_distance / m_speed;
	}

	m_targetPos = playerPosition + playerVelocity * m_timePrediction;
	

	kinematicArrive(m_targetPos);
		
}
void Pursue::update(sf::Vector2f playerPosition, sf::Vector2f playerVelocity)
{

	//kinematicSeek(playerPosition);
	//kinematicArrive(playerPosition);

	if (m_behaviour == 1)
	{
		pursue(playerPosition, playerVelocity);
	}

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);
	m_label.setPosition(m_sprite.getPosition().x - 50, m_sprite.getPosition().y - 130);

}


void Pursue::render(sf::RenderWindow & window)
{

	window.draw(m_sprite);
	window.draw(m_label);
}