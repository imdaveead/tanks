#pragma once
#include "Scene.h"
#include <string>

class LoadingScene : public Scene {
private:
	std::string loadingLine;
	int fadetop_opacity;
public:
	LoadingScene();
	
	void render(sf::RenderTarget* g);
	void update();
};

