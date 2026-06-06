#include "lavi_platform.h"
#include <math.h>

typedef struct {
    int x, y;
} vec2;

typedef struct {
    float x, y;
} vec2f;

vec2f make_vec2f(float x, float y)
{
    vec2f v = {x, y};
    return v;
}

static lavi_api api;

enum {
    O_none,
    O_player,
    O_bullet,
    O_enemy
};

typedef struct {
    int type;
    vec2f pos;
    vec2f vel;
    float ori;
    float angvel;
} Object;

int max_objects = 0;
#define MAX_OBJECTS 16384
static Object g_obj[MAX_OBJECTS];

typedef int objid;
objid player;

#define M_PI 3.141592
float cs[32][256], sn[32][256]; 

void 
sin_cos_cache(int n)
{
    int i;
    for (i = 0; i < n; i++) {
        sn[n][i] = sin(i*M_PI*2/n); 
        cs[n][i] = cos(i*M_PI*2/n); 
    }
}

void 
polygon_star(int n, int s, float r)
{
    int i, j = 0;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++) {
        glVertex2f(cs[n][j]*r, sn[n][j]*r);
        j = (j + s) % n;
    }
    glEnd();
}



objid obj_alloc(int type)
{
    int i;
    for (i = 1; i < MAX_OBJECTS; i++) {
        if (g_obj[i].type == O_none) {
            g_obj[i].type =  type;

            if (i > max_objects) max_objects = i;
            return i;
        }
    }

    assert(0);
    return 0;
}

void obj_free(objid id)
{
    g_obj[id].type = O_none;
}

#define PLAYER_MOVE_SPEED 20.0
void input(void)
{

}

void ai(void)
{
    int i;
    for (i = 1; i < max_objects; i++) {
    
    }    
}

void physics(void)
{
    int i;
    for (i = 1; i < max_objects; i++) {
        Object *o = &g_obj[i];
        if (o->type == O_none) 
            continue;

        o->pos.x += o->vel.x * api.time.delta_sec;
        o->pos.y += o->vel.y * api.time.delta_sec;
        o->ori   += o->angvel * api.time.delta_sec;
    }
}

void render(void)
{
    objid i;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for (i = 1; i <= max_objects; i++) {
        Object *o = &g_obj[i];
        glPushMatrix();
        glTranslatef(o->pos.x, o->pos.y, 0);
        glRotatef(o->ori, 0, 0 ,1);

        glColor3f(1, 0, 1);
        polygon_star(9, 2, 50);

#if 0
        glBegin(GL_LINE_LOOP);
            glVertex2i(-4,  4);
            glVertex2i( 4,  4);
            glVertex2i( 4, -4);
            glVertex2i(-4, -4);
        glEnd();
#endif
        glPopMatrix();
    }
}

void lavi_main(int argc, char **argv)
{
    api.window.size = LAVI_POINT(1600, 1200);
    api.window.name = "Demo";
    lavi_init(&api);

    for (int i = 2; i < 32; i++) {
        sin_cos_cache(i);
    }

    player = obj_alloc(O_player);
    g_obj[player].pos = make_vec2f(1000/2, 750/2);
    g_obj[player].angvel = 60;


    while (!api.quit) {
        Object *pobj = &g_obj[player];
        lavi_update();
   
        
        if (api.keys[LAVI_VK_F1].is_pressed) {
            printf("PRESSED\n");
        }
        if (api.keys[LAVI_VK_F1].is_released) {
            printf("RELEASED\n");
        }

        if (api.gamepad.dpad_down.is_pressed) {
            printf("DPAD DOWN is pressed\n");
        }

        {
            int updown = 0, leftright = 0;
            if (api.keys[LAVI_VK_LEFT].is_down)   {leftright -= 1;}
            if (api.keys[LAVI_VK_RIGHT].is_down)  {leftright += 1;}
            if (api.keys[LAVI_VK_UP].is_down)     {updown    -= 1;}
            if (api.keys[LAVI_VK_DOWN].is_down)   {updown    += 1;}
            
            pobj->vel.x = leftright * PLAYER_MOVE_SPEED;
            pobj->vel.y = updown    * PLAYER_MOVE_SPEED;

            pobj->pos.x += pobj->vel.x * api.time.delta_sec;
            pobj->pos.y += pobj->vel.y * api.time.delta_sec;
        }

        glClearColor(.25, .25, .25, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 1000, 0, 750);

        
        render();
            
        glTranslatef(100, 500, 0);
        for (int i = 2; i < 20; i++) {
            polygon_star(i, 3, 50);
            glTranslatef(60, 0, 0);
        }

    }

}
