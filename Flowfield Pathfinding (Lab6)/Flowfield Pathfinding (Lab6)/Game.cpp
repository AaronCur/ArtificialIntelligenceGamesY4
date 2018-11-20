#include "Game.h"
#include <limits>
#include <list>
#include <queue>

/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(2000, 2000), "AI Lab6", sf::Style::Default)
{

	if (!m_font.loadFromFile("ARLRDBD.ttf"))
	{
		// error...
	}


	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[j][i] = new Tile(x + 10, y + 10, m_tileSize, m_tileScale, j, i, m_font);
			x = x + m_tileSize * m_tileScale;
		}

		x = 0;
		y = y + m_tileSize * m_tileScale;
	}

	for (int i = 0; i < m_gridSize; i++)
	{

		m_tileGrid[0][i]->setCurrentState(OBSTACLE);
		m_tileGrid[i][0]->setCurrentState(OBSTACLE);
		m_tileGrid[m_gridSize - 1][i]->setCurrentState(OBSTACLE);
		m_tileGrid[i][m_gridSize - 1]->setCurrentState(OBSTACLE);
	}

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
		processEvents();
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
			update();
		}

		render();
	}
}
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();

		}
		processGameEvents(event);
	}
}
void Game::processGameEvents(sf::Event& event)
{

	//mouse.getPosition();
	m_mousePos = sf::Mouse::getPosition(m_window);

	
	//std::cout << "Current State :" << m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() << std::endl;
	if (m_mousePos.x > 0 && m_mousePos.x < m_window.getSize().x
		&& m_mousePos.y > 0 && m_mousePos.y < m_window.getSize().y)
		{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_leftPress == false)
		{
			m_tilePosX = static_cast<int>(m_mousePos.x / (m_tileSize * m_tileScale));
			m_tilePosY = static_cast<int>(m_mousePos.y / (m_tileSize * m_tileScale));


			if (m_startTile != NULL)
			{
				m_startTile->setCurrentState(NONE);
			}

			m_startTile = m_tileGrid[m_tilePosX][m_tilePosY];

			m_tileGrid[m_tilePosX][m_tilePosY]->setCurrentState(START);

			m_leftPress = true;

		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_leftPress = false;
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_rightPress == false)
		{
			m_tilePosX = static_cast<int>(m_mousePos.x / (m_tileSize * m_tileScale));
			m_tilePosY = static_cast<int>(m_mousePos.y / (m_tileSize * m_tileScale));


			if (m_goalTile != NULL)
			{
				m_goalTile->setCurrentState(NONE);
			}

			if (m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() != OBSTACLE)
			{
				m_goalTile = m_tileGrid[m_tilePosX][m_tilePosY];

				m_tileGrid[m_tilePosX][m_tilePosY]->setCurrentState(GOAL);

				m_rightPress = true;

				initGrid(m_tilePosX, m_tilePosY);
			}
			
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			m_rightPress = false;
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			m_tilePosX = static_cast<int>(m_mousePos.x / (m_tileSize * m_tileScale));
			m_tilePosY = static_cast<int>(m_mousePos.y / (m_tileSize * m_tileScale));


			if (m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() == NONE)
			{
				m_tileGrid[m_tilePosX][m_tilePosY]->setCurrentState(OBSTACLE);
			}



		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			
			reset();

		}
	}

	
}

void Game::reset()
{


	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[j][i]->setCost(0);
			m_tileGrid[j][i]->setCurrentState(NONE);
			
		}

	}

	for (int i = 0; i < m_gridSize; i++)
	{

		m_tileGrid[0][i]->setCurrentState(OBSTACLE);
		m_tileGrid[i][0]->setCurrentState(OBSTACLE);
		m_tileGrid[m_gridSize - 1][i]->setCurrentState(OBSTACLE);
		m_tileGrid[i][m_gridSize - 1]->setCurrentState(OBSTACLE);
	}
}

/// <summary>
/// 
/// </summary>
void Game::update()
{
	

	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[i][j]->update();
		}

	}
}
void Game::initGrid(int posX, int posY)
{
	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			if (m_tileGrid[i][j]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[i][j]->setCost(std::numeric_limits<int>::max());
			}
		}

	}

	std::list<Tile> tileQueue;

	
	tileQueue.push_back(*m_tileGrid[posX][posY]);

	m_tileGrid[posX][posY]->setCost(0);
	int i = 0;

			auto iter = tileQueue.begin();
			
			//for (; iter != endIter; iter++) {
			while (tileQueue.size() != 0) {
				i++;
				std::cout << i << std::endl;
				if (iter->m_yPos != 0 && m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->getCost()== 0 && m_tileGrid[iter->m_xPos][iter->m_yPos -1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setCost( m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setRotation(90);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos - 1]);
				}
			
				/*if( iter->m_xPos != m_gridSize - 1 && iter->m_yPos != 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setRotation(112.5);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]);
				}*/
				if (iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos ]->setRotation(180);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos]);
				}
				/*if (iter->m_xPos != m_gridSize - 1 && iter->m_yPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setRotation(202.5);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]);
				}*/
				if ( iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos ][iter->m_yPos + 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setRotation(270);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos + 1]);
				}
				/*if (iter->m_yPos != m_gridSize - 1 && iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->getCurrentState()!= GOAL)
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setRotation(292.5);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]);
				}*/
				if (iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setRotation(0);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos]);
				}
				if (iter->m_yPos != 0 && iter->m_xPos !=0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setRotation(22.5);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]);
				}
				
				//tileQueue.remove(*iter);
				iter++;
				tileQueue.pop_front();
			}
	
}


/// <summary>
/// 
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[i][j]->render(m_window);
		}

	}
	m_window.display();
}