#ifndef __CRECTANGLE_HPP
#define __CRECTANGLE_HPP

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

enum EDirectionV2 {LeftV2, RightV2};

class CRectangle
{
	private:
	
		sf::RectangleShape m_rec;
		bool m_isSpawned;
		EDirectionV2 m_eDir;
		float m_moveSpeed;
	
	public:
	
		CRectangle(float type, float psX, float psY);
		~CRectangle(void);

		sf::Vector2f getPosition(void);
		sf::Vector2f getSize(void);
		void update(float dt, float limit);
		void draw(sf::RenderWindow &window);
};

#endif //__CRECTANGLE_HPP
