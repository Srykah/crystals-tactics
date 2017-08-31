#include "States/Arch/Context.hpp"

States::Context::Context(sf::RenderWindow& window,
                         Data::TextureHolder& textures,
                         Data::FontHolder& fonts,
                         Sound::MusicPlayer& music,
                         Sound::SoundPlayer& sounds,
                         Data::EntityHolder& entities,
                         Data::StatsHolder& stats,
                         Data::EquipmentHolder& equipments,
                         Data::WeaponHolder& weapons,
                         Data::ConsumableHolder& consumables,
                         Data::AbilityHolder& abilities,
                         Guild& guild)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, music(&music)
, sounds(&sounds)
, entities(&entities)
, stats(&stats)
, equipments(&equipments)
, weapons(&weapons)
, consumables(&consumables)
, abilities(&abilities)
, guild(&guild)
{

}
