/*  register_types.cpp */

#include "register_types.h"
#include "core/object/class_db.h"
#include "smetch.h"
#include "smetch_properties.h"
#include "smetch_section_properties.h"
#include "smetch_chapter_properties.h"

void register_smetch_types() {
	GDREGISTER_CLASS(Smetch);
	GDREGISTER_CLASS(SmetchProperties);
	GDREGISTER_CLASS(SmetchSectionProperties);
	GDREGISTER_CLASS(SmetchChapterProperties);
}

void unregister_smetch_types() {
}
