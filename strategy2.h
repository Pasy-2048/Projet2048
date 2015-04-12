#ifndef STRATEGY2_H_
#define STRATEGY2_H_
#include "grid.h"
typedef struct strategy_s *strategy;
struct strategy_s{
  void* mem;
  char* name;
  dir (*play_move) (strategy, grid);
  void (*free_strategy) (strategy); };
extern void free_memless_strat (strategy strat);



#endif /* STRATEGY_H_ */