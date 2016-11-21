#include "CursorObserver.h"



CursorObserver::CursorObserver(Cursor* model, Map* context) : _model(model), _context(context) {
	_model->attach(this);
}

CursorObserver::~CursorObserver() {
}

void CursorObserver::update() {
	_context->draw();
}
