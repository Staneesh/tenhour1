#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

int main()
{
	float window_width = 200, window_height = 200;
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	window_width = window.getSize().x;
	window_height = window.getSize().y;
	
	float happiness = 0.0f;
    sf::CircleShape ghost(50.f);
    ghost.setFillColor(sf::Color::Green);
	ghost.setPosition(window_width / 2, window_height / 2);
	ghost.setOrigin(ghost.getRadius(), ghost.getRadius());

	sf::Texture light_tex;
	light_tex.loadFromFile("light.png");
	sf::Sprite light;
	light.setTexture(light_tex);
    light.setColor(sf::Color::Yellow);
	light.setPosition(ghost.getPosition());
	light.setOrigin(light_tex.getSize().x / 2, light_tex.getSize().y / 2);
	light.scale(window_width / light_tex.getSize().x , window_height / light_tex.getSize().y);

    sf::CircleShape ground(5000.f);
    ground.setFillColor(sf::Color::Red);
	ground.setPosition(window_width / 2, window_height / 2 + ground.getRadius());
	ground.setOrigin(ground.getRadius(), ground.getRadius());

    sf::CircleShape grotto(300.f);
    grotto.setFillColor(sf::Color::Blue);
	grotto.setPosition(window_width / 2, window_height / 2 - 50);
	grotto.setOrigin(grotto.getRadius(), grotto.getRadius());
	grotto.setScale(1.0f, 2.0f);

	Clock clock;
	float elapsed = clock.getElapsedTime().asSeconds();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}
        }
		float dt = clock.restart().asSeconds();
		elapsed += dt;

		float frequency = 4;
		//ghost.move(0, 2.0f / frequency * sin(elapsed * frequency));

		float happiness_factor = fmax(1.0f, happiness * 3);
		auto ghostPos = ghost.getPosition() + ghost.getOrigin();

		auto ghostToMouse = (Vector2f)Mouse::getPosition() - ghostPos;
		float ghostToMouseLen = sqrt(ghostToMouse.x * ghostToMouse.x +
				ghostToMouse.y * ghostToMouse.y);
		cout<<ghostToMouseLen<<endl;
		if (ghostToMouseLen <= ghost.getRadius())
		{
			cout<<"Hover"<<endl;
			happiness_factor += 0.3;
		}

		light.setScale(happiness_factor,
				happiness_factor * window_height / light_tex.getSize().y);

        window.clear();
		window.draw(grotto);
		window.draw(ground);
		window.draw(light);
        window.draw(ghost);
        window.display();
    }

    return 0;
}
