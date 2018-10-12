#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Enemy.h"

class Flee : public Enemy
{
public:
	Flee();
	~Flee();
	void kinematicFlee(sf::Vector2f playerPosition);
	float getNewOrientation(float currentOrientation, float velocity);
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
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	//sf::Text m_label;
	sf::Font m_font;

	int id = 2;
};

