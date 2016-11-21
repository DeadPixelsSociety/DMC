#ifndef __CHUD_HPP
#define __CHUD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "CLevel.hpp"
#include "CPlayer.hpp"

class CHud
{
	private :
	
		sf::Font m_font;
		sf::Text m_text;
	
	public :
	
		CHud(std::string fontPath, float charSize, sf::Vector2f posText);
		~CHud();
		
		std::string printFps(sf::Time frameTime);
		std::string printPosition(CPlayer &player);
		std::string printNbrFoesInScreen(sf::Vector2u wDim, sf::Vector2f centerView, CLevel &lvl);
		std::string printNextLockZone(std::queue<float> lockZones);
		
		void update(sf::RenderWindow &window, sf::Time frameTime, CPlayer &player, CLevel &lvl);
		void draw(sf::RenderWindow &window);
};

#endif //__CHUD_HPP
