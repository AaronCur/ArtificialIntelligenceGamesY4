#include "Game.h"

/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(1920, 1080), "AI Lab1", sf::Style::Default)
{
	m_player = new Player();
	m_enemy = new Enemy();
}

/// <summary>
/// 
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = clock.restart();

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
		}

		render();
	}
}

/// <summary>
/// 
/// </summary>
void Game::update(sf::Int32 dt)
{
	m_player->update();
	m_enemy->update();
}

/// <summary>
/// 
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_player->render(m_window);
	m_enemy->render(m_window);
	m_window.display();
}