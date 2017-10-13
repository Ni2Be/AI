#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Area.h"

class Agent_Vacuum_Cleaner : public sf::CircleShape
{
public:
	Agent_Vacuum_Cleaner(int x_pos, int y_pos, float radius)
		:
		sf::CircleShape	(radius)
	{
		this->setFillColor  (sf::Color::Blue);
		this->setOrigin		(sf::Vector2f(radius , radius));
		this->setPosition	(sf::Vector2f(x_pos, y_pos));
	}

	void act(Area& area);

	void plot_statistics();
	
	int& x_speed() { return m_x_speed; }
	int& y_speed() { return m_y_speed; }

private:
	void change_direction();
	void evaluate_next_move();

	int		m_x_direction = 1;
	int		m_y_direction = 0;
	int		m_x_speed = 1;
	int		m_y_speed = 1;

	bool	m_is_moving_sideways = true;

	int		m_width_memory = 1;
	int		m_height_memory = 1;

	int		m_width_counter = 1;
	int		m_height_counter = 1;

	int		m_performance_counter = 0;
	int		m_time_counter = 0;
};
