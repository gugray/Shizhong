#ifndef TIME_FACE_H
#define TIME_FACE_H

struct TimeFace
{
  bool countSeconds = false;
  void loop(uint16_t event);
  void drawTime(bool forceRedraw);
};

#endif
