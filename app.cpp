#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"move.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
using namespace std;

SDL_Window* gWindow=NULL;
SDL_Surface* gScreenSurface=NULL;
SDL_Surface* gHelloWorld=NULL;
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init()
{
	bool success=true;
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<"\n";
		success=false;
	}
	else
	{
		gWindow=SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if(gWindow==NULL)
		{
			cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<"\n";
			success=false;
		}
		else
		{
			gScreenSurface=SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
	bool success=true;
	gHelloWorld=IMG_Load("food_home.png");
	if(gHelloWorld==NULL)
	{
		cout<<"Unable to load image! SDL_Error: "<<SDL_GetError()<<"\n";
		success=false;
	}
	return success;
}

SDL_Surface* loadSurface(string path)
{	
	//SDL_Surface* optimizedSurface=NULL;
	SDL_Surface* loadedSurface=IMG_Load(path.c_str());
	if(loadedSurface==NULL)
	{
		cout<<"Unable to load image! SDL Error: "<<SDL_GetError()<<"\n";
	}
	//else
	//{
		//optimizedSurface=SDL_ConvertSurface(loadedSurface,gScreenSurface->format,0);
	//	if(optimizedSurface==NULL)
	//	{
	//		cout<<"Unable to optimize image SDL Error: "<<SDL_GetError()<<"\n"; 
	//	}
		//SDL_FreeSurface(loadedSurface);
	//	}
	return loadedSurface;
}

void close()
{
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld=NULL;
	SDL_DestroyWindow(gWindow);
	gWindow=NULL;
	SDL_Quit();
}

int main()
{
	bool quit=false;
	SDL_Event e;
	init();
	//loadMedia();
	
	SDL_Surface* gStretchedSurface=NULL;	
	gStretchedSurface=loadSurface("food.png");
	SDL_Rect stretchRect;
	stretchRect.x=300;
	stretchRect.y=300;
	stretchRect.w=100;
	stretchRect.h=100;
	int i= SDL_BlitScaled(gStretchedSurface,NULL,gScreenSurface,&stretchRect);
	cout<<i;
	SDL_UpdateWindowSurface(gWindow);
	
	init_food(stretchRect.x,stretchRect.y,stretchRect.w,stretchRect.h);

	gStretchedSurface=NULL;
	gStretchedSurface=loadSurface("home.png");
	stretchRect.x=100;
	stretchRect.y=100;
	stretchRect.w=30;
	stretchRect.h=30;
	SDL_BlitScaled(gStretchedSurface,NULL,gScreenSurface,&stretchRect);
	SDL_UpdateWindowSurface(gWindow);
	
	init_home(stretchRect.x,stretchRect.y,stretchRect.w,stretchRect.h);
	
	ant a;
	gStretchedSurface=NULL;
	gStretchedSurface=loadSurface("ant.png");
	stretchRect.x=a.x;
	stretchRect.y=a.y;
	stretchRect.w=9;
	stretchRect.h=9;
	SDL_BlitScaled(gStretchedSurface,NULL,gScreenSurface,&stretchRect);
	SDL_UpdateWindowSurface(gWindow);
	
	while(!quit)
	{
		while(SDL_PollEvent(&e)!=0)
		{
			if(e.type==SDL_QUIT)
			{
				quit=true;
			}
		}	
		//SDL_BlitSurface(gHelloWorld,NULL,gScreenSurface,NULL);
		//SDL_UpdateWindowSurface(gWindow);

		angle_sel(a);
		gStretchedSurface=NULL;
		gStretchedSurface=loadSurface("ant.png");
	 	stretchRect.x=a.x;
		stretchRect.y=a.y;
		stretchRect.w=9;
		stretchRect.h=9;
		SDL_BlitScaled(gStretchedSurface,NULL,gScreenSurface,&stretchRect);
		SDL_UpdateWindowSurface(gWindow);

		SDL_Delay(5);
	}
	close();
	return 0;
}
