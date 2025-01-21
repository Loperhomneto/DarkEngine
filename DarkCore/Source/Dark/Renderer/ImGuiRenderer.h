#pragma once

namespace Dark
{

	class ImGuiRenderer
	{
	public:
		void Init();
		void Shutdown();

		void StartRendererCall();
		void EndRendererCall();
	};			

}
