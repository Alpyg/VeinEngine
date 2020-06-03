#pragma once

#include <Core/Input/Input.h>

namespace Vein
{

    class VN_API WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int t_KeyCode) override;

        virtual bool IsMouseButtonPressedImpl(int t_Button) override;
        virtual std::pair<float, float> GetMousePosImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };

}
