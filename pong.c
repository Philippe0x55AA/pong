#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

const int WIDTH = 1200;
const int HEIGHT = 950;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

typedef struct{
    float angle;
    float velocity_X;
    float velocity_Y;
    SDL_Rect pos;

}Ball;

typedef struct{
  //First player rectangle
  SDL_Rect p1_rect;
  //Second player rectangle
  SDL_Rect p2_rect;
  SDL_Rect separator;
  Ball ball;
}Board;

void Draw_Board(SDL_Renderer* renderer, Board* board){
  SDL_SetRenderDrawColor(renderer,255,255,255,255);
  SDL_RenderFillRect(renderer, &board->p1_rect);
  SDL_RenderFillRect(renderer, &board->p2_rect);
  SDL_RenderFillRect(renderer, &board->ball.pos);
  SDL_RenderFillRect(renderer, &board->separator);
  SDL_RenderPresent(renderer);
}

void Update_Ball(Ball* ball, bool touched){
    //Update the ball velocity if touched

    //Update the ball's position based on its current velocity
    ball->pos.x += ball->velocity_X;
    ball->pos.y += ball->velocity_Y;
}
//ball->pos.y > board->p1_rect.y && ball->pos.y < board->p1_rect.h - board->p1_rect.y
bool Detect_Colisions(Board* board, Ball* ball){
  //If the ball touches a rectangle
  ball->angle = rand() % 90;
  int rect_height = board->p1_rect.h;
  printf("%d %d\n", board->p2_rect.x, board->p2_rect.y);
  if((ball->pos.x > board->p2_rect.x) && ((ball->pos.y > board->p2_rect.y || ball->pos.y+ball->pos.h > board->p2_rect.y) && (ball->pos.y < rect_height + board->p2_rect.y || ball->pos.y + ball->pos.h < rect_height + board->p2_rect.y))){
      ball->velocity_X = -(ball->velocity_X);
      if(ball->velocity_X < 0)
        ball->velocity_X-=0.01;
      else
        ball->velocity_X+=0.01;
      if(ball->angle > 45)
        ball->velocity_Y+=0.1;
      else
        ball->velocity_Y-=0.1;

  }
  else if((ball->pos.x < board->p1_rect.x) && ((ball->pos.y > board->p1_rect.y || ball->pos.y+ball->pos.h > board->p2_rect.y) && (ball->pos.y < rect_height + board->p1_rect.y || ball->pos.y + ball->pos.h < rect_height + board->p1_rect.y))){
    ball->velocity_X = -(ball->velocity_X);
    if(ball->velocity_X < 0)
      ball->velocity_X-=0.5;
    else
      ball->velocity_X+=0.5;

      if(ball->angle > 45)
        ball->velocity_Y+=0.1;
      else
        ball->velocity_Y-=0.1;
  }

}

void Is_Max_Y(Board *board){
  if(board->p2_rect.y == 0){
    board->p2_rect.y -= 10;
  }
  printf("%d\n",board->p2_rect.y);
}

int main(int argc, char **argv){
  //MAIN VARIABLES/////////////
  srand(time(NULL));
  Ball ball;
  ball.pos.x = WIDTH / 2;
  ball.pos.y = HEIGHT / 2;
  ball.pos.w = 20;
  ball.pos.h = 20;
  ball.velocity_X = 1.f;
  ball.velocity_Y = 0.f;

  SDL_Rect rect1 = {10,350,20,150};
  SDL_Rect rect2 = {1170,350,20,150};
  SDL_Rect separator = {600,0,5,950};

  Board board;
  board.ball = ball;
  board.p1_rect = rect1;
  board.p2_rect = rect2;
  board.p2_rect = rect2;
  board.separator = separator;
  /////////////////////////////////
  int status = EXIT_FAILURE;

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

  Draw_Board(renderer, &board);
  Is_Max_Y(&board);
  SDL_Event event;
  bool continu = true;
  while(continu){
    Update_Ball(&board.ball, false);
    Detect_Colisions(&board, &board.ball);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    Draw_Board(renderer, &board);

    while(SDL_PollEvent(&event)!=0){
          switch(event.key.keysym.scancode){
            case SDL_SCANCODE_DOWN:
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);
                board.p2_rect.y += 10;
                Draw_Board(renderer, &board);
                break;

            case SDL_SCANCODE_UP:
              SDL_SetRenderDrawColor(renderer,0,0,0,255);
              SDL_RenderClear(renderer);
              board.p2_rect.y -= 10;
              Draw_Board(renderer, &board);
              break;
            }
          }

}

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
