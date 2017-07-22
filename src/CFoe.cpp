#include "../inc/CFoe.hpp"

CFoe::CFoe(float type, float psX, float psY)
: CCharacter(0.0f, sf::Vector2f(psX, psY), sf::Vector2f(30, 38), "res/sprites/animFoe.png", 0.0f, 75.0f, 0.0f, 0.0f)
, m_type(type)
{
  getSprite()->setPosition(getPosition());

  std::vector<sf::Rect<int>> right;
  right.push_back(sf::Rect<int>(0, 38, 30, 38));
  right.push_back(sf::Rect<int>(30, 38, 30, 38));
  right.push_back(sf::Rect<int>(60, 38, 30, 38));

  std::vector<sf::Rect<int>> left;
  left.push_back(sf::Rect<int>(0, 76, 30, 38));
  left.push_back(sf::Rect<int>(30, 76, 30, 38));
  left.push_back(sf::Rect<int>(60, 76, 30, 38));
  
  m_animHandler->addMovement(MOV_RIGHT, right);
  m_animHandler->addMovement(MOV_LEFT, left);
}

CFoe::~CFoe()
{

}

void CFoe::update(sf::Time dt, float limit)
{
	if (m_eDirH == DIR_LEFT) {
	  m_animHandler->update(dt, MOV_LEFT);
		if (getPosition().x + getSize().x > 0) {
			getSprite()->move(-m_velocity * dt.asSeconds(), 0);
		} else {
			m_eDirH = DIR_RIGHT;
			getSprite()->move(m_velocity * dt.asSeconds(), 0);
		}
	} else {
 	  m_animHandler->update(dt, MOV_RIGHT);
		if (getPosition().x + getSize().x < limit) {
			getSprite()->move(m_velocity * dt.asSeconds(), 0);
		}	else {
			m_eDirH = DIR_LEFT;
			getSprite()->move(-m_velocity * dt.asSeconds(), 0);
		}
	}
}
