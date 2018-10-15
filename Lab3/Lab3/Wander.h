#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Enemy.h"

class Wander : public Enemy
{
public:
	Wander();
	~Wander();
	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicWander(sf::Vector2f playerPosition);
	void respawn(float x, float y);
	float getRandom(int x, int y);
	void kinematicFlee(sf::Vector2f playerPosition);
	void collisionAvoidance(std::vector<Enemy*> enemies);
	void update(sf::Vector2f playerPostion, sf::Vector2f playerVelocity);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	int getId();

private:
	sf::Vector2f m_position;
	float m_orientation;
	sf::Vector2f m_velocity;
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Font m_font;

	int id = 5;

	sf::Vector2f m_direction;
	float m_distance;
	sf::Text m_label;
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


