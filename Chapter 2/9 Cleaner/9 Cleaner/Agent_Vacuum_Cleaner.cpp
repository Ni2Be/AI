#include "Agent_Vacuum_Cleaner.h"
#include "Physics.h"

#include <random>


void Agent_Vacuum_Cleaner::act(Area& area)
{
	m_time_counter++;

	Tile& actual_tile	= area.get_tile_on_pos(this->getPosition().x, this->getPosition().y);
	
	if (actual_tile.is_dirty())
	{
		m_performance_counter++;
		actual_tile.clean_up();
	}
	else
	{
		int delta_x = m_x_speed * m_x_direction;
		int delta_y = m_y_speed * m_y_direction;
		if (!area.get_tile_on_pos(this->getPosition().x + delta_x, this->getPosition().y + delta_y)
			.is_obstacle())
		{
			this->move(delta_x, delta_y);
#ifdef RANDOM_AGENT
			change_direction_random();
#else 
			evaluate_next_move();
#endif
		}
		else
		{
#ifdef RANDOM_AGENT
			change_direction_random();
#else 
			change_direction_clockwise();
#endif
		}
	}
	//else
	//{
	//	if (m_width_counter == 0)
	//	{
	//		m_width_memory++;
	//		m_width_counter = m_width_memory;

	//		m_is_moving_sideways = false;
	//		m_x_direction *= -1;
	//	}
	//	else if (m_height_counter == 0)
	//	{
	//		m_height_memory++;
	//		m_height_counter = m_height_memory;

	//		m_is_moving_sideways = true;
	//		m_y_direction *= -1;
	//	}
	//	
	//	m_performance_counter--;
	//	
	//	//move horizontal
	//	if (m_is_moving_sideways
	//		&& (area.horizontal_tile_size() * m_x_direction + this->getPosition().x < area.width())
	//		&& (area.horizontal_tile_size() * m_x_direction + this->getPosition().x > 0))
	//	{
	//		this->move(sf::Vector2f(area.horizontal_tile_size() * m_x_direction, 0));
	//		m_width_counter--;
	//	}
	//	//move vertical
	//	else if (!m_is_moving_sideways
	//		&& (area.vertical_tile_size() * m_y_direction + this->getPosition().y < area.height())
	//		&& (area.vertical_tile_size() * m_y_direction + this->getPosition().y > 0))
	//	{
	//		this->move(sf::Vector2f(0, area.vertical_tile_size() * m_y_direction));
	//		m_height_counter--;
	//	}
	//	//hit edge horizontal
	//	else if (m_is_moving_sideways)
	//	{
	//		m_x_direction *= -1;
	//		m_width_counter = m_width_memory;
	//		
	//		//move one up or down
	//		m_height_memory++;
	//		m_height_counter = m_height_memory;
	//		m_y_direction *= -1;
	//		if ((area.vertical_tile_size() * m_y_direction + this->getPosition().y < area.height())
	//			&& (area.vertical_tile_size() * m_y_direction + this->getPosition().y > 0))
	//			this->move(sf::Vector2f(0, area.vertical_tile_size() * m_y_direction));
	//		else
	//		{

	//			m_height_memory--;
	//			m_height_counter = m_height_memory;
	//		}
	//		m_y_direction *= -1;
	//	}
	//	//hit edge vertical
	//	else
	//	{
	//		m_y_direction *= -1;
	//		m_height_counter = m_height_memory;

	//		//move one left or right
	//		m_width_memory++;
	//		m_width_counter = m_width_memory;
	//		m_x_direction *= -1;
	//		if (   (area.horizontal_tile_size() * m_x_direction + this->getPosition().x < area.width())
	//			&& (area.horizontal_tile_size() * m_x_direction + this->getPosition().x > 0))
	//			this->move(sf::Vector2f(area.horizontal_tile_size() * m_x_direction, 0));
	//		else
	//		{
	//			m_width_memory--;
	//			m_width_counter = m_width_memory;
	//		}
	//		m_x_direction *= -1;
	//	}
	//}
}

void Agent_Vacuum_Cleaner::change_direction_clockwise()
{
	if (m_x_direction == 1 && m_y_direction == 0)
	{
		m_x_direction = 0;
		m_y_direction = 1;
	}
	else if (m_x_direction == -1 && m_y_direction == 0)
	{
		m_x_direction = 0;
		m_y_direction = -1;
	}
	else if (m_x_direction == 0 && m_y_direction == 1)
	{
		m_x_direction = -1;
		m_y_direction = 0;
	}
	else if (m_x_direction == 0 && m_y_direction == -1)
	{
		m_x_direction = 1;
		m_y_direction = 0;
	}
	//just in case
	else
	{
		m_x_direction = 1;
		m_y_direction = 0;
	}
}

void Agent_Vacuum_Cleaner::change_direction_random()
{
	std::random_device					rd;
	std::uniform_int_distribution<int>	dist(0, 3);
	int rand_num						= dist(rd);
	switch (rand_num)
	{
	case 0: m_x_direction = -1; m_y_direction =  0; break;
	case 1: m_x_direction =  1; m_y_direction =  0; break;
	case 2: m_x_direction =  0; m_y_direction = -1; break;
	case 3: m_x_direction =  0; m_y_direction =  1; break;
	}
}

void Agent_Vacuum_Cleaner::evaluate_next_move()
{
	m_height_counter -= abs(m_x_direction);
	m_width_counter  -= abs(m_y_direction);

	if (m_height_counter == 0)
	{
		change_direction_clockwise();
		m_height_counter = ++m_height_memory;
	}
	if (m_width_counter == 0)
	{
		change_direction_clockwise();
		m_width_counter = ++m_width_memory;
	}
}

void Agent_Vacuum_Cleaner::plot_statistics()
{
	std::cout << "performance_counter: " << m_performance_counter << std::endl;
	std::cout << "time_counter: " << m_time_counter << std::endl;
	std::cout << "performance: " << m_performance_counter / static_cast<double>(m_time_counter) << std::endl;
	std::cout << "operations: " << m_time_counter << std::endl;
}
