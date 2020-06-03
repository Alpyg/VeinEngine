#pragma once

#include <VeinEngine.h>

namespace Vein
{

    class SandboxLayer : public Layer
    {
    public:
        SandboxLayer();
        virtual ~SandboxLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& t_Event) override;
    private:
        bool OnMouseMovedEvent(MouseMovedEvent& t_Event);

        Ref<Shader> m_Shader;
        float m_CameraMoveSpeed = 5.0f;
        float m_CameraRotationSpeed = 0.2f;
    };

}