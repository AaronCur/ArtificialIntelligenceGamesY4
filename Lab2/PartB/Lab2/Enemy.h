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
	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::CircleShape shape;
};


