// DaveTanks.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h" // required
#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Scene.h"
#include "LoadingScene.h"
#include "Resources.h"
#include "BackgroundScene.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Dave's Tanks", sf::Style::Close);
sf::View view;
BackgroundScene* bgs = nullptr;

void update() {
	if (resourcesLoaded) {
		// We have to create the backgroundscene after
		// all resources are loaded, or else we cant
		// get texture information about the bg.

		if (!bgs) bgs = new BackgroundScene();
		// Move BG
		bgs->update();
	
	}

	// Update current scene
	currentScene->update();
}
void render() {
	window.clear();

	if (resourcesLoaded) {
		// Apply a default view
		view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
		window.setView(view);

		// Render the background
		bgs->render(&window);
	}

	// Apply shake
	view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
	window.setView(view);

	// Draw the current scene
	currentScene->render(&window);

	window.display();
}

int main() {
	srand((unsigned int)time(NULL));

	// Set initial scene
	currentScene = new LoadingScene();

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	sf::Event ev;

	view = window.getView();
	
	while (window.isOpen()) {

		if (accumulator <= ups) goto skiploop;
		while (accumulator > ups) {
			accumulator -= ups;
			update();
		}
		render();

	skiploop:
		// Poll Events
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) window.close();
			if (ev.type == sf::Event::KeyPressed) {
				currentScene->event_onKeyPress(ev.key);
			}
			if (ev.type == sf::Event::KeyReleased) {
				currentScene->event_onKeyRelease(ev.key);
			}
		}

		accumulator += clock.restart();

	}

	return 0;
}
