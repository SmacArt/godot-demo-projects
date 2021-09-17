/* smetch_content.h */

#ifndef SMETCH_CONTENT_H
#define SMETCH_CONTENT_H

#include "core/io/resource.h"

class SmetchContent : public Resource {
	GDCLASS(SmetchContent, Resource);

protected:
	static void _bind_methods();

public:
	enum ContentType {
		ROOT,
		MODULE,
		CHAPTER,
		SECTION,
		SMETCH
	};

	int get_type();
	void set_type(int type);
	String get_id();
	String get_id_();
	void set_id(String id);
	String get_title();
	void set_title(String description);
	String get_description();
	void set_description(String description);
	void set_image(String image_path);
	String get_image();
  void set_scene(String scene_path);
  String get_scene();

private:
	int type;
	String id;
	String title;
	String description;
	String scene;
	String image;

};

#endif // SMETCH_CONTENT_H
