// DaveTanks.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h" // required
#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "LoadingScene.h"
#include "SceneHandling.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Dave's Tanks", sf::Style::Close);

int main() {
	// Randomize the random number generator.
	srand(time(nullptr));

	// Set initial scene
	currentScene = new LoadingScene();

	const float FPS = 60.0f; //The desired FPS. (The number of updates each second).
	bool redraw = true;      //Do I redraw everything on the screen?
	sf::Clock clock;
	sf::Event ev;

	while (window.isOpen()) {
		//Wait until 1/60th of a second has passed, then update everything.
		if (clock.getElapsedTime().asSeconds() >= 1.0f / FPS) {
			redraw = true; //We're ready to redraw everything
		} else {
			//Sleep until next 1/60th of a second comes around
			sf::Time sleepTime = sf::seconds((1.0f / FPS) - clock.getElapsedTime().asSeconds());
			sleep(sleepTime);
		}
		// Poll Events
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) window.close();
		}

		window.clear();

		currentScene->render(&window);

		window.display();
	}

	return 0;
}
