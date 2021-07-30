/* smetch.cpp */

#include "smetch.h"

void Smetch::add(int p_value) {
  count += p_value;
}

void Smetch::reset() {
  count = 0;
}

int Smetch::get_total() const {
  return count;
}

void Smetch::_bind_methods() {
  ClassDB::bind_method(D_METHOD("add", "value"), &Smetch::add);
  ClassDB::bind_method(D_METHOD("reset"), &Smetch::reset);
  ClassDB::bind_method(D_METHOD("get_total"), &Smetch::get_total);
}

Smetch::Smetch() {
  count = 0;
}
