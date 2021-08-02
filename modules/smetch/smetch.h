/* smetch.h */

#ifndef SMETCH_H
#define SMETCH_H

#include "scene/gui/panel_container.h"
#include "scene/gui/subviewport_container.h"
#include "scene/main/viewport.h"

class Smetch : public SubViewportContainer {
	GDCLASS(Smetch, SubViewportContainer);

protected:
	static void _bind_methods();

public:
	enum Constants {
    RGB,
		HSB,
		HSL,
    CORNER,
    CORNERS,
    RADIUS,
    CENTER
  };

	void background(float value1, float value2, float value3);
	void color_mode(int mode, float value1, float value2, float value3, float value4);
	void create_canvas(int x, int y);
	void no_cursor();
  void no_stroke();
  void rect_mode(int mode);

	Vector2 get_mouse_position();

	Smetch();

private:

  void apply_color(float value1, float value2, float value3, float value4);
  void apply_color_hsv_to_rgb(float H, float S, float V, float A);

	SubViewport *viewport;
	PanelContainer *panel_container;

	int clr_mode = RGB;
  float color_levels[4];
	int color_maxes[3][4] = {
		{ 255, 255, 255, 255 }, // RGB
		{ 360, 100, 100, 1 }, // HSB
		{ 360, 100, 100, 1 } // HSL
	};
  int maxes[4];
	bool renderer_no_cursor;
  bool renderer_no_stroke;
  int rct_mode = CENTER;
};

#endif // SMETCH_H
