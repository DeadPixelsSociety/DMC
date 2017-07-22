#ifndef __CENTITY_HPP
#define __CENTITY_HPP

#include <iostream>
#include <stdbool.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Color.hpp>

#include "CAnimationHandler.hpp"

enum EAction {ACT_JUMP, ACT_ATTACK, ACT_NONE};
enum EDirectionHor {DIR_LEFT, DIR_RIGHT, DIR_NONEH};
enum EDirectionVer {DIR_UP, DIR_DOWN, DIR_NONEV};

class CEntity {
	protected :
		
		float m_weight;
		EAction m_eAction;
		EDirectionHor m_eDirH;
		EDirectionVer m_eDirV;
		
		sf::Vector2f m_size;
		
		CAnimationHandler *m_animHandler;

	public : 
		CEntity(float weight, sf::Vector2f position, sf::Vector2f size, std::string spritePath);
		CEntity(float weight, sf::Vector2f position, sf::Vector2f size, sf::Color color);
		~CEntity(void);

		/* Getters and setters. */
		sf::Sprite *getSprite(void);
		sf::Vector2f getPosition(void);
		sf::Vector2f getSize(void);
		float getWeight(void);
		void  setPosition(sf::Vector2f newPos);
		void  setPosition(float x, float y);
		void  setWeight(float newWeight);
		enum EAction getAction(void);
		void setAction(EAction action);
		enum EDirectionHor getDirectionH(void);
		void  setDirectionH(EDirectionHor newEDirH);
		enum EDirectionVer getDirectionV(void);
		void  setDirectionV(EDirectionVer newEDirV);
		
		/* Draw the sprite of the entity. */
		void draw(sf::RenderWindow &window);
};

#endif //__CENTITY_HPP
