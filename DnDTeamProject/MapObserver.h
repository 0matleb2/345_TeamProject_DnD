#pragma once
#include "Observer.h"



class MapObserver: public Observer {

	public:

		MapObserver(Map* model);
		~MapObserver();

		void update();

	private:

		Map* _model;

	};

