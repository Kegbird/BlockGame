#pragma once

#pragma once
#include "SFML/Audio.hpp"
#include "Constants.hpp"

class SoundManager
{
public:
    static SoundManager* GetInstance();
    SoundManager(SoundManager& other) = delete;
    void operator=(const SoundManager&) = delete;
    void PlaySound(SoundType sound_type);
    void Delete();
private:
    SoundManager();
    static SoundManager* instance;
    sf::Sound _sound_player;
    sf::SoundBuffer _button_sound_fx_buffer;
    sf::SoundBuffer _bomb_sound_fx_buffer;
    sf::SoundBuffer _stripe_sound_fx_buffer;
    sf::SoundBuffer _wrong_action_sound_fx_buffer;
    sf::SoundBuffer _reduce_sound_fx_buffer;
};