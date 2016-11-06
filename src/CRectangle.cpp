#include "../inc/CRectangle.h"

CRectangle::CRectangle(float type, float psX, float psY)
{
	switch ((int) type)
	{
		case 1 : m_rec.setFillColor(sf::Color::Yellow);
			break;
		case 2 : m_rec.setFillColor(sf::Color::Blue);
			break;
		case 3 : m_rec.setFillColor(sf::Color::Red);
			break;
		case 4 : m_rec.setFillColor(sf::Color::Green);
			break;
		default :
			break;
	}
	
	m_isSpawned = false;
	
	m_rec.setSize(sf::Vector2f(50, 100));
	m_rec.setPosition(psX, psY);
	
	m_eDir = Right;
}

CRectangle::~CRectangle()
{

}

void CRectangle::draw(sf::RenderWindow *window)
{
	window->draw(m_rec);
}

void CRectangle::update(float dt, float limit, float moveSpeed)
{
	if (m_eDir == Left)
	{
		if (m_rec.getPosition().x + m_rec.getSize().x > 0)
		{
			m_rec.move(-moveSpeed * dt, 0);
		}
		else
		{
			m_eDir = Right;
			m_rec.move(moveSpeed * dt, 0);
		}
	}
	else
	{
		if (m_rec.getPosition().x + m_rec.getSize().x < limit)
		{
			m_rec.move(moveSpeed * dt, 0);
		}
		else
		{
			m_eDir = Left;
			m_rec.move(-moveSpeed * dt, 0);
		}
	}
}
