#include "lavi_platform.h"
#include <gl/gl.h>

typedef struct {
    int x, y;
} vec2;

typedef struct {
    float x, y;
} vec2f;

static lavi_api api;

enum {
    O_none,
    O_player,
    O_enemy
};

typedef struct {
    int type;
    vec2 position;
    vec2 vel;
} Object;

#define MAX_OBJECTS 16384
static Object g_obj[MAX_OBJECTS];

typedef int objid;
objid player;

objid obj_alloc(void)
{
    int i;
    for (i = 1; i < MAX_OBJECTS; i++) {
        if (g_obj[i].type == O_none)
            return i;
    }

    assert(0);
    return 0;
}

void obj_free(objid id)
{
    g_obj[id].type = O_none;
}


void lavi_main(int argc, char **argv)
{
    api.window.size = LAVI_POINT(1200, 720);
    api.window.name = "Demo";
    api.window.pos  = LAVI_POINT(0, 9);
    lavi_init(&api);

    player = obj_alloc();

    while (!api.quit) {
        lavi_update();
   
        if (api.keys[LAVI_VK_ALT].is_pressed) {
            printf("PRESSED\n");
        }
        if (api.keys[LAVI_VK_ALT].is_released) {
            printf("RELEASED\n");
        }

        if (api.gamepad.dpad_down.is_pressed) {
            printf("DPAD DOWN is pressed\n");
        }

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 1000, 0, 750, 0, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        //glTranslatef();

     }

}
