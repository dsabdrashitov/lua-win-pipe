#include <windows.h>
 
//=== Необходимые для Lua константы ============================================================================//
#define LUA_LIB
#define LUA_BUILD_AS_DLL
 
//=== Заголовочные файлы LUA ===================================================================================//
extern "C" {
#include "include\lauxlib.h"
#include "include\lua.h"
}
 
//=== Стандартная точка входа для DLL ==========================================================================//
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved)
{
   //Каждому событию соответствует свое значение аргумента fdwReason, передаваемого функции DllMain при его возникновении   
   switch (fdwReason)
   {
      case DLL_PROCESS_ATTACH: // Подключение DLL          
         break;
      case DLL_PROCESS_DETACH: // Отключение DLL
         break;
      case DLL_THREAD_ATTACH:  // Создание нового потока
         break;
      case DLL_THREAD_DETACH:  // Завершение потока
         break;
   }	
   return TRUE;
}
 
//=== Реализация функций, вызываемых из LUA ====================================================================//
// static int forLua_TestFunc(lua_State *L)// Возвращает заданный текст
// {
//    lua_pushstring(L, "Привет из C/C++");
//    return(1);
// }
 
 
//=== Регистрация реализованных в dll функций, чтобы они стали "видимы" для Lua ================================//
// static struct luaL_reg ls_lib[] = {
//    { "TestFunc", forLua_TestFunc }, // из скрипта Lua эту функцию можно будет вызывать так: QluaCSharpConnector.TestFunc(); здесь можно указать любое другое название
//    { NULL, NULL }
// };
 
//=== Регистрация названия библиотеки, видимого в скрипте Lua ==================================================//
// extern "C" LUALIB_API int luaopen_QluaCSharpConnector(lua_State *L) {
//    luaL_openlib(L, "QluaCSharpConnector", ls_lib, 0);
//    return 0;
// }

static int l_hell (lua_State *L) {
    lua_pushstring(L, "hello");
    return 1;
}

static const struct luaL_Reg mylib [] = {
    {"somefunc", l_hell},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_hellolib (lua_State *L) {
    luaL_newlib(L, mylib);
    return 1;
}
