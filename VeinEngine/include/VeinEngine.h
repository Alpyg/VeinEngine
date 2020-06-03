#pragma once

// === Core =======================================================
// ================================================================
#include "Core/Core.h"

#include "Core/Application/Application.h"

#include "Core/Assert/Assert.h"

#include "Core/Events/Event.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

#include "Core/Input/Input.h"
#include "Core/Input/KeyCodes.h"
#include "Core/Input/MouseButtonCodes.h"

#include "Core/Logger/Logger.h"

#include "Core/Math/Math.h"

#include "Core/Memory/Allocator.h"
#include "Core/Memory/FreeListAllocator.h"
#include "Core/Memory/LinearAllocator.h"
#include "Core/Memory/Pointers.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/Memory/ProxyAllocator.h"
#include "Core/Memory/StackAllocator.h"

#include "Core/Profiling/Instrumentor.h"
#include "Core/Profiling/InstrumentorTimer.h"

#include "Core/Random/Random.h"

#include "Core/String/String.h"

#include "Core/UUID/UUID.h"

// === Renderer ===================================================
// ================================================================
#include "Renderer/Buffer.h"
#include "Renderer/Camera.h"
#include "Renderer/Context.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"