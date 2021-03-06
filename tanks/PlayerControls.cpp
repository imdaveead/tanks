#include "pch.h"
#include "PlayerControls.h"
#include "Color.h"
#include "Utility.h"

PlayerControls makePlayerControls(int left, int right, int up, int down, int action) {
	PlayerControls c;
	c.left = left;
	c.right = right;
	c.up = up;
	c.down = down;
	c.action = action;
	return c;
}
PlayerControlsVisual makePlayerControlsVisuals(const char* left, const char* right, const char* up, const char* down, const char* action) {
	PlayerControlsVisual c;
	c.left = left;
	c.right = right;
	c.up = up;
	c.down = down;
	c.action = action;
	return c;
}

//                                                   A D W  S  SPACE
PlayerControls playerControls1 = makePlayerControls(0, 3, 22, 18, 57);
PlayerControlsVisual playerVisual1 = makePlayerControlsVisuals("A", "D", "W", "S", "Space");
//                                                   < > ^  V  RCTRL
PlayerControls playerControls2 = makePlayerControls(71, 72, 73, 74, 41);
PlayerControlsVisual playerVisual2 = makePlayerControlsVisuals("<", ">", "^", "v", "Right CTRL");
//                                                   J  L  I  K  H
PlayerControls playerControls3 = makePlayerControls(9, 11, 8, 10, 7);
PlayerControlsVisual playerVisual3 = makePlayerControlsVisuals("J", "L", "I", "K", "H");
//                                                   4  6  8  5  0
PlayerControls playerControls4 = makePlayerControls(79, 81, 83, 80, 75);
PlayerControlsVisual playerVisual4 = makePlayerControlsVisuals("4", "6", "8", "5", "0");

PlayerControls getPlayerControlsByID(const int id) {
	switch (id) {
	case 1: return playerControls1;
	case 2: return playerControls2;
	case 3: return playerControls3;
	case 4: return playerControls4;
	}
}
PlayerControlsVisual getPlayerControlsVisualByID(const int id) {
	switch (id) {
	case 1: return playerVisual1;
	case 2: return playerVisual2; 
	case 3: return playerVisual3;
	case 4: return playerVisual4;
	}
}

sf::Color player1Color = HSL(  5, 270, 255).TurnToRGB();
sf::Color player2Color = HSL( 95, 270, 255).TurnToRGB();
sf::Color player3Color = HSL(185, 270, 255).TurnToRGB();
sf::Color player4Color = HSL(275, 270, 255).TurnToRGB();

sf::Color getPlayerColorByID(const int id) {
	switch (id) {
	case 1: return player1Color;
	case 2: return player2Color;
	case 3: return player3Color;
	case 4: return player4Color;
	}
}

std::string getPlayerNameByID(const int id) {
	switch (id) {
	case 1: return "Red";
	case 2: return "Green";
	case 3: return "Blue";
	case 4: return "Purple";
	}
}