// SDL lesson 04
// Matt Mahan 4/2/13

#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include<string>

// Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// The surfaces
SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

SDL_Surface *load_image(std::string filename){
	// Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;
	
	// The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	
	// Load the image
	loadedImage = IMG_Load( filename.c_str() );
	
	// If nothing went wrong in loading the image
	if( loadedImage != NULL )
	{
		// Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);
		
		// Free the old image
		SDL_FreeSurface(loadedImage);
	}

	// Return the optimized image
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	// Make a temporary rectangle to hold the offsets
	SDL_Rect offset;
	
	// Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface(source,NULL,destination,&offset);
}

bool init(){
	// Initialize all SDL subsystems
	if(SDL_INIT(SDL_INIT_EVERYTHING) == -1) return false;
	
	// set up the screen
	screen = SDK_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	
	
	
	
	
