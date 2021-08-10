/* smetch.cpp */

#include "smetch.h"
#include <math.h>
#include <iostream>

void Smetch::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_properties", "SmetchProperties"), &Smetch::set_properties);
	ClassDB::bind_method(D_METHOD("get_properties"), &Smetch::get_properties);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "SmetchProperties", PROPERTY_HINT_RESOURCE_TYPE, "SmetchProperties"), "set_properties", "get_properties");

	ClassDB::bind_method(D_METHOD("color_mode", "mode", "value1", "value2", "value3", "value4"), &Smetch::color_mode, DEFVAL(RGB), DEFVAL(1), DEFVAL(-1), DEFVAL(-1), DEFVAL(-1));
	ClassDB::bind_method(D_METHOD("prime_color", "value1", "value2", "value3", "value4"), &Smetch::prime_color, DEFVAL(Color()), DEFVAL(1), DEFVAL(-1), DEFVAL(-1), DEFVAL(-1));
	ClassDB::bind_method(D_METHOD("background"), &Smetch::background);
	ClassDB::bind_method(D_METHOD("create_canvas"), &Smetch::create_canvas);
	ClassDB::bind_method(D_METHOD("continuous_drawing"), &Smetch::continuous_drawing);
	ClassDB::bind_method(D_METHOD("fill"), &Smetch::fill);
	ClassDB::bind_method(D_METHOD("fill_with_color"), &Smetch::fill_with_color);
	ClassDB::bind_method(D_METHOD("rect"), &Smetch::rect);
	ClassDB::bind_method(D_METHOD("no_cursor"), &Smetch::no_cursor);
	ClassDB::bind_method(D_METHOD("no_stroke"), &Smetch::no_stroke);
	ClassDB::bind_method(D_METHOD("rect_mode"), &Smetch::rect_mode);
	ClassDB::bind_method(D_METHOD("save_canvas"), &Smetch::save_canvas);
	ClassDB::bind_method(D_METHOD("get_mouse_position"), &Smetch::get_mouse_position);
	ClassDB::bind_method(D_METHOD("get_current_color"), &Smetch::get_current_color);
	ClassDB::bind_method(D_METHOD("lerp_color"), &Smetch::lerp_color);
	ClassDB::bind_method(D_METHOD("update_cursor"), &Smetch::update_cursor);
	ClassDB::bind_method(D_METHOD("_ready"), &Smetch::_ready);
	ClassDB::bind_method(D_METHOD("_process"), &Smetch::_process);

	ClassDB::bind_method(D_METHOD("constrain"), &Smetch::constrain);
	ClassDB::bind_method(D_METHOD("fconstrain"), &Smetch::fconstrain);
	ClassDB::bind_method(D_METHOD("map"), &Smetch::map);
	ClassDB::bind_method(D_METHOD("fmap"), &Smetch::fmap);
	ClassDB::bind_method(D_METHOD("random"), &Smetch::random);
	ClassDB::bind_method(D_METHOD("frandom"), &Smetch::frandom);

	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("RGB"), RGB);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("HSB"), HSB);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("HSL"), HSL);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("CORNER"), CORNER);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("CORNERS"), CORNERS);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("RADIUS"), RADIUS);
	ClassDB::bind_integer_constant(StringName("Smetch"), StringName("Constants"), StringName("CENTER"), CENTER);
}

void Smetch::set_properties(const Ref<SmetchProperties> &p_properties) {
	properties = p_properties;
}

Ref<SmetchProperties> Smetch::get_properties() const {
	return properties;
}

void Smetch::apply_color(float value1, float value2, float value3, float value4, Color to_color) {
	if (value4 == -1) {
		value4 = maxes[3];
	}
	if (clr_mode == HSB) {
		to_color.set_hsv(value1 / maxes[0], value2 / maxes[1], value3 / maxes[2], value4 / maxes[3]);
	} else {
		// RGB
		to_color.r = value1 / maxes[0];
		to_color.g = value2 / maxes[1];
		to_color.b = value3 / maxes[2];
		to_color.a = value4 / maxes[3];
	}
  fill_color = to_color;
}

void Smetch::prime_color(Color color, float value1, float value2, float value3, float value4) {
  apply_color(value1, value2, value3, value4, color);
}

void Smetch::background(float value1, float value2, float value3) {
	apply_color(value1, value2, value3, -1, background_color);
	draw_rect(background_rect, background_color);
}

void Smetch::fill(float value1, float value2, float value3) {
	apply_color(value1, value2, value3, -1, fill_color);
}

void Smetch::fill_with_color(Color color) {
  fill_color = color;
}

void Smetch::rect(float x, float y, float w, float h) {
	if (rct_mode == CORNER) {
		Point2 pos = Point2(x, y);
		Size2 rect_size = Size2(w, h);
		Size2 parent_size = get_size(); // TODO : maybe can cache this, but only will work if always the same parent

		if (pos.x + rect_size.x > parent_size.x) {
			rect_size.x = rect_size.x - (pos.x + rect_size.x - parent_size.x);
		}
		if (pos.y + rect_size.y > parent_size.y) {
			rect_size.y = rect_size.y - (pos.y + rect_size.y - parent_size.y);
		}

		Rect2 rect = Rect2(pos, rect_size);
		draw_rect(rect, fill_color);

	} else if (rct_mode == CENTER) {
		// use x and y as the max w and h radius's
		if (w > x * 2)
			w = x * 2;
		if (h > y * 2)
			h = y * 2;

		Size2 rect_size = Size2(w, h);
		Size2 parent_size = get_size(); // TODO : maybe can cache this, but only will work if always the same parent

		if (rect_size.x > parent_size.x)
			rect_size.x = parent_size.x;
		if (rect_size.y > parent_size.y)
			rect_size.y = parent_size.y;

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
	}
}

