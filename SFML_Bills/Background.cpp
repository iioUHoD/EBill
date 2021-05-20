#include "Background.h"



Background::Background(sf::Texture*& texture)
{
	this->bgsprite.setTexture(*texture);
	this->bgsprite.setPosition(sf::Vector2f(0.0f, 0.0f));
}

Background:: ~Background()
{

}

void Background::update()
{

}

void Background::render(sf::RenderTarget& target)
{
	target.draw(this->bgsprite);

}
