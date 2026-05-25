# lavi 

lavi is a minimal API that abstracts a tight Win32 platform layer, designed for developing small games. 

Windows.h is not used, functions are dynamically linked rather than statically, meaning every Win32 function in this API has been pulled out of a given DLL ourselves. 

The main motivation behind this is Windows.h contains a large mountain of code that is hardly ever used, of course this depends on the complexity of the application if one is using much of it but regardless, reducing such overhead has an immense return in reduced compile time.

So, in the case of a platform layer for developing games, I've collected a minimal set of functions for quick and easy prototyping.

Supports:
* Window management
* Keyboard/Mouse/XInput
* RawInput (HID gamepads soon)
* OpenGL 1.0 
* Time (delta_time, ticks)

All you need to start is to include the header file and call two functions, lavi_init and lavi_update.
```c
#include "lavi_platform.h"

static lavi_api g_api;

// lavi_main is wrapped around WinMain but is required and designed as a simpler entry point 
void lavi_main(int argc, char **argv)
{
    // Optional: Define window yourself, otherwise will be set to default values  
    g_api.windows.size = LAVI_POINT(1280, 720);
    g_api.windows.title = "Demo";

    lavi_init(&g_api);
    while (!g_api.quit) {
        lavi_update();

        // Process Input 
        if (g_api.keys[LAVI_UP].is_pressed) {
            ....
        }
        if (g_api.keys[LAVI_UP].is_released) {
            ....
        }
  
        // Process ...
        // Render frame
        glColorClear(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        ...
    }

}


```

Linking in your own functions from Win32 API:

```c
    // Don't be afraid of what you see here, we're working with a C idiom called xmacros for code generation, simply for ease. 
    // Look for #define LAVI_WIN32_FUNCS \
    // This is the starting point of our code generation, listed below are functions to be dynamically linked where the order
    // does not matter, however notice that it's alphabetical by function name just for readability.
  
    // The format of the macro is as follows:
    // LAVI_WINFUNC( dll, function_name, return_value, args )
    // Provide them correctly, or calling it won't work. Example if you've provided the wrong dll, the compiler will throw a DEP (Data Execution Prevention) error, which
    // pretty says you're touching an area of memory you're not supposed to, which is what's happening there.

    // Example
    NTSTATUS HidP_GetCaps(
    [in]  PHIDP_PREPARSED_DATA PreparsedData,
    [out] PHIDP_CAPS           Capabilities
    );
    // Important to reverse engineer here. Structs such as the two fields in the argument, I would take them from the header file and place them in. Types on the other hand, I woudln't
    // define them, but rather inspect what type they truly are and define them as that directly instead.
    // So as you can see NTSTATUS we're unsure, through some inspection we can see its type is a LONG, we can see then its a signed 32-bit integer, so we cast an int.

    // Provide it like this, prereq understanding of C macro syntax is important. 
    LAVI_WINFUNC(hid,      HidP_GetCaps,                s32,                        (void *ppd, HIDP_CAPS *caps)) \

    // Every function dynamically linked then is prefixed wtih lavi_
    // Here's how you call it:
    lavi_Hid_GetCaps(...);

    NOTE: if you are curious, yes you can debug/step through through this API 

    
```


