/*
	ScriptHookV SDK WRAPPER FOR C PROGRAMMING LANGUAGE
	    https://github.com/Graefal/ScriptHookV-C

	ScriptHookV 1.0.617.1a
	  http://www.dev-c.com/files/ScriptHookV_SDK_1.0.617.1a.zip
*/
#pragma once

#include <windows.h>

/* textures */

// Create texture
//	texFileName	- texture file name, it's best to specify full texture path and use PNG textures
//	returns	internal texture id
//	Texture deletion is performed automatically when game reloads scripts
//	Can be called only in the same thread as natives

int createTexture_C(const char*);
#define createTexture createTexture_C

// Draw texture
//	id		-	texture id recieved from createTexture()
//	index	-	each texture can have up to 64 different instances on screen at one time
//	level	-	draw level, being used in global draw order, texture instance with least level draws first
//	time	-	how much time (ms) texture instance will stay on screen, the amount of time should be enough
//				for it to stay on screen until the next corresponding drawTexture() call
//	sizeX,Y	-	size in screen space, should be in the range from 0.0 to 1.0, e.g setting this to 0.2 means that
//				texture instance will take 20% of the screen space
//	centerX,Y -	center position in texture space, e.g. 0.5 means real texture center
//	posX,Y	-	position in screen space, [0.0, 0.0] - top left corner, [1.0, 1.0] - bottom right,
//				texture instance is positioned according to it's center
//	rotation -	should be in the range from 0.0 to 1.0
//	screenHeightScaleFactor - screen aspect ratio, used for texture size correction, you can get it using natives
//	r,g,b,a	-	color, should be in the range from 0.0 to 1.0
//
//	Texture instance draw parameters are updated each time script performs corresponding call to drawTexture()
//	You should always check your textures layout for 16:9, 16:10 and 4:3 screen aspects, for ex. in 1280x720,
//	1440x900 and 1024x768 screen resolutions, use windowed mode for this
//	Can be called only in the same thread as natives

void drawTexture_C(int, int, int, int,
	float, float, float, float,
	float, float, float, float,
	float, float, float, float);
#define drawTexture drawTexture_C

// IDXGISwapChain::Present callback
// Called right before the actual Present method call, render test calls don't trigger callbacks
// When the game uses DX10 it actually uses DX11 with DX10 feature level
// Remember that you can't call natives inside
// void OnPresent(IDXGISwapChain *swapChain);
typedef void(*PresentCallback)(void *);

// Register IDXGISwapChain::Present callback
// must be called on dll attach
void presentCallbackRegister_C(PresentCallback);
#define presentCallbackRegister presentCallbackRegister_C

// Unregister IDXGISwapChain::Present callback
// must be called on dll detach
void presentCallbackUnregister_C(PresentCallback);
#define presentCallbackUnregister presentCallbackUnregister_C

/* keyboard */

// DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow
typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);

// Register keyboard handler
// must be called on dll attach
void keyboardHandlerRegister_C(KeyboardHandler);
#define keyboardHandlerRegister  keyboardHandlerRegister_C

// Unregister keyboard handler
// must be called on dll detach
void keyboardHandlerUnregister_C(KeyboardHandler);
#define keyboardHandlerUnregister keyboardHandlerUnregister_C

/* scripts */

void scriptWait_C(DWORD);
#define scriptWait scriptWait_C
void scriptRegister_C(HMODULE, void(*)());
#define scriptRegister scriptRegister_C
void scriptRegisterAdditionalThread_C(HMODULE, void(*)());
#define scriptRegisterAdditionalThread scriptRegisterAdditionalThread_C
void scriptUnregister_C(HMODULE);
#define scriptUnregister scriptUnregister_C
void _scriptUnregister_C(void(*)()); // deprecated
#define _scriptUnregister _scriptUnregister_C

void nativeInit_C(UINT64);
#define nativeInit nativeInit_C
void nativePush64_C(UINT64);
#define nativePush64 nativePush64_C
PUINT64 nativeCall_C();
#define nativeCall nativeCall_C

static void WAIT(DWORD time) { scriptWait_C(time); }
static void TERMINATE() { WAIT(MAXDWORD); }

// Returns pointer to global variable
// make sure that you check game version before accessing globals because
// ids may differ between patches
UINT64 *getGlobalPtr_C(int);
#define getGlobalPtr getGlobalPtr_C

/* world */

// Get entities from internal pools
// return value represents filled array elements count
// can be called only in the same thread as natives
int worldGetAllVehicles_C(int*, int);
#define worldGetAllVehicles worldGetAllVehicles_C
int worldGetAllPeds_C(int*, int);
#define worldGetAllPeds worldGetAllPeds_C
int worldGetAllObjects_C(int*, int);
#define worldGetAllObjects worldGetAllObjects_C
int worldGetAllPickups_C(int*, int);
#define worldGetAllPickups worldGetAllPickups_C

/* misc */

// Returns base object pointer using it's script handle
// make sure that you check game version before accessing object fields because
// offsets may differ between patches
BYTE *getScriptHandleBaseAddress_C(int);
#define getScriptHandleBaseAddress getScriptHandleBaseAddress_C

typedef enum 
{
	VER_1_0_335_2_STEAM,
	VER_1_0_335_2_NOSTEAM,

	VER_1_0_350_1_STEAM,
	VER_1_0_350_2_NOSTEAM,

	VER_1_0_372_2_STEAM,
	VER_1_0_372_2_NOSTEAM,

	VER_1_0_393_2_STEAM,
	VER_1_0_393_2_NOSTEAM,

	VER_1_0_393_4_STEAM,
	VER_1_0_393_4_NOSTEAM,

	VER_1_0_463_1_STEAM,
	VER_1_0_463_1_NOSTEAM,

	VER_1_0_505_2_STEAM,
	VER_1_0_505_2_NOSTEAM,

	VER_1_0_573_1_STEAM,
	VER_1_0_573_1_NOSTEAM,

	VER_1_0_617_1_STEAM,
	VER_1_0_617_1_NOSTEAM,

	VER_SIZE,
	VER_UNK = -1
} eGameVersion;

eGameVersion getGameVersion_C();
#define getGameVersion getGameVersion_C
