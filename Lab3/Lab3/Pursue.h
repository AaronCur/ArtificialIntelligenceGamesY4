#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Enemy.h"

class Pursue : public Enemy
{
public:
	Pursue();
	~Pursue();
	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicSeek(sf::Vector2f playerPosition);
	void kinematicArrive(sf::Vector2f playerPosition);
	void kinematicFlee(sf::Vector2f enemyPosition);
	void pursue(sf::Vector2f playerPosition, sf::Vector2f playerVelocity);
	void collisionAvoidance(std::vector<Enemy*> enemies);
	void respawn(float x, float y);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPosition, sf::Vector2f playerVelocity);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	int getId();

private:
	float m_timeToTarget;
	sf::Vector2f m_position;
	float m_orientation;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	sf::Vector2f m_targetPos;
	float m_speed;
	float m_timePrediction;
	float m_maxTimePrediction;
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	float m_distance;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Text m_label;
	sf::Font m_font;

	int id = 3;
	sf::Vector2f m_relVelocity;
	sf::Vector2f m_relPosition;
	float m_relSpeed;
	float m_timeToCollision;
	float m_minSeperation;
	float m_shortestTime;
	float m_radius;
	sf::Vector2f m_firstTarget;
	float m_firstMinSeperation;
	float m_firstDistance;
	sf::Vector2f m_firstRelativePos;
	sf::Vector2f m_firstRelativeVel;

	float m_threshold;
	int m_behaviour;
};


