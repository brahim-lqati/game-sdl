#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
typedef struct PlaceElement{
SDL_Rect *rect;
 struct PlaceElement *next;
}PlaceElement;

typedef struct Agent{
   char *nom;
   int taille;
   SDL_Rect *rect;
}Agent;

typedef struct agentElement{
      Agent *agent;
      struct agentElement *next;
}agentElement;

SDL_Rect *createRectangle(int x,int y,int h,int w){
   SDL_Rect *newrect;
   newrect=(SDL_Rect*)malloc(sizeof(SDL_Rect));
   newrect->x=x;
   newrect->y=y;
   newrect->h=h;
   newrect->w=w;
   return newrect;
}

Agent *createAgent(char *nom,int taille,int abs,int ord,int height,int width){
  Agent *newagent;
  newagent=(Agent*)malloc(sizeof(Agent));
  newagent->nom=nom;
  newagent->taille=taille;
  newagent->rect=createRectangle(abs,ord,height,width);
 return newagent;
}

agentElement *createAgentElement(Agent *agent){
    agentElement *newElementAg;
    newElementAg=(agentElement*)malloc(sizeof(agentElement));
    newElementAg->agent=agent;
    newElementAg->next=NULL;
    return newElementAg;
}

void insertAgentFirst(agentElement **headAgent,Agent *agent){
  agentElement *newEltAge;
  newEltAge=createAgentElement(agent);
  newEltAge->next=*headAgent;
  *headAgent=newEltAge;
}

void drawAgents(SDL_Renderer *renderer , agentElement *agents){
    agentElement *ptr;
    for(ptr = agents;ptr != NULL;ptr = ptr->next){
        SDL_RenderFillRect(renderer , ptr->agent->rect);
    }
}


PlaceElement *createPlaceElement(SDL_Rect *Rect){
  PlaceElement *newElement;
  newElement=(PlaceElement*)malloc(sizeof(PlaceElement));
  newElement->rect=Rect;
  newElement->next=NULL;
  return newElement;
  }

  void insertFirstPlace(PlaceElement **Places,SDL_Rect *Rect){
  PlaceElement *newElement;
  newElement=createPlaceElement(Rect);
  newElement->next=*Places;
  *Places=newElement;
  }
void drawPlaceElements(SDL_Renderer *renderer, PlaceElement *places ){
      SDL_Rect *placeRect=createRectangle(10,40,80,80);
      PlaceElement* p1 = createPlaceElement(placeRect);
      insertFirstPlace(&places , p1);
      SDL_RenderFillRect(renderer , p1->rect);

      placeRect=createRectangle(200,230,80,80);
      p1 = createPlaceElement(placeRect);
      insertFirstPlace(&places , p1);
      SDL_RenderFillRect(renderer , p1->rect);


      placeRect=createRectangle(250,400,80,80);
      p1 = createPlaceElement(placeRect);
      insertFirstPlace(&places , p1);
      SDL_RenderFillRect(renderer , p1->rect);


     placeRect=createRectangle(600,460,80,80);
      p1 = createPlaceElement(placeRect);
      insertFirstPlace(&places , p1);
      SDL_RenderFillRect(renderer , p1->rect);
}


int main(int arg, char *arc[])
{
   if(SDL_Init(SDL_INIT_EVERYTHING)<0){
    printf("error :%s",SDL_GetError());
    exit(-1);
   }

   SDL_Window *Window;
   Window=SDL_CreateWindow("hello sdl",150,150,850,600,SDL_WINDOW_OPENGL);
   if(Window==NULL){
    printf("\n%s",SDL_GetError());
    exit(-1);
   }
   PlaceElement *places;
   places=NULL;
   agentElement *agents;
   agents=NULL;
   SDL_Rect *depart;
   SDL_Rect *arrive;

    SDL_Event WindowEvent;
    SDL_Renderer *renderer = SDL_CreateRenderer(Window , -1 , SDL_RENDERER_ACCELERATED);

   //pour la fenetre reste ouvere jusqu'on le fermer
   while(1){
    if(SDL_PollEvent(&WindowEvent)){
        if(WindowEvent.type==SDL_QUIT)
             break;


  if(WindowEvent.type==SDL_MOUSEBUTTONDOWN){
    Agent *agent=createAgent("brahim",4,WindowEvent.button.x,WindowEvent.button.y,20,20);
    insertAgentFirst(&agents,agent);
  }
  if(WindowEvent.type==SDL_KEYDOWN){
        if(WindowEvent.key.keysym.sym== SDLK_s){
            depart=createRectangle(0,0,30,60);
            arrive=createRectangle(790,570,30,60);
        }

    }
   }

     // code
  SDL_SetRenderDrawColor(renderer , 204 , 102 , 0 , 255);
  SDL_RenderClear(renderer);

  // Pour initialiser les places
  SDL_SetRenderDrawColor(renderer , 0 , 255 , 0 , 255);
  drawPlaceElements(renderer , places);


  SDL_SetRenderDrawColor(renderer , 0, 0 , 0 , 255);
  drawAgents(renderer , agents);

  SDL_SetRenderDrawColor(renderer , 255 , 0 , 0, 255);
  SDL_RenderFillRect(renderer , depart);


  SDL_SetRenderDrawColor(renderer , 255 , 0 , 255, 255);
  SDL_RenderFillRect(renderer , arrive);
  SDL_RenderPresent(renderer);
   }
   //SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(Window);
   SDL_Quit();
   return 0;
}
