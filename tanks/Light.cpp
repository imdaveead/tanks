#include "pch.h"
#include "Light.h"

Light::Light(sf::Color c, int x, int y, int falloff) {
	color = c;
	startx = x;
	starty = y;
	type = GameObjectType::LightEffectType;
	this->falloff = falloff;
}
Light::~Light() {

}
void Light::update() {
	if (color.a > 4) color.a -= 4;
	else destroySelf();
}
void Light::drawSquare(int posx, int posy, float opacity) {
	if (opacity < 0) return;
	if (visitedmap[posx][posy] > opacity) return;
	visitedmap[posx][posy] = opacity;

	Maze m = getMaze();
	if (!m.wallUp(posx, posy, true)) drawSquare(posx, posy - 1, opacity - falloff);
	if (!m.wallDown(posx, posy, true)) drawSquare(posx, posy + 1, opacity - falloff);
	if (!m.wallLeft(posx, posy, true)) drawSquare(posx - 1, posy, opacity - falloff);
	if (!m.wallRight(posx, posy, true)) drawSquare(posx + 1, posy, opacity - falloff);
}
void Light::render(sf::RenderTarget* g) {
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			visitedmap[i][j] = 0;
		}
	}
	drawSquare(startx, starty, color.a);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			sf::RectangleShape rect;
			rect.setFillColor(sf::Color(color.r, color.g, color.b, visitedmap[i][j]));
			rect.setPosition(i * 60, j * 60);
			rect.setSize(sf::Vector2f(60, 60));
			g->draw(rect, sf::BlendAdd);

			rect.setFillColor(sf::Color(color.r, color.g, color.b, visitedmap[i][j] / 3));
			g->draw(rect);
		}
	}
}