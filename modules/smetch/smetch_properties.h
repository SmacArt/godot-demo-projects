/* smetch_properties.h */

#ifndef SMETCH_PROPERTIES_H
#define SMETCH_PROPERTIES_H

#include "core/io/resource.h"

class SmetchProperties : public Resource {
	GDCLASS(SmetchProperties, Resource);

private:
  String identifier;
  String title;
  String description;
  int random_seed;

protected:
	static void _bind_methods();

public:
  String get_title();
  void set_title(String title);
  String get_identifier();
  void set_identifier(String title);
  String get_description();
  void set_description(String title);
  int get_random_seed();
  void set_random_seed(int seed);

private:
};

#endif // SMETCH_PROPERTIES_H
