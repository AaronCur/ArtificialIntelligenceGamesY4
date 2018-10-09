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
	void pursue(sf::Vector2f playerPosition, sf::Vector2f playerVelocity);
	void respawn(float x, float y);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPosition, sf::Vector2f playerVelocityr);
	void render(sf::RenderWindow & window);

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
};


