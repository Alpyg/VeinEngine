#include "SandboxLayer.h"

namespace Vein
{
	struct Object
	{
		uint32_t a = 0xFFFFFFFF, b = 0xCCCCCCCC, c = 0xCCCCCCCC, d = 0xFFFFFFFF;
	};

    SandboxLayer::SandboxLayer()
        : Layer("SandboxLayer")
    {
		Renderer::SetClearColor({ 0.05f, 0.05f, 0.05f, 1.0f });
    }

	SandboxLayer::~SandboxLayer()
	{
	}

	void SandboxLayer::OnAttach()
	{
	}

	void SandboxLayer::OnDetach()
	{
	}

	void SandboxLayer::OnUpdate()
	{
		Renderer::Clear();

		//if (Input::IsKeyPressed(VEIN_KEY_W))
		//	m_Camera->transform->Translate({ 0, 0, -m_CameraMoveSpeed * Time::GetDeltaTime() });
		//else if (Input::IsKeyPressed(VEIN_KEY_S))
		//	m_Camera->transform->Translate({ 0, 0, +m_CameraMoveSpeed * Time::GetDeltaTime() });
		//
		//if (Input::IsKeyPressed(VEIN_KEY_A))
		//	m_Camera->transform->Translate({ -m_CameraMoveSpeed * Time::GetDeltaTime(), 0, 0 });
		//else if (Input::IsKeyPressed(VEIN_KEY_D))
		//	m_Camera->transform->Translate({ +m_CameraMoveSpeed * Time::GetDeltaTime(), 0, 0 });
		//
		//if (Input::IsKeyPressed(VEIN_KEY_SPACE))
		//	m_Camera->transform->Translate({ 0, +m_CameraMoveSpeed * Time::GetDeltaTime(), 0 });
		//else if (Input::IsKeyPressed(VEIN_KEY_LEFT_SHIFT))
		//	m_Camera->transform->Translate({ 0, -m_CameraMoveSpeed * Time::GetDeltaTime(), 0 });
		//
		//if (Input::IsMouseButtonPressed(VEIN_MOUSE_BUTTON_1))
		//	m_Camera->GetComponent<Camera>()->ScreenToRay({ Input::GetMouseX(), Input::GetMouseY() });
		
		//auto cam = m_Camera->GetComponent<Camera>();
		//cam->GetViewProjectionMatrix();
		//Renderer::BeginScene(cam);
		//
		//for (auto& object : m_Model0->GetChildren())
		//{
		//	object->GetComponent<Material>()->SetColor("", Vec4(1, 1, 1, 1));
		//	Renderer::Submit(object);
		//}
		//for (auto& object : m_Model1->GetChildren())
		//{
		//	object->GetComponent<Material>()->SetColor("", Vec4(1, 1, 0, 1));
		//	Renderer::Submit(object);
		//}
		//for (auto& object : m_Model2->GetChildren())
		//{
		//	object->GetComponent<Material>()->SetColor("", Vec4(0, 1, 1, 1));
		//	Renderer::Submit(object);
		//}
		//
		//Renderer::EndScene();
	}

	void SandboxLayer::OnEvent(Event& t_Event)
	{
		EventDispatcher dispatcher(t_Event);

		if (Input::IsMouseButtonPressed(VN_MOUSE_BUTTON_2))
		{
			if (t_Event.GetEventType() == EventType::MouseMoved)
			{
				dispatcher.Dispatch<MouseMovedEvent>(VN_BIND_EVENT_FN(SandboxLayer::OnMouseMovedEvent));
			}
		}
	}

	bool SandboxLayer::OnMouseMovedEvent(MouseMovedEvent& t_Event)
	{
		float x = t_Event.GetX();
		float l = t_Event.GetLastX();
		float offsetX = t_Event.GetX() - t_Event.GetLastX();
		float offsetY = t_Event.GetLastY() - t_Event.GetY();

		offsetX *= m_CameraRotationSpeed;
		offsetY *= m_CameraRotationSpeed;
		//m_Camera->transform->Rotate({ offsetY, offsetX, 0.0f});

		return true;
	}

}