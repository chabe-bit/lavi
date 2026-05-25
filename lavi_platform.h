#ifndef LAVI_PLATFORM_H
#define LAVI_PLATFORM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>

// OpenGL stuff 
// GL.h is tied heavily with windows.h, but just WINGDIAPI & APIENTRY, 
// which we can easily define ourselves 
#define WINGDIAPI __declspec(dllimport)
#define APIENTRY  __stdcall
#include <gl/GL.h>
//////////////////////////////


#define HID_USAGE_GENERIC_PAGE  0x01
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define ASSERT(x) \
    if (!(x)) { lavi_MessageBoxA(0, #x, "Assertion Failure", MB_OK); __debugbreak();  }


#if __STDC_VERSION__ > 199901L
#include <stdint.h>	
typedef uint8_t					u8;
typedef uint16_t				u16;
typedef uint32_t 				u32;
typedef uint64_t				u64;

typedef uint8_t 				s8;
typedef uint16_t				s16;
typedef uint32_t				s32;
typedef uint64_t				s64;
#else 
typedef unsigned char			u8;
typedef unsigned short			u16;
typedef unsigned int			u32;
typedef unsigned long long int	u64;

typedef signed char				s8;
typedef signed short			s16;
typedef signed int				s32;
typedef signed long long int	s64;
#endif

typedef s32 boolean;
#define LAVI_FALSE  0
#define LAVI_TRUE   1

typedef struct {
    int x, y;
} point;

typedef struct {
    float x, y;
} pointf;

// API 
struct lavi_api;
extern void lavi_main(int argc, char **argv);
extern void lavi_init(struct lavi_api *api);
extern void lavi_update(void);
extern void lavi_printf(const char *fmt, ...);
extern void lavi_msgbox(const char *fmt, ...);
extern void lavi_fatal(const char *fmt, ...);
extern point LAVI_POINT (int   x, int   y) { point p = {x,y}; return p; }
extern point LAVI_POINTF(float x, float y) { point p = {x,y}; return p; }

//////////////////////

typedef int  (__stdcall *lavi_wproc)();
typedef void (__stdcall *lavi_WNDPROC)(void *hwnd, u32 message, size_t wparam, size_t lparam);


typedef struct {
    s32  x;
    s32  y;
} POINT;
typedef union {
    struct {
        u32 LowPart;
        s32 HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        u32 LowPart;
        s32 HighPart;
    } u;
    s64 QuadPart;
} LARGE_INTEGER;
typedef struct {
    void *        hwnd;
    u32         message;
    size_t      wParam;
    size_t      lParam;
    u32       time;
    POINT       pt;
} MSG;
typedef struct {
    u16                               wButtons;
    u8                                bLeftTrigger;
    u8                                bRightTrigger;
    s16                               sThumbLX;
    s16                               sThumbLY;
    s16                               sThumbRX;
    s16                               sThumbRY;
} XINPUT_GAMEPAD;
typedef struct {
    u32                               dwPacketNumber;
    XINPUT_GAMEPAD                      Gamepad;
} XINPUT_STATE;
typedef u32   (__stdcall *XINPUTGETSTATE)(u32 dwUserIndex, XINPUT_STATE *pState);
typedef struct {
    u16 wLeftMotorSpeed;
    u16 wRightMotorSpeed;
} XINPUT_VIBRATION;
typedef struct {
    s32    left;
    s32    top;
    s32    right;
    s32    bottom;
} RECT;
typedef struct {
    u32          style;
    lavi_WNDPROC lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    void *    hInstance;
    void *    hIcon;
    void *    hCursor;
    void *    hbrBackground;
    char *    lpszMenuName;
    char *    lpszClassName;
} WNDCLASSA;
typedef struct {
    u16  nSize;
    u16  nVersion;
    u32 dwFlags;
    u8  iPixelType;
    u8  cColorBits;
    u8  cRedBits;
    u8  cRedShift;
    u8  cGreenBits;
    u8  cGreenShift;
    u8  cBlueBits;
    u8  cBlueShift;
    u8  cAlphaBits;
    u8  cAlphaShift;
    u8  cAccumBits;
    u8  cAccumRedBits;
    u8  cAccumGreenBits;
    u8  cAccumBlueBits;
    u8  cAccumAlphaBits;
    u8  cDepthBits;
    u8  cStencilBits;
    u8  cAuxBuffers;
    u8  iLayerType;
    u8  bReserved;
    u32 dwLayerMask;
    u32 dwVisibleMask;
    u32 dwDamageMask;
} PIXELFORMATDESCRIPTOR;
typedef struct {
    u32 dwType;
    u32 dwSize;
    void * hDevice;
    size_t wParam;
} RAWINPUTHEADER;
typedef struct {
    u16 usFlags;
    union {
        u32 ulButtons;
        struct  {
            u16  usButtonFlags;
            u16  usButtonData;
        } s_param;
    } u_param;
    u32 ulRawButtons;
    s32 lLastX;
    s32 lLastY;
    s32 ulExtraInformation;
} RAWMOUSE;
typedef struct {
    u16 MakeCode;
    u16 Flags;
    u16 Reserved;
    u16 VKey;
    u32 Message;
    u32 ExtraInformation;
} RAWKEYBOARD;
typedef struct {
    u32 dwSizeHid;    
    u32 dwCount;      
    u8 bRawData[1];
} RAWHID;
typedef struct {
    RAWINPUTHEADER header;
    union {
        RAWMOUSE    mouse;
        RAWKEYBOARD keyboard;
        RAWHID      hid;
    } data;
} RAWINPUT;
typedef struct {
    u16 usUsagePage; 
    u16 usUsage;     
    u32 dwFlags;
    void * hwndTarget;    
} RAWINPUTDEVICE;
typedef struct {
  void *hDevice;
  u32 dwType;
} RAWINPUTDEVICELIST;
typedef struct {
    u32 dwVendorId;
    u32 dwProductId;
    u32 dwVersionNumber;

    /*
     * Top level collection UsagePage and Usage
     */
    u16 usUsagePage;
    u16 usUsage;
} RID_DEVICE_INFO_HID;
typedef struct {
    u32 cbSize;
    u32 dwType;
    union {
        // Removed mouse and keyboard 
        RID_DEVICE_INFO_HID hid;
    } param;
} RID_DEVICE_INFO;
typedef struct {
    u16    UsagePage;
    u8     ReportID;
    u8     IsAlias;

    u16    BitField;
    u16    LinkCollection;   // A unique internal index pointer

    u16     LinkUsage;
    u16     LinkUsagePage;

    u8  IsRange;
    u8  IsStringRange;
    u8  IsDesignatorRange;
    u8  IsAbsolute;

    u16    ReportCount;   // Available in API version >= 2 only.

    u16    Reserved2;

    u32    Reserved[9];
    union {
        struct {
            u16     UsageMin,         UsageMax;
            u16    StringMin,        StringMax;
            u16    DesignatorMin,    DesignatorMax;
            u16    DataIndexMin,     DataIndexMax;
        } Range;
        struct  {
            u16     Usage,            Reserved1;
            u16    StringIndex,      Reserved2;
            u16    DesignatorIndex,  Reserved3;
            u16    DataIndex,        Reserved4;
        } NotRange;
    };
} HIDP_BUTTON_CAPS;
typedef struct {
    u16     UsagePage;
    u8    ReportID;
    u8  IsAlias;

    u16    BitField;
    u16    LinkCollection;   // A unique internal index pointer

    u16     LinkUsage;
    u16     LinkUsagePage;

    u8  IsRange;
    u8  IsStringRange;
    u8  IsDesignatorRange;
    u8  IsAbsolute;

    u8  HasNull;        // Does this channel have a null report   union
    u8    Reserved;
    u16    BitSize;        // How many bits are devoted to this value?

    u16    ReportCount;    // See Note below.  Usually set to 1.
    u16    Reserved2[5];

    u32    UnitsExp;
    u32    Units;

    s32     LogicalMin,       LogicalMax;
    s32     PhysicalMin,      PhysicalMax;

    union {
        struct {
            u16     UsageMin,         UsageMax;
            u16    StringMin,        StringMax;
            u16    DesignatorMin,    DesignatorMax;
            u16    DataIndexMin,     DataIndexMax;
        } Range;

        struct {
            u16     Usage,            Reserved1;
            u16    StringIndex,      Reserved2;
            u16    DesignatorIndex,  Reserved3;
            u16    DataIndex,        Reserved4;
        } NotRange;
    };
} HIDP_VALUE_CAPS;
typedef struct {
    u16    Usage;
    u16    UsagePage;
    u16    InputReportByteLength;
    u16    OutputReportByteLength;
    u16    FeatureReportByteLength;
    u16    Reserved[17];

    u16    NumberLinkCollectionNodes;

    u16    NumberInputButtonCaps;
    u16    NumberInputValueCaps;
    u16    NumberInputDataIndices;

    u16    NumberOutputButtonCaps;
    u16    NumberOutputValueCaps;
    u16    NumberOutputDataIndices;

    u16    NumberFeatureButtonCaps;
    u16    NumberFeatureValueCaps;
    u16    NumberFeatureDataIndices;
} HIDP_CAPS;

// Window Messages
#define WM_INPUT            0x00FF
#define WM_TIMER            0x0113
#define WM_ENTERMENULOOP    0x0211
#define WM_ENTERSIZEMOVE    0x0231
#define WM_EXITMENULOOP     0x0212
#define WM_EXITSIZEMOVE     0x0232
#define WM_CLOSE            0x0010
#define WM_DESTROY          0x0002

// Window Styles 
#define WS_OVERLAPPED       0x00000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_MAXIMIZE         0x01000000L
#define WS_CAPTION          0x00C00000L     
#define WS_BORDER           0x00800000L
#define WS_DLGFRAME         0x00400000L
#define WS_VSCROLL          0x00200000L
#define WS_HSCROLL          0x00100000L
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L
#define WS_GROUP            0x00020000L
#define WS_TABSTOP          0x00010000L
#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED    |  \
                             WS_CAPTION       |  \
                             WS_SYSMENU       |  \
                             WS_THICKFRAME    |  \
                             WS_MINIMIZEBOX   |  \
                             WS_MAXIMIZEBOX)
#define   WS_TILED         WS_OVERLAPPED
#define   WS_ICONIC        WS_MINIMIZE
#define   WS_SIZEBOX       WS_THICKFRAME
#define   WS_TILEDWINDOW   WS_OVERLAPPEDWINDOW

// Create Window 
#define CW_USEDEFAULT       0x80000000

// Class Styles 
#define CS_HREDRAW          0x0002
#define CS_VREDRAW          0x0001
#define CS_OWNDC            0x0020

#define GWLP_USERDATA       -21
#define MB_OK               0x00000000L 


// XInput Macros
#define XINPUT_GAMEPAD_DPAD_UP              0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN            0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT            0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT           0x0008
#define XINPUT_GAMEPAD_START                0x0010
#define XINPUT_GAMEPAD_BACK                 0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB           0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB          0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER        0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER       0x0200
#define XINPUT_GAMEPAD_A                    0x1000
#define XINPUT_GAMEPAD_B                    0x2000
#define XINPUT_GAMEPAD_X                    0x4000
#define XINPUT_GAMEPAD_Y                    0x8000
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689


// RawInput Macros 
#define RIDEV_INPUTSINK         0x00000100 
#define RIDEV_DEVNOTIFY         0x00002000
#define RIDI_PREPARSEDDATA      0x20000005
#define RIDI_DEVICENAME         0x20000007  // the return valus is the character length, not the byte size
#define RIDI_DEVICEINFO         0x2000000b

#define RID_INPUT 0x10000003
#define RIM_TYPEMOUSE 0
#define RIM_TYPEHID 2

#define MOUSE_MOVE_RELATIVE 0
#define WHEEL_DELTA 120
#define RI_MOUSE_LEFT_BUTTON_DOWN   0x0001  // Left Button changed to down.
#define RI_MOUSE_LEFT_BUTTON_UP     0x0002  // Left Button changed to up.
#define RI_MOUSE_RIGHT_BUTTON_DOWN  0x0004  // Right Button changed to down.
#define RI_MOUSE_RIGHT_BUTTON_UP    0x0008  // Right Button changed to up.
#define RI_MOUSE_MIDDLE_BUTTON_DOWN 0x0010  // Middle Button changed to down.
#define RI_MOUSE_MIDDLE_BUTTON_UP   0x0020  // Middle Button changed to up.
#define RI_MOUSE_WHEEL              0x0400
#define HEAP_ZERO_MEMORY            0x00000008 



// Keys 
#define LAVI_VK_PAUSE      0x07 
#define LAVI_VK_BACK       0x08
#define LAVI_VK_TAB        0x09 
#define LAVI_VK_LWIN       0x0a
#define LAVI_VK_RWIN       0x0b
#define LAVI_VK_NUMLOCK    0x0c
#define LAVI_VK_RETURN     0x0d 
#define LAVI_VK_SCROLL     0x0e

#define LAVI_VK_SHIFT      0x10
#define LAVI_VK_CONTROL    0x11
#define LAVI_VK_ALT        0x12
#define LAVI_VK_APPS       0x13
#define LAVI_VK_CAPSLOCK   0x14 
#define LAVI_VK_LSHIFT     0x15
#define LAVI_VK_RSHIFT     0x16
#define LAVI_VK_LCONTROL   0x17
#define LAVI_VK_RCONTROL   0x18
#define LAVI_VK_LALT       0x19
#define LAVI_VK_RALT       0x1a
#define LAVI_VK_ESC        0x1b 
#define LAVI_VK_PRTSCR     0x1c
#define LAVI_VK_OEM_8      0x1d
#define LAVI_VK_NUM_ENTER  0x1e 
#define LAVI_VK_NUM_DIVIDE 0x1f

#define LAVI_VK_SPACE      0x20 
#define LAVI_VK_PAGEUP     0x21 
#define LAVI_VK_PAGEDOWN   0x22 
#define LAVI_VK_END        0x23
#define LAVI_VK_HOME       0x24
#define LAVI_VK_INSERT     0x25
#define LAVI_VK_DELETE     0x26
#define LAVI_VK_QUOTE      0x27 
#define LAVI_VK_LEFT       0x28
#define LAVI_VK_RIGHT      0x29
#define LAVI_VK_UP         0x2a
#define LAVI_VK_DOWN       0x2b
#define LAVI_VK_COMMA      0x2c 
#define LAVI_VK_MINUS      0x2d 
#define LAVI_VK_PERIOD     0x2e 
#define LAVI_VK_SLASH      0x2f 

#define LAVI_VK_SEMICOLON  0x3b 
#define LAVI_VK_EQUALS     0x3d 
#define LAVI_VK_F1        0x40
#define LAVI_VK_F2        0x41
#define LAVI_VK_F3        0x42
#define LAVI_VK_F4        0x43
#define LAVI_VK_F5        0x44
#define LAVI_VK_F6        0x45
#define LAVI_VK_F7        0x46
#define LAVI_VK_F8        0x47
#define LAVI_VK_F9        0x48
#define LAVI_VK_F10       0x49
#define LAVI_VK_F11       0x4a
#define LAVI_VK_F12       0x4b
#define LAVI_VK_F13       0x4c
#define LAVI_VK_F14       0x4d
#define LAVI_VK_F15       0x4e
#define LAVI_VK_F16       0x4f

#define LAVI_VK_NUM_0     0x50
#define LAVI_VK_NUM_1     0x51
#define LAVI_VK_NUM_2     0x52
#define LAVI_VK_NUM_3     0x53
#define LAVI_VK_NUM_4     0x54
#define LAVI_VK_NUM_5     0x55
#define LAVI_VK_NUM_6     0x56
#define LAVI_VK_NUM_7     0x57
#define LAVI_VK_NUM_8     0x58
#define LAVI_VK_NUM_9     0x59

#define LAVI_VK_OPENBRACE  0x5b 
#define LAVI_VK_BACKSLASH  0x5c 
#define LAVI_VK_CLOSEBRACE 0x5d 

#define LAVI_VK_BACKQUOTE      0x60
#define LAVI_VK_NUM_MULITPLY   0x7b
#define LAVI_VK_NUM_ADD        0x7c
#define LAVI_VK_NUM_SEPARATOR  0x7d
#define LAVI_VK_NUM_SUBTRACT   0x7e
#define LAVI_VK_NUM_DECIMAL    0x7f



// Generate functions that I want  
/*
    AllocConsole
    AdjustWindowRect
    ChoosePixelFormat
    ClientToScreen
    ConvertThreadToFiber
    CreateEventA
    CreateFiber
    CreateThread
    CreateWindowA
    DefWindowProcA
    DescribePixelFormat
    DestroyWindow
    DispatchMessageA
    FreeConsole
    GetClientRect
    GetCursor
    GetCursorPos
    GetDC
    GetKeyState
    GetKeyboardState
    GetLastError
    GetRawInputData
    GetWindowConsole
    KillTimer
    OutputDebugStringA
    MessageBoxA
    PeekMessageA
    QueryPerformanceCounter
    QueryPerformanceFrequency
    SetPixelFormat
    SetThreadPriority
    SetTimer
    ShowWindow
    Sleep
    SwapBuffers
    SwitchToFiber
    TranslateMessage
    XInputGetState
    XInputSetState
    UpdateWindow

    GetRawInputDeviceInfoA
    HidP_GetUsageValue
    HidP_GetUsage
    HidP_GetCaps
    HidP_GetButtonCaps
    HidP_GetValueCaps
    HidD_GetManufacturerString
 
 */



/*               DLL       NAME                         RETVAL                      ARGS                                    */
#define LAVI_WIN32_FUNCS \
    LAVI_WINFUNC(kernel32, AttachConsole,               int,                        (u32 dwProcessId)) \
    LAVI_WINFUNC(user32,   AdjustWindowRect,            int,                        (RECT *rect, u32 dwStyle, int bMenu)) \
    LAVI_WINFUNC(gdi32,    ChoosePixelFormat,           int,                        (void *hdc, const PIXELFORMATDESCRIPTOR *pfd)) \
    LAVI_WINFUNC(user32,   ClientToScreen,              int,                        (void *hwnd, POINT *lpPoint)) \
    LAVI_WINFUNC(kernel32, ConvertThreadToFiber,        void *,                     (void *lpParam)) \
    LAVI_WINFUNC(kernel32, CreateEventA,                void * ,                    (void *lpEventAttribs, int bManualReset, boolean bInitialState, char *lpName)) \
    LAVI_WINFUNC(kernel32, CreateFiber,                 void * ,                    (size_t dwStackSize, lavi_wproc *lpStartAddress, void *lpParam)) \
    LAVI_WINFUNC(user32,   CreateWindowExA,             void *,                     (s32 dwExStyle, const char *lpClassName, const char *lpWindowName, s32 dwStyle, int x, int y, int w, int h, void * hwndParent, void *hMenu, void *hInstance, void *lpParam)) \
    LAVI_WINFUNC(user32,   DefWindowProcA,              size_t,                     (void *hwnd, u32 message, size_t wparam, size_t lparam)) \
    LAVI_WINFUNC(gdi32,    DescribePixelFormat,         int,                        (void *hdc, int iPixelFormat, u32 nBytes, PIXELFORMATDESCRIPTOR *pfd)) \
    LAVI_WINFUNC(user32,   DestroyWindow,               int,                        (void *hwnd)) \
    LAVI_WINFUNC(user32,   DispatchMessageA,            size_t,                     (const MSG *message)) \
    LAVI_WINFUNC(user32,   GetClientRect,               int,                        (void * hwnd, RECT *rect)) \
    LAVI_WINFUNC(kernel32, GetConsoleWindow,            void * ,                    (void)) \
    LAVI_WINFUNC(user32,   GetDC,                       void *,                     (void * hwnd)) \
    LAVI_WINFUNC(user32,   GetKeyboardState,            int,                        (u8 *lpKeyState)) \
    LAVI_WINFUNC(user32,   GetLastError,                s32 ,                       (void)) \
    LAVI_WINFUNC(user32,   GetWindowLongPtrA,           s64,                        (void *hwnd, int nIndex)) \
    LAVI_WINFUNC(kernel32, GetProcessHeap,              void *,                     (void)) \
    LAVI_WINFUNC(user32,   GetRawInputData,             u32,                        (void *hRawInput, u32 uiCmd, void *pData, u32 *pcbSize, u32 cbSizeHeader)) \
    LAVI_WINFUNC(user32,   GetRawInputDeviceInfoA,      u32,                        (void *hDevice, u32 uiCmd, void *data, u32 *size)) \
    LAVI_WINFUNC(user32,   GetRawInputDeviceList,       u32,                        (void *RawinputDeviceList, u32 *NumDevices, u32 cbSize)) \
     LAVI_WINFUNC(hid,     HidP_GetButtonCaps,          s32,                        (s32 report_type, HIDP_BUTTON_CAPS *button_caps, u16 *button_caps_length, void *ppd)) \
    LAVI_WINFUNC(hid,      HidP_GetCaps,                s32,                        (void *ppd, HIDP_CAPS *caps)) \
    LAVI_WINFUNC(hid,      HidD_GetManufacturerString,  u8,                         (void *hHid, void *buffer, u32 buffer_length)) \
    LAVI_WINFUNC(hid,      HidP_GetUsages,              s32,                        (s32 report_type, u16 usage_page, u16 link_collection, u16 *usage_list, u32 *usage_length, void *ppd, char *report, u32 report_length)) \
    LAVI_WINFUNC(hid,      HidP_GetUsageValue,          s32,                        (s32 report_type, u16 usage_page, u16 link_collection, u16 usage, u32 *usage_value, void *ppd, char *report, u32 report_length)) \
    LAVI_WINFUNC(hid,      HidP_GetValueCaps,           s32,                        (s32 report_type, HIDP_VALUE_CAPS *value_caps, u16 *value_caps_length, void *ppd)) \
    LAVI_WINFUNC(kernel32, HeapAlloc,                   void *,                     (void *hHeap, u64 idEvent, size_t dwBytes)) \
    LAVI_WINFUNC(kernel32, HeapFree,                    int,                        (void *hHeap, s32 dwFlags, void *lpMem)) \
    LAVI_WINFUNC(user32,   KillTimer,                   int,                        (void *hwnd, u64 idEvent)) \
    LAVI_WINFUNC(kernel32, OutputDebugStringA,          void,                       (const char *str)) \
    LAVI_WINFUNC(user32,   MessageBoxA,                 int,                        (void *hwnd, const char *lpText, const char *lpCaption, u32 uType)) \
    LAVI_WINFUNC(user32,   PeekMessageA,                int,                        (MSG *lpMsg, void *, u32 wMsgFilterMin, u32 wMsgFilterMax, u32 wRemoveMsg)) \
    LAVI_WINFUNC(kernel32, QueryPerformanceCounter,     int,                        (LARGE_INTEGER *counter)) \
    LAVI_WINFUNC(kernel32, QueryPerformanceFrequency,   int,                        (LARGE_INTEGER *freq)) \
    LAVI_WINFUNC(user32,   RegisterClassA,              u16,                        (const WNDCLASSA *lpWindowClass)) \
    LAVI_WINFUNC(user32,   RegisterRawInputDevices,     int,                        (RAWINPUTDEVICE *pRawInputDevice, u32 nDevices, u32 cbSize)) \
    LAVI_WINFUNC(gdi32,    SetPixelFormat,              int,                        (void *hdc,  int fmt, const PIXELFORMATDESCRIPTOR *pfd))  \
    LAVI_WINFUNC(user32,   SetTimer,                    u64,                        (void *hwnd, u64 nIDEvent, u32 uElapse, lavi_wproc *lpTimerFunc)) \
    LAVI_WINFUNC(user32,   SetWindowLongPtrA,           s64,                        (void *hwnd, int nIndex, s64 dwNewLong)) \
    LAVI_WINFUNC(user32,   ShowWindow,                  int,                        (void *hwnd, int nCmdShow)) \
    LAVI_WINFUNC(user32,   Sleep,                       void,                       (u32 milliseconds)) \
    LAVI_WINFUNC(gdi32,    SwapBuffers,                 int,                        (void *hdc)) \
    LAVI_WINFUNC(kernel32, SwitchToFiber,               void,                       (void *lpFiber)) \
    LAVI_WINFUNC(user32,   TranslateMessage,            size_t,                     (MSG *message)) \
    LAVI_WINFUNC(user32,   UpdateWindow,                int,                        (void *hwnd)) 

#define LAVI_WINFUNC(dll, name, retval, args) \
    static retval (__stdcall *lavi_##name) args;
LAVI_WIN32_FUNCS
#undef LAVI_WINFUNC

typedef struct {
    boolean is_down;
    boolean is_pressed;
    boolean is_released;
} lavi_digitalbutton;

typedef struct {
    float threshold;
    float value;
    boolean is_down;
    boolean is_pressed;
    boolean is_released;
} lavi_analogbutton;

typedef struct {
    float threshold;
    pointf axis;
} lavi_stick;

typedef struct {
    /* XBOX/XInput profile */
    boolean connected;
    lavi_digitalbutton a, 
                       b, 
                       y, 
                       x;
    lavi_analogbutton  ltrigger,
                       rtrigger;
    lavi_digitalbutton lshoulder,
                       rshoulder;
    lavi_digitalbutton dpad_up,
                       dpad_down,
                       dpad_left,
                       dpad_right;
    lavi_stick         lthumb_stick,
                       rthumb_stick;
    lavi_digitalbutton lthumb_button,
                       rthumb_button;
    lavi_digitalbutton start, 
                       back;
} lavi_gamepad;

typedef struct {
    // why do we need to pack this? 
    void *ppd;
    HIDP_BUTTON_CAPS *b_caps;
    HIDP_VALUE_CAPS  *v_vaps;
    HIDP_CAPS caps;
    u32 ppd_count;
    u16 b_caps_count;
    u16 v_caps_count;
} _hid;

typedef struct {
    struct {
        boolean connected;
        // Struct for user to interface gamepad with 
        lavi_digitalbutton dpad_up,
                           dpad_down,
                           dpad_left,
                           dpad_right;
        lavi_stick lstick,
                   rstick;
    } gamepad;

    // Open hid for the user to interface more than just the gamepad
} lavi_hid;

enum {
    HID_GAMEPAD_N64,
};

static void
lavi_hid_set_gamepad_profile(lavi_hid *hid, s32 gamepad_profile_id)
{
    switch (gamepad_profile_id) {
    case HID_GAMEPAD_N64:
        // call function ...
        // Map buttons and so on.
        break;
    }
}

enum {
    LAVI_MAX_KEYS = 256, 
    LAVI_MAX_USAGE_KEYS = 128,
};

typedef struct {
    lavi_digitalbutton lbutton,
                       rbutton;
    int wheel;
    int dt_wheel;
    point pos;
    point dt_pos;
} lavi_mouse;

typedef struct lavi_api lavi_api;
struct lavi_api {
    boolean quit;
    boolean initialized;

    struct {
        const char *name;
        point size;
        point pos;
    } window;

    struct {
        float	delta_sec;
        u64     delta_ticks;    // raw 
        u64		delta_ns;
        u64		delta_mu;
        u64		delta_ms;
        u64		delta_samples;
        u64		delta_nanoseconds;
        u64		delta_microseconds;
        u64		delta_milliseconds;


        double	time_sec;
        u64     time_ticks;
        u64		time_ns;
        u64		time_mu;
        u64		time_ms;
        u64		time_nanoseconds;
        u64		time_microseconds;
        u64		time_milliseconds;

        // lower-level
        u64     initial_ticks;  
        u64     curr_ticks;
        u64     ticks_per_sec;  // raw
    } time;

    lavi_digitalbutton keys[LAVI_MAX_KEYS];
    lavi_gamepad gamepad;
    lavi_hid hid;
    lavi_mouse   mouse; 

    struct {
        void *hwnd;
        void *hdc;
        void *hglrc;
        void *main_fiber;
        void *message_fiber;
        XINPUTGETSTATE xinput_getstate;
    } win32;
};

// Globals
static lavi_api *g_api;
extern __declspec(dllimport) lavi_wproc __stdcall GetProcAddress(void *mod, const char *func_name);
extern __declspec(dllimport) void *     __stdcall LoadLibraryA(const char *name);

// HELPER FUNCS
static void
lavi_console_attach(void)
{
    // NOTE to reader: 
    // printf to the console via MSVC does not work, we work around that   
    // by attaching THIS process to the console, in my case CMD.

    lavi_AttachConsole((u32)-1);

    if (lavi_GetConsoleWindow() != NULL) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
}

void 
lavi_printf(const char *fmt, ...)
{
    char buffer[1024];
    va_list va;
    va_start(va, fmt);
    vsprintf_s(buffer, sizeof(buffer), fmt, va);
    va_end(va);
    lavi_OutputDebugStringA(buffer);
}   

void 
lavi_msgbox(const char *fmt, ...)
{
    char buffer[1024];
    va_list va;
    va_start(va, fmt);
    vsprintf_s(buffer, sizeof(buffer), fmt, va);
    va_end(va);
    if (lavi_MessageBoxA == NULL) { 
        // ...
    }
    lavi_MessageBoxA(g_api->win32.hwnd, buffer, g_api->window.name, 0 /* MB_OK */);
}

void 
lavi_fatal(const char *fmt, ...)
{
    char buffer[1024];
    va_list va;
    va_start(va, fmt);
    vsprintf_s(buffer, sizeof(buffer), fmt, va);
    va_end(va);
    lavi_msgbox(fmt);
    exit(1);
}

//////////////
static void 
lavi_load_dlls(void)
{
    void *avrt      = LoadLibraryA("avrt.dll");
    void *gdi32     = LoadLibraryA("gdi32.dll");
    void *kernel32  = LoadLibraryA("kernel32.dll");
    void *ole32     = LoadLibraryA("ole32.dll");
    void *user32    = LoadLibraryA("user32.dll");
    void *hid       = LoadLibraryA("hid.dll");
    void *winmm     = LoadLibraryA("winmm.dll");
    void *xinput    = LoadLibraryA("xinput9_1_0.dll");
    if (xinput == NULL)
       xinput = LoadLibraryA("xinput1_3.dll");

    #define LAVI_WINFUNC(dll, name, retval, args) \
        lavi_##name = (retval (__stdcall *) args) GetProcAddress(dll, #name);
    LAVI_WIN32_FUNCS
    #undef LAVI_WINFUNC
}

// Update 
static void
lavi_update_digitalbutton(lavi_digitalbutton *button, boolean is_down)
{
    boolean was_down = button->is_down;
    button->is_down = is_down;
    button->is_pressed = !was_down && is_down;
    button->is_released = was_down && !is_down;
}

static void
lavi_update_analogbutton(lavi_analogbutton *analog, float value)
{
    boolean was_down = analog->is_down;
    analog->value = value;
    analog->is_down = (value >= analog->threshold);
    analog->is_pressed = !was_down && analog->is_down;
    analog->is_released = was_down && !analog->is_down;
}

static void
lavi_update_stick(lavi_stick *stick, float x, float y)
{
    if (fabs(x) <= stick->threshold)
        x = 0.0f;
    if (fabs(y) <= stick->threshold)
        y = 0.0f;
    stick->axis.x = x;
    stick->axis.y = y;
}

// Pull
static void
lavi_pull_window(void)
{
    RECT client_rect;
    POINT win_pos;
    
    lavi_GetClientRect(g_api->win32.hwnd, &client_rect);	
	g_api->window.size.x = client_rect.right  - client_rect.left;
	g_api->window.size.y = client_rect.bottom - client_rect.top;
	
	win_pos.x = client_rect.left;
	win_pos.y = client_rect.top;
	lavi_ClientToScreen(g_api->win32.hwnd, &win_pos);
	g_api->window.pos.x	= win_pos.x;
	g_api->window.pos.y	= win_pos.y;
}

static void
lavi_pull_keyboard(void)
{
    int i;
    u8 keyboard_state[256];

    if (!lavi_GetKeyboardState(keyboard_state)) {
        return;
    }

    for (i = 0; i < LAVI_MAX_KEYS; i++) {
        u8 key = keyboard_state[i];
        lavi_update_digitalbutton(g_api->keys + i, keyboard_state[i] >> 7);
    }
}

static void
lavi_pull_xinput_gamepad(void)
{
    XINPUT_STATE xinput_state = {0};

    if (!g_api->win32.xinput_getstate) 
        return;
   
    if (g_api->win32.xinput_getstate(0, &xinput_state) != 0) {
        g_api->gamepad.connected = LAVI_FALSE;
        return;
    }
    
    g_api->gamepad.connected = LAVI_TRUE; 

    lavi_update_digitalbutton(&g_api->gamepad.a, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.b, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.x, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.y, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.dpad_up, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.dpad_down, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.dpad_left, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.dpad_right, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.lshoulder, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.rshoulder, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.lthumb_button, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.rthumb_button, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.start, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
    lavi_update_digitalbutton(&g_api->gamepad.back, (xinput_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
    lavi_update_analogbutton(&g_api->gamepad.ltrigger, xinput_state.Gamepad.bLeftTrigger / 255.0f);
    lavi_update_analogbutton(&g_api->gamepad.rtrigger, xinput_state.Gamepad.bRightTrigger / 255.0f);

#define CONVERT(x) (2.0f * (((x + 32768) / 65535.0f) - 0.5f))
    lavi_update_stick(&g_api->gamepad.lthumb_stick, CONVERT(xinput_state.Gamepad.sThumbLX), CONVERT(xinput_state.Gamepad.sThumbLY));
    lavi_update_stick(&g_api->gamepad.rthumb_stick, CONVERT(xinput_state.Gamepad.sThumbRX), CONVERT(xinput_state.Gamepad.sThumbRY));
#undef CONVERT

}

static void
lavi_pull_hid_gamepad(lavi_api *api)
{

}

static void
lavi_pull_time(void)
{
    LARGE_INTEGER counter, freq;
    u64 curr_ticks;

    lavi_QueryPerformanceCounter(&counter);
    lavi_QueryPerformanceCounter(&freq);
    curr_ticks = counter.QuadPart;

    g_api->time.delta_ticks = curr_ticks - g_api->time.time_ticks;
    g_api->time.time_ticks = curr_ticks - g_api->time.initial_ticks;

    g_api->time.delta_nanoseconds = (1000 * 1000 * 1000 * g_api->time.delta_ticks) / g_api->time.ticks_per_sec;
    g_api->time.delta_microseconds = g_api->time.delta_nanoseconds / 1000;
    g_api->time.delta_milliseconds = g_api->time.delta_microseconds / 1000;
    g_api->time.delta_sec = (float)g_api->time.delta_ticks / (float)g_api->time.ticks_per_sec; 

    g_api->time.time_nanoseconds = (1000 * 1000 * 1000 * g_api->time.time_ticks) / g_api->time.ticks_per_sec;
    g_api->time.time_microseconds = g_api->time.time_nanoseconds / 1000;
    g_api->time.time_milliseconds = g_api->time.time_microseconds / 1000;
    g_api->time.time_sec = (double)g_api->time.time_ticks / (double)g_api->time.ticks_per_sec; 
}


static void 
lavi_pull(void)
{
    if (!g_api->initialized) {
        lavi_fatal("Faiiled to init");
        return;
    }

    lavi_SwitchToFiber(g_api->win32.message_fiber);

    lavi_pull_window();
    lavi_pull_time();  
    lavi_pull_keyboard();
    lavi_pull_xinput_gamepad();
}

// Push
static void
lavi_push_opengl(void)
{
    lavi_SwapBuffers(g_api->win32.hdc);
}


static void
lavi_push(void)
{
    lavi_push_opengl();
}

// Update 
static void
lavi_update_rawinput(RAWINPUT *ri)
{
    // TODO: Parse PPD, Button Caps, Value Caps  
    void *ppd = NULL;
    HIDP_CAPS caps = {0};
    HIDP_BUTTON_CAPS *b_caps = NULL;
    HIDP_VALUE_CAPS  *v_caps = NULL; 
    u32 ppd_count;
    u16 b_caps_count, v_caps_count;
    void *hheap = lavi_GetProcessHeap();
    u32 button_count = 0;
    
    if (lavi_GetRawInputDeviceInfoA(ri->header.hDevice, RIDI_PREPARSEDDATA, NULL, &ppd_count) == (u32)-1) {
        goto cleanup;
    }
    ppd = (void *)lavi_HeapAlloc(lavi_GetProcessHeap(), HEAP_ZERO_MEMORY, ppd_count);
    if (!ppd) {
        goto cleanup;
    }

    if (lavi_GetRawInputDeviceInfoA(ri->header.hDevice, RIDI_PREPARSEDDATA, ppd, &ppd_count) == 0) {
        goto cleanup;
    }

    lavi_HidP_GetCaps(ppd, &caps);
    
    b_caps_count = caps.NumberInputButtonCaps;
    b_caps = (HIDP_BUTTON_CAPS *)lavi_HeapAlloc(hheap, HEAP_ZERO_MEMORY, b_caps_count * sizeof(HIDP_BUTTON_CAPS));
    if (!b_caps)
        goto cleanup;
    
    lavi_HidP_GetButtonCaps(0, b_caps, &b_caps_count, ppd);
    
    button_count = b_caps->Range.UsageMax - b_caps->Range.UsageMin + 1; 
    //printf("button_count: %d\n", button_count);


    v_caps_count = caps.NumberInputValueCaps;
    v_caps = (HIDP_VALUE_CAPS *)lavi_HeapAlloc(hheap, HEAP_ZERO_MEMORY, v_caps_count * sizeof(HIDP_VALUE_CAPS));
    if (!v_caps)
        goto cleanup;
    
    lavi_HidP_GetValueCaps(0, v_caps, &v_caps_count, ppd);
    
    {
        u16 i;
        for (i = 0; i < b_caps_count; i++) {
            u32 value;
            lavi_HidP_GetUsageValue(0, v_caps[i].UsagePage, 0, v_caps[i].Range.UsageMin, &value, ppd, (char *)ri->data.hid.bRawData, ri->data.hid.dwSizeHid);
            //printf("%d:%d \n", i, value);
        }
    }


#if 0
    {
        boolean is_down;
        u32 i;
        u16 usage_list[LAVI_MAX_USAGE_KEYS];
        u32 usage_length = 0;
        (lavi_HidP_GetUsages(0, b_caps->UsagePage, 0, usage_list, &usage_length, ppd, (char *)ri->data.hid.bRawData, ri->data.hid.dwSizeHid));
        
        //printf("usage_length: %d\n", usage_length);   
        for (i = 0; i < button_count; i++) {
            printf("ulist: %d\n", usage_list[i]);
        }
    } 
#endif 

cleanup:
    if (ppd) lavi_HeapFree(hheap, 0, ppd);
    if (b_caps) lavi_HeapFree(hheap, 0, b_caps);
    if (v_caps) lavi_HeapFree(hheap, 0, v_caps);

}


void 
lavi_update(void)
{
    lavi_pull();
    lavi_push();
}

static void __stdcall 
lavi_message_fiber_proc(void)
{
    lavi_SetTimer(g_api->win32.hwnd, 1, 1, (lavi_wproc *)0);
    for (;;) {
        MSG message;
        while (lavi_PeekMessageA(&message, 0, 0, 0, 1 /* PM_REMOVE */)) {
            lavi_TranslateMessage(&message);
            lavi_DispatchMessageA(&message);
        }
        lavi_SwitchToFiber(g_api->win32.main_fiber);
    }
}

static size_t __stdcall 
lavi_main_proc(void * hwnd,
               u32 message,
               size_t wparam,
               size_t lparam)
{
    lavi_api *api = (lavi_api *)lavi_GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    size_t result = 0;
    
    switch (message) {
    case WM_INPUT: {
        RAWINPUT *ri = NULL;
        u32 ri_size = 0;
        void *hheap = lavi_GetProcessHeap();
            
        if (lavi_GetRawInputData((void *)lparam, RID_INPUT, NULL, &ri_size, sizeof(RAWINPUTHEADER)) == (u32)-1) {
            goto cleanup;
        }

        ri = (RAWINPUT *)lavi_HeapAlloc(hheap, HEAP_ZERO_MEMORY, ri_size);
        if (!ri)
            goto cleanup;
        
        if (lavi_GetRawInputData((void *)lparam, RID_INPUT, ri, &ri_size, sizeof(RAWINPUTHEADER)) == 0) {
            goto cleanup;
        }

        if (ri->header.dwType == RIM_TYPEMOUSE && ri->data.mouse.usFlags == MOUSE_MOVE_RELATIVE) {
            u16 button_flags;
            boolean lbutton_down;
            boolean rbutton_down;

            api->mouse.dt_pos.x += ri->data.mouse.lLastX;
            api->mouse.dt_pos.y += ri->data.mouse.lLastY;
            button_flags = ri->data.mouse.u_param.s_param.usButtonFlags;
            
            lbutton_down = api->mouse.lbutton.is_down;
            if (button_flags & RI_MOUSE_LEFT_BUTTON_DOWN)
                lbutton_down = LAVI_TRUE;
            if (button_flags & RI_MOUSE_LEFT_BUTTON_UP)
                lbutton_down = LAVI_FALSE;
            lavi_update_digitalbutton(&api->mouse.lbutton, lbutton_down);

            rbutton_down = api->mouse.rbutton.is_down;
            if (button_flags & RI_MOUSE_RIGHT_BUTTON_DOWN)
                rbutton_down = LAVI_TRUE;
            if (button_flags & RI_MOUSE_RIGHT_BUTTON_UP)
                rbutton_down = LAVI_FALSE;
            lavi_update_digitalbutton(&api->mouse.rbutton, rbutton_down);

            if (button_flags & RI_MOUSE_WHEEL) 
                api->mouse.dt_wheel += ((s16)ri->data.mouse.u_param.s_param.usButtonData) / WHEEL_DELTA;
        }

        lavi_update_rawinput(ri);

cleanup:
        if (ri) 
            lavi_HeapFree(hheap, 0, ri);

        break;
    }
    case WM_TIMER:
        lavi_SwitchToFiber(api->win32.main_fiber);
        break;
    case WM_ENTERMENULOOP:
    case WM_ENTERSIZEMOVE:
        lavi_SetTimer(api->win32.hwnd, 0, 1, (lavi_wproc *)0);
        break;
    case WM_EXITMENULOOP:
    case WM_EXITSIZEMOVE:
        lavi_KillTimer(api->win32.hwnd, 0);
        break;
    case WM_CLOSE:
        lavi_DestroyWindow(api->win32.hwnd);
        break;
    case WM_DESTROY:
        api->quit = LAVI_TRUE;
        break;
    default:
        result = lavi_DefWindowProcA(hwnd, message, wparam, lparam);
    }

    return result;
}


// Init 
static boolean 
lavi_init_window(void)
{
    RECT rect;
    WNDCLASSA wc = {0};
    point win_pos;
    int win_width;
    int win_height;
    
    wc.lpfnWndProc = (lavi_WNDPROC)lavi_main_proc;
    wc.lpszClassName = "Lavi";
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    
    if (!lavi_RegisterClassA(&wc)) {
        lavi_fatal("RegisterClassA failed");
    }
    
    if (g_api->window.pos.x) 
        win_pos.x = g_api->window.pos.x;
    else 
        win_pos.x = CW_USEDEFAULT;

    if (g_api->window.pos.y) 
        win_pos.y = g_api->window.pos.y;
    else 
        win_pos.y = CW_USEDEFAULT;
 
    if (g_api->window.size.x) 
        win_width = g_api->window.size.x;
    else 
        win_width = CW_USEDEFAULT;
    
    if (g_api->window.size.y) 
        win_height = g_api->window.size.y;
    else 
        win_height = CW_USEDEFAULT;
    
    g_api->win32.main_fiber = lavi_ConvertThreadToFiber(0);
    ASSERT(g_api->win32.main_fiber);
    g_api->win32.message_fiber = lavi_CreateFiber(0, (lavi_wproc *)lavi_message_fiber_proc, g_api);
    ASSERT(g_api->win32.message_fiber);
    
    /* User can fill the API themselves, otherwise default stuff */ 
    // Should maybe do this in window pull not init
    if (!g_api->window.name) 
        g_api->window.name = "Default Window Name";
    
    if (win_height != CW_USEDEFAULT && win_width != CW_USEDEFAULT) {
        RECT rect;
        rect.left = 0;
        rect.right = win_width;
        rect.top = 0;
        rect.bottom = win_height;
        if (lavi_AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0)) {
            win_width  = rect.right - rect.left;
            win_height = rect.bottom - rect.top;
        } 
    }
    

    //lavi_fatal("CreateWindowA failed");
    g_api->win32.hwnd = lavi_CreateWindowExA(0, wc.lpszClassName, g_api->window.name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, win_pos.x, win_pos.y, win_width, win_height, 0, 0, 0, 0);
    if (!g_api->win32.hwnd) {
        lavi_fatal("CreateWindowA failed");
    }

    lavi_SetWindowLongPtrA(g_api->win32.hwnd, GWLP_USERDATA, (s64)g_api);
    lavi_ShowWindow(g_api->win32.hwnd, 1);
    lavi_UpdateWindow(g_api->win32.hwnd);

    g_api->win32.hdc = lavi_GetDC(g_api->win32.hwnd);

    return LAVI_TRUE;
}

static boolean 
lavi_init_time(void)
{
    LARGE_INTEGER freq, counter;
    lavi_QueryPerformanceFrequency(&freq);
    lavi_QueryPerformanceCounter(&counter);

    g_api->time.ticks_per_sec = freq.QuadPart;
    g_api->time.initial_ticks = counter.QuadPart; 
    
    return LAVI_TRUE;
}

static lavi_wproc   (__stdcall *lavi_wglGetProcAddress)(const char *name);
static void *       (__stdcall *lavi_wglCreateContext )(void *hdc);
static int          (__stdcall *lavi_wglMakeCurrent   )(void *hdc, void *hglrc);
static int          (__stdcall *lavi_wglDeleteCurrent )(void *hglrc);

static void *
opengl_get_func(const char *func_name)
{
    void *opengl32 = NULL;
    void *p;

    if (opengl32 == NULL) {
        opengl32 = LoadLibraryA("opengl32.dll");
        lavi_wglGetProcAddress = (lavi_wproc (__stdcall *)(const char *))GetProcAddress(opengl32, "wglGetProcAddress");
    }
    
    p = (void *)lavi_wglGetProcAddress(func_name);
    if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1) )
        p = (void *)GetProcAddress(opengl32, func_name);
   return p;

}

static boolean
lavi_init_opengl(void)
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(pfd), 
        1,  
        0x20/*OpenGL*/ | 0x4 /*DRAW_TO_WINDOW*/ | 1 /* DOUBLEBUFFER */,
        0 /*rgba*/, 
        32, 
        0,0,0,0,0,0, 
        0,0,0, 
        0,0,0,0,
        24,0,0,
        0/*MAIN_PLANE*/, 
        0,0,0,0 
    };
    int pf = lavi_ChoosePixelFormat(g_api->win32.hdc, &pfd);
    if (!pf) {
        lavi_fatal("ChoosePixelFormat: failed\n");
    }

    if (!lavi_DescribePixelFormat(g_api->win32.hdc, pf, sizeof(pfd), &pfd)) {
        lavi_fatal("DescribePixelFormat: failed\n");
    }

    if (!lavi_SetPixelFormat(g_api->win32.hdc, pf, &pfd)) {
        lavi_fatal("SetPixelFormat: failed\n");
    }

    {
        lavi_wglCreateContext = (void *(__stdcall *)(void *))opengl_get_func("wglCreateContext");
        lavi_wglDeleteCurrent = (int   (__stdcall *)(void *))opengl_get_func("wglDeleteCurrent");
        lavi_wglMakeCurrent = (int   (__stdcall *)(void *, void *))opengl_get_func("wglMakeCurrent");
       

        g_api->win32.hglrc = lavi_wglCreateContext(g_api->win32.hdc);
        lavi_wglMakeCurrent(g_api->win32.hdc, g_api->win32.hglrc);
    }
    return LAVI_TRUE;
}


