#include "Input.h"
#include <SFML\Window\Mouse.hpp>
#include <gtc\matrix_transform.hpp>
//#include <gtx/transform.hpp>


Input::Input(sf::Window& win) : win(win) {
	sf::Vector2u win_size = win.getSize();
	sf::Vector2i new_pos(win_size.x / 2, win_size.y / 2);
	sf::Mouse::setPosition(new_pos, win);
}


Input::~Input() {
}

void Input::compute(std::chrono::microseconds deltatime) {
	sf::Vector2u win_size = win.getSize();

	std::chrono::milliseconds ms_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(deltatime);
	std::chrono::duration<float> f_dur_deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(deltatime);
	float f_deltaTime = f_dur_deltaTime.count();

	// Get cursor position
	sf::Vector2i pos = sf::Mouse::getPosition(win);

	// Reset cursor to window center
	sf::Vector2i new_pos(win_size.x / 2, win_size.y / 2);
	sf::Mouse::setPosition(new_pos, win);

	h_angle += mouse_speed * f_deltaTime * float(new_pos.x - pos.x);
	v_angle += mouse_speed * f_deltaTime * float(new_pos.y - pos.y);

	glm::vec3 direction = glm::vec3(
		cos(v_angle) * sin(h_angle),
		sin(v_angle),
		cos(v_angle) * cos(h_angle)
	);

	glm::vec3 right = glm::vec3(
		sin(h_angle - 3.14f / 2.0f),
		0,
		cos(h_angle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		pos_camera += direction * f_deltaTime * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		pos_camera -= direction * f_deltaTime * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		pos_camera += right * f_deltaTime * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		pos_camera -= right * f_deltaTime * speed;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		FOV_curr = FOV_initial - 20;
	}
	else {
		FOV_curr = FOV_initial;
	}

	ProjectionMatrix = glm::perspective(glm::radians(FOV_curr), win_ration, 0.1f, 100.0f);

	ViewMatrix = glm::lookAt(
		pos_camera,           // Camera is here
		pos_camera + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}
