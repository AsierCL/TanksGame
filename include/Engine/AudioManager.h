#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#pragma once
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioManager {
public:
    static AudioManager& get() {
        static AudioManager inst;
        return inst;
    }

    // inicializa SDL_mixer; devuelve false en fallo
    bool init(int freq = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048) {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            SDL_Log("SDL_Init audio error: %s", SDL_GetError());
            return false;
        }
        if (Mix_OpenAudio(freq, format, channels, chunksize) < 0) {
            SDL_Log("Mix_OpenAudio error: %s", Mix_GetError());
            return false;
        }
        return true;
    }

    // carga un efecto de sonido en memoria
    bool loadSound(const std::string& name, const std::string& path) {
        Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
        if (!chunk) {
            SDL_Log("Mix_LoadWAV error: %s", Mix_GetError());
            return false;
        }
        sounds[name] = chunk;
        return true;
    }

    // reproduce un sonido (canal libre, sin bucle)
    void playSound(const std::string& name) {
        auto it = sounds.find(name);
        if (it != sounds.end()) {
            Mix_PlayChannel(-1, it->second, 0);
        }
    }

    int playLoop(const std::string& name, int loops = -1) {
        auto it = sounds.find(name);
        if (it == sounds.end()) return -1;
        return Mix_PlayChannel(-1, it->second, loops);
    }

    // Detiene un canal dado
    void stopChannel(int channel) {
        if (channel >= 0) Mix_HaltChannel(channel);
    }


       // Música de fondo (más larga, en bucle)
       bool loadMusic(const std::string& name, const std::string& path) {
        Mix_Music* mus = Mix_LoadMUS(path.c_str());
        if (!mus) {
            SDL_Log("Mix_LoadMUS error: %s", Mix_GetError());
            return false;
        }
        music[name] = mus;
        return true;
    }

    // loops = -1 → bucle infinito, 0 → una vez, N → N+1 veces
    void playMusic(const std::string& name, int loops = -1) {
        auto it = music.find(name);
        if (it != music.end()) {
            Mix_PlayMusic(it->second, loops);
        }
    }

    void stopMusic() {
        Mix_HaltMusic();
    }


    // limpiar al cerrar
    void shutdown() {
        for (auto& kv : sounds) {
            Mix_FreeChunk(kv.second);
        }
        sounds.clear();
        Mix_CloseAudio();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }

    private:
    AudioManager() = default;
    ~AudioManager() = default;
    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, Mix_Music*> music;
};

#endif // AUDIOMANAGER_H