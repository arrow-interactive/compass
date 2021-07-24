
/*
Copyright © 2021 FOSSBAY / ARROW INTERACTIVE
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

NOTE: Make sure your OpenGL context loader is LOADED before <CompassGraphics.h>




*/

#ifndef  COMPASS_GRAPHICS_H
#define COMPASS_GRAPHICS_H



#ifndef COMPASS_SIN
#include <math.h>
#define COMPASS_SIN sin
#endif


#ifndef COMPASS_COS
#include <math.h>
#define COMPASS_COS cos
#endif

#ifndef COMPASS_MALLOC
#include <stdlib.h>
#define COMPASS_MALLOC malloc
#endif


#ifndef COMPASS_REALLOC 
#include <stdlib.h>
#define COMPASS_REALLOC realloc
#endif


#ifndef  COMPASS_FREE
#include <stdlib.h>
#define  COMPASS_FREE free
#endif


#ifndef  COMPASS_PRINTF
#include <stdio.h>
#define  COMPASS_PRINTF printf
#endif

#ifndef  COMPASS_STRCAT
#include <string.h>
#define  COMPASS_STRCAT strcat
#endif

#define COMPASS_VERSION "Compass Framework <1.2>" 
#define COMPASS_DEVELOPMENT_BUILD 0



#ifdef _WIN32

/* WIN32 (.dll) */
#ifdef COMPASS_BUILD_TYPE_SHARED   /* building compass as a .dll */
#define COMPASS_API   __declspec(dllexport)
#elif defined(COMPASS_USE_TYPE_SHARED) /* Using compass as a .dll */
#define COMPASS_API __declspec(dllimport) 
#else 
#define COMPASS_API  /* Compass as a static library, or a linux shared library */
#endif
#else 

#define COMPASS_API /* Compass as a static library, or a linux shared library */
#endif


typedef unsigned int    u32;
typedef float           f32;
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned long   u64;
typedef char            s8;
typedef int             s32;
typedef short           s16;
typedef long            s64;
typedef float           m4[4][4];
typedef struct {f32 x; f32 y;}               v2;
typedef struct {u32 x; f32 y; f32 z;}        v3;
typedef struct {f32 x; f32 y; f32 z; f32 w;} v4;
typedef struct {u32 r; u32 g; u32 b; u32 a;} Color;


typedef struct {
    
    f32 w;
    f32 h;
    u8* data;
    v2 left_top, left_bottom,  right_top, right_bottom;
    u32 texture;
    u32 texture_State;
    
} compass_texture_t;

typedef struct {
    /* Framebuffer Object ID -- this probably doesn't really concern you as it's managed by compass already. */
    u32 framebuffer_object;
    /*  Framebuffer texture -- returns the texture for the framebuffer.*/
    compass_texture_t texture;
    /*  Framebuffer renderbuffer -- This is a rendererbuffer, faster than the framebuffer however you can't send this to a shader. this means you can't append the framebuffer texture to the shader. */
    u32 renderbuffer;
    /* Framebuffer sizes --- This should only be one size throughout the entire framebuffer. Doing this will result in a 36054 error. */
    f32 w;
    f32 h;
    /* Framebuffer RBO checker -- this checks if the Renderbuffer does exist. and if so, then we'll bind the renderbuffer. */
    u32 rbo_enabled;
    
} compass_framebuffer_t;



typedef struct {
    
    const s8* fragment;
    const s8* vertex;
    struct
    {
        void* handle;
    } shader_handle;
    
} compass_shader_t;

typedef struct {
    f32 w;
    f32 h;
    f32 x;
    f32 y;
    f32 scale;
    f32 rotate;
    
    
} compass_view_t;


typedef struct {
    
    u32 w;
    u32 h;
    compass_shader_t shader;
    struct
    {
        void* handle;
    } graphics;
    Color color;
    compass_view_t view;
    
    
} compass_renderer_t;

typedef struct 
{
    v3 position;
    v4 color;
    v2 textureCoords;
    u32 texture_on;
} compass_vertex_t;

typedef struct {
    s8 *key;
    u32 value;
} compass_uniform_cache_t;

typedef struct {
    f32 w;
    f32 h;
    f32 x;
    f32 y;
    Color color;
    compass_texture_t texture;
} compass_rect_t;

typedef struct {
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
    Color color;
    
} compass_line_t;


typedef enum {
    COMPASS_IMAGE_Png,
    COMPASS_IMAGE_Jpg,
    COMPASS_IMAGE_Bmp
        
        
} compass_image_flags_t;
typedef enum
{
    COMPASS_DRAW_Triangle = 0,
    COMPASS_DRAW_Points = 1,
    COMPASS_DRAW_Line = 2,
    COMPASS_DRAW_TriangleFan = 3
} compass_draw_mode_t;



typedef enum {
    COMPASS_ZERO = 0,
    COMPASS_ONE = 1,
    COMPASS_SRC_COLOR = 2,
    COMPASS_ONE_MINUS_SRC_COLOR = 3,
    COMPASS_DST_COLOR = 4,
    COMPASS_ONE_MINUS_DST_COLOR = 5,
    COMPASS_SRC_ALPHA =6,
    COMPASS_ONE_MINUS_SRC_ALPHA = 7,
    COMPASS_DST_ALPHA = 8,
    COMPASS_ONE_MINUS_DST_ALPHA = 9,
    COMPASS_CONSTANT_COLOR = 10,
    COMPASS_ONE_MINUS_CONSTANT_COLOR = 11, 
    COMPASS_CONSTANT_ALPHA = 12,
    COMPASS_ONE_MINUS_CONSTANT_ALPHA= 13,
    COMPASS_SRC_ALPHA_SATURATE = 14,
    COMPASS_SRC1_COLOR = 15,
    COMPASS_ONE_MINUS_SRC1_COLOR = 16,
    COMPASS_SRC1_ALPHA = 17,
    COMPASS_ONE_MINUS_SRC1_ALPHA = 18 
} compass_blend_factor_t;
typedef enum {
    COMPASS_Rgba = 1 << 1,
    COMPASS_Rgb = 1<< 2
} compass_format_t;


