#pragma once
#include <vector>

class Map;

class Observer {

	public:

		Observer() {};
		virtual ~Observer() {};

		virtual void update() = 0;

};

