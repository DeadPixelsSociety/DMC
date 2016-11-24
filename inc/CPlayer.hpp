#ifndef __CPLAYER_HPP
#define __CPLAYER_HPP

#include <cmath> // abs() in updateView()

#include "CCharacter.hpp"

class CPlayer : public CCharacter
{
	private :
	
		std::string m_szName;
		sf::View m_view;
		
		bool m_isBlocked;

	public :
		CPlayer(sf::Vector2f wDim, std::string name);
		~CPlayer();
		
		/* Getters and setter. */
		sf::View getView(void);
		sf::Vector2f getViewPos(void);
		bool getIsBlocked(void);
		void setIsBlocked(bool newBlocked);
		
		/* Update the view the player with his movement. */
		void updateView(float x, float y, sf::Vector2f wDim, float lvlLength);
		/* Update the action of the player limited by the view. */
		void update(float dt, sf::Vector2f wDim, float lvlLength, float lvlDepth);
};

#endif //__CPLAYER_HPP
