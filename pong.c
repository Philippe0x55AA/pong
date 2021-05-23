#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main(){
  
  SDL_Window *window = NULL;
  int status = EXIT_FAILURE;
  SDL_Renderer *renderer = NULL;
  SDL_Rect rect1 = {10,350,30,150};
  SDL_Rect rect2 = {1160,350,30,150};
  SDL_Rect separator = {600,0,5,950};
  SDL_Rect ball = {600,350,20,20};


  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    fprintf(stderr,"Error: %s",SDL_GetError());
    goto Quit;
  }


  window = SDL_CreateWindow("pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1200,950,SDL_WINDOW_SHOWN);

  if(window == NULL){
    fprintf(stderr, "Erreur: %s",SDL_GetError());
    goto Quit;
  }


  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  if(renderer == NULL){
    fprintf(stderr,"Erreur: %s",SDL_GetError());
    goto Quit;
  }
  if(SDL_SetRenderDrawColor(renderer,0,0,0,0) != 0){
    fprintf(stderr,"Erreur: %s",SDL_GetError());
    goto Quit;
  }

  if(SDL_RenderClear(renderer)){
    fprintf(stderr,"Erreur: %s",SDL_GetError());
    goto Quit;
  }

  SDL_SetRenderDrawColor(renderer,255,255,255,255);
  SDL_RenderFillRect(renderer,&rect1);
  SDL_RenderFillRect(renderer,&rect2);
  SDL_RenderFillRect(renderer,&separator);
  SDL_RenderFillRect(renderer,&ball);

  SDL_RenderPresent(renderer);

  SDL_Delay(4000);

  status = EXIT_SUCCESS;
  Quit:
      if(renderer != NULL)
          SDL_DestroyRenderer(renderer);
      if(window != NULL)
          SDL_DestroyWindow(window);
      SDL_Quit();
      return status;
}
