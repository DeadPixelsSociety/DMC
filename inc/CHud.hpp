#ifndef __CHUD_HPP
#define __CHUD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class CHud
{
	private :
	
		sf::Font m_font;
		sf::Text m_text;
	
	public :
	
		CHud(std::string fontPath, float charSize, sf::Vector2f posText);
		~CHud();
		
		void update(sf::RenderWindow &window, sf::View viewPlayer, std::string infos);
		void draw(sf::RenderWindow &window);
};

#endif //__CHUD_HPP
