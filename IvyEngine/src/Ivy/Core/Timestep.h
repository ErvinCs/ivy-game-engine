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
		~Timestep() = default;
		
		float operator*(const float& seconds) {
			this->time *= seconds;
			return time;
		}

		Timestep operator*(const Timestep& ts) {
			time *= ts.time;
			return *this;
		}

		float operator/(const float& seconds) {
			this->time /= seconds;
			return time;
		}

		Timestep operator/(const Timestep& ts) {
			time /= ts.time;
			return *this;
		}

		float operator+(const float& seconds)
		{
			this->time += seconds;
			return time;
		}

		Timestep operator+(const Timestep& ts) {
			time += ts.time;
			return *this;
		}

		float operator-(const float& seconds)
		{
			this->time -= seconds;
			return time;
		}


		Timestep operator-(const Timestep& ts) {
			time -= ts.time;
			return *this;
		}

		// ---------------------------------------------------------

		float& operator+=(const float& seconds)
		{
			this->time += seconds;
			return time;
		}

		Timestep& operator+=(const Timestep& ts) 
		{
			time += ts.time;
			return *this;
		}

		float& operator-=(const float& seconds) 
		{
			this->time -= seconds;
			return time;
		}

		Timestep& operator-=(const Timestep& ts) 
		{
			time -= ts.time;
			return *this;
		}

		float& operator*=(const float& seconds) {
			this->time *= seconds;
			return time;
		}

		Timestep& operator*=(const Timestep& ts) {
			time *= ts.time;
			return *this;
		}

		float& operator/=(const float& seconds) {
			this->time /= seconds;
			return time;
		}

		Timestep& operator/=(const Timestep& ts) {
			time /= ts.time;
			return *this;
		}

		// ---------------------------------------------------------

		bool operator==(const Timestep& other) const {
			return other.time == this->time;
		}

		bool operator!=(const Timestep& other) const {
			return other.time != this->time;
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

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

	};

}