COMPASS_API f32 
Compass_Lerp(f32 start, f32 end , f32 amt);
COMPASS_API f32 
Compass_Max(f32 x, f32 y);
COMPASS_API f32 
Compass_Min(f32 x, f32 y);
COMPASS_API f32 
Compass_Clamp(f32 value, f32 min_, f32 max_);
COMPASS_API compass_view_t
Compass_CreateView(compass_renderer_t* renderer);
COMPASS_API void
Compass_SetViewPosition(compass_renderer_t* renderer,compass_view_t* view, f32 x, f32 y);
COMPASS_API void
Compass_SetViewRotate(compass_renderer_t* renderer,compass_view_t* view, f32 rotate);
COMPASS_API void
Compass_SetViewScale(compass_renderer_t* renderer,compass_view_t* view, f32 scale);
COMPASS_API void
Compass_SetShaderViewPosition(compass_shader_t* shader,compass_view_t* view, f32 x, f32 y);
COMPASS_API void
Compass_SetShaderViewRotate(compass_shader_t* shader,compass_view_t* view, f32 rotate);
COMPASS_API void
Compass_SetShaderViewScale(compass_shader_t* shader,compass_view_t* view, f32 scale);
COMPASS_API compass_rect_t
Compass_CreateRectangle(f32 w, f32 h, f32 x, f32 y );
COMPASS_API void
Compass_M4xM4(m4 a , m4 b, m4 sum);
COMPASS_API void
Compass_Viewport(f32 x, f32 y, f32 w, f32 h);
COMPASS_API compass_renderer_t 
Compass_CreateRenderer(u32 w , u32 h);
COMPASS_API void
Compass_FreeRenderer(compass_renderer_t* renderer);
COMPASS_API void 
Compass_DrawRect(compass_rect_t rectangle, compass_renderer_t renderer);
COMPASS_API compass_line_t
Compass_CreateLine(f32 x , f32 y, f32 x1 , f32 y1);
COMPASS_API void
Compass_DrawLine(compass_line_t line, compass_renderer_t renderer);
COMPASS_API void 
Compass_DrawRectRot(compass_rect_t rectangle, compass_renderer_t renderer, f32 rotation); /* NOTE(@rxx) Rotation is in radians. */
COMPASS_API void 
Compass_Clear(compass_renderer_t renderer);
COMPASS_API compass_texture_t
Compass_CreateTexture(f32 w, f32 h, u8* data, compass_image_flags_t imgFormat);

COMPASS_API compass_shader_t
Compass_CreateShader(const s8* vertex, const s8* fragment);
COMPASS_API void 
Compass_ShaderUniformSampler2D(compass_shader_t* shader, s8* location , compass_texture_t* val);
COMPASS_API void
Compass_ReloadShaderUniforms(compass_shader_t* shader, u32 w, u32 h);
COMPASS_API void 
Compass_ShaderUniform1i(compass_shader_t* shader, s8* location , s32 _val);
COMPASS_API void 
Compass_UseShader(compass_shader_t* shader);
COMPASS_API void 
Compass_ShaderUniformM4(compass_shader_t* shader, s8* location, f32* matrix);
COMPASS_API void 
Compass_FreeShader(compass_shader_t* shader);
COMPASS_API void
Compass_CreateFramebuffer(f32 w, f32 h, compass_framebuffer_t* framebuffer_object,
                          compass_format_t color_model, u32 index);
COMPASS_API void
Compass_CreateRenderbuffer(compass_framebuffer_t* framebuffer);
COMPASS_API void 
Compass_BindDefaultFrameBuffer();
COMPASS_API u32 
Compass_FramebufferGetError(compass_framebuffer_t framebuffer);
COMPASS_API void 
Compass_BindFrameBuffer(compass_framebuffer_t framebuffer);
COMPASS_API void 
Compass_Blend(compass_blend_factor_t  bf1, compass_blend_factor_t bf2);
COMPASS_API void
Compass_RotationM4(m4 matrix, f32 rotation);
COMPASS_API void
Compass_LoadIdentityM4(m4 matrix);
COMPASS_API v4
Compass_V4xM4(v4* vector  , m4 matrix);
COMPASS_API void
Compass_TranslateM4(m4 matrix, v2 translation);
COMPASS_API s8*
Compass_GetVersion();
COMPASS_API void
Compass_BeginDrawing(compass_renderer_t renderer );
COMPASS_API void
Compass_PushVertex(f32* vertices, s32 size,  compass_renderer_t renderer );
COMPASS_API void
Compass_EndDrawing(compass_draw_mode_t draw_mode, compass_renderer_t renderer, f32 vertex_count );
COMPASS_API void 
Compass_BeginTexture(compass_renderer_t renderer, compass_texture_t texture);
COMPASS_API void 
Compass_EndTexture();


#ifdef COMPASS_IMPL_GFX


