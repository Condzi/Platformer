#pragma once
#include "GameObject.hpp"

class Player :
	public GameObject
{
public:
	Player();
	~Player();

	void Update();
};

