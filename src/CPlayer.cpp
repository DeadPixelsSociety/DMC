#include "../inc/CPlayer.hpp"

CPlayer::CPlayer(sf::Vector2f wDim, std::string name)
: CCharacter(0.0f, sf::Vector2f(0, wDim.y - 20), sf::Vector2f(20, 20), "res/sprites/player.png", 0.0f, 80000.0f, 0.0f, 0.0f)
, m_szName(name)
, m_view(sf::FloatRect(0, 0, wDim.x, wDim.y))
, m_isBlocked(false)
{

}

CPlayer::~CPlayer()
{

}

sf::View CPlayer::getView()
{
	// Getter for the view.
	
	return m_view;
}

sf::Vector2f CPlayer::getViewPos()
{
	// Getter for the position of the view.
	
	return m_view.getCenter();
}

bool CPlayer::getIsBlocked()
{
	// Indicate if the view of the player his lock or not.
	
	return m_isBlocked;
}

void CPlayer::setIsBlocked(bool newBlocked)
{
	// Setter to lock or unlock the view of the player.
	
	m_isBlocked = newBlocked;
}

void CPlayer::updateView(float x, float y, sf::Vector2f wDim, float lvlLength)
{
	// Update the view the player with his movement.
	
	sf::Vector2f viewPos(wDim.x / 2, wDim.y / 2);

	float halfSize = getSize().x / 2;
	float coordX = getPosition().x + halfSize;
	int dist = (int) abs(coordX - m_view.getCenter().x);
	static int accel = 10;

	// Move or stop the scrolling when the player is either
	// at the start of the level or at the end.
	if (coordX  >= wDim.x / 2)
	{	
		if (coordX >= lvlLength - (wDim.x / 2))
		{
			// View reach end of the level.
			viewPos.x = lvlLength - (wDim.x / 2);
		}
		else
		{
			// After a lock zone, the player is not always at the center
			// of the view, so we move it to correct that.
			if (dist > 1)
			{
				if (coordX > m_view.getCenter().x && x > 0) {
					m_view.move(dist / accel, 0);
					accel = (accel > 1) ? accel - 1 : 1;
				} else if (coordX < m_view.getCenter().x && x < 0) {
					m_view.move(- (dist / accel), 0);
					accel = (accel > 1) ? accel - 1 : 1;
				} else {
					return;
				}
			}
			else
			{
				// Normal deplacement of the view.
				accel = 10;
				m_view.move(x, 0);
			}
			return;
		}
	}
	else
	{
		// View at the start of the level.
		viewPos.x = wDim.x / 2;
	}
	
	m_view.setCenter(viewPos);
}

void CPlayer::update(float dt, sf::Vector2f wDim, float lvlLength, float lvlDepth)
{
	// Update the action of the player limited by the view.
	
	float x = 0.0f;
	float y = 0.0f;
	
	switch (m_eDirH)
	{
		case Right : x = (getPosition().x < (getView().getCenter().x + (wDim.x / 2)) - getSize().x) ? m_velocity * dt : 0.0f;
			break;
		case Left : x = (getPosition().x > (getView().getCenter().x - (wDim.x / 2))) ? -m_velocity * dt : 0.0f;
			break;
		case NoneH : break;
	}
	
	switch (m_eDirV)
	{
		case Up : y = (getPosition().y > wDim.y - lvlDepth - getSize().y) ? -m_velocity * dt : 0.0f;
			break;
		case Down : y = (getPosition().y < wDim.y - getSize().y) ? m_velocity * dt : 0.0f;
			break;
		case NoneV : break;
	}
	
	if (x == 0.0f && y == 0.0f) return;
	
	if (!m_isBlocked) updateView(x, y, wDim, lvlLength);
	
	m_sprite.move(x, y);
}