f32 Compass_Lerp(f32 start, f32 end , f32 amt)
{
    return amt* (end-start) + start;
}

f32 Compass_Max(f32 x, f32 y)
{
    return x > y == 1 ? x : y;
}
f32 Compass_Min(f32 x, f32 y)
{
    return x > y == 1 ? y : x;
}

f32 Compass_Clamp(f32 value, f32 min_, f32 max_)
{
    return Compass_Min(Compass_Max(value,min_), max_);
}


void
Compass_LoadIdentityM4(m4 matrix)
{
    for (int x=0;x<4;x++){
        for (int y=0;y<4;y++){
            matrix[x][y] = 0;
        }
    }
    
}
void
Compass_RotationM4(m4 matrix, f32 rotation)
{
    
    matrix[0][0] = COMPASS_COS(rotation * 3.14 / 180) ;
    matrix[0][1] = -COMPASS_SIN(rotation* 3.14 / 180);
    matrix[1][0] = COMPASS_SIN(rotation* 3.14 / 180) ;
    matrix[1][1] = COMPASS_COS(rotation * 3.14 / 180);
    matrix[2][3] = 1;
    matrix[3][3] = 1;
}


void
Compass_TranslateM4(m4 matrix, v2 translation)
{
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
    matrix[3][0] = translation.x ;
    matrix[3][1] = translation.y ;
    matrix[3][2] = 1;
    matrix[3][3] = 1;
}

void 
Compass_M4xM4(m4 a , m4 b , m4 sum)
{
    
    for (int x=0;x<4;x++){
        for (int y=0;y<4;y++){
            
            sum[x][y] = a[x][y] * b[x][y];
        }
    }
    
}
v4
Compass_V4xM4(v4* vector  , m4 matrix)
{
    v4 res;
    f32 sum =0;
    sum += matrix[0][0] * vector->x;
    sum += matrix[1][0] * vector->y;
    sum += matrix[2][0] * vector->z;
    sum += matrix[3][0] * vector->w;
    res.x = sum;
    sum = 0;
    sum += matrix[0][1] * vector->x;
    sum += matrix[1][1] * vector->y;
    sum += matrix[2][1] * vector->z;
    sum += matrix[3][1] * vector->w;
    res.y = sum;
    sum = 0;
    sum += matrix[0][2] * vector->x;
    sum += matrix[1][2] * vector->y;
    sum += matrix[2][2] * vector->z;
    sum += matrix[3][2] * vector->w;
    res.z =sum;
    sum = 0;
    sum += matrix[0][3] * vector->x;
    sum += matrix[1][3] * vector->y;
    sum += matrix[2][3] * vector->z;
    sum += matrix[3][3] * vector->w;
    res.w = sum;
    
    return res;
}


#ifdef COMPASS_BACKEND_OPENGL




typedef struct {
    u32 vbo,vao;
    s32 buffersize;
} compass_opengl_handle_t;

typedef struct {
    u32 program;
} compass_opengl_shader_handle_t;

void
Compass_Viewport(f32 x, f32 y, f32 w, f32 h)
{
    glViewport(x,y,w,h);
}
compass_renderer_t 
Compass_CreateRenderer(u32 w , u32 h)
{
    
#if COMPASS_DEVELOPMENT_BUILD == 1
    printf("[Compass::Warning]: You're using a version of compass that is in development. To overwrite this message, set COMPASS_DEVELOPMENT_BUILD to zero. Things in here are subject to change.\n");
#endif
    glEnable(GL_MULTISAMPLE);  
    glEnable(GL_BLEND);
    glEnable(GL_STENCIL_TEST);    
    Compass_Blend(COMPASS_SRC_ALPHA, COMPASS_ONE_MINUS_SRC_ALPHA);
    
    compass_renderer_t renderer;
    renderer.graphics.handle = COMPASS_MALLOC(sizeof(compass_opengl_handle_t));
    compass_opengl_handle_t* handle = (compass_opengl_handle_t*)renderer.graphics.handle; 
    renderer.color.r = 0;;
    renderer.color.g = 0;
    renderer.color.b = 0;
    renderer.color.a = 255;
    renderer.w =w;
    renderer.h =h;
    
    u32 success; 
    s8 infolog[512] = {0};
    
    const s8* vs =  
        "#version 330 core\n"
        "layout (location = 0) in vec3 Position;\n"
        "layout (location = 1) in vec4 Colors;\n"
        "layout (location = 2) in vec2 tc;\n"
        "layout (location = 3) in float textureEnabled;\n"
        "out vec4 color;\n"
        "out vec2 texc;\n"
        "uniform mat4 Compass_ViewOrthographic;\n"
        
        "uniform mat4  Compass_ViewPosition;\n"
        "uniform mat4  Compass_ViewScale ;\n"
        "uniform mat4  Compass_ViewRotate ;\n"
        "out float UsingTexture;\n"
        "void main() {\n"
        "UsingTexture = textureEnabled;\n"
        "color = Colors;\n"
        "texc = tc;\n"
        "gl_Position =    Compass_ViewOrthographic*   ( Compass_ViewPosition *  Compass_ViewRotate ) *  Compass_ViewScale * vec4(Position.xy, 1.0, 0.0);" 
        "}\n\0";
    
    const s8* fs = 
        "#version 330 core\n"
        "out vec4 OutColor;\n"
        "in vec4 color;\n"
        "in  vec2 texc;\n"
        "in float UsingTexture;\n"
        "uniform sampler2D _texture2d;\n"
        "void main() {\n"
        "if (UsingTexture == 1 ) {"
        "OutColor = texture(_texture2d, texc) * color;\n"
        "}\n"
        "else if (UsingTexture == 2 ) {\n"
        "vec4 sampled = vec4(1.0,1.0,1.0,texture( _texture2d, texc).r);\n"
        "OutColor =  sampled * color;\n"
        "}\n"
        "else { \n"
        "OutColor = vec4(color.rgba);\n"
        "}\n"
        "}\n\0";
    
    renderer.shader = Compass_CreateShader(vs, fs);
    
    
    
    
    glGenBuffers(1, &handle->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, handle->vbo);
    u32 size = 2024 * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, sizeof(compass_vertex_t) * size , (void*)0, GL_DYNAMIC_DRAW);
    handle->buffersize = size;
    
    glGenVertexArrays(1, &handle->vao);
    glBindVertexArray(handle->vao);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(compass_vertex_t), (void*)offsetof(compass_vertex_t, position));
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, sizeof(compass_vertex_t), (void*)(offsetof(compass_vertex_t, color)));
    
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, sizeof(compass_vertex_t), (void*)(offsetof(compass_vertex_t, textureCoords)));
    
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,2,GL_FLOAT, GL_FALSE, sizeof(compass_vertex_t), (void*)(offsetof(compass_vertex_t,  texture_on)));
    
    Compass_ReloadShaderUniforms(&renderer.shader, w, h);
    
    Compass_UseShader(&renderer.shader);
    
    renderer.view = Compass_CreateView(&renderer);
    
    Compass_SetViewPosition(&renderer,&renderer.view, 0,0);
    Compass_SetViewScale(&renderer,&renderer.view, 1);
    Compass_SetViewRotate(&renderer,&renderer.view, 0); 
    return renderer;
}


