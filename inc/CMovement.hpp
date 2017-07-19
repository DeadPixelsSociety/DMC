#ifndef __CMOVEMENT_HPP
#define __CMOVEMENT_HPP

#include <iostream>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

class CMovement {
	private :

    std::vector<sf::Rect<int>> m_frames;
    size_t m_current;

	public : 
		CMovement(std::vector<sf::Rect<int>> newFrames);
		~CMovement(void);
		
		void nextFrame(sf::Sprite *toChange);
};

#endif //__CMOVEMENT_HPP
