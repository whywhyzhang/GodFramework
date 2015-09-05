#ifndef L_CONFIG_H
#define L_CONFIG_H

/*
	This is some information for the linux devices.
*/

#include "G_Config.h"

// Some configs about Key and Mouse.
typedef unsigned long L_MES_STA;

const L_MES_STA LM_KEY_PRE=1<<0;
const L_MES_STA LM_KEY_REL=1<<1;
const L_MES_STA LM_MOU_PRE=1<<2;
const L_MES_STA LM_MOU_REL=1<<3;
const L_MES_STA LM_MOU_MOV=1<<4;
const L_MES_STA LM_EXPOSE =1<<5;

#endif
