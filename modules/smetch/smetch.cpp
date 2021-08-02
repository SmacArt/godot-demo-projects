/* smetch.cpp */

#include "smetch.h"
#include <iostream>

Vector2 Smetch::get_mouse_position() {
	return viewport->get_mouse_position();
}

void Smetch::_bind_methods() {
	ClassDB::bind_method(D_METHOD("color_mode", "mode", "value1", "value2", "value3", "value4"), &Smetch::color_mode, DEFVAL(RGB), DEFVAL(1), DEFVAL(-1), DEFVAL(-1), DEFVAL(-1));
	ClassDB::bind_method(D_METHOD("background"), &Smetch::background);
	ClassDB::bind_method(D_METHOD("create_canvas"), &Smetch::create_canvas);
	ClassDB::bind_method(D_METHOD("no_cursor"), &Smetch::no_cursor);
	ClassDB::bind_method(D_METHOD("no_stroke"), &Smetch::no_stroke);
	ClassDB::bind_method(D_METHOD("rect_mode"), &Smetch::rect_mode);

	ClassDB::bind_method(D_METHOD("get_mouse_position"), &Smetch::get_mouse_position);

	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("RGB"), RGB);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("HSB"), HSB);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("HSL"), HSL);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("CORNER"), CORNER);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("CORNERS"), CORNERS);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("RADIUS"), RADIUS);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("CENTER"), CENTER);
}

void Smetch::apply_color(float value1, float value2, float value3, float value4) {
	if (value4 == -1) {
		value4 = maxes[3];
	}
	if (clr_mode == HSB) {
		color.set_hsv(value1 / maxes[0], value2 / maxes[1], value3 / maxes[2], value4 / maxes[3]);
	} else {
    // RGB
		color.r = value1 / maxes[0];
		color.g = value2 / maxes[1];
		color.b = value3 / maxes[2];
		color.a = value4 / maxes[3];
	}
}

void Smetch::background(float value1, float value2, float value3) {
	apply_color(value1, value2, value3, -1);
	background_rect->set_self_modulate(color);
}

void Smetch::color_mode(int mode, float value1, float value2, float value3, float value4) {
	if (mode == RGB || mode == HSB || mode == HSL) {
		clr_mode = mode;

		for (int i = 0; i < 4; i++) {
			maxes[i] = color_maxes[clr_mode][i];
		}

		if (value2 == -1) {
			maxes[0] = value1; // Red
			maxes[1] = value1; // Green
			maxes[2] = value1; // Blue
			maxes[3] = value1; // Alpha
		} else if (value4 == -1) {
			maxes[0] = value1; // Red
			maxes[1] = value2; // Green
			maxes[2] = value3; // Blue
		} else {
			maxes[0] = value1; // Red
			maxes[1] = value2; // Green
			maxes[2] = value3; // Blue
			maxes[3] = value1; // Alpha
		}

		print_line("Color Mode: " + itos(clr_mode) + " - " + itos(maxes[0]) + "," + itos(maxes[1]) + "," + itos(maxes[2]) + "," + itos(maxes[3]));
	}
}

void Smetch::create_canvas(int x, int y) {
	std::cout << "create canvas" << std::endl;

	// todo : if this gets called again then need to clear the old objects

	Size2 s2 = Size2(x, y);
	this->set_size(s2);

	viewport = memnew(SubViewport);
	viewport->set_size_2d_override_stretch(true);
	viewport->set_size(s2);

	background_rect = memnew(TextureRect);
  background_rect->set_expand(true);
	background_rect->set_size(s2);

  CanvasTexture *background_canvas_texture = memnew(CanvasTexture);
  background_rect->set_texture(background_canvas_texture);

	viewport->add_child(background_rect);
	this->add_child(viewport);

	std::cout << "create canvas end" << std::endl;
}

void Smetch::no_stroke() {
	// TODO : Add no_stroke functionality
	renderer_no_stroke = false;
	print_line("todo : no_stroke does nothing");
}

void Smetch::no_cursor() {
	// TODO : Add no_cursor functionality
	renderer_no_cursor = false;
	print_line("todo : no_cursor does nothing");
}

void Smetch::rect_mode(int mode) {
	if (mode == CORNER ||
			mode == CORNERS ||
			mode == RADIUS ||
			mode == CENTER) {
		rct_mode = mode;
	}
}

Smetch::Smetch() {}

// todo : destructor
