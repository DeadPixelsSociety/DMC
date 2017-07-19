#ifndef __CANIMATIONHANDLER_HPP
#define __CANIMATIONHANDLER_HPP

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "CMovement.hpp"

enum EMovements {
  MOV_NONE = 0,
  MOV_RIGHT,
  MOV_LEFT,
  MOV_JUMP,
  ALL_MOVEMENTS
};

class CAnimationHandler {
	private :

    std::string m_resourcePath;
    sf::Texture *m_pTexture;
    sf::Sprite *m_sprite;
    
    float m_acc;
    
    // Array who stock the array for each move.
    CMovement *m_movements[ALL_MOVEMENTS];

	public : 
		CAnimationHandler(std::string resPath, sf::Vector2f size, sf::Vector2f position);
		~CAnimationHandler(void);
		
		sf::Sprite *getSprite(void);
		
		void addMovement(EMovements movement, std::vector<sf::Rect<int>> newMovement);
		void update(sf::Time dt, EMovements movement);
		void draw(sf::RenderWindow &window);
};

#endif //__CANIMATIONHANDLER_HPP
