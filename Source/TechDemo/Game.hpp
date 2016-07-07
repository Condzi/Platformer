#pragma once

#include "..\Physic\PhysicEngine\PhysicEngine.hpp"
#include "..\Graphic\TextureManager\TextureManager.hpp"
#include "Player.hpp"

class Game
{
private:
	void handleEvents();
	void update(const float & deltaTime);
	void draw();

	//Here are loading all object to engines:

	void initPhysicEngine();
	void initTextureManager();

public:
	Game(uint16_t winX = 800, uint16_t winY = 600, uint8_t fpsLimit = 64);
	~Game();

	void Run();

private:
	PhysicEngine * m_physicEngine;
	TextureManager * m_textureManager;
	sf::RenderWindow m_window;
	sf::Event m_event;

	//----TEST-ZONE
	Player test_player;
};