u32
Compass_GetUniformLocation(u32 programId, s8* name)
{
    u32 location = -1;
    
    static u64 last = 0;
    static compass_uniform_cache_t locations[128] = {0};
    for (int i = 0; i < 128; ++i)
        if (locations[i].key == name)
        location = locations[i].value;
    
    if (location == -1)
    {
        location = glGetUniformLocation(programId, name);
        locations[last++] = (compass_uniform_cache_t) { name, location };
    }
    
    return location;   
}

compass_line_t
Compass_CreateLine(f32 x , f32 y, f32 x1 , f32 y1)
{
    compass_line_t line;
    line.x0 = x;
    line.y0 = y;
    line.x1 = x1;
    line.y1 = y1;
    line.color = (Color){255,255,255,255};
    
    
    return line;
}
void
Compass_ReloadShaderUniforms(compass_shader_t* shader, u32 w, u32 h)
{
    m4 matrix = {0};
    f32 left = 0;
    f32 right = w; 
    f32 bottom = h;
    f32 top = 0;
    f32 nearVal = -1;
    f32 farVal=1;
    
    matrix[0][0] = 2 / (right - left);
    matrix[1][1] = 2 / (top - bottom);
    matrix[2][2] = -2/ (farVal - nearVal);
    matrix[3][0] = -( (right + left ) / right - left);
    matrix[3][1] = -( (top + bottom) / (top - bottom) );
    matrix[3][2] = -( (farVal + nearVal) / (farVal - nearVal));
    matrix[3][3] = 1;
    
    Compass_UseShader(shader);
    Compass_ShaderUniformM4(shader, "Compass_ViewOrthographic" , (f32*)matrix );
}

compass_rect_t
Compass_CreateRectangle(f32 w, f32 h, f32 x, f32 y )
{
    compass_rect_t rectangle = {0};
    rectangle.w = w;
    rectangle.h = h;
    rectangle.x = x;
    rectangle.y = y;
    
    rectangle.texture.left_top = (v2){0,0};
    rectangle.texture.right_top = (v2){1,0};
    rectangle.texture.left_bottom = (v2){0,1};
    rectangle.texture.right_bottom = (v2){1,1};
    rectangle.color = (Color){255,255,255,255};
    return rectangle;
    
}


void 
Compass_UseShader(compass_shader_t* shader)
{
    compass_opengl_shader_handle_t* handle  = (compass_opengl_shader_handle_t*)shader->shader_handle.handle;
    glUseProgram(handle->program);
}
void 
Compass_DrawRect(compass_rect_t rectangle, compass_renderer_t renderer)
{
    
    if (rectangle.texture.texture_State){
        Compass_BeginTexture(renderer, rectangle.texture);
    } 
    
    
    f32 vertex_data[] = {
        rectangle.x,rectangle.y +  rectangle.h,0,
        rectangle.color.r / 255.0, 
        rectangle.color.g  / 255.0,rectangle.color.b / 255.0,rectangle.color.a / 255.0,
        rectangle.texture.left_bottom.x,rectangle.texture.left_bottom.y,
        rectangle.texture.texture_State,
        
        rectangle.x,rectangle.y,0,
        
        
        rectangle.color.r / 255.0, rectangle.color.g  / 255.0,rectangle.color.b / 255.0,rectangle.color.a / 255.0,
        
        rectangle.texture.left_top.x,rectangle.texture.left_top.y,
        rectangle.texture.texture_State,
        
        rectangle.x+ rectangle.w,rectangle.y ,0,
        
        
        rectangle.color.r / 255.0, rectangle.color.g  / 255.0,rectangle.color.b / 255.0,rectangle.color.a / 255.0,
        
        
        rectangle.texture.right_top.x,rectangle.texture.right_top.y,
        rectangle.texture.texture_State,
        
        
        rectangle.x + rectangle.w,rectangle.y +rectangle.h,0,
        
        
        rectangle.color.r / 255.0, 
        rectangle.color.g  / 255.0,rectangle.color.b / 255.0,rectangle.color.a / 255.0,
        
        
        rectangle.texture.right_bottom.x,rectangle.texture.right_bottom.y,
        rectangle.texture.texture_State
            
            
    };  
    
    Compass_BeginDrawing(renderer);
    Compass_PushVertex(vertex_data, sizeof(vertex_data),  renderer );
    Compass_EndDrawing(COMPASS_DRAW_TriangleFan,renderer, 4);
    Compass_EndTexture();
    
}



