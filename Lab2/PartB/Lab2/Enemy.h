#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Enemy
{
public:
	Enemy();
	~Enemy();
	void respawn(float x, float y);
	float getRandom(int x, int y);
	void update();
	void render(sf::RenderWindow & window);

private:
	sf::Vector2f m_position;
	float m_orientation;
	sf::Vector2f m_velocity;
	flaot m_rotation;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
};


