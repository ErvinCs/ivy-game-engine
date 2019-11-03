#pragma once

namespace Ivy {

	class Timestep
	{
	private:
		float time = 0;

	public:
		Timestep(float time = 0.0f)
		{
			this->time = time;
		}

		float operator+(const float seconds)
		{
			this->time += seconds;
		}

		float operator+=(const float seconds)
		{
			this->time += seconds;
		}

		float operator-(const float seconds)
		{
			this->time -= seconds;
		}

		float operator-=(const float seconds)
		{
			this->time -= seconds;
		}

		/*
		 * Allow time to be cast to a float value
		 */
		operator float() const {
			return this->time;
		}

		float getSeconds() const {
			return time;
		}

		float getMilliseconds() const {
			return time * 1000.0f;
		}

	};

}