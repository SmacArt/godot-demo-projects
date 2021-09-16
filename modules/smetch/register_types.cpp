/*  register_types.cpp */

#include "register_types.h"
#include "core/object/class_db.h"
#include "smetch.h"
#include "smetch_parameters.h"
#include "smetch_content.h"

void register_smetch_types() {
	GDREGISTER_CLASS(Smetch);
	GDREGISTER_CLASS(SmetchParameters);
	GDREGISTER_CLASS(SmetchContent);
}

void unregister_smetch_types() {
}
