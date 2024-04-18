#pragma once
#include "Model.h"
#include "LightSource.h"

class AssetManager
{
public:


	static AssetManager* GetInstance();
	static bool Init();
	std::vector<Model*> GetModels();
	std::vector<LightSource*> GetLightSources();
	std::shared_ptr<Shader> GetLightShader();
	std::shared_ptr<Shader> GetObjectShader();

	static void DeleteModels();
	void CreateModel(std::string path, std::string name);
	void CreateLightSource(std::string path, std::string name);
private:
	AssetManager() : objectShader(nullptr), lightShader(nullptr)
	{
		objectShader = std::make_unique<Shader>("shaders/DefaultLightedCubeShader/DefaultCube_VertexShader.vs", "shaders/DefaultLightedCubeShader/DefaultCube_FragmentShader.fs");
		lightShader = std::make_unique<Shader>("shaders/LightSourceShader/LightSource_VertexShader.vs", "shaders/LightSourceShader/LightSource_FragmentShader.fs");
	}

	static AssetManager* instance;


	std::vector<Model*> models;
	std::vector<LightSource*> lightSources;

	std::shared_ptr<Shader> objectShader;
	std::shared_ptr<Shader> lightShader;
};

