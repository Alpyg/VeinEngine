#pragma once

#include "Core/Core.h"

namespace Vein
{

    class VN_API Input
    {
    public:
        inline static bool IsKeyPressed(int t_KeyCode) { return s_Instance->IsKeyPressedImpl(t_KeyCode); };

        inline static bool IsMouseButtonPressed(int t_Button) { return s_Instance->IsMouseButtonPressedImpl(t_Button); };
        inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); };
        inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); };
        inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); };


    protected:
        virtual bool IsKeyPressedImpl(int t_KeyCode) = 0;

        virtual bool IsMouseButtonPressedImpl(int t_Button) = 0;
        virtual std::pair<float, float> GetMousePosImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
    private:
        static Input* s_Instance;
    };

}
