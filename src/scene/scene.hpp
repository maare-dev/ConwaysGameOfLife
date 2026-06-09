#pragma once
#include <memory>
#include <unordered_map>

class Scene {
public:
    virtual ~Scene() = default;
    virtual void DrawFrame() = 0;
};

std::shared_ptr<Scene> GetCurrentScene();

void AddScene(int id, std::shared_ptr<Scene> scn);

int GetCurrentSceneId();
void SetCurrentSceneId(int id);

std::unordered_map<int, std::shared_ptr<Scene>>& GetScenes();
void SetScenes(std::unordered_map<int, std::shared_ptr<Scene>>& scenes_map);

void ClearScenes();
