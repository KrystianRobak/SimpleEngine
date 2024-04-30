#pragma once
#include <memory>
#include "OpenGlFrameBuffer.h"
#include "UIComponent.h"
#include "Application.h"
#include <filesystem>
#include <string>

class SceneView : public UIComponent
{
public:
    SceneView() : application(nullptr), frameBuffer(nullptr), size(800, 600)
    {
        application = std::make_unique<Application>();
        application->Init();
        frameBuffer = std::make_unique<OpenGlFrameBuffer>();
        frameBuffer->create_buffers(800, 600);
       // mLight = std::make_unique<nelems::Light>();
        
    }


    void resize(int32_t width, int32_t height);

    virtual void Render();

private:
    std::unique_ptr<Application> application;
    std::unique_ptr<OpenGlFrameBuffer> frameBuffer;
    glm::vec2 size;
};
