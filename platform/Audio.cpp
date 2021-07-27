#include "GLPlatformLayer.hpp"
#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <iostream>
#include <exception>

struct jzj::GLPlatformLayer::Audio::implementation {
    std::unordered_map<std::string, Mix_Chunk*> audioChunks;
    std::unordered_map<std::string, Mix_Music*> audioMusic;
};

jzj::GLPlatformLayer::Audio::Audio(jzj::GLPlatformLayer *layer) {
    this->impl = new jzj::GLPlatformLayer::Audio::implementation;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

jzj::GLPlatformLayer::Audio::~Audio() {
    Mix_CloseAudio();
    delete this->impl;
}

int jzj::GLPlatformLayer::Audio::playSound(const std::string &path, int loops, int channel) {
    if (impl->audioChunks.find(path) == impl->audioChunks.end()) {
        impl->audioChunks[path] = Mix_LoadWAV(path.c_str());
        if (!impl->audioChunks[path]) {
            throw std::runtime_error("Unable to load sound from: " + path + "\n" + SDL_GetError());
        }
    }
    int res = Mix_PlayChannel(channel, impl->audioChunks[path], loops);
    if (res < 0) {
        throw std::runtime_error("Unable to play sound from: " + path);
    }
    return res;
}

void jzj::GLPlatformLayer::Audio::playMusic(const std::string &path, int loops) {
    if (impl->audioMusic.find(path) == impl->audioMusic.end()) {
        impl->audioMusic[path] = Mix_LoadMUS(path.c_str());
        if (!impl->audioMusic[path]) {
            throw std::runtime_error("Unable to load music from: " + path);
        }
    }
    if (Mix_PlayMusic(impl->audioMusic[path], loops) < 0) {
        throw std::runtime_error("Unable to play music from: " + path + "\n" + SDL_GetError());
    }
}

void jzj::GLPlatformLayer::Audio::stopMusic() {
    Mix_HaltMusic();
}

void jzj::GLPlatformLayer::Audio::stopSoundChannel(int channel) {
    Mix_HaltChannel(channel);
}

bool jzj::GLPlatformLayer::Audio::isPlayingMusic() {
    return Mix_PlayingMusic();
}

bool jzj::GLPlatformLayer::Audio::isPlayingSoundChannel(int channel) {
    return Mix_Playing(channel);
}

int jzj::GLPlatformLayer::Audio::setMusicVolume(int volume) {
    return Mix_VolumeMusic(volume);
}

int jzj::GLPlatformLayer::Audio::setSoundVolume(const std::string &path, int volume) {
    if (impl->audioChunks.find(path) != impl->audioChunks.end()) {
        return Mix_VolumeChunk(impl->audioChunks[path], volume);
    }
    return -1;
}

void jzj::GLPlatformLayer::Audio::loadMusic(const std::string &path) {
    if (impl->audioMusic.find(path) == impl->audioMusic.end()) {
        impl->audioMusic[path] = Mix_LoadMUS(path.c_str());
        if (!impl->audioMusic[path]) {
            throw std::runtime_error("Unable to load sound from: " + path);
        }
    }
}

void jzj::GLPlatformLayer::Audio::loadSound(const std::string &path) {
    if (impl->audioChunks.find(path) == impl->audioChunks.end()) {
        impl->audioChunks[path] = Mix_LoadWAV(path.c_str());
        if (!impl->audioChunks[path]) {
            throw std::runtime_error("Unable to load sound from: " + path + "\n" + SDL_GetError());
        }
    }
}
