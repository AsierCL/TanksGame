#include <iostream>
#include "../../include/Engine/AudioManager.h"
#include "../../include/Engine/AudioInit.h"


void initAudio(){
    if (!AudioManager::get().init()) {
        std::cerr << "No se pudo inicializar audio\n";
    }
    
    AudioManager::get().loadSound("hit",   "./assets/audio/hit.wav");
    AudioManager::get().loadSound("shoot", "./assets/audio/shoot.wav");
    AudioManager::get().loadSound("tank", "./assets/audio/tank-moving.wav");
    AudioManager::get().loadSound("turret", "./assets/audio/turret.wav");
    AudioManager::get().loadSound("wall", "./assets/audio/wallHit.wav");
    AudioManager::get().loadMusic("bgm", "./assets/audio/bgSound.wav");
    
    AudioManager::get().playMusic("bgm", -1);  // bucle infinito
    // ajustar volumen de fondo
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}
