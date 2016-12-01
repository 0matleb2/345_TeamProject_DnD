#include "Observable.h"

Observable::Observable(){
}

Observable::~Observable(){
}

void Observable::attach(Observer* observer) {
	_views.push_back(observer);
}

void Observable::detach(Observer* observer) {
	int pos = std::find(_views.begin(), _views.end(), observer) - _views.begin();
	_views.erase(_views.begin() + pos);
}

void Observable::notify() {
	for (int i = 0, n = _views.size(); i < n; i++) {
		_views[i]->update();
	}
}