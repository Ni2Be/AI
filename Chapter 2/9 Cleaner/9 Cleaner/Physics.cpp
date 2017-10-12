#include "Physics.h"

void Physics::update_time()
{
	m_delta_time = m_delta_clock.restart();
}

sf::Time  Physics::m_delta_time  = sf::Time();
sf::Clock Physics::m_delta_clock = sf::Clock();
