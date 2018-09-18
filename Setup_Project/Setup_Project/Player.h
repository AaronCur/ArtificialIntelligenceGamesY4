#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class Player
{
public:
	Player();
	~Player();

	void respawn(float x, float y);
	void update(float x, float y);
	void render(sf::RenderWindow &window);

private:
	sf::CircleShape shape;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;

};