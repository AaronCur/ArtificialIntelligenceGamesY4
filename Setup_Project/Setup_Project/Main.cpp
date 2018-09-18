#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(2000, 1000), "SFML works!");
	sf::CircleShape shape(100.f);
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	

	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// left key is pressed: move our character
			m_velocity.x = m_velocity.x + 0.002;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// left key is pressed: move our character
			m_velocity.x = m_velocity.x - 0.002;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// left key is pressed: move our character
			m_velocity.y = m_velocity.y - 0.002;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// left key is pressed: move our character
			m_velocity.y = m_velocity.y + 0.002;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			// left key is pressed: move our character
			m_velocity.x = 0;
			m_velocity.y = 0;
		}


		if (shape.getPosition().y >= 1000 + 100)
		{
			m_position.y = -200;
		}
		
		else if (shape.getPosition().y < -200)
		{
			m_position.y = 1100;
		}
		else if (shape.getPosition().x < -200)
		{
			m_position.x = 2100;
		}
		else if (shape.getPosition().x >= 2100)
		{
			m_position.x = -200;
		}

		m_position = m_position + m_velocity;

		shape.setPosition(m_position);
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
