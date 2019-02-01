#include "Game.h"
/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(1920, 1080), "AI Lab2B", sf::Style::Default)
{
	m_player = new Player();
	m_fuzzy = new Fuzzy;
	//Enemy* m_pursue = new Pursue(*this);
	//Enemy* m_arriveFast = new Arrive(60.0f, 100.0f, 100.0f);
	Enemy* m_arriveSlow = new Arrive(150.0f, 1720.0f, 1000.0f);
	//Enemy* m_seek = new Seek();
	//Enemy* m_wander = new Wander();

	//Factory* factory = new EnemyFactory;

	/*enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());*/

	//enemies.push_back(m_pursue);
	//enemies.push_back(m_arriveFast);
	enemies.push_back(m_arriveSlow);
	//enemies.push_back(m_seek);
	//enemies.push_back(m_flee);
	//enemies.push_back(m_wander);
	
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
void Game::update(double dt)
{
	m_player->update(dt);

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(m_player->getPosition(), m_player->getVelocity());
		enemies[i]->collisionAvoidance(enemies);
	}

	//Vector player to enemy
	sf::Vector2f m_direction = enemies[0]->getPosition() - m_player->getPosition();
	double m_distance = std::sqrt(m_direction.x*m_direction.x + m_direction.y* m_direction.y);
	m_fuzzy->update(m_distance);
	//m_enemy->update(m_player->getPosition());
	//m_enemySeek->update(m_player->getPosition());

//	m_enemyFlee->update(m_player->getPosition());
	//m_enemyPursue->update(m_player->getPosition(), m_player->getVelocity());
	
}

/// <summary>
/// 
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_player->render(m_window);

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(m_window);
	}
//	m_enemyPursue->render(m_window);
	//m_enemy->render(m_window);
	//m_enemySeek->render(m_window);
	//m_enemyFlee->render(m_window);
	m_window.display();
}