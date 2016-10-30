#include "../inc/CLevel.h"

CLevel::CLevel(std::string _num)
{

	/*
		SUPPRIMER LES OBJETS (YAML::Node, les textures, ...) ?
	*/

	std::string name("res/levels/level");
	std::string ext(".yaml");
	
	YAML::Node levelFile = YAML::LoadFile(name + _num + ext);
	
	if (levelFile.IsNull()) {
		std::cerr << "[!] Can't open " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}
	
	m_szName = levelFile["name"].as<std::string>();
	
	size_t sizeLock = levelFile["lock"].size();
	for(size_t zone = 0; zone < sizeLock; zone++)
	{
		m_lockZones.push_back(levelFile["lock"][zone].as<float>());
	}


	size_t nbrFoe = levelFile["foe"].size();
	float type, spX, spY;
	for(size_t foe = 0; foe < nbrFoe; foe++)
	{
		type = levelFile["foe"][foe]["type"].as<float>();
		spX = levelFile["foe"][foe]["spawnPos"]["x"].as<float>();
		spY = levelFile["foe"][foe]["spawnPos"]["y"].as<float>();
		
		m_pArrayFoes.push_back(new CRectangle(type, spX, spY));
	}
	
	m_pTPath = new sf::Texture();
	if (!m_pTPath->loadFromFile(levelFile["path"].as<std::string>()))
	{
		exit(EXIT_FAILURE);
	}	
	m_path.setTexture(*m_pTPath);
	
	m_pTFore = new sf::Texture();
	if (!m_pTFore->loadFromFile(levelFile["foreground"].as<std::string>()))
	{
		exit(EXIT_FAILURE);
	}	
	m_foreground.setTexture(*m_pTFore);
	
	m_pTBack = new sf::Texture();	
	if (!m_pTBack->loadFromFile(levelFile["background"].as<std::string>()))
	{
		exit(EXIT_FAILURE);
	}	
	m_background.setTexture(*m_pTBack);
	
	m_sizeLevel = m_pTPath->getSize().x;
	
	// view ?
	
	m_depth = m_pTPath->getSize().y;
	
	// music ?
	
	m_difficulty = levelFile["difficulty"].as<float>();	
}

CLevel::~CLevel()
{
	delete m_pTBack;
	delete m_pTPath;
	delete m_pTFore;

	size_t size = m_pArrayFoes.size();
	for (size_t foe = 0; foe < size; foe++)
	{
		delete m_pArrayFoes[foe];
	}
}

size_t *CLevel::foesInScreen()
{
	// Si position de foe dans view
	// mettre index du foe dans res
	
	// Dynamic obligé ?
	
	return 0;
}

void CLevel::update(float dt, float wWidth, float wHeight, float moveSpeed)
{
	// Gestion de view et parallaxe du décors
	
	// Gestion des foes
	/*
		- Comment determiner qels foes sont dans la vue courante. (view ?)
		  Pour chacun de ces foes, appeller leur update() (ou fonction ia, puis update())
		  
		  (De même si arme / obstacle implantés.)
	*/
	
	// Delete tous les foes qui sont à gauche de la view ?
	
	size_t size = m_pArrayFoes.size();
	for (size_t rect = 0; rect < size; rect++)
	{
		m_pArrayFoes[rect]->update(dt, wWidth, wHeight, moveSpeed);
	}
}

void CLevel::draw(sf::RenderWindow *window)
{
	window->draw(m_background);
	window->draw(m_foreground);
	window->draw(m_path);

	size_t size = m_pArrayFoes.size();
	for (size_t rect = 0; rect < size; rect++)
	{
		m_pArrayFoes[rect]->draw(window);
	}
}
