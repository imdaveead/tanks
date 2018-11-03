#pragma once
#include "pch.h"
#include "LoadingScene.h"

#include "Scene.h"
#include "GameScene.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Constants.h"
#include <Windows.h>
#include <fstream>
#include <deque>
#include <iostream>
#include <filesystem>

bool loadingThreadComplete = false;

namespace {
	void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}
	bool replace(std::string& str, const std::string& from, const std::string& to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}
}

DWORD WINAPI resourceLoaderThread(LPVOID lpParameter) {
	// Load up all resources
	std::string root = getRootFolder();

	#pragma warning(disable : 4996) // This is deprecated, not sure what else to use for now.
	for (std::tr2::sys::recursive_directory_iterator i(root), end; i != end; ++i) {
	#pragma warning(default : 4996) 

		if (!is_directory(i->path())) {

			std::string name = i->path().string().substr(root.length());

			replaceAll(name, "\\", "/");

			if (replace(name, "texture/", "")) {
				loadTexture(name.substr(0, name.length() - 4));
			}
			if (replace(name, "audio/", "")) {
				loadSound(name.substr(0, name.length() - 4));
			}
		}
	}

	if (true) {
		Sleep(1000); // >:)
	}

	loadingThreadComplete = true;
	resourcesLoaded = true;

	return 0;
}


// Load the proggy font, init the resource loader thread
// and choose a loading line.
LoadingScene::LoadingScene() {
	
	loadFont("clean");

	std::deque<std::string> loadingLines;
	std::ifstream fin("../res/tips.txt");
	std::string line;
	while (std::getline(fin, line)) {
		loadingLines.push_back(line);
	}

	int randomIndex = rand() % loadingLines.size();
	this->loadingLine = loadingLines[randomIndex];
	
	this->fadetop_opacity = 0;

	DWORD threadID;
	HANDLE hand = CreateThread(0, 0, resourceLoaderThread, 0, 0, &threadID);
}

void LoadingScene::update() {
	if (loadingThreadComplete) {
			if (this->fadetop_opacity < 255) {
				this->fadetop_opacity += 20;
			} else {
				currentScene = new GameScene();
			}
	}

	SYSTEMTIME st;
	GetSystemTime(&st);
	time = st.wMilliseconds + st.wSecond * 1000 + st.wMinute * 60000;
}

void LoadingScene::render(sf::RenderTarget* g) {
	sf::RectangleShape rs;
	rs.setFillColor(sf::Color(20,20,20));
	rs.setPosition(0, 0);
	rs.setSize(sf::Vector2f(1280, 720));

	
	sf::Text splashtext;
	splashtext.setFont(getFont("clean"));
	splashtext.setString("Loading...");
	splashtext.setPosition(g->getSize().x / 2, g->getSize().y / 2 + sin(time / 300.0f) * 15);
	splashtext.setCharacterSize(96);
	splashtext.setOrigin(splashtext.getLocalBounds().width / 2, splashtext.getLocalBounds().height);
	splashtext.setFillColor(sf::Color::White);

	sf::Text loadingline;
	loadingline.setFont(getFont("clean"));
	loadingline.setString(this->loadingLine);
	loadingline.setPosition(32, g->getSize().y - 32);
	loadingline.setCharacterSize(24);
	loadingline.setOrigin(0, 24);
	loadingline.setFillColor(sf::Color::White);

	sf::Text date;
	date.setFont(getFont("clean"));
	date.setString("Built on 2018-11-02");
	date.setCharacterSize(24);
	date.setOrigin(200, 24);
	date.setPosition(g->getSize().x - 32, g->getSize().y - 32);
	date.setFillColor(sf::Color::White);

	g->draw(rs);
	g->draw(splashtext);
	g->draw(loadingline);
	g->draw(date);

	if (loadingThreadComplete) {
		sf::RectangleShape fadetop;
		fadetop.setFillColor(sf::Color(30, 30, 30, this->fadetop_opacity));
		fadetop.setPosition(0, 0);
		fadetop.setSize(sf::Vector2f(1280, 720));

		g->draw(fadetop);
	}
}