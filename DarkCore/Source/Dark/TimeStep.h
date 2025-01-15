#pragma once

namespace Dark {

	class TimeStep
	{
	public:
		TimeStep(double delta);

		double getProgramTime();
		double getProgramTimeMilliseconds();
		double getDeltatime();
	private:
		double deltatime;
	};

}