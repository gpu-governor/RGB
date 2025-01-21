#include"sdl.hpp"
#include<iostream>

using namespace std;
const Color COLOR_LIGHT_GRAY = {192, 192, 192, 255};
const Color COLOR_BLACK = {0, 0, 0, 255};


class Actor{
    public:
    int x, y;

    Actor(int xpos, int ypos){
        x = xpos;
        y = ypos;
    }

    void render(){
        draw_rect(x,y,50,70,COLOR_BLACK);
    }

    void position(int xpos, int ypos){
        x = xpos;
        y = ypos;
    }
    private:
};

int main(){
    init_window(1080, 720,"RGB",60);
    bool running= true;
    SDL_Event event;
    
    while(SDL_PollEvent(&event)){
     switch(event.type){
        case SDL_QUIT:
            running = false;
        break;
        
     }
    clear_screen(COLOR_LIGHT_GRAY);



    present();
    }
    quit_window();
    return 0;
}
