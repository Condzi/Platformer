#pragma once
#include "GameObject.hpp"
#include "..\Animation\Animator\Animator.hpp"

class Player :
	public GameObject
{
public:
	Player();
	~Player();

	void Update();

	bool SetAnimationSheet(const TextureFixed * texture);

private:
	Animator m_animator;
	const TextureFixed * m_animationSheet;
};

