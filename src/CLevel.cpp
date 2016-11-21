#include "../inc/CLevel.hpp"

CLevel::CLevel(std::string _num)
{
	std::string name("res/levels/level");
	std::string ext(".yaml");
	
	YAML::Node levelFile = YAML::LoadFile(name + _num + ext);
	
	if (levelFile.IsNull())
	{
		std::cerr << "[!] Can't open " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}
	
	m_szName = levelFile["name"].as<std::string>();
	
	size_t sizeLock = levelFile["lock"].size();
	for(size_t zone = 0; zone < sizeLock; zone++)
	{
		m_lockZones.push(levelFile["lock"][zone].as<float>());
	}

	size_t nbrFoes = levelFile["foe"].size();
	float type, spX, spY;
	for(size_t foe = 0; foe < nbrFoes; foe++)
	{
		type = levelFile["foe"][foe]["type"].as<float>();
		spX = levelFile["foe"][foe]["spawnPos"]["x"].as<float>();
		spY = levelFile["foe"][foe]["spawnPos"]["y"].as<float>();
		
		m_arrayFoes.push_back(new CFoe(type, spX, spY));
	}
	
	m_pTPath = new sf::Texture();
	if (!m_pTPath->loadFromFile(levelFile["path"].as<std::string>()))
	{
		std::cerr << "[!] Can't load the path picture of : " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}	
	m_path.setTexture(*m_pTPath);
	
	m_pTFore = new sf::Texture();
	if (!m_pTFore->loadFromFile(levelFile["foreground"].as<std::string>()))
	{
		std::cerr << "[!] Can't load the foreground picture of : " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}	
	m_foreground.setTexture(*m_pTFore);
	
	m_pTBack = new sf::Texture();	
	if (!m_pTBack->loadFromFile(levelFile["background"].as<std::string>()))
	{
		std::cerr << "[!] Can't load the background picture of : " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}	
	m_background.setTexture(*m_pTBack);
	
	m_length = m_pTPath->getSize().x;
	
	m_depth = levelFile["depth"].as<float>();
	
	m_difficulty = levelFile["difficulty"].as<float>();	
}

CLevel::~CLevel()
{
	// Free all the alocate memory for the level.
	
	delete m_pTBack;
	delete m_pTPath;
	delete m_pTFore;

	for (auto foe : m_arrayFoes)
	{
		delete foe;
	}
}

std::queue<float> CLevel::getLockZones()
{
	//
	
	return m_lockZones;
}

float CLevel::getLength(void)
{
	// Getter for the length of the level.
	
	return m_length;
}

float CLevel::getDepth(void)
{
	// Getter for the depth of the level.
	
	return m_depth;
}

void CLevel::foesInScreen(sf::Vector2u wDim, sf::Vector2f centerView, std::vector<size_t> *foesVisibles)
{
	// Fill a vector with indexs of all the foes visibled in the view.
	
	size_t xPosLeftView = centerView.x - wDim.x / 2;
	size_t xPosRightView = centerView.x + wDim.x / 2;
	size_t rightCorner = 0;
	size_t leftCorner = 0;
	
	size_t size = m_arrayFoes.size();
	for (size_t foe = 0; foe < size; foe++)
	{
		rightCorner = m_arrayFoes[foe]->getPosition().x + m_arrayFoes[foe]->getSize().x;
		leftCorner = m_arrayFoes[foe]->getPosition().x;
		
		if ((rightCorner > xPosLeftView && rightCorner < xPosRightView) ||
			(leftCorner > xPosLeftView && leftCorner < xPosRightView))
		{
			foesVisibles->push_back(foe);
		}
	}
}

void CLevel::update(float dt, sf::RenderWindow &window, CPlayer &player)
{
	//
	
	if (!m_lockZones.empty() || player.getIsBlocked())
	{
		// The player is in a lock zone,
		// we check if there are foes in the view,
		// if not, we disable the lock zone.
		if (player.getIsBlocked()) {
			std::vector<size_t> foesVisibles;
			foesInScreen(window.getSize(), player.getView().getCenter(), &foesVisibles);
		
			if (foesVisibles.size() == 0) {
				player.setIsBlocked(false);
			}
		}
		// We block the player when he enter a lock zone.
		else
		{
			if (player.getPosition().x >= m_lockZones.front())
			{
				player.setIsBlocked(true);
				m_lockZones.pop();
			}
		}
	}
	
	for (auto foe : m_arrayFoes)
	{
		foe->update(dt, getLength());
	}
}

void CLevel::draw(sf::RenderWindow &window, sf::View viewPlayer)
{
	// Draw all the drawable entitys inside the level.
	
	// Drawing of the 3 sprites of the level with parallaxe effect.
	sf::View viewParallaxe(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	
	viewParallaxe.move(viewPlayer.getCenter().x * 0.15f, 0);
	window.setView(viewParallaxe);
	window.draw(m_background);
	
	viewParallaxe.move(viewPlayer.getCenter().x * 0.35f, 0);
	window.setView(viewParallaxe);
	window.draw(m_foreground);

	// Reset the view to default so the path sprite
	// is draw at the speed of the player.	
	window.setView(viewPlayer);
	window.draw(m_path);

	// Draw only the entity in the view.
	std::vector<size_t> foesVisibles;
	foesInScreen(window.getSize(), viewPlayer.getCenter(), &foesVisibles);
	for (auto index : foesVisibles)
	{
		m_arrayFoes[index]->draw(window);
	}
}
