#pragma once
#include <memory>
#include "OpenGlFrameBuffer.h"
#include "UIComponent.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include <filesystem>
#include <string>

class SceneView : public UIComponent
{
public:
    SceneView() : camera(nullptr), frameBuffer(nullptr), size(800, 600)
    {
        frameBuffer = std::make_unique<OpenGlFrameBuffer>();
        frameBuffer->create_buffers(800, 600);
        
       // mLight = std::make_unique<nelems::Light>();
        camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    }

    void resize(int32_t width, int32_t height);

    virtual void Render();

private:
    std::unique_ptr<Camera> camera;
    std::unique_ptr<OpenGlFrameBuffer> frameBuffer;
    glm::vec2 size;
};
