#ifndef GAME_H
#define GAME_H

#include "Sprit.h"

bool Welcome(God &, G_World *, G_Eye *);
bool Game_Run(God &, G_World *, S_Image *);
void Button_Init(Game_But **, G_World *, SIZE, int, SIZE, SIZE, POS, S_Image *);
void GetRand(int *,int);
int  GetNum(int,SIZE,int *);			// Get how many landmine is this but's neigh.

void Game_Result(God &,G_World *,int);

#endif
