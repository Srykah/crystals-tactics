#ifndef BOOK_DATATABLES_HPP
#define BOOK_DATATABLES_HPP

#include "../Other/ResourceIdentifiers.hpp"

#include <SFML/System/String.hpp>

#include <vector>

struct MissionData
{
	int rank;
	sf::String name;
	sf::String description;
	int prime;
	std::string battlePath;
};

std::vector<MissionData>	initializeMissionData();

#endif // BOOK_DATATABLES_HPP
