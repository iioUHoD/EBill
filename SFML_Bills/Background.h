#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
class Background
{
private:
	sf::Sprite  bgsprite;
	sf::Texture bgtexture;

	/*private function*/

public:
	Background(sf::Texture*& texture);
	virtual ~Background();
	/*FUNCTIONS*/

	void update();
	void render(sf::RenderTarget& target);

};