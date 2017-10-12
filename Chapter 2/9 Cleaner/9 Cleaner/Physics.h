#pragma once

#include <SFML/System/Clock.hpp>

#include <iostream>


class Physics
{
public:
	static void			update_time();

	static sf::Clock&	delta_clock() { return m_delta_clock; }
	static int			delta_time()  { return static_cast<int>(m_delta_time.asMilliseconds()); }
private:
	static sf::Time		m_delta_time;
	static sf::Clock	m_delta_clock;
};