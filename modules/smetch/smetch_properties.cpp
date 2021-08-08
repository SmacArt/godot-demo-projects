/* smetch_properties.cpp */

#include "smetch_properties.h"

void SmetchProperties::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_identifier"), &SmetchProperties::get_identifier);
	ClassDB::bind_method(D_METHOD("set_identifier", "identifier"), &SmetchProperties::set_identifier);
	ClassDB::bind_method(D_METHOD("get_title"), &SmetchProperties::get_title);
	ClassDB::bind_method(D_METHOD("set_title", "title"), &SmetchProperties::set_title);
	ClassDB::bind_method(D_METHOD("get_description"), &SmetchProperties::get_description);
	ClassDB::bind_method(D_METHOD("set_description", "description"), &SmetchProperties::set_description);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "identifier"), "set_identifier", "get_identifier");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "description"), "set_description", "get_description");
}

String SmetchProperties::get_identifier() {
  return identifier;
}
void SmetchProperties::set_identifier(String p_identifier) {
	identifier = p_identifier;
}

String SmetchProperties::get_title() {
  return title;
}
void SmetchProperties::set_title(String p_title) {
	title = p_title;
}

String SmetchProperties::get_description() {
  return description;
}
void SmetchProperties::set_description(String p_description) {
	description = p_description;
}
