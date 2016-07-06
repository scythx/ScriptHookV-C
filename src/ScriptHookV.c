#include <Windows.h>

static 
	void *g_scriptRegister = NULL;
void scriptRegister_CALLBACK()
{
	void(*g_scriptRegister_CALL)();
	g_scriptRegister_CALL = (void(*)())g_scriptRegister;
	g_scriptRegister_CALL();
}
void SET_scriptRegister_CALLBACK(void(*LP_SCRIPT_MAIN)())
{
	g_scriptRegister = LP_SCRIPT_MAIN;
}

static void 
	*g_scriptRegisterAdditionalThread = NULL;
void scriptRegisterAdditionalThread_CALLBACK()
{
	void(*g_scriptRegisterAdditionalThread_CALL)();
	g_scriptRegisterAdditionalThread_CALL = (void(*)())g_scriptRegisterAdditionalThread;
	g_scriptRegisterAdditionalThread_CALL();
}
void SET_scriptRegisterAdditionalThread_CALLBACK(void(*LP_SCRIPT_MAIN)())
{
	g_scriptRegisterAdditionalThread = LP_SCRIPT_MAIN;
}

static 
	void *g__scriptUnregister = NULL;
void _scriptUnregister_CALLBACK()
{
	void(*g__scriptUnregister_CALL)();
	g__scriptUnregister_CALL = (void(*)())g__scriptUnregister;
	g__scriptUnregister_CALL();
}
void SET__scriptUnregister_CALLBACK(void(*LP_SCRIPT_MAIN)())
{
	g__scriptUnregister = LP_SCRIPT_MAIN;
}
