#include <windows.h>
//#include <iostream.h>
#include <objbase.h>

#include <stdint.h>
#include "ioctl.h"
#include "ifc_ldev.h"
//#include <unknwn.h>

#include "create.h"

CREATEFUNCPTR CreateInstance;

HINSTANCE CallCreateInstance(char* name)
{
   HINSTANCE hComponent = ::LoadLibrary(name);
   if(hComponent==NULL)
   {
//      cout << "Unable load dll" << endl;
      return 0;
   }

   CreateInstance = (CREATEFUNCPTR)::GetProcAddress(hComponent,"CreateInstance");
   if(CreateInstance==NULL)
   {
//      cout << "Unable find CreateInstance" << endl;
      return 0;
   }
   return hComponent;
}

