#include "../inc/CLevel.hpp"

CLevel::CLevel(std::string _num, sf::Vector2f wDim)
: m_viewFore(sf::FloatRect(0, 0, wDim.x, wDim.y))
, m_viewBack(sf::FloatRect(0, 0, wDim.x, wDim.y))
{
	// Build the path of the yaml file of the current level.
	std::string name("res/levels/level");
	std::string ext(".yaml");
	
	YAML::Node levelFile = YAML::LoadFile(name + _num + ext);
	
	if (levelFile.IsNull())
	{
		std::cerr << "[!] Can't open " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}
	
	m_szName = levelFile["name"].as<std::string>();
	
	m_difficulty = levelFile["difficulty"].as<float>();
	
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
	
	// Get the velocity of the foreground and background.
	m_veloFore = levelFile["veloFore"].as<float>();
	m_veloBack = levelFile["veloBack"].as<float>();
	
	m_length = m_pTPath->getSize().x;	
	m_depth = levelFile["depth"].as<float>();
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
	// Getter for the queue of zones lock.
	
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
	
	// We keep indexs of foes in the view.
	size_t size = m_arrayFoes.size();
	for (size_t foe = 0; foe < size; ++foe)
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

void CLevel::foesInOrder(float playerPosY, std::vector<size_t> *foesVisibles, std::vector<size_t> *foesFront, std::vector<size_t> *foesBack)
{
	// Slice the visibles foes if they are in front of the player of behind him.
	
	for (auto index : *foesVisibles)
	{
		if ((m_arrayFoes[index]->getPosition().y + m_arrayFoes[index]->getSize().y) > playerPosY) {
			foesFront->push_back(index);
		} else {
			foesBack->push_back(index);
		}
	}
}

void CLevel::update(sf::Time dt, sf::RenderWindow &window, CPlayer &player)
{
	// Update entity present in the level.
	
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
	
	// Tmp update for the foes.
	for (auto foe : m_arrayFoes)
	{
		foe->update(dt, getLength());
	}
}

void CLevel::draw(sf::RenderWindow &window, CPlayer &player)
{
	// Draw all the drawable entitys inside the level.
	
	// Drawing of the 3 sprites of the level with parallaxe effect.	
	if (player.getLastViewDep() > 0.0f) m_viewBack.move(player.getLastViewDep() * m_veloBack, 0);
	else m_viewBack.move(m_veloBack, 0);
	window.setView(m_viewBack);
	window.draw(m_background);
	
	m_viewFore.move(player.getLastViewDep() * m_veloFore, 0);
	window.setView(m_viewFore);
	window.draw(m_foreground);

	// Reset the view to default so the path sprite
	// is draw at the speed of the player.	
	window.setView(player.getView());
	window.draw(m_path);

	// Draw only the entity in the view.
	std::vector<size_t> foesVisibles;
	foesInScreen(window.getSize(), player.getViewPos(), &foesVisibles);
	
	// Draw with correct perspective.
	std::vector<size_t> foesFront;
	std::vector<size_t> foesBack;
	foesInOrder(player.getPosition().y + player.getSize().y, &foesVisibles, &foesFront, &foesBack);
	
	for (auto index : foesBack)
	{
		m_arrayFoes[index]->draw(window);
	}
	
	player.draw(window);
	
	for (auto index : foesFront)
	{
		m_arrayFoes[index]->draw(window);
	}
}