void 
Compass_DrawRectRot(compass_rect_t rectangle, compass_renderer_t renderer, f32 rotation)
{
    
    
    if (rectangle.texture.texture_State){
        Compass_BeginTexture(renderer, rectangle.texture);
    } 
    
    
    
    
    v4 vertex_a = (v4){rectangle.x,rectangle.y +  rectangle.h};
    
    
    v4 vertex_b = (v4){rectangle.x,rectangle.y};
    
    
    
    v4 vertex_c = (v4){rectangle.x+ rectangle.w,rectangle.y };
    
    
    
    v4 vertex_d = (v4){rectangle.x + rectangle.w,rectangle.y +rectangle.h};
    
    
    f32 cx =rectangle.x + rectangle.w / 2;
    f32 cy =rectangle.y + rectangle.h / 2;
    
    f32 s = COMPASS_SIN(rotation );
    f32 c = COMPASS_COS(rotation );
    
    vertex_a.x -= cx;
    vertex_a.y -= cy;
    f32 xnewA = vertex_a.x * c -vertex_a.y * s;
    f32 ynewA = vertex_a.x * s + vertex_a.y * c;
    vertex_a.x = xnewA + cx;
    vertex_a.y = ynewA + cy;
    
    
    vertex_b.x -= cx;
    vertex_b.y -= cy;
    f32 xnewB = vertex_b.x * c -vertex_b.y * s;
    f32 ynewB = vertex_b.x * s + vertex_b.y * c;
    vertex_b.x = xnewB + cx;
    vertex_b.y = ynewB + cy;
    
    
    
    vertex_c.x -= cx;
    vertex_c.y -= cy;
    f32 xnewC = vertex_c.x * c -vertex_c.y * s;
    f32 ynewC = vertex_c.x * s + vertex_c.y * c;
    vertex_c.x = xnewC + cx;
    vertex_c.y = ynewC + cy;
    
    
    vertex_d.x -= cx;
    vertex_d.y -= cy;
    f32 xnewD = vertex_d.x * c -vertex_d.y * s;
    f32 ynewD = vertex_d.x * s + vertex_d.y * c;
    vertex_d.x = xnewD + cx;
    vertex_d.y = ynewD + cy;
    
    
    
    
    f32 vertex_data[] = {
        vertex_a.x , vertex_a.y,0,
        
        rectangle.color.r / 255.0,
        rectangle.color.g  / 255.0,rectangle.color.b / 255.0,rectangle.color.a / 255.0,
        
        
        
        rectangle.texture.left_bottom.x,rectangle.texture.left_bottom.y,
        rectangle.texture.texture_State,
        
        vertex_b.x , vertex_b.y,0,
        
        
        rectangle.color.r / 255.0, rectangle.color.g  / 255.0,rectangle.color.b / 255.0,rectangle.color.a / 255.0,
        
        rectangle.texture.left_top.x,rectangle.texture.left_top.y,
        rectangle.texture.texture_State,
        
        vertex_c.x , vertex_c.y,0,
        
        
        rectangle.color.r / 255.0, rectangle.color.g  / 255.0,rectangle.color.b / 255.0,rectangle.color.a / 255.0,
        
        
        rectangle.texture.right_top.x,rectangle.texture.right_top.y,
        rectangle.texture.texture_State,
        
        
        vertex_d.x , vertex_d.y,0,
        
        
        rectangle.color.r / 255.0, 
        rectangle.color.g  / 255.0,rectangle.color.b / 255.0,rectangle.color.a / 255.0,
        
        
        rectangle.texture.right_bottom.x,rectangle.texture.right_bottom.y,
        rectangle.texture.texture_State
            
            
    };  
    
    Compass_BeginDrawing(renderer);
    Compass_PushVertex(vertex_data, sizeof(vertex_data),  renderer );
    Compass_EndDrawing(COMPASS_DRAW_TriangleFan,renderer, 4);
    Compass_EndTexture();
}


void 
Compass_ShaderUniform1i(compass_shader_t* shader, s8* location , s32 _val)
{
    compass_opengl_shader_handle_t* handle  = (compass_opengl_shader_handle_t*)shader->shader_handle.handle;
    
    u32 loc = Compass_GetUniformLocation(handle->program, location);
    
    
    glUniform1i(loc, _val);
}

void 
Compass_Clear(compass_renderer_t renderer)
{
    glClearColor(renderer.color.r /255.0, renderer.color.g / 255.0, renderer.color.b/ 255.0, renderer.color.a/255.0);
    glClear(GL_COLOR_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);
    
    
}
void
Compass_FreeRenderer(compass_renderer_t* renderer)
{
    COMPASS_FREE(renderer->graphics.handle);
    
    Compass_FreeShader(&renderer->shader);
    
}


