#include "Physic\PhysicEngine\PhysicEngine.hpp"
#include "Graphic\TextureManager\TextureManager.hpp"
#include "Animation\Animator\Animator.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer", sf::Style::Close);
	window.setFramerateLimit(61);
	sf::Event event;
	PhysicEngine p;
	TextureManager t;
	Animator anim;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		p.Update(0.f);
		t.Update();

		window.clear();
		window.display();
	}
}