void Smetch::create_canvas(int x, int y) {
	// TODO : if this gets called again then need to clear the old objects

	Size2 this_size = Size2(x, y);
	this->set_size(this_size);
	this->set_expand(true);

	canvas_texture = memnew(CanvasTexture);
	set_texture(canvas_texture);

	background_rect = Rect2(Point2(0, 0), get_size());

	parent_mouse_mode = Input::get_singleton()->get_mouse_mode();
}

void Smetch::no_stroke() {
	// TODO : Add no_stroke functionality
	renderer_no_stroke = false;
	print_line("todo : no_stroke does nothing");
}

void Smetch::no_cursor() {
	cursor_mode = CURSOR_HIDDEN;
	update_cursor();
}

void Smetch::update_cursor() {
	if (cursor_mode == CURSOR_HIDDEN) {
		Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_HIDDEN);
	} else {
		Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
	}
}

void Smetch::continuous_drawing(bool is_continuous) {
	is_continuous_drawing = is_continuous;
}

void Smetch::rect_mode(int mode) {
	if (mode == CORNER ||
			mode == CORNERS ||
			mode == RADIUS ||
			mode == CENTER) {
		rct_mode = mode;
	}
}

String Smetch::save_canvas(String file_name) {
	Ref<Image> image = get_viewport()->get_texture()->get_image();
	String dir = OS::get_singleton()->get_user_data_dir();
	String save_location = dir + "/" + file_name + "_" + itos(OS::get_singleton()->get_unix_time()) + ".png";
	image->save_png(save_location);
	return save_location;
}

Vector2 Smetch::get_mouse_position() {
	return get_local_mouse_position();
}

Color Smetch::get_current_color() {
	return fill_color;
}

void Smetch::mouse_entered() {
	update_cursor();
}

void Smetch::mouse_exited() {
	Input::get_singleton()->set_mouse_mode(parent_mouse_mode);
}

void Smetch::_ready() {
	connect("mouse_entered", callable_mp(this, &Smetch::mouse_entered));
	connect("mouse_exited", callable_mp(this, &Smetch::mouse_exited));
}

void Smetch::_process(float delta) {
	if (is_continuous_drawing) {
		update();
	}
}


Smetch::Smetch() {
  print_line("constructor");
	random_number_generator = memnew(RandomNumberGenerator);
  random_number_generator->set_seed(OS::get_singleton()->get_unix_time());
  random_number_generator->randomize();
	if (properties != nullptr) {
    print_line("seeding: " + itos(properties->get_random_seed()) );
		random_number_generator->set_seed(properties->get_random_seed());
	}
}
Smetch::~Smetch() {}

///////////////////////////////////////////////////////////////////
double Smetch::random(double from, double to) {
	return random_number_generator->randi_range(from, to);
}

float Smetch::frandom(float from, float to) {
	return random_number_generator->randf_range(from, to);
}

double Smetch::constrain(double n, double low, double high) {
  return max(min(n,high),low);
}
float Smetch::fconstrain(float n, float low, float high) {
  return fmax(fmin(n,high),low);
}

double Smetch::map(double n, double start1, double stop1, double start2, double stop2) {
	return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}
float Smetch::fmap(float n, float start1, float stop1, float start2, float stop2) {
	return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}

double Smetch::min(double n1, double n2) {
  return n1 < n2 ? n1 : n2;
}
double Smetch::max(double n1, double n2) {
  return n1 > n2 ? n1 : n2;
}

Color Smetch::lerp_color(Color c1, Color c2, float amt) {
	float l0, l1, l2, l3;
	float from_array[4];
	float to_array[4];
  Color color;

	if (clr_mode == RGB) {
		from_array[0] = c1.r;
		from_array[1] = c1.g;
		from_array[2] = c1.b;
		from_array[3] = c1.a;
		to_array[0] = c2.r;
		to_array[1] = c2.g;
		to_array[2] = c2.b;
		to_array[3] = c2.a;
	} else if (clr_mode == HSB) {
		from_array[0] = c1.get_h();
		from_array[1] = c1.get_s();
		from_array[2] = c1.get_v();
		from_array[3] = c1.a;
		to_array[0] = c2.get_h();
		to_array[1] = c2.get_s();
		to_array[2] = c2.get_v();
		to_array[3] = c2.a;
	} else if (clr_mode == HSL) {
		print_error("Lerp_color for HSL not implemented!");
	}

	amt = fmax(fmin(amt, 1.0), 0);

	l0 = Math::lerp(from_array[0], to_array[0], amt);
	l1 = Math::lerp(from_array[1], to_array[1], amt);
	l2 = Math::lerp(from_array[2], to_array[2], amt);
	l3 = Math::lerp(from_array[3], to_array[3], amt);

	if (clr_mode == HSB) {
		color.set_hsv(l0, l1, l2, l3);
	} else if (clr_mode == HSL) {
		print_error("Lerp_color for HSL not implemented!");
	} else {
		// RGB
		color.r = l0;
		color.g = l1;
		color.b = l2;
		color.a = l3;
	}
  return color;
}

