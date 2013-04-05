// SDL Lesson 07
// Matt Mahan 4/4/13

#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"
#include<string>

// Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// The surfaces
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;

// The event structure
SDL_Event event;

// The font that's going to be used
TTF_Font *font = NULL;

// The color of the font
SDL_Color textColor = {255,255,255};

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
		
		//If the surface was optimized
        if( optimizedImage != NULL )
        {
         	//Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
	}

	// Return the optimized image
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip=NULL){
	// Make a temporary rectangle to hold the offsets
	SDL_Rect offset;
	
	// Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface(source,clip,destination,&offset);
}

bool init(){
	// Initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	
	// set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	// If there was an error in setting up the screen
	if (screen == NULL) return false;
	
	// Initialize SDL_ttf
	if(TTF_Init()==-1) return false;
	
	// Set the window caption
	SDL_WM_SetCaption("TTF test", NULL);
	
	// If everythign initialized fine
	return true;
}

bool load_files(){

	// Load the image
	background = load_image("background.png");
	
	// Open the font
	font = TTF_OpenFont("lazy.ttf",28);
	
	// If there was an error in loading the image
	if(background==NULL) return false;
	
	// If there was an error loading the font
	if (font==NULL) return false;
	
	// If everything loaded fine
	return true;
}

void clean_up(){
	// Free the surfaces
	SDL_FreeSurface(background);
	SDL_FreeSurface(message);
	
	// Close the font
	TTF_CloseFont(font);
	
	// Quit SDL_ttf
	TTF_Quit();
	
	// Quit SDL
	SDL_Quit();
}

int main(int argc, char* args[]){
	// Make sure the program waits for a quit
	bool quit=false;
	
	// Initialize
	if(init()==false) return 1;
	
	// Load the files
	if(load_files()==false) return 1;
	
	// Render the text
	message=TTF_RenderText_Solid(font,"The quick brown fox jumps over the lazy dog", textColor);
	
	// Check for error rendering
	if(message==NULL) return 1;
	
	// Apply the images to the screen
	apply_surface(0,0,background,screen);
	apply_surface(0,150,message,screen);

	
	// Update the screen
	if(SDL_Flip(screen)==-1) return 1;
	
	// While the user hasn't quit
	while(quit==false){
	
		while(SDL_PollEvent(&event)){
			// If the user has Xed out the window
			if(event.type==SDL_QUIT) quit = true;
		}
		
	}
	
	// Free the surface and quit SDL
	clean_up();
	return 0;
}
