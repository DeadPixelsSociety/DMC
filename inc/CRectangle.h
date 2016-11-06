#ifndef __CRECTANGLE_H
#define __CRECTANGLE_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

enum EDirection {Left, Right};

class CRectangle
{
	private:
	
		sf::RectangleShape m_rec;
		bool m_isSpawned;
		EDirection m_eDir;
	
	public:
	
		CRectangle(float type, float psX, float psY);
		~CRectangle(void);
		
		void update(float dt, float limit, float moveSpeed);
		void draw(sf::RenderWindow *window);
};

#endif
