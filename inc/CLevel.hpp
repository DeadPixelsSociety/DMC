#ifndef __CLEVEL_HPP
#define __CLEVEL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include <yaml-cpp/yaml.h>

#include "CFoe.hpp"
#include "CPlayer.hpp"

class CLevel
{
	private:
		
		std::string m_szName;
		
		// Keep the x coordonate of zones where we lock the scrolling.
		std::queue<float> m_lockZones;
		
		// Array of foes within the level.
		std::vector<CFoe *> m_arrayFoes;
		
		// Where the player walk.
		sf::Texture *m_pTPath;
		sf::Sprite m_path;
		// Sprite a the front.
		sf::Texture *m_pTFore;
		sf::Sprite m_foreground;
		sf::View m_viewFore;
		float m_veloFore;
		// Sprite a the back.
		sf::Texture *m_pTBack;
		sf::Sprite m_background;
		float m_veloBack;
		sf::View m_viewBack;
		
		float m_length;
		float m_depth;
		
		// music ?
		
		float m_difficulty;
		
	public:
	
		CLevel(std::string _num, sf::Vector2f wDim);
		~CLevel(void);
		
		/* Getters and setters */
		float getLength(void);
		float getDepth(void);
		std::queue<float> getLockZones(void);
		
		/* Fill a vector with indexs of all the foes visibled in the view. */
		void  foesInScreen(sf::Vector2u wDim, sf::Vector2f centerView, std::vector<size_t> *foesVisibles);
		/* Slice the visibles foes if they are in front of the player of behind him. */
		void  foesInOrder(float playerPosY, std::vector<size_t> *foesVisibles, std::vector<size_t> *foesFront, std::vector<size_t> *foesBack);
		
		/* Update entity present in the level. */
		void  update(sf::Time dt, sf::RenderWindow &window, CPlayer &player);
		/* Draw all the drawable entitys inside the level. */
		void  draw(sf::RenderWindow &window, CPlayer &player);
	
	private:
};

#endif //__CLEVEL_HPP
