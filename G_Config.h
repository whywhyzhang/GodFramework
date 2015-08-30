#ifndef G_CONFIG_H
#define G_CONFIG_H

/*
	The config that the Engine need.
*/

// Record all the information about a God.

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <utility>

using std::queue;
using std::map;
using std::set;
using std::vector;
using std::pair;
using std::multimap;

class G_Object;
class G_Input;
class G_Output;
class G_World;
class G_Sprit;
class G_Eye;

// Config about World.
typedef int WORLD_NUM;

// Config about Object.
typedef int OBJECT_TYPE;
typedef int OBJECT_NUM;

const int OBJ_KIND=4;

const OBJECT_TYPE OBJ_IN =0;
const OBJECT_TYPE OBJ_OUT=1;
const OBJECT_TYPE OBJ_SPR=2;
const OBJECT_TYPE OBJ_EYE=3;

// Config about keyboard.
typedef int KEY_ID;
typedef int KEY_STA;

// Config about window.

typedef int COLOR;

struct S_COLOR
{
	unsigned short r,g,b;
	
	S_COLOR(unsigned short _r=0,unsigned short _g=0,unsigned short _b=0):r(_r),g(_g),b(_b) {}
	S_COLOR(COLOR col)
	{
		r=col>>16;
		g=(col>>8) & ((1<<8)-1);
		b=col & ((1<<8)-1);
	}

	operator COLOR() { return (r<<16)|(g<<8)|b; }
};

const COLOR TRANS_COLOR=1;
const COLOR COL_WHITE=16777215;
const COLOR COL_BLACK=0;

struct POS
{
	int x,y;
	
	POS(int _x=0,int _y=0):x(_x),y(_y) {}
};

struct SIZE
{
	unsigned int w,h;
	
	SIZE(unsigned int _w=0,unsigned int _h=0):w(_w),h(_h) {}
};

// Config about Message.
typedef int MES_TYPE;

// Need C++ 11 there.
struct MESSAGE
{
	MES_TYPE type;
	int num[8];
	double dnum[4];
	void *p;
};

// Config about Event.
typedef MESSAGE EVENT;

// Define of message type:

// Base message type:
const MES_TYPE M_NULL=0;
const MES_TYPE M_QUIT=1;

// Input message type:
const MES_TYPE M_KEY_PRE=100;
const MES_TYPE M_KEY_REL=101;
const MES_TYPE M_MOU_PRE=102;
const MES_TYPE M_MOU_REL=103;
const MES_TYPE M_MOU_MOV=104;

// Output message type:
const MES_TYPE M_EXPOSE =200;
const MES_TYPE M_BUF_SHW=201;
const MES_TYPE M_LIN_SET=202;
const MES_TYPE M_FIL_SET=203;
const MES_TYPE M_FOR_COL=204;
const MES_TYPE M_BAC_COL=205;
const MES_TYPE M_STR_DRW=206;
const MES_TYPE M_POI_DRW=207;
const MES_TYPE M_LIN_DRW=208;
const MES_TYPE M_REC_DRW=209;
const MES_TYPE M_CIR_DRW=210;
const MES_TYPE M_REC_FIL=211;

// Eye message type:
const MES_TYPE M_PAINT  =300;

#endif