static void
lavi_register_rawinput(void)
{
    u32 i;
    u16 dev_usage[] = {
        0x02,   // HID mouse 
        0x06,   // HID keyboard
        0x04,   
        0x05,
        0x08,
    };

    RAWINPUTDEVICE rid[ARRAY_SIZE(dev_usage)];
    for (i = 0; i < ARRAY_SIZE(dev_usage); i++) {
        rid[i].usUsagePage = HID_USAGE_GENERIC_PAGE;
        rid[i].usUsage = dev_usage[i];
        
        // NOTE: DO NOT USE RIDEV_NOLEGACY, IT WILL HANG!!!!!!!!!!!!
        rid[i].dwFlags = RIDEV_INPUTSINK | RIDEV_DEVNOTIFY;
        rid[i].hwndTarget = g_api->win32.hwnd;
    }

    if (!lavi_RegisterRawInputDevices(rid, ARRAY_SIZE(rid), sizeof(rid[0]))) {
        return;
    }   

    printf("Succesfully registered rawinput devs\n");
}


static void 
lavi_rawinput_getinfo(void *hdevice)
{
    RID_DEVICE_INFO *rdi = NULL;
    u32 rdi_cnt = 0;
    void *hheap = lavi_GetProcessHeap();
    if (lavi_GetRawInputDeviceInfoA(hdevice, RIDI_DEVICEINFO, NULL, &rdi_cnt) == (u32)-1) {
        goto cleanup;
    }

    rdi = (RID_DEVICE_INFO *)lavi_HeapAlloc(hheap, HEAP_ZERO_MEMORY, rdi_cnt);
    if (rdi == NULL) {
        goto cleanup;
    }

    if (lavi_GetRawInputDeviceInfoA(hdevice, RIDI_DEVICEINFO, rdi, &rdi_cnt) == 0) {
        goto cleanup;
    }
    
    char buffer[256];
    lavi_HidD_GetManufacturerString(hdevice, buffer, sizeof(buffer));

    printf("Manufacturer: %s\n", buffer);
    printf("VID: %d\n", rdi->param.hid.dwVendorId);
    printf("PID: %d\n", rdi->param.hid.dwProductId);

cleanup:
    if (rdi) lavi_HeapFree(hheap, 0, rdi);
}