void
Compass_BeginDrawing(compass_renderer_t renderer )
{
    compass_opengl_handle_t* handle = (compass_opengl_handle_t*)renderer.graphics.handle; 
    glBindBuffer(GL_ARRAY_BUFFER, handle->vbo);
}



void
Compass_PushVertex(f32* vertices, s32 size ,  compass_renderer_t renderer )
{
    
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}



void
Compass_EndDrawing(compass_draw_mode_t draw_mode, compass_renderer_t renderer, f32 vertex_count )
{
    compass_opengl_handle_t* handle = (compass_opengl_handle_t*)renderer.graphics.handle; 
    GLenum mode;
    switch (draw_mode)
    {
        case (COMPASS_DRAW_Triangle ):
        {
            mode = GL_TRIANGLES;
        } break;
        
        
        case (COMPASS_DRAW_Points ):
        {
            mode = GL_POINTS;
        } break;
        
        
        case (COMPASS_DRAW_Line ):
        {
            mode = GL_LINES;
            
        } break;
        
        
        case (COMPASS_DRAW_TriangleFan):
        {
            mode = GL_TRIANGLE_FAN;
            
        } break;
        
        default : 
        {
            mode= GL_TRIANGLE_FAN;
        }
    }
    glBindVertexArray(handle->vao);
    glDrawArrays(mode, 0, vertex_count);
}



void 
Compass_BeginTexture(compass_renderer_t renderer, compass_texture_t texture)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.texture);
    
    
}

void 
Compass_EndTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}



compass_shader_t
Compass_CreateShader(const s8* vertex, const s8* fragment)
{
    compass_shader_t shader;
    
    shader.vertex = vertex;
    shader.fragment = fragment;
    
    shader.shader_handle.handle = COMPASS_MALLOC(sizeof(compass_opengl_shader_handle_t));
    compass_opengl_shader_handle_t* handle  = (compass_opengl_shader_handle_t*)shader.shader_handle.handle;
    
    u32 success;
    s8 infolog[512];
    GLuint s_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertex, 1, &vertex, NULL);
    glCompileShader(s_vertex);
    glGetShaderiv(s_vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(s_vertex, 512, NULL, infolog);
        COMPASS_PRINTF("[vertex shader] : compass %s\n", infolog);
        
    }
    
    
    GLuint s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragment, 1, &fragment, 0);
    glCompileShader(s_fragment);
    glGetShaderiv(s_fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        
        glGetShaderInfoLog(s_fragment, 512, 0, infolog);
        printf("[fragment shader] : compass %s\n", infolog);
        
    };
    
    
    handle->program = glCreateProgram();
    glAttachShader(handle->program, s_vertex);
    glAttachShader(handle->program, s_fragment);
    glLinkProgram(handle->program);
    
    glGetProgramiv(handle->program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(handle->program, 512,0, infolog);
        COMPASS_PRINTF("[program] : compass %s\n", infolog);
    }
    
    
    return shader;
    
}


void
Compass_ShaderUniformM4(compass_shader_t* shader, s8* location, f32* matrix)
{
    compass_opengl_shader_handle_t* handle  = (compass_opengl_shader_handle_t*)shader->shader_handle.handle;
    
    Compass_UseShader(shader);
    int loc =Compass_GetUniformLocation(handle->program, location);
    
    glUniformMatrix4fv(loc, 1, GL_FALSE, (f32*)matrix);
}



void 
Compass_FreeShader(compass_shader_t* shader)
{
    COMPASS_FREE(shader->shader_handle.handle);
}

COMPASS_API compass_texture_t
Compass_CreateTexture(f32 w, f32 h, u8* data, compass_image_flags_t imgFormat)
{
    compass_texture_t texture;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.w = w;
    texture.h = h;
    u32 texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    
    switch (imgFormat)
    {
        case (COMPASS_IMAGE_Png)  :
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } break;
        case (COMPASS_IMAGE_Jpg)  :
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } break;
        case (COMPASS_IMAGE_Bmp)  :
        { 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
        } break;
        
        default :
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
        }
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    texture.texture = texture_id;
    
    
    texture.texture_State = 1;
    
    texture.left_top = (v2){0,0};
    texture.right_top = (v2){1,0};
    texture.left_bottom = (v2){0,1};
    texture.right_bottom = (v2){1,1};
    
    return texture;
    
}

COMPASS_API compass_texture_t
Compass_LoadTextTexture(f32 w, f32 h , unsigned char* bytes)
{
    compass_texture_t texture;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    texture.w = w;
    texture.h = h;
    u32 texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,w,h,0,GL_RED,GL_UNSIGNED_BYTE,bytes);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    texture.texture = texture_id;
    
    texture.texture_State = 3;
    
    texture.left_top = (v2){0,0};
    texture.right_top = (v2){1,0};
    texture.left_bottom = (v2){0,1};
    texture.right_bottom = (v2){1,1};
    
    
    return texture;
}

