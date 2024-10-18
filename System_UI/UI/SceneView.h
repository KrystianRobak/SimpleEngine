#pragma once
#include <memory>
#include "OpenGlFrameBuffer.h"
#include "UIComponent.h"

#include <filesystem>
#include <string>
#include <glm.hpp>

class SceneView : public UIComponent
{
public:
    SceneView() : frameBuffer(nullptr), size(800, 600)
    {
        frameBuffer = std::make_unique<OpenGlFrameBuffer>();
        frameBuffer->create_buffers(800, 600);
       // mLight = std::make_unique<nelems::Light>();
    }


    void resize(int32_t width, int32_t height);

    virtual void Render();

private:
    std::unique_ptr<OpenGlFrameBuffer> frameBuffer;
    glm::vec2 size;
};
