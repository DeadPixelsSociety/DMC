#ifndef __CHUD_HPP
#define __CHUD_HPP

#include <SFML/Graphics.hpp>
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
		
		/* Print the fps of the game. */
		std::string printFps(sf::Time frameTime);
		/* Print the position of the player. */
		std::string printPosition(CPlayer &player);
		/* Print the number of foes in the screen. */
		std::string printNbrFoesInScreen(sf::Vector2u wDim, sf::Vector2f centerView, CLevel &lvl);
		/* Print the x coordonate of the next lock zone. */
		std::string printNextLockZone(std::queue<float> lockZones);
		
		/* Update the the informations to display. */
		void update(sf::RenderWindow &window, sf::Time frameTime, CPlayer &player, CLevel &lvl);
		/* Display the informations to the screen. */
		void draw(sf::RenderWindow &window);
};

#endif //__CHUD_HPP
