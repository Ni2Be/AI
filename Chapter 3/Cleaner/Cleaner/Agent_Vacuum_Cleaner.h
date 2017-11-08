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
#include <queue>

#include <SFML/Graphics.hpp>

#include "Area.h"



enum Actions
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	CLEAN
};

/*
area model is a model of the given area
that makes it possible to give every tile a value.
The starting Value is 0, and obstacles will be marked
with a bool.
______
|0000|
|00X0|
|0000|
|X000|
------
*/
class Area_Model
{
public:
	//generates the model of the area
	Area_Model(Area& area, float cleaner_start_x, float cleaner_start_y);


	//finds the shortest cleaning path through the area
	//and returns it as a queue of actions
	std::queue<Actions>  generate_solution(const Area_Model& area);


private:
	class Tile_Model
	{
	public:
		Tile_Model(int value, bool is_obstacle)
			:
			m_value(value),
			m_is_obstacle(is_obstacle)
		{}
		int   m_value;
		bool  m_is_obstacle;
	};


	//returns the minimum moves needed to clean the given area
	int					heuristic_function(const Area& area);



	int									 m_cleaner_row;
	int									 m_cleaner_column;
	int									 m_heuristic_value;
	std::vector<std::vector<Tile_Model>> m_tiles;
};

class Agent_Vacuum_Cleaner : public sf::CircleShape
{
public:
	Agent_Vacuum_Cleaner(float x_pos, float y_pos, float radius, Area& area)
		:
		sf::CircleShape	(radius),
		m_area_model    (area, x_pos, y_pos)
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


	std::queue<Actions> m_actions;
	Area_Model		    m_area_model;

	int		m_x_direction = 1;
	int		m_y_direction = 0;
	float	m_x_speed = 1.0f;
	float	m_y_speed = 1.0f;

	int		m_performance_counter = 0;
	int		m_time_counter = 0;
};



