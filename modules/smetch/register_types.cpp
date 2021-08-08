/*  register_types.cpp */

#include "register_types.h"
#include "core/object/class_db.h"
#include "smetch.h"
#include "smetch_properties.h"

void register_smetch_types() {
	GDREGISTER_CLASS(Smetch);
	GDREGISTER_CLASS(SmetchProperties);
}

void unregister_smetch_types() {
}
