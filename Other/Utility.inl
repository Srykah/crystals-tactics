
#include <SFML/Graphics/Rect.hpp>

template <typename T>
void centerOrigin(T& transformable)
{
	sf::FloatRect bounds = transformable.getLocalBounds();
	transformable.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}
