#include "VeinEngine.h"
#include "Core/EntryPoint.h"

#include "SandboxLayer.h"

using namespace Vein;
class VeinSandbox : public Application
{
public:
    VeinSandbox() : Application("Vein Sandbox")
    {
        Renderer::Init(Renderer::API::OpenGL);
        PushLayer(new SandboxLayer());
    }

    ~VeinSandbox()
    {
    }
};

Vein::Application* Vein::CreateApplication()
{
    return new VeinSandbox();
}