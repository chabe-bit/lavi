#ifndef LAVI_3D_H
#define LAVI_3D_H

#ifndef LAVI_PLATFORM_H
#error Include lavi_platform.h before lavi_3d.h
#endif 


#include <stddef.h>
#include <string.h>
#include <math.h>

#ifndef LAVI_3D_MAX_LINE_VERTICES
#define LAVI_3D_MAX_LINE_VERTICES 4096
#endif 

typedef enum {
    LAVI_3D_SUCCESS = 0,
    LAVI_3D_ERROR_INVALID_ARG,
    LAVI_3D_ERROR_NOT_INITIALIZED,
    LAVI_3D_ERROR_OPENGL_FUNCTION,
    LAVI_3D_ERROR_OPENGL_VERSION,
    LAVI_3D_ERROR_SHADER_COMPILE,
    LAVI_3D_ERROR_PROGRAM_LINK,
    LAVI_3D_ERROR_CONTEXT,
} lavi_3d_status;

extern void lavi_3d_init(lavi_api *api);
extern void lavi_3d_deinit(lavi_3d *gfx);


void 
lavi_3d_init(lavi_api *api)
{

}


#endif /* LAVI_3D_H */
