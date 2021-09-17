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
	int get_seq();
	void set_seq(int seq);
	String get_id();
	String get_id_();
	void set_id(String id);
	String get_title();
	void set_title(String description);
	String get_description();
	void set_description(String description);
	void set_image(String image);
	String get_image();
	Ref<SmetchContent> get_parent_content();
	void set_parent_content(const Ref<SmetchContent> &parent_content);

private:
	int type;
	int seq;
	String id;
	String title;
	String description;
	String image;

	Ref<SmetchContent> parent_content;
};

#endif // SMETCH_CONTENT_H
