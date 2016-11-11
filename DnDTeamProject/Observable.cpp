#include "Observable.h"
using namespace std;

//! constructor
Observable::Observable() {}

//! destructor
Observable::~Observable() {}

//! attaches an observer to the subject
void Observable::attach(Observer* obs) {
	views.push_back(obs);
}

//! detaches an observer from the subject
void Observable::detach(Observer* obs) {
	int pos = std::find(views.begin(), views.end(), obs) - views.begin();
	views.erase(views.begin() + pos);
}

//! Goes through list of attached Observers, and has them update accordingly based on subject's change in state
void Observable::notify() {
	for (int i = 0; i < views.size(); i++)
		views[i]->update();
}
