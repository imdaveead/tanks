#pragma once
#include "Scene.h"
#include "Player.h"

class TankChooseMenuScene : public Scene {
private:
	bool player1 = false;
	bool player2 = false;
	bool player3 = false;
	bool player4 = false;

	Player playerDummy1;
	Player playerDummy2;
	Player playerDummy3;
	Player playerDummy4;

	int timeOut = 0;

	std::string endAction;
	std::string title;

	float yOffset;
	float fadeOffset;

	bool closing = false;

	Scene* ms;
	Scene* gamescene;
	int transition_gamescene = 0;
public:
	TankChooseMenuScene(std::string endActionStr, std::string titleText, float yOffset = 0);
	virtual ~TankChooseMenuScene();

	void render(sf::RenderTarget* g);
	void update();

	virtual void event_onKeyPress(sf::Event::KeyEvent event);
	virtual void event_onKeyRelease(sf::Event::KeyEvent event);
};