void
Compass_CreateFramebuffer(f32 w, f32 h, compass_framebuffer_t* framebuffer_object, compass_format_t color_model, u32 index)
{
    
    framebuffer_object->w = w;
    framebuffer_object->h = h;
    
    
    u32 framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
    
    u32 fbo_texture;
    
    glGenTextures(index, &fbo_texture);
    
    
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    if (color_model == COMPASS_Rgba){
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    } else
    {
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, fbo_texture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    
    
    framebuffer_object->framebuffer_object = framebuffer;
    framebuffer_object->texture.texture = fbo_texture;
    framebuffer_object->texture.w= w;
    framebuffer_object->texture.h = h;
    framebuffer_object->texture.texture_State = 1;
    framebuffer_object->texture.left_top = (v2){0,1};
    framebuffer_object->texture.right_top = (v2){1,1};
    framebuffer_object->texture.left_bottom = (v2){0,0};
    framebuffer_object->texture.right_bottom = (v2){1,0};
    
    Compass_FramebufferGetError(*framebuffer_object);
    
    
}


void 
Compass_BindDefaultFrameBuffer()
{
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    glBindRenderbuffer(GL_RENDERBUFFER,0 );
    
    
    
}


void 
Compass_BindFrameBuffer(compass_framebuffer_t framebuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.framebuffer_object);
    
    glBindRenderbuffer(GL_RENDERBUFFER,framebuffer.renderbuffer );
    
    
    
}


void
Compass_CreateRenderbuffer(compass_framebuffer_t* framebuffer)
{
    
    u32 render_buffer_object;
    glGenRenderbuffers(1, &render_buffer_object);
    glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,framebuffer->w,framebuffer->h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer_object);
    
    framebuffer->renderbuffer = render_buffer_object;
    Compass_FramebufferGetError(*framebuffer);
}

u32 
Compass_FramebufferGetError(compass_framebuffer_t framebuffer)
{
    Compass_BindFrameBuffer(framebuffer);
    u32 framebuffer_status = 0;
    if ((framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER))!= GL_FRAMEBUFFER_COMPLETE)
    {
        
        switch (framebuffer_status){
            case 36054: {
                COMPASS_PRINTF("{compass:Framebuffer} Invalid framebuffer attachment points. %i\n", framebuffer_status);
            } break;
            case 36057: {
                printf("{compass:Framebuffer} all attached images do not have the same width and height associated to it. %i\n", framebuffer_status);
            } break;
            case 36055: {
                COMPASS_PRINTF("{compass:Framebuffer} there is no image attached to the framebuffer. %i\n", framebuffer_status);
            } break;
            case 36061: {
                COMPASS_PRINTF("{compass:Framebuffer} the internal formates violates an implementation-dependent restrictions. %i\n", framebuffer_status);
            } break;
            default:
            {
                COMPASS_PRINTF("{compass:Framebuffer} unknown error message?  %i\n", framebuffer_status);
            }
        }
    }
    return framebuffer_status;
}

void 
Compass_Blend(compass_blend_factor_t  bf1, compass_blend_factor_t bf2)
{
    
    
    
    GLenum sfactor;
    GLenum dfactor;
    
    
    switch(bf1)
    {
        case 0: {
            sfactor = GL_ZERO; 
        } break;
        
        case 1: {
            sfactor= GL_ONE;
            
        } break;
        
        case 2: {
            sfactor= GL_SRC_COLOR;
        } break;
        
        case  3: {
            sfactor= GL_ONE_MINUS_SRC_COLOR;
        } break;
        
        case 4: {
            sfactor= GL_DST_COLOR;
        } break;
        
        case 5 : {
            sfactor= GL_ONE_MINUS_DST_COLOR;
        } break;
        
        case 6: {
            sfactor= GL_SRC_ALPHA;
        } break;
        
        case 7: {
            sfactor= GL_ONE_MINUS_SRC_ALPHA;
        } break;
        
        case 8 : {
            sfactor= GL_DST_ALPHA;
        } break;
        
        case 9: {
            sfactor= GL_ONE_MINUS_DST_ALPHA;
        } break;
        
        case 10: {
            sfactor= GL_CONSTANT_COLOR;
        } break;
        
        case 11: {
            sfactor= GL_ONE_MINUS_CONSTANT_COLOR;
        } break;
        
        case 12: {
            sfactor= GL_CONSTANT_ALPHA;
        } break;
        
        case 13: {
            sfactor= GL_ONE_MINUS_CONSTANT_COLOR;
        } break;
        
        case 14: {
            sfactor = GL_SRC_ALPHA_SATURATE;
        } break;
        
        case 15: {
            sfactor= GL_SRC1_COLOR;
        } break;
        
        case 16: {
            sfactor= GL_ONE_MINUS_SRC1_COLOR;
        } break;
        
        case 17: {
            sfactor= GL_SRC1_ALPHA;
        } break;
        
        case 18: {
            sfactor = GL_ONE_MINUS_SRC1_ALPHA;
        } break;
        
    };
    
    
    
    switch(bf2)
    {
        case 0: {
            dfactor = GL_ZERO; 
        } break;
        
        case 1: {
            dfactor= GL_ONE;
            
        } break;
        
        case 2: {
            dfactor= GL_SRC_COLOR;
        } break;
        
        case  3: {
            dfactor= GL_ONE_MINUS_SRC_COLOR;
        } break;
        
        case 4: {
            dfactor= GL_DST_COLOR;
        } break;
        
        case 5 : {
            dfactor= GL_ONE_MINUS_DST_COLOR;
        } break;
        
        case 6: {
            dfactor= GL_SRC_ALPHA;
        } break;
        
        case 7: {
            dfactor= GL_ONE_MINUS_SRC_ALPHA;
        } break;
        
        case 8 : {
            dfactor= GL_DST_ALPHA;
        } break;
        
        case 9: {
            dfactor= GL_ONE_MINUS_DST_ALPHA;
        } break;
        
        case 10: {
            dfactor= GL_CONSTANT_COLOR;
        } break;
        
        case 11: {
            dfactor= GL_ONE_MINUS_CONSTANT_COLOR;
        } break;
        
        case 12: {
            dfactor= GL_CONSTANT_ALPHA;
        } break;
        
        case 13: {
            dfactor= GL_ONE_MINUS_CONSTANT_COLOR;
        } break;
        
        case 14: {
            dfactor = GL_SRC_ALPHA_SATURATE;
        } break;
        
        case 15: {
            dfactor= GL_SRC1_COLOR;
        } break;
        
        case 16: {
            dfactor= GL_ONE_MINUS_SRC1_COLOR;
        } break;
        
        case 17: {
            dfactor= GL_SRC1_ALPHA;
        } break;
        
        case 18: {
            dfactor = GL_ONE_MINUS_SRC1_ALPHA;
        } break;
        
    };
    
    
    
    glBlendFunc(sfactor,dfactor);
}



