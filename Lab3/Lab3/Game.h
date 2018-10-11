#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Pursue.h"
#include "Arrive.h"

class Game
{
public:
	Game();
	void run();

private:
	void update(double dt);
	void render();

protected:
	sf::RenderWindow m_window;
	Player* m_player;

	//Enemy* m_pursue;

	std::vector<Enemy*> enemies;
	
};
#endif // !GAME_H