#include "AssetManager.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::GetInstance()
{
	return instance;
}

bool AssetManager::Init()
{
	if (instance = new AssetManager())
		return true;
	return false;
}

std::vector<Model*> AssetManager::GetModels()
{
	return instance->models;
}

std::vector<LightSource*> AssetManager::GetLightSources()
{
	return instance->lightSources;
}

std::shared_ptr<Shader> AssetManager::GetLightShader()
{
	return instance->lightShader;
}

std::shared_ptr<Shader> AssetManager::GetObjectShader()
{
	return instance->objectShader;
}

void AssetManager::DeleteModels()
{
    for (auto it = instance->models.begin(); it != instance->models.end(); )
    {
        if ((*it)->toDelete)
        {
            delete* it;
            it = instance->models.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void AssetManager::CreateModel(std::string path, std::string name)
{
	instance->models.push_back(new Model(path, name));
}

void AssetManager::CreateLightSource(std::string path, std::string name)
{

}

