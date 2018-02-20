#pragma once

#ifndef INPUT_H
#define INPUT_H

#include <chrono>
#include <SFML\Window.hpp>
#include <glm.hpp>

class Input
{
public:
	Input(sf::Window& win);
	~Input();

	void compute(std::chrono::microseconds deltatime);

	float FOV_curr = 45.0f;
	float win_ration = 800 / 700;

	glm::vec3 pos_camera = glm::vec3(0, 0, 5);

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

private:
	sf::Window& win;

	float h_angle = 3.14f;
	float v_angle = 0;
	const float FOV_initial = 45.0f;

	float speed = 3;
	float mouse_speed = 0.05f;
};

#endif // !INPUT_H