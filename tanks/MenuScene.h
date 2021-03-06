#pragma once
#include "Scene.h"
#include "Menu.h"
#include "TankChooseMenuScene.h"
#include "SFML/Graphics.hpp"

class MenuScene : public Scene {
public:
	Menu* currentMenu;
	int selected = 0;

	int width = 500;

	float yOffset = 1;
	float titleImageY = 0;
	float titleImageYO = 1;

	sf::IntRect selectBoxTarget;
	sf::IntRect selectBox;

	MenuScene* sub;
	
	int level;

	MenuScene(std::string menuID, int level = 0);
	MenuScene();
	virtual ~MenuScene();
	
	void render(sf::RenderTarget* g);
	void update();

	virtual void event_onKeyPress(sf::Event::KeyEvent event);
	virtual void event_onKeyRelease(sf::Event::KeyEvent event);

	void setMenu(Menu* newMenu, int defaultPos = 0);
	void setSubMenu(std::string newMenu);

	bool closing = false;

	TankChooseMenuScene* tcms = nullptr;
};

MenuScene* startingMenuScene();