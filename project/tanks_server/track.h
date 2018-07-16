#pragma once
#include "action.h"
#include "stdint.h"
namespace tank {
class Track_desc {
 public:
  Track_desc();
  bool operator <(const Track_desc& rhs);
  bool operator == (const Track_desc& rhs);
  uint8_t velocity;
  direction up_down;
  bool is_right;
};

struct Tank_Tracks {
  Track_desc left_track;
  Track_desc right_track;
};
}// namespace tank
