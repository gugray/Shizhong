#ifndef TIME_FACE_H
#define TIME_FACE_H

struct TimeFace
{
  void enter();
  uint8_t loop(uint16_t event);

private:
  void drawTime(bool forceRedraw);
};

#endif
