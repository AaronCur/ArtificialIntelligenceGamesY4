#include <SFML/Graphics.hpp>

#include "SFML/Audio.hpp"
#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

Game::Game() :
	m_window(sf::VideoMode(1920, 1080, 32), "ProjectO.R.B")
{
	

}

Game::~Game()
{
	
}


/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);


	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}

// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		event.type == sf::Event::KeyPressed;
		//To check for the Akeypress to transition from splash screen to main menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_currentGameState == GameState::Splash)
		{
			m_splashScreen->checkButtonPress();
		}
		if (m_mainMenu->close)
		{
			m_window.close();
		}
		///sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
	}

}



/// <summary>
/// sets the current game state 
/// </summary>
/// <param name="gameState"></param>
void Game::setGameState(GameState gameState)
{
	m_currentGameState = gameState;
}

/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
//{
//sf::Event event;
//while (m_window.pollEvent(event))
//{
//if (event.type == sf::Event::Closed)
//{
//	m_window.close();
//}
//event.type == sf::Event::KeyPressed;
//To check for the Akeypress to transition from splash screen to main menu
//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || controller->m_currentState.A == true && m_currentGameState == GameState::License)
//  {
//	m_splashScreen->checkButtonPress();
//}
//if (m_mainMenu->close)
//{
//	m_window.close();
//}
//sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
//}


//
/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(sf::Time time)
{
	switch (m_currentGameState)
	{
	case GameState::None:
		//	m_splashScreen->print(time);
		std::cout << "no GameState" << std::endl;
		break;
	case GameState::License:
		m_licenseScreen->update(time);
		break;
	case GameState::Splash:
		m_splashScreen->update(time);
		break;
	case GameState::MainMenu:
		m_mainMenu->update(time, *controller);
		break;
	case GameState::GameScreen:
		m_GameScreen->update(time, *controller);
		break;
	case GameState::Options:
		m_optionsScreen->update(time, *controller);
		break;
	case GameState::CoopScreen:
		m_CoopScreen->update(time, *controller);
		break;
	case GameState::Help:
		m_help->update(time, *controller);
		break;
	default:
		break;
	}

}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	switch (m_currentGameState)
	{
	case GameState::None:
		//	m_splashScreen->print(time);
		std::cout << "no GameState" << std::endl;
		break;
	case GameState::License:
		m_licenseScreen->render(m_window);
		break;
	case GameState::Splash:
		m_splashScreen->render(m_window);
		break;
	case GameState::MainMenu:
		m_mainMenu->render(m_window);
		break;
	case GameState::GameScreen:
		m_GameScreen->render(m_window);
		break;
	case GameState::CoopScreen:
		m_CoopScreen->render(m_window);
		break;
	case GameState::Options:
		m_optionsScreen->render(m_window);
		break;
	case GameState::Help:
		m_help->render(m_window);
	default:
		break;
	}
	m_window.display();
}

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
