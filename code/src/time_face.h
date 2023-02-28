#ifndef TIME_FACE_H
#define TIME_FACE_H

struct TimeFace
{
  bool countSeconds = false;
  void loop(uint8_t event);
  void drawTime(bool forceRedraw);
};

#endif
