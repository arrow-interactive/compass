#if 0

/*
This is a test application, that is used to test out
rendering backends.

 --------
More specifically, this test tests out these components:

- translation
- image loading
- scaling
- texture coordinates
 - colors.
---------





*/
#include <vulkan/vulkan.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define COMPASS_BACKEND_OPENGL
#define COMPASS_IMPL_GFX
#include "ext/compass.h"
#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb/stb_image.h"

compass_texture_t generate_texture(char* texture, compass_image_flags_t flags)
{
    int w,h, nrChannels;
    
    u8* data = stbi_load(texture, &w, &h, &nrChannels,0);
    if (data == NULL)
    {
        COMPASS_PRINTF("Failed to load : %s\n", texture);
    }
    return Compass_CreateTexture(w,h,data,flags);
    
    
}

void splice(compass_texture_t* obj, f32 x, f32 y)
{
    f32 sprite_width = (obj->w / x )  ;
    f32 sprite_height = obj->h / y;
    
    obj->left_bottom =  (v2){ (x * sprite_width) / obj->w       ,   ((y+1) * sprite_height) / obj->h };
    obj->right_bottom = (v2){ ((x+  1)* sprite_width) / obj->w ,   ((y+1) * sprite_height) / obj->h };
    obj->right_top =    (v2){ ((x+  1) * sprite_width) / obj->w,   ((y) * sprite_height) / obj->h  };
    obj->left_top =      (v2){(x * sprite_width) / obj->w      ,   ((y) * sprite_height) / obj->h  };
    
}


void update_anim(compass_texture_t* obj, f32 x, f32 y, f32 delay)
{
    /* Calculate a specific sprite */
    
    splice(obj, x,y);
    
    
    
} 

void PrintInformation()
{
    
    printf("Compass Version: %s\n" , Compass_GetVersion());
    printf("This application is a test application used for benchmarking rendering APIs.\n");
}

#define VELOCITY_VAL(Y , WindowHeight) Y < 200  ? 1 : 0

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    f32 window_width, window_height;
    window_width = 1200;
    window_height = 900;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height,"compass testing", 0,0);
    
    
    
    glfwMakeContextCurrent(window);
    
    
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return -1;
    }
    
    
    
    compass_renderer_t renderer = Compass_CreateRenderer(1200,900);
    
    /* Player */
    
    compass_texture_t playerTexture = generate_texture("sprites/adventurer-Sheet.png", COMPASS_IMAGE_Png);
    compass_rect_t player = Compass_CreateRectangle((playerTexture.w/7) * 5,(playerTexture.h/12) * 5,0,0);
    splice(&playerTexture, 7,12);
    player.texture = playerTexture;
    
    v2 velocity;
    
    /* Enemy */
    
    
    /* Cosmetics */
    
    compass_rect_t background = Compass_CreateRectangle(window_width, window_height , 0,0);
    background.texture = generate_texture("sprites/sky.jpg", COMPASS_IMAGE_Jpg);
    
    PrintInformation();
    
    
    compass_rect_t transform = Compass_CreateRectangle(200,200,300,300);
    
    while (!glfwWindowShouldClose(window))
    {
        
        glfwPollEvents();
        
        
        
        Compass_Clear(renderer);
        
        /* Cosemetics*/
        Compass_DrawRect(background, renderer);
        transform.x += sin(glfwGetTime()) * 2;
        transform.w += cos(glfwGetTime()) * 2;
        transform.y += sin(glfwGetTime()) * 2;
        transform.h += cos(glfwGetTime()) * 2;
        transform.color = (Color){100,0,100,255};
        Compass_DrawRectRot(transform, renderer, sin(glfwGetTime()) );
        
        
        /* Player */
        
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_SPACE))
        {
            velocity.y -= 10;
            
        }
        
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
        {
            velocity.x -= 2.5;
            
        }
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
        {
            velocity.x += 2.5;
        }
        
        if (VELOCITY_VAL(player.y, window_height)){
            velocity.y += 1.5;
            
        } else
        {
            velocity.y = 0;
        }
        player.x += velocity.x;
        player.y += velocity.y;
        velocity.y *= 0.9;
        velocity.x *= 0.9;
        
        
        Compass_DrawRect(player, renderer);
        
        
        
        /* Enemy */
        
        
        glfwSwapBuffers(window);
    }
    
    Compass_FreeRenderer(&renderer);
    
    
    return 0;
    
}

#else
//#define COMPASS_DEBUG /* NOTE: Create validation layers, and then use this. */
#define VK_USE_PLATFORM_LINUX_KHR

#define COMPASS_BACKEND_VULKAN
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define COMPASS_IMPL_GFX
#include "ext/compass.h"
int main()
{
    glfwInit();
    
    f32 window_width, window_height;
    window_width = 1200;
    window_height = 900;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    
    GLFWwindow* window = glfwCreateWindow(window_width, window_height,"hi", 0,0);
    
    
    
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    compass_renderer_t renderer = Compass_CreateVulkanRenderer("hi", glfwExtensionCount, glfwExtensions, COMPASS_VK_DISCRETE_GPU, window_width, window_height);
    
    
    
    
    while (!glfwWindowShouldClose(window))
    {
        
        glfwPollEvents();
        
        
        
        
        glfwSwapBuffers(window);
    }
    
    Compass_FreeRenderer(&renderer);
    
    
    return 0;
    
}

#endif


s