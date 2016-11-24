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

enum EDirectionHor {Left, Right, NoneH};
enum EDirectionVer {Up, Down, NoneV};

class CEntity {
	protected :
		
		float m_weight;
		EDirectionHor m_eDirH;
		EDirectionVer m_eDirV;
		bool m_isSpawned;
		
		sf::Vector2f m_size;		
		sf::Texture *m_pText;
		sf::Sprite m_sprite;

	public : 
		CEntity(float weight, sf::Vector2f position, sf::Vector2f size, std::string spritePath);
		CEntity(float weight, sf::Vector2f position, sf::Vector2f size, sf::Color color);
		~CEntity(void);

		/* Getters and setters. */
		sf::Vector2f getPosition(void);
		sf::Vector2f getSize(void);
		float getWeight(void);
		void  setPosition(sf::Vector2f newPos);
		void  setPosition(float x, float y);
		void  setWeight(float newWeight);
		void  setDirectionH(EDirectionHor newEDirH);
		void  setDirectionV(EDirectionVer newEDirV);
		
		/* Draw the sprite of the entity. */
		void draw(sf::RenderWindow &window);
		/* Print the direction of an entity (for debuging). */
		void printDir();
};

#endif //__CENTITY_HPP
