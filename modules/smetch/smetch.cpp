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
		apply_color_hsv_to_rgb(value1, value2, value3, value4);
	} else { //rgb
		color_levels[0] = value1 / maxes[0];
		color_levels[1] = value2 / maxes[1];
		color_levels[2] = value3 / maxes[2];
		color_levels[3] = value4 / maxes[3];
	}

	//print_line("todo:  use max color levels");
}

void Smetch::background(float value1, float value2, float value3) {
	apply_color(value1, value2, value3, -1);
	Color c = Color(color_levels[0], color_levels[1], color_levels[2], color_levels[3]);
	panel_container->set_modulate(c);
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

	panel_container = memnew(PanelContainer);
	panel_container->set_size(s2);

	viewport->add_child(panel_container);
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

void Smetch::apply_color_hsv_to_rgb(float H, float S, float V, float A) {
	// todo : note this assumes Hue is always in range of 360 .. so is ignoring
	//        what has been requested in setup
	float s = S / maxes[1];
	float v = V / maxes[2];
	float C = s * v;
	float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	float m = v - C;
	float r, g, b;
	if (H >= 0 && H < 60) {
		r = C, g = X, b = 0;
	} else if (H >= 60 && H < 120) {
		r = X, g = C, b = 0;
	} else if (H >= 120 && H < 180) {
		r = 0, g = C, b = X;
	} else if (H >= 180 && H < 240) {
		r = 0, g = X, b = C;
	} else if (H >= 240 && H < 300) {
		r = X, g = 0, b = C;
	} else {
		r = C, g = 0, b = X;
	}
	color_levels[0] = (r + m); // * 255;
	color_levels[1] = (g + m); // * 255;
	color_levels[2] = (b + m); // * 255;
  color_levels[3] = A;
}

Smetch::Smetch() {}

// todo : destructor
