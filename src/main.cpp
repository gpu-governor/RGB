#include "sdl.hpp"
#include <iostream>

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
    bool active; // To check if the portal is created

    Portal() : active(false) {}

    void create(int xpos, int ypos, TYPE portalType) {
        x = xpos;
        y = ypos;
        type = portalType;
        active = true;
    }

    void render() {
        if (!active) return; // If the portal is inactive, don't render it

        Color portalColor;
        if (type == RED) {
            portalColor = COLOR_RED;
        } else if (type == BLUE) {
            portalColor = COLOR_BLUE;
        } else {
            portalColor = COLOR_GREEN;
        }
        draw_circle(x, y, 30, portalColor); // Draw portal as a circle
    }

    void position(int xpos, int ypos) {
        x = xpos;
        y = ypos;
    }

    void deactivate() {
        active = false; // Deactivate the portal
    }
};

int main() {
    init_window(1080, 720, "RGB", 60);
    bool running = true;
    SDL_Event event;

    Actor player(100, 100);

    // Create one portal for each color, initially inactive
    Portal redPortal, greenPortal, bluePortal;

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
                            if (!redPortal.active) {
                                redPortal.create(player.x, player.y, Portal::RED);
                            } else {
                                redPortal.position(player.x, player.y);
                            }
                            break;
                        case SDLK_g:
                            if (!greenPortal.active) {
                                greenPortal.create(player.x, player.y, Portal::GREEN);
                            } else {
                                greenPortal.position(player.x, player.y);
                            }
                            break;
                        case SDLK_b:
                            if (!bluePortal.active) {
                                bluePortal.create(player.x, player.y, Portal::BLUE);
                            } else {
                                bluePortal.position(player.x, player.y);
                            }
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

        // Render active portals
        redPortal.render();
        greenPortal.render();
        bluePortal.render();

        // Present the rendered screen to the window
        present();
    }

    quit_window();
    return 0;
}
