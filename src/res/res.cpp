#include "res.hpp"
#include <raylib.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "../shell/shell.hpp"

std::unordered_map<int, Texture> textures;
std::unordered_map<int, Sound> sounds;
void ExecuteResCommand(std::vector<std::string> args){
    if (args.size() == 1){
        if (args[0] == "unload_all_textures"){
            UnloadAllTextures();
        }
        else if (args[0] == "unload_all_sounds"){
            UnloadAllSounds();
        }
        else if (args[0] == "unload_all_res"){
            UnloadAllRes();
        }
    }
}

void RegisterResCommands(){
    RegisterCommand("res", ExecuteResCommand);
}
Texture GetTexture(int id){
    return textures[id];
}
void SetTexture(int id, Texture tex){
    textures[id] = tex;
}
std::unordered_map<int, Texture>& GetAllTextures(){
    return textures;
}
void SetAllTextures(std::unordered_map<int, Texture> &textures_map){
    textures = textures_map;
}
Sound GetSound(int id){
    return sounds[id];
}
void SetSound(int id, Sound snd){
    sounds[id] = snd;
}
std::unordered_map<int, Sound>& GetAllSounds(){
    return sounds;
}
void SetAllSounds(std::unordered_map<int, Sound> &sounds_map){
    sounds = sounds_map;
}
void UnloadAllTextures(){
    for (auto& [id, tex] : textures){
        UnloadTexture(tex);
    }
}
void UnloadAllSounds(){
    for (auto& [id, snd] : sounds){
        UnloadSound(snd);
    }
}
void UnloadAllRes(){
    UnloadAllTextures();
    UnloadAllSounds();
}
