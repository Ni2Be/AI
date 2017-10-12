#include "Game.h"

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

Area& Game::area_factory_std(int width, int height, int column_count, int row_count)
{
	auto area = std::make_unique<Area>(new Area(width, height, column_count, row_count));

	float horizontal_tile_size	= width  / static_cast<float>(column_count);
	float vertical_tile_size	= height / static_cast<float>(row_count);

	for (int h = 0; h < row_count + 2; h++)
	{
		std::vector<Tile> row;
		for (int w = 0; w < column_count + 2; w++)
		{
			if ((h == 0) || (h == row_count + 1)
				|| (w == 0) || (w == column_count + 1))
			{
				row.push_back(Tile(
					horizontal_tile_size,
					vertical_tile_size,
					w * horizontal_tile_size,
					h * vertical_tile_size,
					true,
					true,
					(h * column_count) + w));
			}
			else
			{
				row.push_back(Tile(
					horizontal_tile_size,
					vertical_tile_size,
					w * horizontal_tile_size,
					h * vertical_tile_size,
					true,
					false,
					(h * column_count) + w));
			}
		}
		area.tiles.push_back(row);
	}
}