#ifndef LAVI_3D_H
#define LAVI_3D_H

#ifndef LAVI_PLATFORM_H
#error include lavi_platform.h before lavi_3d.h
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

typedef enum {
    LAVI_3D_UNLIT = 0,
    LAVI_3D_LIT,
} lavi_3d_shading_mode;

typedef enum {
    LAVI_3D_DEPTH_DISABLED = 0,
    LAVI_3D_DEPTH_LESS,
    LAVI_3D_DEPTH_LESS_EQUAL,
} lavi_3d_depth_mode;

typedef enum {
    LAVI_3D_CULL_DISABLED = 0,
    LAVI_3D_CULL_BACK,
    LAVI_3D_CULL_FRONT,
} lavi_3d_cull_mode;

enum { LAVI_3D_CLEAR_COLOR = 1, LAVI_3D_CLEAR_DEPTH = 2 };

typedef struct {
    float x, y, z;
} lavi_3d_vec3;

typedef struct {
    float r, g, b, a;
} lavi_3d_color;

typedef struct {
    float elements[16];
} lavi_3d_mat4;

typedef struct {
    lavi_3d_vec3 pos;
    lavi_3d_vec3 rot_deg;
    lavi_3d_vec3 scale;
} lavi_3d_transform;

typedef struct {
    lavi_3d_vec3 pos;
    lavi_3d_vec3 target;
    lavi_3d_vec3 up;
    float fovy_deg;
    float near_plane;
    float far_plane;
} lavi_3d_camera;

typedef struct {
    lavi_3d_vec3 pos;
    lavi_3d_vec3 normal;
} lavi_3d_vertex;

typedef struct {
    lavi_3d_vec3 pos;
    lavi_3d_color color;
} lavi_3d_line_vertex;


typedef void (APIENTRY *lavi_3d_proc)(void);
typedef lavi_3d_proc (*lavi_3d_load_proc)(const char *name, void *user);
typedef int (APIENTRY *lavi_3d_wgl_make_current_proc)(void *, void *);
typedef int (APIENTRY *lavi_3d_wgl_delete_context_proc)(void *);
typedef const unsigned char *(APIENTRY *lavi_3d_gl_get_string_proc)(unsigned int);
typedef void (APIENTRY *lavi_3d_gl_get_integer_proc)(unsigned int, int *);
typedef void (APIENTRY *lavi_3d_gl_void_enum_proc)(unsigned int);
typedef void (APIENTRY *lavi_3d_gl_clear_color_proc)(float, float, float, float);
typedef void (APIENTRY *lavi_3d_gl_viewport_proc)(int, int, int, int);
typedef void (APIENTRY *lavi_3d_gl_blend_func_proc)(unsigned int, unsigned int);
typedef void (APIENTRY *lavi_3d_gl_polygon_mode_proc)(unsigned int, unsigned int);
typedef void (APIENTRY *lavi_3d_gl_line_width_proc)(float);
typedef void (APIENTRY *lavi_3d_gl_gen_objects_proc)(int, unsigned int *);
typedef void (APIENTRY *lavi_3d_gl_delete_objects_proc)(int, const unsigned int *);
typedef void (APIENTRY *lavi_3d_gl_bind_object_proc)(unsigned int);
typedef void (APIENTRY *lavi_3d_gl_bind_buffer_proc)(unsigned int, unsigned int);
typedef void (APIENTRY *lavi_3d_gl_buffer_data_proc)(unsigned int, ptrdiff_t, const void *, unsigned int);
typedef void (APIENTRY *lavi_3d_gl_buffer_sub_data_proc)(unsigned int, ptrdiff_t, ptrdiff_t, const void *);
typedef void (APIENTRY *lavi_3d_gl_vertex_attrib_pointer_proc)(unsigned int, int, unsigned int, unsigned char, int, const void *);
typedef void (APIENTRY *lavi_3d_gl_enable_vertex_attrib_proc)(unsigned int);
typedef unsigned int (APIENTRY *lavi_3d_gl_create_shader_proc)(unsigned int);
typedef void (APIENTRY *lavi_3d_gl_shader_source_proc)(unsigned int, int, const char *const *, const int *);
typedef void (APIENTRY *lavi_3d_gl_compile_shader_proc)(unsigned int);
typedef void (APIENTRY *lavi_3d_gl_get_shader_iv_proc)(unsigned int, unsigned int, int *);
typedef void (APIENTRY *lavi_3d_gl_get_shader_log_proc)(unsigned int, int, int *, char *);
typedef void (APIENTRY *lavi_3d_gl_delete_shader_proc)(unsigned int);
typedef unsigned int (APIENTRY *lavi_3d_gl_create_program_proc)(void);
typedef void (APIENTRY *lavi_3d_gl_program_shader_proc)(unsigned int, unsigned int);
typedef void (APIENTRY *lavi_3d_gl_link_program_proc)(unsigned int);
typedef void (APIENTRY *lavi_3d_gl_get_program_iv_proc)(unsigned int, unsigned int, int *);
typedef void (APIENTRY *lavi_3d_gl_get_program_log_proc)(unsigned int, int, int *, char *);
typedef void (APIENTRY *lavi_3d_gl_delete_program_proc)(unsigned int);
typedef void (APIENTRY *lavi_3d_gl_use_program_proc)(unsigned int);
typedef int (APIENTRY *lavi_3d_gl_get_uniform_location_proc)(unsigned int, const char *);
typedef void (APIENTRY *lavi_3d_gl_uniform_1i_proc)(int, int);
typedef void (APIENTRY *lavi_3d_gl_uniform_1f_proc)(int, float);
typedef void (APIENTRY *lavi_3d_gl_uniform_3f_proc)(int, float, float, float);
typedef void (APIENTRY *lavi_3d_gl_uniform_4f_proc)(int, float, float, float, float);
typedef void (APIENTRY *lavi_3d_gl_uniform_mat4_proc)(int, int, unsigned char, const float *);
typedef void (APIENTRY *lavi_3d_gl_draw_arrays_proc)(unsigned int, int, int);
typedef void (APIENTRY *lavi_3d_gl_draw_elements_proc)(unsigned int, int, unsigned int, const void *);

