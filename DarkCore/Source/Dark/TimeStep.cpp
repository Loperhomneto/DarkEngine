#include "dkpch.h"
#include "TimeStep.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Dark {
	TimeStep::TimeStep(double delta) : deltatime(delta) {}

	double TimeStep::getProgramTime()
	{
		return glfwGetTime();
	}

	double TimeStep::getProgramTimeMilliseconds()
	{
		return glfwGetTime() * 1000;
	}

	double TimeStep::getDeltatime()
	{
		return deltatime;
	}

}