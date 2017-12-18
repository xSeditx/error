#include<Creature.h>
#include<main.h>
using namespace std;

void CREATURE::WRAPX(){
	if (POSITION.X < LEFT_BOUNDS) POSITION.X = (float)SCREENX + (int)POSITION.X;
	if (POSITION.X > WORLD_WIDTH) POSITION.X = POSITION.X - (WORLD_WIDTH);
	}
void CREATURE::WRAPY(){
	if (POSITION.Y < TOP_BOUNDS) POSITION.Y = (float)SCREENY + (int)POSITION.Y; 
	if (POSITION.Y > WORLD_HEIGHT) POSITION.Y = POSITION.Y - (WORLD_HEIGHT);
}

int CREATURE::WRAPX(float INPUT){
	if (INPUT < LEFT_BOUNDS) INPUT = (float)WX + INPUT;
	if (INPUT >= (float)WORLD_WIDTH) INPUT = INPUT - ((float)WORLD_WIDTH);
return INPUT;
}
int CREATURE::WRAPY(float INPUT){
	if (INPUT < TOP_BOUNDS) INPUT = (float)WY + INPUT;
	if (INPUT >= (float)WORLD_HEIGHT) INPUT = INPUT - ((float)WORLD_HEIGHT);
return INPUT;
}

float CREATURE::NEWX(float x, float A,float DIST){
    float NX = x + DIST * cos(A * _RADIANS) ;
	return NX;
}
float CREATURE::NEWY(float y,float A,float DIST){
    float NY = y + DIST * sin(A * 3.14159 / 180);
return NY;
}

void CREATURE::DRAW(){
	SetPixel(WINDOW_HDC, POSITION.X, POSITION.Y, COLOR);
}

void CREATURE::ROTATE(float CHANGE){
	POSITION.ANGLE += CHANGE;
	float rads = POSITION.ANGLE * _RADIANS;
	VELOCITY.X = POSITION.SPEED * cos(rads);
	VELOCITY.Y = POSITION.SPEED * sin(rads);
}

void CREATURE::MOVE(float SPEED){

	POTENTIAL.X = POSITION.X + VELOCITY.X;
	POTENTIAL.Y = POSITION.Y + VELOCITY.Y;

	POSITION.X += VELOCITY.X;
	POSITION.Y += VELOCITY.Y;
}

void CREATURE::SET_POSITION(){
	POSITION.X = WRAPX(POTENTIAL.X);
	POSITION.Y = WRAPY(POTENTIAL.Y);
	POSITION.ANGLE = WRAP_ANGLE(POSITION.ANGLE);
	WORLD[(int)POSITION.X][(int)POSITION.Y] = ID;
return;
}

void CREATURE::BREED(int OTHER_OD){

		COLORREF Color = COLOR;

		Vec3 Location;
		     Location.X =  POSITION.X + rand() % 6 - 3;
	    	 Location.Y =  POSITION.Y + rand() % 6 - 3;


		Vision Sight;
			   Sight.DISTANCE = SIGHT.DISTANCE + rand() % 2 - 1;
			   Sight.FOV      = SIGHT.FOV + rand() % 2 - 1;

        LIFE[GET_FREE_ID()] = CREATURE(0, Location, Color, Sight);   
}

int  CREATURE::SIGHT_HANDLER(){
   int SEES;

return SEES;
}

float CREATURE::WRAP_ANGLE(float angle){
	if (angle < 0)return angle + 360;
	if (angle > 0)return 360 - angle;
	return angle;
}

bool _INIT_creatures(int AMOUNT){

//=================================================================================================================================
//==================================== Initalize Starting creatures	===========================================================
//=================================================================================================================================
	
	for(int count = 0;count < AMOUNT; count++){
		
		COLORREF Color = RGB(rand()%255,rand()%255,rand()%255);
		Vec3 Location;
		     Location.X =  rand() % WORLD_WIDTH;
	    	 Location.Y =  rand() % WORLD_HEIGHT;
		     Location.SPEED =  rand() % 6;
		     Location.ANGLE = rand() % 360;

		Vision Sight;
			   Sight.DISTANCE = rand()%15;
			   Sight.FOV      = rand() % 30;

        LIFE[count] = CREATURE(0, Location, Color, Sight);   
 	}
//=================================================================================================================================

return 1;
}

