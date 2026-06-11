#include "scene.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include "../shell/shell.hpp"

std::unordered_map<int, std::shared_ptr<Scene>> scenes;
int currentSceneId = 0;
void ExecuteSceneCommand(std::vector<std::string> args){
    if (args.size() == 2){
        if (args[0] == "set_current_scene_id"){
            try{
                SetCurrentSceneId(std::stoi(args[1]));
            }catch(...){}
        }
    }
}

void RegisterSceneCommands(){
    RegisterCommand("scene", ExecuteSceneCommand);
}
std::shared_ptr<Scene> GetCurrentScene(){
    return scenes[currentSceneId];
}
void AddScene(int id, std::shared_ptr<Scene> scn){
    scenes[id] = scn;
}
int GetCurrentSceneId(){
    return currentSceneId;
}
void SetCurrentSceneId(int id){
    currentSceneId = id;
}
std::unordered_map<int, std::shared_ptr<Scene>>& GetScenes(){
    return scenes;
}
void SetScenes(std::unordered_map<int, std::shared_ptr<Scene>>& scenes_map){
    scenes = scenes_map;
}
void ClearScenes(){
    scenes.clear();
}
