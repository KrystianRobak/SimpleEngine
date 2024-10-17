#pragma once
#include <memory>
#include "OpenGlFrameBuffer.h"
#include "UIComponent.h"

#include <filesystem>
#include <string>

class SceneView : public UIComponent
{
public:
    SceneView(std::shared_ptr<Application> application) : frameBuffer(nullptr), size(800, 600)
    {
        frameBuffer = std::make_unique<OpenGlFrameBuffer>();
        frameBuffer->create_buffers(800, 600);
       // mLight = std::make_unique<nelems::Light>();
        std::cout << application << std::endl;
    }


    void resize(int32_t width, int32_t height);

    virtual void Render();

private:
    std::unique_ptr<OpenGlFrameBuffer> frameBuffer;
    glm::vec2 size;
};
