#include "scene.hpp"
#include <memory>
#include <unordered_map>

std::unordered_map<int, std::shared_ptr<Scene>> scenes;
int currentSceneId = 0;

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
