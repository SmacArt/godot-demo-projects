/* smetch.h */

#ifndef SMETCH_H
#define SMETCH_H

#include "scene/main/viewport.h"
#include "core/io/resource.h"

class Smetch : public Resource {
  GDCLASS(Smetch, Resource);

  int count;

protected:
  static void _bind_methods();

public:
  void add(int p_value);
  void reset();
  int get_total() const;

  Smetch();

};

#endif // SMETCH_H
