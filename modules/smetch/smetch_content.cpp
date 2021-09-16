/* smetch_content.cpp */

#include "smetch_content.h"

void SmetchContent::_bind_methods() {
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Module"), MODULE);
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Chapter"), CHAPTER);
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Section"), SECTION);
	ClassDB::bind_integer_constant(StringName("SmetchContent"), StringName("ContentType"), StringName("Smetch"), SMETCH);

	ClassDB::bind_method(D_METHOD("get_type"), &SmetchContent::get_type);
	ClassDB::bind_method(D_METHOD("set_type"), &SmetchContent::set_type);
	ClassDB::bind_method(D_METHOD("get_seq"), &SmetchContent::get_seq);
	ClassDB::bind_method(D_METHOD("set_seq"), &SmetchContent::set_seq);
	ClassDB::bind_method(D_METHOD("get_id"), &SmetchContent::get_id);
	ClassDB::bind_method(D_METHOD("set_id"), &SmetchContent::set_id);
	ClassDB::bind_method(D_METHOD("get_title"), &SmetchContent::get_title);
	ClassDB::bind_method(D_METHOD("set_title"), &SmetchContent::set_title);
	ClassDB::bind_method(D_METHOD("get_description"), &SmetchContent::get_description);
	ClassDB::bind_method(D_METHOD("set_description"), &SmetchContent::set_description);
	ClassDB::bind_method(D_METHOD("get_image"), &SmetchContent::get_image);
	ClassDB::bind_method(D_METHOD("set_image"), &SmetchContent::set_image);
	ClassDB::bind_method(D_METHOD("set_parent_content", "SmetchContent"), &SmetchContent::set_parent_content);
	ClassDB::bind_method(D_METHOD("get_parent_content"), &SmetchContent::get_parent_content);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "parent_content", PROPERTY_HINT_RESOURCE_TYPE, "SmetchContent"), "set_parent_content", "get_parent_content");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Module,Chapter,Section,Smetch"), "set_type", "get_type");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "seq"), "set_seq", "get_seq");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "id"), "set_id", "get_id");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "description"), "set_description", "get_description");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "image", PROPERTY_HINT_FILE, "*.png"), "set_image", "get_image");
}

int SmetchContent::get_seq() {
	return seq;
}
void SmetchContent::set_seq(int p_seq) {
	seq = p_seq;
}

String SmetchContent::get_id() {
	return id;
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

Ref<SmetchContent> SmetchContent::get_parent_content() {
	return parent_content;
}
void SmetchContent::set_parent_content(const Ref<SmetchContent> &p_parent_content) {
	parent_content = p_parent_content;
}
