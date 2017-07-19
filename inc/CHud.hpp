#ifndef __CHUD_HPP
#define __CHUD_HPP

#include <stdbool.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "CLevel.hpp"
#include "CEntity.hpp"
#include "CPlayer.hpp"

class CHud
{
	private :
	
		sf::Font m_font;
		sf::Text m_text;
		bool m_visible;
	
	public :
	
		CHud(std::string fontPath, float charSize, sf::Vector2f posText);
		~CHud();
		
		/* Indicate if the hud is visible or not. */
		void toggle();
		
		/* Print the fps of the game. */
		std::string printFps(sf::Time frameTime);
		/* Print the position of the player. */
		std::string printPosition(CPlayer &player);
		/* Print the number of foes in the screen. */
		std::string printNbrFoesInScreen(sf::Vector2u wDim, sf::Vector2f centerView, CLevel &lvl);
		/* Print the x coordonate of the next lock zone. */
		std::string printNextLockZone(std::queue<float> lockZones);
		/* Print the direction of an entity. */
		std::string printDirection(CEntity &entity);
		/* Print the distance between the x of the center of the view and the x of the center of the player. */
		std::string printDist(CPlayer &player);
		
		/* Update the the informations to display. */
		void update(sf::Time frameTime, sf::RenderWindow &window, CPlayer &player, CLevel &lvl);
		/* Display the informations to the screen. */
		void draw(sf::RenderWindow &window);
};

#endif //__CHUD_HPP
