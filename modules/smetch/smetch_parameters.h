/* smetch_parameters.h */

#ifndef SMETCH_PARAMETERS_H
#define SMETCH_PARAMETERS_H

#include "core/io/resource.h"

class SmetchParameters : public Resource {
	GDCLASS(SmetchParameters, Resource);

private:
  int random_seed;

protected:
	static void _bind_methods();

public:
  int get_random_seed();
  void set_random_seed(int seed);

private:
};

#endif // SMETCH_PARAMETERS_H
