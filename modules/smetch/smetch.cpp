/* smetch.cpp */

#include "smetch.h"
#include <iostream>

Vector2 Smetch::get_mouse_position() {
	return viewport->get_mouse_position();
}

void Smetch::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_mouse_position"), &Smetch::get_mouse_position);
	ClassDB::bind_method(D_METHOD("create_canvas"), &Smetch::create_canvas);
}


void Smetch::create_canvas(int x, int y) {
	std::cout << "create canvas" << std::endl;

  //xxxxxxxxxxxxxxx
  // todo : if this gets called again then need to clear the old objects

  Size2 s2 = Size2(x, y);
  this->set_size(s2);

	viewport = memnew(SubViewport);
	viewport->set_size_2d_override_stretch(true);
  viewport->set_size(s2);

	panel_container = memnew(PanelContainer);
  panel_container->set_size(s2);

	viewport->add_child(panel_container);
	this->add_child(viewport);

	std::cout << "create canvas end" << std::endl;
}

Smetch::Smetch(){}

// todo : destructor
