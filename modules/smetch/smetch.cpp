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
	ClassDB::bind_method(D_METHOD("fill"), &Smetch::fill);
	ClassDB::bind_method(D_METHOD("rect"), &Smetch::rect);
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

void Smetch::fill(float value1, float value2, float value3) {
	apply_color(value1, value2, value3, -1);
	fill_color = color;
}

void Smetch::rect(float x, float y, float w, float h) {
  if (rct_mode == CORNER) {

    Point2 pos = Point2(x,y);
    Size2 rect_size = Size2(w,h);
		Size2 parent_size = get_size(); // TODO : maybe can cache this, but only will work if always the same parent

    if (pos.x + rect_size.x > parent_size.x) {
      rect_size.x = rect_size.x - (pos.x + rect_size.x - parent_size.x);
    }
    if (pos.y + rect_size.y > parent_size.y) {
      rect_size.y = rect_size.y - (pos.y + rect_size.y - parent_size.y);
    }

    Rect2 rect = Rect2(pos,rect_size);
    draw_rect(rect,fill_color);

  } else if (rct_mode == CENTER) {
		// use x and y as the max w and h radius's
		if (w > x * 2)
			w = x * 2;
		if (h > y * 2)
			h = y * 2;

		Size2 rect_size = Size2(w, h);
		Size2 parent_size = get_size(); // TODO : maybe can cache this, but only will work if always the same parent

    if (rect_size.x > parent_size.x) rect_size.x = parent_size.x;
    if (rect_size.y > parent_size.y) rect_size.y = parent_size.y;

		Point2 pos = Point2(0, 0);
		if (rect_size.x < parent_size.x) {
			pos.x = (parent_size.x - rect_size.x) * 0.5;
		}
		if (rect_size.y < parent_size.y) {
			pos.y = (parent_size.y - rect_size.y) * 0.5;
		}
		Rect2 rect = Rect2(pos, rect_size);
		draw_rect(rect, fill_color); // TODO : if no_stroke is false can add a border
	}
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
	// TODO : if this gets called again then need to clear the old objects

	Size2 this_size = Size2(x, y);
	this->set_size(this_size);

	Size2 parent_size = get_parent_area_size();

	// try and centre this in the parent
	// if parent is not big enough then this wont scale smaller
	// TODO : scale to size
	Point2 pos = Point2(0, 0);
	if (this_size.x < parent_size.x) {
		pos.x = (parent_size.x - this_size.x) * 0.5;
	}
	if (this_size.y < parent_size.y) {
		pos.y = (parent_size.y - this_size.y) * 0.5;
	}
	this->set_position(pos);

	viewport = memnew(SubViewport);
	viewport->set_size_2d_override_stretch(true);
	viewport->set_size(this_size);
  viewport->set_use_occlusion_culling(true);

	background_rect = memnew(TextureRect);
	background_rect->set_expand(true);
	background_rect->set_size(this_size);

	CanvasTexture *background_canvas_texture = memnew(CanvasTexture);
	background_rect->set_texture(background_canvas_texture);

	viewport->add_child(background_rect);
	this->add_child(viewport);
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
