#include "track.h"
namespace tank {
Track_desc::Track_desc() {
  velocity = 0; 
  up_down = direction::NONE;
  is_right = false;
};
bool Track_desc::operator <(const Track_desc& rhs) {
  return velocity < rhs.velocity;
}
bool Track_desc::operator == (const Track_desc& rhs) {
  return velocity == rhs.velocity;
}
}//namespace tank