static void
lavi_enumerate_rawinput(void)
{
    RAWINPUTDEVICELIST *rid_list = NULL;
    u32 i, count = 0;
    void *hheap = lavi_GetProcessHeap();

    if (lavi_GetRawInputDeviceList(NULL, &count, sizeof(RAWINPUTDEVICELIST)) == (u32)-1) {
        goto cleanup;
    }

    rid_list = (RAWINPUTDEVICELIST *)lavi_HeapAlloc(hheap, HEAP_ZERO_MEMORY, count * sizeof(RAWINPUTDEVICELIST));
    if (!rid_list)
        goto cleanup;

    if (lavi_GetRawInputDeviceList(rid_list, &count, sizeof(RAWINPUTDEVICELIST)) == 0) {
        goto cleanup;
    }

    for (i = 0; i < count; i++) {
        if (rid_list->dwType == RIM_TYPEHID) {
            lavi_rawinput_getinfo(rid_list[i].hDevice);
            //printf("HID!\n");
        }
    }



cleanup:
    if (rid_list) 
        lavi_HeapFree(hheap, 0, rid_list);
}


static void
lavi_init_rawinput(void)
{
    lavi_register_rawinput();
    lavi_enumerate_rawinput();
}


static void
lavi_init_xinput(void)
{
    void *xinput_mod;
    float trigger_threshold;
    
    xinput_mod = LoadLibraryA("xinput1_3.dll");
    if (xinput_mod)
        g_api->win32.xinput_getstate = (XINPUTGETSTATE)GetProcAddress(xinput_mod, "XInputGetState");
  
    trigger_threshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD / 255.0f;
    g_api->gamepad.ltrigger.threshold = trigger_threshold;
    g_api->gamepad.rtrigger.threshold = trigger_threshold;
    g_api->gamepad.lthumb_stick.threshold = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 32767.0f;
    g_api->gamepad.rthumb_stick.threshold = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE / 32767.0f;
}


static void
lavi_init_hid(void)
{
    // Register HID 
    // Parse HID 
    

}

void 
lavi_init(struct lavi_api *api)
{
    g_api = api;

    lavi_init_window();
    lavi_init_time();
    lavi_init_xinput();
    lavi_init_opengl();
    lavi_init_rawinput();



    api->initialized = LAVI_TRUE;
    lavi_pull();
}

int __stdcall
WinMain(void *instance,
        void *prev_instance,
        char *cmd_line,
        int cmd_show)
{
    lavi_load_dlls();
    lavi_console_attach();
    
    // Ommit cmd_line & cmd_show to keep the compiler quiet, shhhhhh
    (void)cmd_line;
    (void)cmd_show;

    int argc = 0;
    char *argv[256] = {0};


    
    lavi_main(argc, argv);
    return 0;
}


#endif /* LAVI_PLATFORM_H */
