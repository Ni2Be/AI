#include "Game.h"


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