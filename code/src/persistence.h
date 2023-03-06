#ifndef PERSISTENCE_H
#define PERSISTENCE_H

struct Persistence
{
  static int16_t loadStaticError();
  static void saveStaticError(int16_t err);
  static int16_t loadCrystalT0();
  static void saveCrystalT0(int16_t err);
};

#endif