typedef struct {
    lavi_3d_gl_get_string_proc              GetString;
    lavi_3d_gl_get_integer_proc             GetIntegerv;
    lavi_3d_gl_clear_color_proc             ClearColor;
    lavi_3d_gl_void_enum_proc               Clear;
    lavi_3d_gl_viewport_proc                Viewport;
    lavi_3d_gl_void_enum_proc               Enable;
    lavi_3d_gl_void_enum_proc               Disable;
    lavi_3d_gl_void_enum_proc               DepthFunc;
    lavi_3d_gl_void_enum_proc               CullFace;
    lavi_3d_gl_void_enum_proc               FrontFace;
    lavi_3d_gl_blend_func_proc              BlendFunc;
    lavi_3d_gl_polygon_mode_proc            PolygonMode;
    lavi_3d_gl_line_width_proc              LineWidth;
    lavi_3d_gl_gen_objects_proc             GenBuffers;
    lavi_3d_gl_delete_objects_proc          DeleteBuffers;
    lavi_3d_gl_bind_buffer_proc             BindBuffer;
    lavi_3d_gl_buffer_data_proc             BufferData;
    lavi_3d_gl_buffer_sub_data_proc         BufferSubData;
    lavi_3d_gl_gen_objects_proc             GenVertexArrays;
    lavi_3d_gl_delete_objects_proc          DeleteVertexArrays;
    lavi_3d_gl_bind_object_proc             BindVertexArray;
    lavi_3d_gl_enable_vertex_attrib_proc    EnableVertexAttribArray;
    lavi_3d_gl_vertex_attrib_pointer_proc   VertexAttribPointer;
    lavi_3d_gl_create_shader_proc           CreateShader;
    lavi_3d_gl_shader_source_proc           ShaderSource;
    lavi_3d_gl_compile_shader_proc          CompileShader;
    lavi_3d_gl_get_shader_iv_proc           GetShaderiv;
    lavi_3d_gl_get_shader_log_proc          GetShaderInfoLog;
    lavi_3d_gl_delete_shader_proc           DeleteShader;
    lavi_3d_gl_create_program_proc          CreateProgram;
    lavi_3d_gl_program_shader_proc          AttachShader;
    lavi_3d_gl_link_program_proc            LinkProgram;
    lavi_3d_gl_get_program_iv_proc          GetProgramiv;
    lavi_3d_gl_get_program_log_proc         GetProgramInfoLog;
    lavi_3d_gl_program_shader_proc          DetachShader;
    lavi_3d_gl_delete_program_proc          DeleteProgram;
    lavi_3d_gl_use_program_proc             UseProgram;
    lavi_3d_gl_get_uniform_location_proc    GetUniformLocation;
    lavi_3d_gl_uniform_1i_proc              Uniform1i;
    lavi_3d_gl_uniform_1f_proc              Uniform1f;
    lavi_3d_gl_uniform_3f_proc              Uniform3f;
    lavi_3d_gl_uniform_4f_proc              Uniform4f;
    lavi_3d_gl_uniform_mat4_proc            UniformMatrix4fv;
    lavi_3d_gl_draw_arrays_proc             DrawArrays;
    lavi_3d_gl_draw_elements_proc           DrawElements;
} lavi_3d_gl;

