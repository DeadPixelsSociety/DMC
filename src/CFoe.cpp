#include "../inc/CFoe.hpp"

CFoe::CFoe(float type, float psX, float psY)
: CCharacter(0.0f, sf::Vector2f(psX, psY), sf::Vector2f(50, 100), "res/sprites/foe.png", 0.0f, 50000.0f, 0.0f, 0.0f)
, m_type(type)
{

}

CFoe::~CFoe()
{

}

void CFoe::update(float dt, float limit)
{
	if (m_eDirH == Left)
	{
		if (getPosition().x + getSize().x > 0)
		{
			m_sprite.move(-m_velocity * dt, 0);
		}
		else
		{
			m_eDirH = Right;
			m_sprite.move(m_velocity * dt, 0);
		}
	}
	else
	{
		if (getPosition().x + getSize().x < limit)
		{
			m_sprite.move(m_velocity * dt, 0);
		}
		else
		{
			m_eDirH = Left;
			m_sprite.move(-m_velocity * dt, 0);
		}
	}
}
