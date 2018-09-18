#include "Player.h"

class Game
{
public:
	Game();
	~Game();


private:
	sf::Time m_cumulativeTime;//the time 
	Player m_player;
	sf::RenderWindow m_window;

};
