/* smetch.h */

#ifndef SMETCH_H
#define SMETCH_H

#include "core/math/color.h"
#include "core/os/os.h"
#include "scene/gui/texture_rect.h"
#include "scene/main/viewport.h"

class Smetch : public TextureRect {
	GDCLASS(Smetch, TextureRect);

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
	void fill(float value1, float value2, float value3);
	void rect(float x, float y, float w, float h);
	void no_cursor();
	void no_stroke();
	void rect_mode(int mode);
	void save_canvas(String file_name);

	Vector2 get_mouse_position();

	Smetch();

private:
	void apply_color(float value1, float value2, float value3, float value4);

	Color color;
	Color fill_color;
	Rect2 background_rect;

	int clr_mode = RGB;
	int color_maxes[3][4] = {
		{ 255, 255, 255, 255 }, // RGB
		{ 360, 100, 100, 1 }, // HSB
		{ 360, 100, 100, 1 } // HSL
	};
	int maxes[4];
	bool renderer_no_cursor;
	bool renderer_no_stroke;
	int rct_mode = CORNER;
};

#endif // SMETCH_H
