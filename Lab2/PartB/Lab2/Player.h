#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <math.h>
#include  <cmath>
#include <iostream>

class Player
{
public:
	Player();
	~Player();

	float getNewOrientation(float m_rotation, float m_speed);
	void speedUp();
	void speedDown();
	void increaseRotation();
	void decreaseRotation();
	void respawn(float x, float y);
	void update(double dt);
	void render(sf::RenderWindow &window);

private:
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;

	float  DEG_TO_RAD;
	float m_maxSpeed;
	float m_rotation;
	sf::Vector2f m_heading;
	float m_speed;

};