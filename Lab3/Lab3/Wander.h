#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
class Wander 
{
public:
	Wander();
	~Wander();
	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicWander(sf::Vector2f playerPosition);
	void respawn(float x, float y);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPostion, sf::Vector2f playerVelocity);
	void render(sf::RenderWindow & window);

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
};


