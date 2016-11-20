#ifndef __CCHARACTER_HPP
#define __CCHARACTER_HPP

#include "CEntity.hpp"

class CCharacter : public CEntity
{
	protected :
		float m_health;
		float m_velocity;
		float m_atkSpeed;
		float m_damage;

	public :
		CCharacter(float weight, sf::Vector2f position, sf::Vector2f size, std::string spritePath,\
				   float health, float velocity, float atkSpeed, float damage);
		~CCharacter(void);

		float getHealth(void);
		void  setHealth(float newHealth);
		float getVelocity(void);
		void  setVelocity(float newVelocity);
		float getAtkSpeed(void);
		void  setAtkSpeed(float newAtkSpeed);
		float getDamage(void);
		void  setDamage(float newDamage);
};

#endif //__CCHARACTER_HPP

