#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

//Define offsets
#define BASEOFFSET 0x00F875E0
#define OFFSET0 0x18
#define OFFSET1 0x10
#define OFFSET2 0x28
#define OFFSET3 0x10
#define OFFSET4 0x20

//Define function to grab module base address
UINT_PTR dwGetModuleBaseAddress(DWORD dwProcID, TCHAR *szModuleName);

int main()
{
	//Initializing values to grab PID & module base address
    DWORD pid; //Initializing the pid value
    UINT_PTR BaseAddress = 0; //Initializing the base address value
    
    
    //Grabbing PID
	HANDLE hwnd = FindWindowA(NULL, "Logitech Gaming Software"); // Gets the handle of LGS and saves it to the variable hwnd
    if(hwnd == NULL){ // Displays an error and exits the program with code 1 if the LGS does not exist
        printf("FindWindow Error.");
        exit(1);
    }
    
    GetWindowThreadProcessId(hwnd,&pid); // Gets the LGS process ID and saves it to the pid variable
    HANDLE phandle = OpenProcess(PROCESS_VM_READ,0,pid); // Opens the LGS process to memory reading
    if(phandle == NULL){ // If not able to apply the memory read flag to the process exits the program with code 1
        printf("OpenProcess Error.");
        exit(1);
    }
    
    //Grabbing module base address
	BaseAddress = dwGetModuleBaseAddress(pid, _T("LCore.exe"));
    
    while(1){ // Endless loop
    	UINT_PTR address = BaseAddress + BASEOFFSET; //Base address of LGS is derived from both the module address and an offset
		UINT_PTR value = NULL; // Initialize value to NULL
		
		ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0); // Reads the pointer stored in the base address and stores it to value
        address = value + OFFSET0; // Adds offset 0 to the pointer stored in the base address
		ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0); // Reads the pointer stored in the offset 0 address and stores it to value
        address = value + OFFSET1; // Adds offset 1 to the pointer stored in the base address
		ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0); // Reads the pointer stored in the offset 1 address and stores it to value
        address = value + OFFSET2; // Adds offset 2 to the pointer stored in the base address
		ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0); // Reads the pointer stored in the offset 2 address and stores it to value
        address = value + OFFSET3; // Adds offset 3 to the pointer stored in the base address
		ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0); // Reads the pointer stored in the offset 3 address and stores it to value
        address = value + OFFSET4; // Adds offset 4 to the pointer stored in the base address
        ReadProcessMemory(phandle,(void*)address,&value,sizeof(value),0); // Reads the battery value from the pointer(offset 4 address)
        
        printf("G933 Battery Level = %d\n", value); // Prints the battery value
        
        FILE *f = fopen("batteryLevel.txt", "w"); // Opens file "batteryLevel.txt" for writing
        if (f == NULL){ // If not able to open file with write flag exits the program with code 1
            printf("Error opening file!\n");
            exit(1);
        }
        fprintf(f, "%d", value); // Writes the battery value to the txt file
        fclose(f); // Closes the txt file
        Sleep(5000); // Wait for 5 seconds
    }
    return 0;
}

//Function to grab module base address
UINT_PTR dwGetModuleBaseAddress(DWORD dwProcID, TCHAR *szModuleName)
{
    UINT_PTR dwModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID); //Get a snapshot of the module info
    if (hSnapshot != INVALID_HANDLE_VALUE) //Making sure a good result is returned
    {
    	//Define memory to store resultsf
        MODULEENTRY32 ModuleEntry32;
        ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
        
        //Sorting
        if (Module32First(hSnapshot, &ModuleEntry32))
        {
            do
            {
                if (_tcsicmp(ModuleEntry32.szModule, szModuleName) == 0)
                {
                    dwModuleBaseAddress = (UINT_PTR) ModuleEntry32.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnapshot, &ModuleEntry32));
        }
        CloseHandle(hSnapshot);
    }
    return dwModuleBaseAddress;
}
