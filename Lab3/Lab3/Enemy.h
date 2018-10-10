#pragma once 
#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy() {}
	virtual ~Enemy() {}
	virtual void render(sf::RenderWindow & window) = 0;
	virtual void update(sf::Vector2f playerPosition, sf::Vector2f playerVelocity) = 0;
	virtual sf::Vector2f getVelocity() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual int getId() = 0;


};

//class Factory {
//public:
//	virtual Enemy* CreatePursue() = 0;
//	//virtual Enemy* CreateSeek() = 0;
//	//virtual Enemy* CreateArrive() = 0;
//	//virtual Enemy* CreateWander() = 0;*/
//	//virtual Enemy* CreateFlee() = 0;
//};
//
//class EnemyFactory : public Factory {
//public:
//	Enemy * CreatePursue() {
//		return new Pursue;
//	}
//};