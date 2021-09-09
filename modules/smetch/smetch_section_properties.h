/* smetch_section_properties.h */

#ifndef SMETCH_SECTION_PROPERTIES_H
#define SMETCH_SECTION_PROPERTIES_H

#include "core/io/resource.h"

class SmetchSectionProperties : public Resource {
	GDCLASS(SmetchSectionProperties, Resource);

private:
  String identifier;
  String title;
  String description;
  Rect2 description_rect;

protected:
	static void _bind_methods();

public:
  String get_title();
  void set_title(String title);
  String get_identifier();
  void set_identifier(String title);
  String get_description();
  void set_description(String title);
  Rect2 get_description_rect();
  void set_description_rect(Rect2 seed);

private:
};

#endif // SMETCH_SECTION_PROPERTIES_H
