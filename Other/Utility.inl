
#include <SFML/Graphics/Rect.hpp>
#include <numeric>

template <typename T>
void centerOrigin(T& transformable)
{
	sf::FloatRect bounds = transformable.getLocalBounds();
	transformable.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

template <typename T>
sf::String ToStr(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

template<typename Enum>
constexpr auto toInt(Enum e)
{
   return static_cast<typename std::underlying_type<Enum>::type>(e);
}

template<typename Enum>
std::vector<short> getRange()
{
    std::vector<short> vec(toInt<Enum>(Enum::Count), 0);
    std::iota(vec.begin(), vec.end(), 0);
    return vec;
}
