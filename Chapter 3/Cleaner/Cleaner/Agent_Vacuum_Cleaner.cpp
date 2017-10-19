#include "Agent_Vacuum_Cleaner.h"
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
		float delta_x = m_x_speed * m_x_direction;
		float delta_y = m_y_speed * m_y_direction;
		if (!area.get_tile_on_pos(this->getPosition().x + delta_x, this->getPosition().y + delta_y)
			.is_obstacle())
		{
			this->move(delta_x, delta_y);
			change_direction_random();
		}
		else
		{
			change_direction_random();
		}
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

void Agent_Vacuum_Cleaner::plot_statistics()
{
	std::cout << "performance_counter: " << m_performance_counter << std::endl;
	std::cout << "time_counter: " << m_time_counter << std::endl;
	std::cout << "performance: " << m_performance_counter / static_cast<double>(m_time_counter) << std::endl;
	std::cout << "operations: " << m_time_counter << std::endl;
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


Area_Model::Area_Model(const Area& area, int start_row, int start_column)
	:
	m_start_row(start_row),
	m_start_column(start_column)
{
	//calculate heuristic
	m_heuristic_value = heuristic_function(area);

	//fill model
	for (int r = 0; r < area.row_count(); r++)
	{
		std::vector<Tile_Model> row;
		for (int c = 0; c < area.column_count(); c++)
		{
			row.push_back(Tile_Model(0, area[r][c].is_obstacle()));
		}
		m_tiles.push_back(row);
	}
}

//in best case the cleaner only needs to move over every tile ones
//and can clean the tile where he started without moving
int Area_Model::heuristic_function(const Area& area)
{
	return area.column_count() * area.row_count() - 1;
}

std::queue<Actions>  Area_Model::generate_solution(const Area_Model& area)
{
	struct Path
	{
		int					 path_cost = 0;
		int					 actual_row;
		int					 actual_column;
		std::vector<Actions> actions;
	};

	auto cmp = [](Path& left, Path& right) { return left.path_cost < right.path_cost; };

	std::priority_queue<Path, std::deque<Path>, decltype(cmp)>	paths(cmp);
	
	Path actual_path = initial_path(area);

	do
	{
		//TODO
		paths.push(possible_paths(actual_path));

		actual_path = paths.top();
		paths.pop();
	} while (actual_path.path_cost >= paths.top().path_cost);
}
