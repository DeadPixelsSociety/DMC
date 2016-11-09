#ifndef __CRECTANGLE_H
#define __CRECTANGLE_H

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

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
		float m_moveSpeed;
	
	public:
	
		CRectangle(float type, float psX, float psY);
		~CRectangle(void);

		sf::Vector2f getPosition(void);
		sf::Vector2f getSize(void);
		void update(float dt, float limit);
		void draw(sf::RenderWindow &window);
};

#endif
