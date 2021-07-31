/* smetch.h */

#ifndef SMETCH_H
#define SMETCH_H

#include "scene/gui/subviewport_container.h"
#include "scene/main/viewport.h"
#include "scene/gui/panel_container.h"

class Smetch : public SubViewportContainer {
	GDCLASS(Smetch, SubViewportContainer);

protected:
	static void _bind_methods();

public:

  void create_canvas(int x, int y);
  Vector2 get_mouse_position();

	Smetch();

private:
  SubViewport *viewport;
  PanelContainer *panel_container;
};

#endif // SMETCH_H
