/* smetch_content.cpp */

#include "smetch_content.h"

void SmetchContent::_bind_methods() {
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Root"), ROOT);
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Module"), MODULE);
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Chapter"), CHAPTER);
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Section"), SECTION);
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Smetch"), SMETCH);

	ClassDB::bind_method(D_METHOD("get_type"), &SmetchContent::get_type);
	ClassDB::bind_method(D_METHOD("set_type"), &SmetchContent::set_type);
	ClassDB::bind_method(D_METHOD("get_id"), &SmetchContent::get_id);
	ClassDB::bind_method(D_METHOD("get_id_"), &SmetchContent::get_id_);
	ClassDB::bind_method(D_METHOD("set_id"), &SmetchContent::set_id);
	ClassDB::bind_method(D_METHOD("get_title"), &SmetchContent::get_title);
	ClassDB::bind_method(D_METHOD("set_title"), &SmetchContent::set_title);
	ClassDB::bind_method(D_METHOD("get_description"), &SmetchContent::get_description);
	ClassDB::bind_method(D_METHOD("set_description"), &SmetchContent::set_description);
	ClassDB::bind_method(D_METHOD("get_scene"), &SmetchContent::get_scene);
	ClassDB::bind_method(D_METHOD("set_scene"), &SmetchContent::set_scene);
	ClassDB::bind_method(D_METHOD("get_image"), &SmetchContent::get_image);
	ClassDB::bind_method(D_METHOD("set_image"), &SmetchContent::set_image);
	ClassDB::bind_method(D_METHOD("get_color"), &SmetchContent::get_color);
	ClassDB::bind_method(D_METHOD("set_color"), &SmetchContent::set_color);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Root,Module,Chapter,Section,Smetch"), "set_type", "get_type");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "id"), "set_id", "get_id");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "description"), "set_description", "get_description");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "image", PROPERTY_HINT_FILE, "*.png"), "set_image", "get_image");
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color", PROPERTY_HINT_COLOR_NO_ALPHA), "set_color", "get_color");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "scene", PROPERTY_HINT_FILE, "*.tscn"), "set_scene", "get_scene");
}

String SmetchContent::get_id() {
	return id;
}
String SmetchContent::get_id_() {
	// todo : check for null
	return id.replace(".", "_");
}
void SmetchContent::set_id(String p_id) {
	id = p_id;
}

int SmetchContent::get_type() {
	return type;
}
void SmetchContent::set_type(int p_type) {
	type = p_type;
}

String SmetchContent::get_title() {
	return title;
}
void SmetchContent::set_title(String p_title) {
	title = p_title;
}

String SmetchContent::get_description() {
	return description;
}
void SmetchContent::set_description(String p_description) {
	description = p_description;
}

String SmetchContent::get_image() {
	return image;
}
void SmetchContent::set_image(String p_image) {
	image = p_image;
}
Color SmetchContent::get_color() {
	return color;
}
void SmetchContent::set_color(Color p_color) {
	color = p_color;
}


String SmetchContent::get_scene() {
	return scene;
}
void SmetchContent::set_scene(String p_scene) {
	scene = p_scene;
}