#pragma once

#include "Dark/Renderer/Renderer2D.h"
#include "Dark/Application.h"
#include "Dark/EntryPoint.h"
#include "Dark/SoundEngine.h"
#include "Dark/Input.h"
#include "Dark/Logger.h"
#include "imgui.h"

#define BIND_FN(x) std::bind(x, this, std::placeholders::_1)