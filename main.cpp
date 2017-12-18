#include<main.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

 
	_MAKE_STD_WINDOW_N_DC(hInstance, hPrevInstance, WINDOW_HWND, WINDOW_HDC);
	_INIT();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    // Step 3: The Message Loop
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
		   _MOVE_CREATURES();
		      // UpdateWindow(WINDOW_HWND);
           _PRINT_STATS();
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return Msg.wParam;
}


int  _INIT(){

    if( !(_INIT_creatures(MAX_CREATURES / 2))) Print("Error Making Creatures");
    if( !(_INIT_world(SCREENX, SCREENY)))      Print("Error Making World");

	return 1;
}


void _PRINT_STATS()
{
		return;
}




void _CONTROL_CREATURE()
{
//	int COUNT;
/*	
	int OX = CREATURES[1].X,OY = CREATURES[1].Y;
	WORLD[OX][OY] = 0;
	if(dbUpKey())CREATURES[1].MOVE(1);
	if(dbDownKey())CREATURES[1].MOVE(-1);
	if(dbRightKey())CREATURES[1].ROTATE(1);
	if(dbLeftKey())CREATURES[1].ROTATE(-1);
	
	CREATURES[1].SIGHT();
	CREATURES[1].HIT();
	if(CREATURES[1].HIT()){
		CREATURES[1].X = OX;
		CREATURES[1].Y = OY;
	
	}
	CREATURES[1].DRAW();
	CREATURES[1].SET_POSITION();*/
	return;
}
