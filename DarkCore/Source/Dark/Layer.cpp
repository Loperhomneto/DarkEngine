#include "Layer.h"

namespace Dark
{

	Layer::Layer()
	{
		Layer::OnAttach();
	}

	Layer::~Layer()
	{
		Layer::OnDetach();
	}

}
	