#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class Player
{
public:
	Player();
	~Player();

	void respawn(float x, float y);
	void update();
	void render(sf::RenderWindow &window);

private:
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;

};