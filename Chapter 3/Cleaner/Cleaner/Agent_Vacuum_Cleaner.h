/*
class Agent_Vcuum_Cleaner is an agent that moves
randomly and cleans a tile if it's dirty.
The agent can only poove if the tile where he stands
is dirty and if the tile he wants to move to is an
obstacle.

The function evaluate_next_move() is not used at the 
moment. There should the smartness take place.
*/

#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Area.h"


class Agent_Vacuum_Cleaner : public sf::CircleShape
{
public:
	Agent_Vacuum_Cleaner(float x_pos, float y_pos, float radius)
		:
		sf::CircleShape	(radius)
	{
		this->setFillColor  (sf::Color::Blue);
		this->setOrigin		(sf::Vector2f(radius , radius));
		this->setPosition	(sf::Vector2f(x_pos, y_pos));
	}

	//lets the agent do one move on the area: cleaning or moving
	void act(Area& area);

	void plot_statistics();

	//the horizontal distance the agent moves per action
	float& x_speed() { return m_x_speed; }
	//the vertical distance the agent moves per action
	float& y_speed() { return m_y_speed; }

private:
	//changes the direction to a random direction 
	//(also the to same as previous)
	void change_direction_random();

	//not used at the moment
	void change_direction_clockwise();
	//not used at the moment
	void evaluate_next_move();

	int		m_x_direction = 1;
	int		m_y_direction = 0;
	float	m_x_speed = 1.0f;
	float	m_y_speed = 1.0f;

	int		m_performance_counter = 0;
	int		m_time_counter = 0;
};