typedef struct {
    lavi_3d_gl gl;
    lavi_3d_status status;
    char err[1024];
    int initialized;
    int major_version;
    int minor_version;
    lavi_3d_depth_mode depth_mode;
    lavi_3d_cull_mode cull_mode;
    void *device_context;
    void *render_context;
    void *api;
    int using_render_context;
} lavi_3d;

typedef struct {
    unsigned int id;
} lavi_3d_program;

typedef struct {
    unsigned int vertex_array;
    unsigned int vertex_buffer;
    unsigned int index_buffer;
    unsigned int vertex_count;
    unsigned int index_count;
} lavi_3d_mesh;

typedef struct {
    lavi_3d *gfx;
    lavi_3d_line_vertex line_vertices[LAVI_3D_MAX_LINE_VERTICES];
    int line_count;
    int initialized;
    lavi_3d_mat4 view;
    lavi_3d_mat4 projection;
    lavi_3d_mat4 view_projection;
} lavi_3d_renderer;


// System 
extern void lavi_3d_init(lavi_3d *gfx, lavi_api *api);
extern void lavi_3d_deinit(lavi_3d *gfx);

// Loggers
extern const char *lavi_3d_status_print(lavi_3d_status status);
extern const char *lavi_3d_error_print(lavi_3d *gfx);

// --------------- Math Work -------------------- 

// Vec3 
extern lavi_3d_vec3 lavi_3d_vec3_make(float x, float y, float z);
extern lavi_3d_vec3 lavi_3d_vec3_add(lavi_3d_vec3 a, lavi_3d_vec3 b);
extern lavi_3d_vec3 lavi_3d_vec3_sub(lavi_3d_vec3 a, lavi_3d_vec3 b);
extern lavi_3d_vec3 lavi_3d_vec3_scale(lavi_3d_vec3 value, float scale);
extern float        lavi_3d_vec3_dot(lavi_3d_vec3 a, lavi_3d_vec3 b);
extern lavi_3d_vec3 lavi_3d_vec3_cross(lavi_3d_vec3 a, lavi_3d_vec3 b);
extern lavi_3d_vec3 lavi_3d_vec3_norm(lavi_3d_vec3 value);

// Mat4 
extern lavi_3d_mat4 lavi_3d_mat4_identity(void);
extern lavi_3d_mat4 lavi_3d_mat4_mult(lavi_3d_mat4 a, lavi_3d_mat4 b);
extern lavi_3d_mat4 lavi_3d_mat4_translation(lavi_3d_vec3 pos);
extern lavi_3d_mat4 lavi_3d_mat4_scale(lavi_3d_vec3 scale);
extern lavi_3d_mat4 lavi_3d_mat4_rot_x(float deg);
extern lavi_3d_mat4 lavi_3d_mat4_rot_y(float deg);
extern lavi_3d_mat4 lavi_3d_mat4_rot_z(float deg);
extern lavi_3d_mat4 lavi_3d_mat4_perspective(float fovy_deg, 
                                             float aspect,
                                             float near_plane,
                                             float far_plane);
extern lavi_3d_mat4 lavi_3d_mat4_look_at(lavi_3d_vec3 eye, lavi_3d_vec3 target, lavi_3d_vec3 up); 


// LAVI_3D_IMPLEMENTATION 
#ifdef LAVI_3D_IMPLMEMENTATION

#define LAVI_3D_GL_VERSION                 0x1F02
#define LAVI_3D_GL_MAJOR_VERSION           0x821B
#define LAVI_3D_GL_MINOR_VERSION           0x821C
#define LAVI_3D_GL_COLOR_BUFFER_BIT        0x00004000
#define LAVI_3D_GL_DEPTH_BUFFER_BIT        0x00000100
#define LAVI_3D_GL_DEPTH_TEST              0x0B71
#define LAVI_3D_GL_CULL_FACE               0x0B44
#define LAVI_3D_GL_BLEND                   0x0BE2
#define LAVI_3D_GL_LESS                    0x0201
#define LAVI_3D_GL_LEQUAL                  0x0203
#define LAVI_3D_GL_BACK                    0x0405
#define LAVI_3D_GL_FRONT                   0x0404
#define LAVI_3D_GL_CCW                     0x0901
#define LAVI_3D_GL_FRONT_AND_BACK          0x0408
#define LAVI_3D_GL_FILL                    0x1B02
#define LAVI_3D_GL_LINE                    0x1B01
#define LAVI_3D_GL_ARRAY_BUFFER            0x8892
#define LAVI_3D_GL_ELEMENT_ARRAY_BUFFER    0x8893
#define LAVI_3D_GL_STATIC_DRAW             0x88E4
#define LAVI_3D_GL_DYNAMIC_DRAW            0x88E8
#define LAVI_3D_GL_FLOAT                   0x1406
#define LAVI_3D_GL_UNSIGNED_INT            0x1405
#define LAVI_3D_GL_FALSE                   0
#define LAVI_3D_GL_TRIANGLES               0x0004
#define LAVI_3D_GL_LINES                   0x0001
#define LAVI_3D_GL_VERTEX_SHADER           0x8B31
#define LAVI_3D_GL_FRAGMENT_SHADER         0x8B30
#define LAVI_3D_GL_COMPILE_STATUS          0x8B81
#define LAVI_3D_GL_LINK_STATUS             0x8B82