void _MOVE_CREATURES()
{

	for(int count = 0;count < MAX_CREATURES; count++){

		if(LIFE[count].ALIVE == true){
// -----------------------CALCULATES THE AVERAGE OF ALL THE CREATURES BRAIN CELLS TO PROVE LEARNING -----------------------------
        	for(int avgcount=0;count < NUM_RESPONSES;avgcount++)
        	{
            	for(int avg2count=0;avg2count < NUM_NEURONS;avg2count++) AVERAGES[avg2count][avgcount] += LIFE[count].BRAIN[avg2count][avgcount];
        	}
//===============================================================================================================================

//------------------------- INC VARIOUS COUNTERS --------------------------------------------------------------------------------
			LIFE[count].AGE++;
			LIFE[count].LAST.BREED++;
			LIFE[count].LAST.MEAL++;
//===============================================================================================================================


		} //<--------CREATURE IS ALIVE ?
	}//  <-------- CREATURE CYCLE
	return;
}





bool _MAKE_STD_WINDOW_N_DC(HINSTANCE hInstance, HINSTANCE hPrevInstance,HWND WINDOW_HWND,HDC WINDOW_HDC)
{
	bool Success;

	   //Step 1: Registering the Window Class
    WINDOW_CLASS.cbSize        = sizeof(WNDCLASSEX);
    WINDOW_CLASS.style         = 0;
    WINDOW_CLASS.lpfnWndProc   = WndProc;
    WINDOW_CLASS.cbClsExtra    = 0;
    WINDOW_CLASS.cbWndExtra    = 0;
    WINDOW_CLASS.hInstance     = hInstance;
    WINDOW_CLASS.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    WINDOW_CLASS.hCursor       = LoadCursor(NULL, IDC_ARROW);
    WINDOW_CLASS.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
    WINDOW_CLASS.lpszMenuName  = NULL;
    WINDOW_CLASS.lpszClassName = g_szClassName;
    WINDOW_CLASS.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&WINDOW_CLASS))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	//SW_SHOWMAXIMIZED
    // Step 2: Creating the Window
    WINDOW_HWND = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName,"WinGDI Life", WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, SCREENX, SCREENY,NULL, NULL, hInstance, NULL);
    
	if(WINDOW_HWND == NULL){MessageBox(NULL, "Window Creation Failed!", "Error!",MB_ICONEXCLAMATION | MB_OK);return 0;}

	SetGraphicsMode(WINDOW_HDC, GM_ADVANCED);

	ShowWindow(WINDOW_HWND, SW_SHOWNORMAL);
    UpdateWindow(WINDOW_HWND);

	WINDOW_HDC =  GetDC(WINDOW_HWND);
	if(WINDOW_HDC == NULL)Success = false;

return Success;
}


bool _INIT_world(int SIZEX,int SIZEY)
{

//------------------ADD THE FOOD --------------------------------------------
	for(int count = 0;count < AMOUNT_FOOD;count++)
	{
		int x= rand()%SIZEX;
	    int y= rand()%SIZEY;
		WORLD[x][y] = -2;
	}

	cout << "Drew Food" << endl;


//------------------ MAKE THE INITIAL MAZE---------------------------------

	for(int COUNT = 0;COUNT < 1000;COUNT++)
	{
		int LENGTH = rand() % 200;
		int X = CREATURE::WRAPX(rand()%SIZEX);
		int Y = CREATURE::WRAPY(rand()%SIZEY);

		for (int c = 0;c < LENGTH; c++){
		      X += rand()%3 - 1;
		      X = CREATURE::WRAPX(X);
		      Y += rand()%3 - 1;
		      Y = CREATURE::WRAPY(Y);
			  WORLD[X][Y] = -1;
		}
	}

	cout << "Made maze" << endl;

return 1;
}

int CHECK_SPACE(int X,int Y){
     return   WORLD[(int)CREATURE::WRAPX(X)][(int)(CREATURE::WRAPY(Y))];
}

int GET_FREE_ID()
{
	for (int FREE_ID =0;FREE_ID < MAX_CREATURES;FREE_ID++)if(LIFE[FREE_ID].ALIVE = false)return FREE_ID;
return 0;
}



void _CONTROL_CREATURE(MSG &msg)
{


}