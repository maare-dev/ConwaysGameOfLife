#pragma once
#include <raylib.h>
#include <unordered_map>


void RegisterResCommands();
Texture GetTexture(int id);
void SetTexture(int id, Texture tex);

std::unordered_map<int, Texture>& GetAllTextures();
void SetAllTextures(std::unordered_map<int, Texture>& textures_map);

Sound GetSound(int id);
void SetSound(int id, Sound snd);

std::unordered_map<int, Sound>& GetAllSounds();
void SetAllSounds(std::unordered_map<int, Sound>& sounds_map);

void UnloadAllTextures();
void UnloadAllSounds();
void UnloadAllRes();
