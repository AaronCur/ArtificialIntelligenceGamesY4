#include "Game.h"
#include <limits>
#include <list>
#include <queue>

/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(3000, 2000), "AI Lab6", sf::Style::Default)
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

	m_button = new Button(m_font, "Reset", 2000, 100);
	m_vecButton = new Button(m_font, "Vector", 2000, 400);
	m_costButton = new Button(m_font, "Cost", 2000, 700);
	m_clearButton = new Button(m_font, "Clear", 2000, 1000);

	m_startText.setCharacterSize(50);
	m_startText.setFont(m_font);
	m_startText.setString("Left Click a Tile to Place Starting Tile");
	m_startText.setFillColor(sf::Color::Black);
	m_startText.setPosition(2100, 1275);

	m_goalText.setCharacterSize(50);
	m_goalText.setFont(m_font);
	m_goalText.setString("Right Click to Place Goal Tile");
	m_goalText.setFillColor(sf::Color::Black);
	m_goalText.setPosition(2100, 1375);

	m_obstacleText.setCharacterSize(50);
	m_obstacleText.setFont(m_font);
	m_obstacleText.setString("Middle Click to Place Obstacle Tile");
	m_obstacleText.setFillColor(sf::Color::Black);
	m_obstacleText.setPosition(2100, 1475);

	m_pathText.setCharacterSize(50);
	m_pathText.setFont(m_font);
	m_pathText.setString("Path from Start to Goal");
	m_pathText.setFillColor(sf::Color::Black);
	m_pathText.setPosition(2100, 1575);

	m_startRec.setSize(sf::Vector2f(70, 70));
	m_startRec.setOutlineThickness(2);
	m_startRec.setOutlineColor(sf::Color::Black);
	m_startRec.setPosition(2000, 1275);
	m_startRec.setFillColor(sf::Color::Green);

	m_goalRec.setSize(sf::Vector2f(70, 70));
	m_goalRec.setOutlineThickness(2);
	m_goalRec.setOutlineColor(sf::Color::Black);
	m_goalRec.setPosition(2000, 1375);
	m_goalRec.setFillColor(sf::Color::Red);

	m_obstacleRec.setSize(sf::Vector2f(70, 70));
	m_obstacleRec.setOutlineThickness(2);
	m_obstacleRec.setOutlineColor(sf::Color::Black);
	m_obstacleRec.setPosition(2000, 1475);
	m_obstacleRec.setFillColor(sf::Color(40,40,40));

	m_pathRec.setSize(sf::Vector2f(70, 70));
	m_pathRec.setOutlineThickness(2);
	m_pathRec.setOutlineColor(sf::Color::Black);
	m_pathRec.setPosition(2000, 1575);
	m_pathRec.setFillColor(sf::Color(50, 255, 255));




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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) )
	{
		m_button->mouseDetection(m_mousePos);
		m_costButton->mouseDetection(m_mousePos);
		m_clearButton->mouseDetection(m_mousePos);
		m_vecButton->mouseDetection(m_mousePos);

		if (m_button->selected == true)
		{
				reset();

		}
		if (m_costButton->selected == true)
		{
			for (int i = 0; i < m_gridSize; i++)
			{
				for (int j = 0; j < m_gridSize; j++)
				{
					m_tileGrid[j][i]->setDrawState(COST);

				}

			}
			m_costButton->selected = false;

		}
		if (m_vecButton->selected == true)
		{
			for (int i = 0; i < m_gridSize; i++)
			{
				for (int j = 0; j < m_gridSize; j++)
				{
					m_tileGrid[j][i]->setDrawState(FLOW);

				}

			}
			m_vecButton->selected = false;

		}
		if (m_clearButton->selected == true)
		{
			for (int i = 0; i < m_gridSize; i++)
			{
				for (int j = 0; j < m_gridSize; j++)
				{
					m_tileGrid[j][i]->setDrawState(CLEAR);

				}

			}
			m_clearButton->selected = false;

		}

	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) == false))
	{
		m_button->selected = false;

	}

	//std::cout << "Current State :" << m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() << std::endl;
	if (m_mousePos.x > 0 && m_mousePos.x < m_window.getSize().x
		&& m_mousePos.y > 0 && m_mousePos.y < m_window.getSize().y
		&& m_mousePos.x < (m_gridSize * (m_tileSize * m_tileScale)) + 10)
		{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_leftPress == false )
		{
			m_tilePosX = static_cast<int>(m_mousePos.x / (m_tileSize * m_tileScale));
			m_tilePosY = static_cast<int>(m_mousePos.y / (m_tileSize * m_tileScale));


			if (m_startTile != NULL)
			{
				m_startTile->setCurrentState(NONE);
			}

			if (m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() != OBSTACLE)
			{
				m_startTile = m_tileGrid[m_tilePosX][m_tilePosY];

				m_tileGrid[m_tilePosX][m_tilePosY]->setCurrentState(START);

				//getPath(m_tilePosX, m_tilePosY);
				m_leftPress = true;
			}

		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_leftPress = false;
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_rightPress == false && m_startTile != NULL)
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


	}

	
}

void Game::reset()
{

	m_startTile = NULL;
	m_goalTile = NULL;

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

	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			if (m_tileGrid[i][j]->getCurrentState() == NONE)
			{
				m_tileGrid[i][j]->setCost(0);
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
			
				if (iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos ]->setRotation(180);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos]);
				}
			
				if ( iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos ][iter->m_yPos + 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setRotation(270);
					m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos + 1]);
				}
				
				if (iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setRotation(0);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos]);
				}
				
				if (iter->m_yPos != 0 && m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->getCost() == 0 && m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setRotation(90);
					m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos - 1]);
				}
				if (iter->m_xPos != m_gridSize - 1 && iter->m_yPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setRotation(202.5);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]);
				}
				if (iter->m_yPos != m_gridSize - 1 && iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setRotation(292.5);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]);
				}
				if (iter->m_yPos != 0 && iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setRotation(45);
					m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]);
				}
				if (iter->m_xPos != m_gridSize - 1 && iter->m_yPos != 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->getCurrentState() != GOAL)
				{
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setRotation(112.5);
					m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
					tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]);
				}
				
				//tileQueue.remove(*iter);
				iter++;
				tileQueue.pop_front();
			}


			getPath(*m_startTile);

	
}
void Game::getPath(Tile m_startTile)
{


	std::list<Tile> tileQueue;


	tileQueue.push_back(m_startTile);

	//m_tileGrid[posX][posY]->setCost(0);
	//int i = 0;

	auto iter = tileQueue.begin();

	//for (; iter != endIter; iter++) {
	while (iter->m_cost !=0 && m_tileGrid[iter->m_previous.first][iter->m_previous.second]->getCurrentState() != GOAL) {

		
		m_tileGrid[iter->m_previous.first][iter->m_previous.second]->setCurrentState(PATH);
		tileQueue.push_back(*m_tileGrid[iter->m_previous.first][iter->m_previous.second]);

			//tileQueue.remove(*iter);
		iter++;
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
	m_button->render(m_window);
	m_costButton->render(m_window);
	m_vecButton->render(m_window);
	m_clearButton->render(m_window);
	m_window.draw(m_goalRec);
	m_window.draw(m_startRec);
	m_window.draw(m_goalText);
	m_window.draw(m_startText);
	m_window.draw(m_obstacleRec);
	m_window.draw(m_obstacleText);
	m_window.draw(m_pathRec);
	m_window.draw(m_pathText);
	m_window.display();
}