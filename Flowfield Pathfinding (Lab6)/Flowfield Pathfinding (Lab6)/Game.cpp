#include "Game.h"
#include <limits>
#include <list>
#include <queue>

/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(500, 500), "AI Lab6", sf::Style::Default)
{
	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[j][i] = new Tile(x, y, m_tileSize, m_tileScale, j, i);
			x = x + m_tileSize * m_tileScale;
		}

		x = 0;
		y = y + m_tileSize * m_tileScale;
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
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
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

	std::cout << m_mousePos.x << std::endl;
	
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

			m_goalTile = m_tileGrid[m_tilePosX][m_tilePosY];

			m_tileGrid[m_tilePosX][m_tilePosY]->setCurrentState(GOAL);

			m_rightPress = true;

			initGrid(*m_goalTile);

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
	}

	
}

/// <summary>
/// 
/// </summary>
void Game::update(double dt)
{
	

	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
		//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_leftPress == false)
		//	{
		//		m_leftPress = true;
		//		/*if (m_startTile != NULL)
		//		{
		//			m_startTile->setCurrentState(NONE);
		//		}*/

		//		m_startTile = m_tileGrid[i][j];
		//		m_tileGrid[i][j]->mouseDetection(m_mousePos, 1);
		//		m_tileGrid[i][j]->setCurrentState(START);

		//		

		//	}
		//	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
		//	{
		//		m_leftPress = false;
		//	}


		//	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		//	{

		//		m_tileGrid[i][j]->mouseDetection(m_mousePos, 2);

		//	}
		
			m_tileGrid[i][j]->update();
		}

	}
}
void Game::initGrid(Tile m_goalTile)
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

	
	tileQueue.push_back(m_goalTile);

	m_goalTile.setCost(0);

	// loop through the queue while there are nodes in it.
		while (tileQueue.size() != 0) {

			m_goalTile = tileQueue.front();
			//tileQueue.pop_front();

			auto iter = tileQueue.front();
			auto endIter = tileQueue.back();

			//for (; iter != endIter; iter++) {
			for (auto iter = tileQueue.begin(); iter != tileQueue.end(); ++iter){
				
				if (iter->m_yPos != 0 && m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->m_cost == 0 )
				{
					m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setCost( m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos - 1]);
				}
			
				if ( iter->m_xPos != m_gridSize && iter->m_yPos != 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->m_cost == 0)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]);
				}
				if (iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->m_cost == 0)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos]);
				}
				if (iter->m_xPos != m_gridSize - 1 && iter->m_yPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->m_cost == 0)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]);
				}
				if ( iter->m_yPos != 0 && m_gridSize && m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->m_cost == 0 )
				{
					m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos + 1]);
				}
				if (iter->m_yPos != m_gridSize - 1 && iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->m_cost == 0 )
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]);
				}
				if (iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->m_cost == 0 )
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos]);
				}
				if (iter->m_yPos != 0 && iter->m_xPos !=0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->m_cost == 0 )
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]);
				}
				
				//tileQueue.remove(*iter);
			}

			// dequeue the current node.
			tileQueue.pop_back();
			//tileQueue.pop_back();
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