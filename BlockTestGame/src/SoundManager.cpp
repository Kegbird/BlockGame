#include "headers/SoundManager.hpp"

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
    _sound_player.setVolume(10);
    _button_sound_fx_buffer.loadFromFile(BUTTON_SOUND_FX_FILE);
    _bomb_sound_fx_buffer.loadFromFile(BOMB_SOUND_FX_FILE);
    _stripe_sound_fx_buffer.loadFromFile(STRIPE_SOUND_FX_FILE);
    _wrong_action_sound_fx_buffer.loadFromFile(WRONG_ACTION_FX_FILE);
    _reduce_sound_fx_buffer.loadFromFile(REDUCE_SOUND_FX_FILE);
}

SoundManager* SoundManager::GetInstance()
{
    if (instance == nullptr) {
        instance = new SoundManager();
    }
    return instance;
}

void SoundManager::PlaySound(SoundType sound_type)
{
    sf::SoundBuffer* buffer = nullptr;
    switch (sound_type)
    {
    case BUTTON_SOUND:
        buffer = &_button_sound_fx_buffer;
        break;
    case BOMB_SOUND:
        buffer = &_bomb_sound_fx_buffer;
        break;
    case STRIPE_SOUND:
        buffer = &_stripe_sound_fx_buffer;
        break;
    case WRONG_ACTION_SOUND:
        buffer = &_wrong_action_sound_fx_buffer;
        break;
    case REDUCE_SOUND:
        buffer = &_reduce_sound_fx_buffer;
        break;
    }
    _sound_player.setBuffer(*buffer);
    _sound_player.play();
}


void SoundManager::Delete()
{
    delete instance;
    instance = nullptr;
}