#include "Game.h"
#include "Physics.h"

#include <memory>

void Game::run()
{
	std::cout << 
		"Usage:\n"
		"i: 1000 iterations\n"
		"o: one iteration\n"
		"s: plot statistics\n"
		<< std::endl;
	while (this->isOpen())
	{
		Physics::update_time();

		sf::Event event;
		while (this->	pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->	close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					for (int i = 0; i < 1000; i++)
						this->m_cleaner.act(this->m_cleaning_area);
					m_cleaner.plot_statistics();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
					this->m_cleaner.act(this->m_cleaning_area);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
					this->m_cleaner.plot_statistics();
			}
		}
		this->			clear();

		this->			draw(m_background);
		
		//draw area
		m_cleaning_area.draw_to_window(this);

		//draw cleaner
		this->			draw(m_cleaner);
		
		this->			display();

		sf::sleep(sf::milliseconds(41));
	}
}

Area& Game::area_factory_std(int width, int height, int row_count, int column_count)
{
	int row_count_with_border	 = row_count + 2;
	int column_count_with_border = column_count + 2;
	auto area					 = std::make_unique<Area>(width, height, 
									row_count_with_border, column_count_with_border);

	
	for (int h = 0; h < area->row_count(); h++)
	{
		std::vector<Tile> row;
		for (int w = 0; w < area->column_count(); w++)
		{
			if ((h == 0) || (h == area->row_count() - 1)
				|| (w == 0) || (w == area->column_count() - 1))
			{
				row.push_back(Tile(
					area->horizontal_tile_size(),
					area->vertical_tile_size(),
					w * area->horizontal_tile_size(),
					h * area->vertical_tile_size(),
					false,
					true,
					(h * area->column_count()) + w));
			}
			else
			{
				row.push_back(Tile(
					area->horizontal_tile_size(),
					area->vertical_tile_size(),
					w * area->horizontal_tile_size(),
					h * area->vertical_tile_size(),
					true,
					false,
					(h * area->column_count()) + w));
			}
		}
		area->add_row(row);
	}
	return *area.release();
}


Area& Game::area_factory_random_obstacles(int width, int height, int row_count, int column_count, int obstacle_count)
{
	Area& area = area_factory_std(width, height, row_count, column_count);

	std::random_device					rd;
	std::uniform_int_distribution<int>	dist_w(0, area.column_count() - 1);
	std::uniform_int_distribution<int>	dist_h(0, area.row_count() - 1);

	for (int i = 0; i < obstacle_count; i++)
	{
		int w = dist_w(rd);
		int h = dist_h(rd);

		if (area[h][w].is_obstacle())
		{
			i--;
		}
		else
		{
			area[h][w].is_obstacle() = true;
			area[h][w].update_color();
		}
	}
	return area;
}


//will fail if there is no tile that's no obstacle
void Game::place_on_rand_tile(Agent_Vacuum_Cleaner& cleaner)
{
	//place the cleaner on a random position that's no obstacle
	std::random_device					rd;
	std::uniform_int_distribution<int>	dist_h(0, m_cleaning_area.column_count() - 1);
	std::uniform_int_distribution<int>	dist_v(0, m_cleaning_area.row_count() - 1);

	float h_tile_distance;
	float v_tile_distance;
	do
	{
		int h_tile_count = dist_h(rd);
		int v_tile_count = dist_v(rd);

		h_tile_distance = h_tile_count * m_cleaning_area.horizontal_tile_size() + m_cleaning_area.horizontal_tile_size() / 2;
		v_tile_distance = v_tile_count * m_cleaning_area.vertical_tile_size() + m_cleaning_area.vertical_tile_size() / 2;
	} while (m_cleaning_area.get_tile_on_pos(h_tile_distance, v_tile_distance).is_obstacle());

	cleaner.setPosition(h_tile_distance, v_tile_distance);
}
