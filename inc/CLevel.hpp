#ifndef __CLEVEL_HPP
#define __CLEVEL_HPP

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include <yaml-cpp/yaml.h>

#include "../inc/CFoe.hpp"

class CLevel
{
	private:
		
		std::string m_szName;
		
		// Keep the x coordonate of zones where we lock the scrolling
		std::vector<float> m_lockZones;
		
		// Array of foes.
		std::vector<CFoe *> m_pArrayFoes;
		
		// Where the player walk
		sf::Texture *m_pTPath;
		sf::Sprite m_path;
		// Sprite a the front.
		sf::Texture *m_pTFore;
		sf::Sprite m_foreground;
		// Sprite a the back.
		sf::Texture *m_pTBack;
		sf::Sprite m_background;
		
		float m_length;
		float m_depth;
		
		// music ?
		
		float m_difficulty;
		
	public:
	
		CLevel(std::string _num);
		~CLevel(void);
		
		float getLength(void);
		float getDepth(void);
		void  foesInScreen(sf::Vector2u wDim, sf::Vector2f centerView, std::vector<size_t> *foesVisibles);
		std::string nbrFoesInScreen(sf::Vector2u wDim, sf::Vector2f centerView);
		void  update(float dt, sf::Vector2f wDim);
		void  draw(sf::RenderWindow &window, sf::View viewPlayer);
	
	private:
};

#endif //__CLEVEL_HPP
