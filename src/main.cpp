#include "sdl.hpp"
#include <iostream>
#include <vector>

using namespace std;

const Color COLOR_LIGHT_GRAY = {192, 192, 192, 255};
const Color COLOR_BLACK = {0, 0, 0, 255};
const Color COLOR_RED = {255, 0, 0, 255};
const Color COLOR_GREEN = {0, 255, 0, 255};
const Color COLOR_BLUE = {0, 0, 255, 255};

class Actor {
public:
    int x, y;

    Actor(int xpos, int ypos) {
        x = xpos;
        y = ypos;
    }

    void render() {
        draw_rect(x, y, 50, 70, COLOR_BLACK); // Draw actor as a rectangle
    }

    void position(int xpos, int ypos) {
        x = xpos;
        y = ypos;
    }
};

class Portal {
public:
    int x, y;
    enum TYPE {
        RED,   // 0 by default
        BLUE,  // 1 by default
        GREEN  // 2 by default
    };

    TYPE type;

    Portal(int xpos, int ypos, TYPE portalType) {
        x = xpos;
        y = ypos;
        type = portalType;
    }

    void render() {
        Color portalColor;
        if (type == RED) {
            portalColor = COLOR_RED;
        } else if (type == BLUE) {
            portalColor = COLOR_BLUE;
        } else {
            portalColor = COLOR_GREEN;
        }
        draw_circle(x, y, 50, portalColor); // Draw portal as a circle
    }

    void position(int xpos, int ypos) {
        x = xpos;
        y = ypos;
    }
};

int main() {
    init_window(1080, 720, "RGB", 60);
    bool running = true;
    SDL_Event event;

    Actor player(100, 100);

    // Vector to store the portals
    vector<Portal> portals;

    // Main game loop
    while (running) {
        // Clear the screen with light gray color
        clear_screen(COLOR_LIGHT_GRAY);

        // Event handling loop
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_r:
                            portals.push_back(Portal(player.x, player.y, Portal::RED));
                            break;
                        case SDLK_g:
                            portals.push_back(Portal(player.x, player.y, Portal::GREEN));
                            break;
                        case SDLK_b:
                            portals.push_back(Portal(player.x, player.y, Portal::BLUE));
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }

        // Get current keyboard state
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        // Check key states for continuous movement
        if (keystate[SDL_SCANCODE_UP]) {
            player.y -= 10;  // Move up
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            player.y += 10;  // Move down
        }
        if (keystate[SDL_SCANCODE_LEFT]) {
            player.x -= 10;  // Move left
        }
        if (keystate[SDL_SCANCODE_RIGHT]) {
            player.x += 10;  // Move right
        }

        // Render the actor
        player.render();

        // Render all portals
        for (auto& portal : portals) {
            portal.render();
        }

        // Present the rendered screen to the window
        present();
    }

    quit_window();
    return 0;
}