void  
Compass_ShaderUniformSampler2D(compass_shader_t* shader, s8* location , compass_texture_t* val)
{
    compass_opengl_shader_handle_t* handle  = (compass_opengl_shader_handle_t*)shader->shader_handle.handle;
    
    Compass_UseShader(shader);
    glUniform1f(Compass_GetUniformLocation(handle->program, location), val->texture);
    Compass_UseShader(shader);
}


compass_view_t
Compass_CreateView(compass_renderer_t* renderer)
{
    compass_view_t view = {0};
    view.x = 0;
    view.y = 0;
    view.w = renderer->w;
    view.h = renderer->h;
    
    return view;
}




void
Compass_SetShaderViewPosition(compass_shader_t* shader,compass_view_t* view, f32 x, f32 y)
{
    view->x = x;
    view->y = y;
    
    m4 TranslationMatrix = {0};
    TranslationMatrix[0][0] = 1 ;
    TranslationMatrix[1][1] = 1;
    TranslationMatrix[2][2] = 1;
    TranslationMatrix[2][3] = 0;
    TranslationMatrix[3][0] = x  ;
    TranslationMatrix[3][1] = y ;
    TranslationMatrix[3][2] = 1;
    TranslationMatrix[3][3] = 1;
    
    Compass_UseShader(shader);
    Compass_ShaderUniformM4(shader, "Compass_ViewPosition" , (f32*)TranslationMatrix );
}

void
Compass_SetShaderViewRotate(compass_shader_t* shader,compass_view_t* view, f32 rotate)
{
    view->rotate = rotate;
    m4 RotateMatrix = {0};
    
    
    RotateMatrix[0][0] = COMPASS_COS(rotate * 3.14 / 180) ;
    RotateMatrix[0][1] = -COMPASS_SIN(rotate* 3.14 / 180) ;
    RotateMatrix[1][0] = COMPASS_SIN(rotate* 3.14 / 180) ;
    RotateMatrix[1][1] = COMPASS_COS(rotate* 3.14 / 180)  ;
    RotateMatrix[2][3] = 1;
    RotateMatrix[3][3] = 1;
    
    Compass_UseShader(shader);
    Compass_ShaderUniformM4(shader, "Compass_ViewRotate" , (f32*)RotateMatrix );
}

void
Compass_SetShaderViewScale(compass_shader_t* shader,compass_view_t* view, f32 scale)
{
    view->scale = scale;
    
    
    m4 ScaleMatrix = {1};
    
    ScaleMatrix[0][0] =  scale;
    ScaleMatrix[1][1] =  scale;
    ScaleMatrix[2][2] =  scale;
    ScaleMatrix[3][3] = 1;
    
    Compass_UseShader(shader);
    Compass_ShaderUniformM4(shader, "Compass_ViewScale" , (f32*)ScaleMatrix);
}



void
Compass_SetViewPosition(compass_renderer_t* renderer,compass_view_t* view, f32 x, f32 y)
{
    Compass_SetShaderViewPosition(&renderer->shader,view, x,y);
}


void
Compass_SetViewRotate(compass_renderer_t* renderer,compass_view_t* view, f32 rotate)
{
    Compass_SetShaderViewRotate(&renderer->shader,view, rotate);
}



void
Compass_SetViewScale(compass_renderer_t* renderer,compass_view_t* view, f32 scale)
{
    Compass_SetShaderViewScale(&renderer->shader,view, scale);
}


s8*
Compass_GetVersion()
{
    
    s8* ver = COMPASS_VERSION;
    const s8* gl = glGetString(GL_VERSION);
    s8* final = {0};
    final = COMPASS_STRCAT(ver,"  OpenGL Version: ");
    final = COMPASS_STRCAT(ver,gl);
    return final;
}



void
Compass_DrawLine(compass_line_t line, compass_renderer_t renderer)
{
    
    Compass_BeginDrawing(renderer);
    
    f32 vertex_data[] = {
        line.x0, line.y0,0,
        line.color.r / 255.0, 
        line.color.g  / 255.0,line.color.b / 255.0,line.color.a / 255.0,
        0,0,
        0,
        
        line.x1, line.y1,0,
        line.color.r / 255.0, 
        line.color.g  / 255.0,line.color.b / 255.0,line.color.a / 255.0,
        0,0,
        0
            
    };
    
    
    
    Compass_PushVertex(vertex_data, sizeof(vertex_data),  renderer );
    Compass_EndDrawing(COMPASS_DRAW_Line,renderer, 2);
    Compass_EndTexture();
    
}


#endif

#endif

#endif

