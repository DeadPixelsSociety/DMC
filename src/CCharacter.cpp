#include "../inc/CCharacter.hpp"


CCharacter::CCharacter(float weight, sf::Vector2f position, sf::Vector2f size, std::string spritePath,\
					   float health, float velocity, float atkSpeed, float damage)
: CEntity(weight, position, size, spritePath)
, m_health(health)
, m_velocity(velocity)
, m_atkSpeed(atkSpeed)
, m_damage(damage)
{

}

CCharacter::~CCharacter()
{

}

float CCharacter::getHealth()
{
	// Getter for the health
	
	return m_health;
}

void CCharacter::setHealth(float newHealth)
{
	// Setter for the health
	
	m_health = newHealth;
}


float CCharacter::getVelocity()
{
	// Getter for the velocity
	
	return m_velocity;
}

void CCharacter::setVelocity(float newVelocity)
{
	// Setter for the velocity
	
	m_velocity = newVelocity;
}


float CCharacter::getAtkSpeed()
{
	// Getter for the attack speed
	
	return m_atkSpeed;
}

void CCharacter::setAtkSpeed(float newAtkSpeed)
{
	// Setter for the attack speed
	
	m_atkSpeed = newAtkSpeed;
}


float CCharacter::getDamage()
{
	// Getter for the damage
	
	return m_damage;
}

void CCharacter::setDamage(float newDamage)
{
	// Setter for the damage
	
	m_damage = newDamage;
}
