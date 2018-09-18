#pragma once
#include <iostream>
#include <fstream>
#include "Player.h"


class Main
{
public:
	Main();
	~Main();

	Player m_player;


private:
	sf::Time m_cumulativeTime;//the time 
	
	
};
