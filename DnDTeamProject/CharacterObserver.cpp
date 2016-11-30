#include "CharacterObserver.h"



CharacterObserver::CharacterObserver(Character* model, Map* context) : _model(model), _context(context) {
	_model->attach(this);
}

CharacterObserver::~CharacterObserver() {
	_model->detach(this);
}

void CharacterObserver::update() {
	_context->draw();
}
