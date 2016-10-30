#ifndef __CLEVEL_H
#define __CLEVEL_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <yaml-cpp/yaml.h>

#include "../inc/CRectangle.h"

class CLevel
{
	private:
		
		std::string m_szName;
		
		// Keep the x coordonate of zones where we lock the scrolling
		std::vector<float> m_lockZones;
		
		// Array of foes.
		std::vector<CRectangle *> m_pArrayFoes;
		
		// Where the player walk
		sf::Texture *m_pTPath;
		sf::Sprite m_path;
		// Sprite a the front.
		sf::Texture *m_pTFore;
		sf::Sprite m_foreground;
		// Sprite a the back.
		sf::Texture *m_pTBack;
		sf::Sprite m_background;
		
		float m_sizeLevel;
		float m_depth;
		
		// music ?
		
		float m_difficulty;
		
	public:
	
		CLevel(std::string _num);
		~CLevel(void);
		
		void update(float dt, float wWidth, float wHeight, float moveSpeed);
		void draw(sf::RenderWindow *window);
	
	private:
	
		size_t *foesInScreen(void);
};

#endif