#if 0
static void 
lavi_3d_set_error(lavi_3d *gfx, 
                  lavi_3d_status status,
                  const char *message)
{
    LAVI_ASSERT(gfx);
    LAVI_ASSERT(message);
    
    size_t length;
    gfx->status = status;
    gfx->err[0] = '\0';
    
    length = strlen(message);
    if (length >= sizeof(gfx->err)) {
        length = sizeof(gfx->err) - 1;    
    }    
    
    memcpy(gfx->err, message, length);
    gfx->err[length] = '\0';
}

const char *
lavi_3d_status_print(lavi_3d_status status)
{
    const char *result = "";
    
    switch (status) {
    case LAVI_3D_SUCCESS: result = "Success"; break;
    case LAVI_3D_ERROR_INVALID_ARG: result = "Invalid arg"; break;
    case LAVI_3D_ERROR_NOT_INITIALIZED: result = "Not initialized"; break;
    case LAVI_3D_ERROR_OPENGL_FUNCTION: result = "Missing OpenGL function"; break;
    case LAVI_3D_ERROR_OPENGL_VERSION: result = "OpenGL 3.3 is required"; break;
    case LAVI_3D_ERROR_SHADER_COMPILE: result = "Shader compilation failed"; break;
    case LAVI_3D_ERROR_PROGRAM_LINK: result = "Program linking failed"; break;
    case LAVI_3D_ERROR_CONTEXT: result = "OpenGL context creation failed"; break;
    default: result = "Unknown error"; break;
    }   
    
    return result;
}

const char *
lavi_3d_get_error(lavi_3d *gfx)
{
    const char *result = "";
    
    if (gfx == NULL) { 
        result = "Invalid status state";
        return result;
    }
    
    if (gfx->err[0] == '\0') {
        result = lavi_3d_status_print(gfx->status); 
        return result;
    }
    
    result = gfx->err;
    return result;
}
#endif 


void 
lavi_3d_init(lavi_api *api)
{

}



lavi_3d_vec3 
lavi_3d_vec3_make(float x, float y, float z) 
{
    lavi_3d_vec3 v3 = {0};
    v3.x = x;
    v3.y = y;
    v3.z = z;
    return v3;    
}

lavi_3d_vec3 
lavi_3d_vec3_add(lavi_3d_vec3 a, lavi_3d_vec3 b) 
{
    lavi_3d_vec3 add = {0};
    add.x = a.x + b.x;
    add.y = a.y + b.y;
    add.z = a.z + b.z;    
    return add;    
}    

lavi_3d_vec3 
lavi_3d_vec3_sub(lavi_3d_vec3 a, lavi_3d_vec3 b)
{    
    lavi_3d_vec3 sub = {0};
    sub.x = a.x - b.x;
    sub.y = a.y - b.y;
    sub.z = a.z - b.z;    
    return sub;
}

lavi_3d_vec3
lavi_3d_vec3_scale(lavi_3d_vec3 value, float scale)
{
    lavi_3d_vec3 result = {0};
    result.x = value.x * scale;
    result.y = value.y * scale;
    result.z = value.z * scale;
    return result;   
}

float
lavi_3d_vec3_dot(lavi_3d_vec3 a, lavi_3d_vec3 b)
{
    float dot = 0.0f;
    dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);    
    return dot;
}

lavi_3d_color 
lavi_3d_color_rgba(float r, float g, float b, float a) 
{
    lavi_3d_color color = {0};
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;    
}

lavi_3d_color 
lavi_3d_color_rgb(float r, float g, float b) 
{
    lavi_3d_color color = {0};
    color = lavi_3d_color_rgba(r, g, b, 0.0f); 
    return color;   
}




#endif /* LAVI_3D_IMPLMEMENTATION */

#endif /* LAVI_3D_H */
