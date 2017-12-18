#pragma once

#ifndef CREATURE_HEADER 
#define CREATURE_HEADER 


#include<Windows.h>
#include<Math.h>
#include<iostream>

#define MUTATION_RATE ((rand()%101)-50)
#define _RADIANS  0.0174532925199444

#define SCREENX    1024
#define SCREENY     800




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// FUNCTION DECLARATIONS /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const int MAZE_SIZE =  1000;

const int MAX_AGE       = 100;
const int MAX_HEALTH    = 2000;
const int MAX_CREATURES = 5000;

const bool Male   = 0;
const bool Female = 1;

const int NUM_NEURONS   =  3;
const int NUM_RESPONSES =  4;

const int NORTHING = 0;
const int ENEMY    = 1;
const int MATE     = 2;
const int WALL     = 3;

const int AMOUNT_FOOD  = 10000;


struct Vec3{
	 float X,Y,Z;
	 float ANGLE;
	 float SPEED;
};


struct Vision{
   int FOV,
	   DISTANCE;
};

class CREATURE{
       public:

		     int  ID;
		     
			 int  AGE, 
			      HEALTH;

			 struct{
				 int BREED,
				     MEAL;
			 }LAST;

			 struct{
				 float X,
					   Y;
			 }VELOCITY;

			 Vec3 POSITION,
		          POTENTIAL;

			 Vision SIGHT;
			 
			 COLORREF COLOR;

			 bool ALIVE;

			 enum GENDER{MALE,FEMALE};

        	 CREATURE::CREATURE();
			 CREATURE::~CREATURE();

        	 CREATURE::CREATURE(int          parent,
				                Vec3         LOCATION,
								COLORREF     color,
								Vision       SIGHT);
	 

			 int BRAIN[NUM_NEURONS][NUM_RESPONSES];



             void SET_POSITION();
             void BREED(int OTHER_OD);

			 void MOVE(float SPEED);
             void DRAW();
             void ROTATE(float CHANGE);
             void KILL();
			
			 int  SIGHT_HANDLER();
             int  HIT();
             int  BREED (CREATURE OTHER);

	  static int  WRAPX (float INPUT);  void WRAPX();
      static int  WRAPY (float INPUT);  void WRAPY();
private:
        
             float NEWX       (float X, float ANGLE,float DIST);
             float NEWY       (float Y, float ANGLE,float DIST);

             float WRAP_ANGLE (float);
 

}
LIFE[MAX_CREATURES];


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// GLOBAL VARIABLES ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long AVERAGES[NUM_NEURONS][NUM_RESPONSES];

int FPS, 
	DAYS;

int MAIN_LOOP_SPEED,
    NUM_OF_COLLISIONS,
    NUM_CREATURES;

int DEATHS,   
	BIRTHS;

bool SHOW_VISION, 
	 SHOW_COLLISION;

int FAILS; 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////// Window Variables Setup////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDCLASSEX WINDOW_CLASS;
HWND WINDOW_HWND;
MSG Msg;
HDC WINDOW_HDC;		   

const char g_szClassName[] = "myWindowClass" ;

bool _MAKE_STD_WINDOW_N_DC(HINSTANCE hInstance, HINSTANCE hPrevInstance,HWND& window,HDC& device);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool   _INIT_creatures  (int);
void   _MOVE_CREATURES  (void);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int CAMERA_X, CAMERA_Y;

const int LEFT_BOUNDS   = 0;
const int TOP_BOUNDS    = 0;

const int WORLD_WIDTH   = SCREENX; 
const int WORLD_HEIGHT  = SCREENY;

const int WX = SCREENX + LEFT_BOUNDS;
const int WY = SCREENY + TOP_BOUNDS;


int WORLD[SCREENX][SCREENY] = {NULL};

bool   _INIT_world     (int SIZEX,int SIZEY);
int    _CHECK_SPACE    (int X, int Y);
int     GET_FREE_ID    ();

void _CONTROL_CREATURE();

#endif



/*HAZURL SUGGESTION

struct Node {
    Creature * c;
    Node* next = nullprt;
};
Node* free_list = nullptr;
void add(Creature& c) {
    Node* n = new Node;
    n->c = &c;
    n->next = free_list;
    free_list = n;
}

=------------------==========================--------------------------------

Creature cs[10]; // call 10 times the constructor
{
//    Creature c ( /* ... */ //); // call the constructor
//    cs[0] = c; // call Creature::operator = (Creature const&) from the instance at cs[0]; so it make a copy of c into cs[0]
//} // call the destructor of c
//*/


/*
huhlig - Yesterday at 5:47 PM
you're better off with something like 
template<class T>
class Entry {
    bool tombstone;
    T value;
}

Entry<Creature> entries[10];
 and making sure Creature has a default empty constructor
or make a proper container class out of it*/