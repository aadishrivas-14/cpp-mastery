#include "unique_ptr.h"

Resource::Resource() : value_(42) {}

int Resource::getValue() const {
  return value_;
}
