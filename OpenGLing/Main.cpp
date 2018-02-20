#include <chrono>
#include <string>
#include <thread>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Graphics.h"
#include "Input.h"

using secu = std::chrono::duration<double, std::chrono::seconds>;

const unsigned fps_wanted = 120;
const std::chrono::microseconds frame_time(1000000 / fps_wanted);

auto last_tp = std::chrono::system_clock::now();
auto now_tp = std::chrono::system_clock::now();
std::chrono::microseconds exec_time;
std::chrono::microseconds time_to_wait;

long double fps = 0;


void do_timing() {
	now_tp = std::chrono::system_clock::now();
	exec_time = std::chrono::duration_cast<std::chrono::microseconds>(now_tp - last_tp);
	last_tp = now_tp;
	time_to_wait = frame_time - exec_time;

	// Sleep to save cpu
	if (time_to_wait.count() > 1000) {
		std::this_thread::sleep_for(time_to_wait);
	}

	long double num_sec = (long double)exec_time.count() / (long double)1000000;
	if (num_sec != 0) {
		fps = (long double)1 / (long double)num_sec;
	}
}

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 2;
	settings.majorVersion = 4;
	settings.minorVersion = 4;
	settings.attributeFlags = sf::ContextSettings::Core;

	// SFML WINDOW
	sf::RenderWindow window(sf::VideoMode(800, 700), "SFML window", sf::Style::Close, settings);

	/*GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	printf("%u\n", vertexBuffer);*/
	// Load a sprite to display
	/*sf::Texture texture;
	if (!texture.loadFromFile("minepun.jpg"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("OpenSans-Light.ttf"))
		return EXIT_FAILURE;
	sf::Text text("Hello SFML", font, 50);*/

	// MUSIC
	sf::Music music;
	if (!music.openFromFile("nice_music.ogg")) {
		return EXIT_FAILURE;
	}
	music.play();

	// OpenGL
	Input input(window);
	Graphics graphics(input);
	

	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}
		do_timing();

		graphics.draw(exec_time);

		window.display();
	}

	return EXIT_SUCCESS;
}