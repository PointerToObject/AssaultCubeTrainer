#include "mem.h"


DWORD GetProcId(const wchar_t* procName) { // create a function named get procid with a paramater of procName, what we will be using to compare strings to find our procID, returns a DWORD (unsigned long)
    DWORD procId = 0; //initilize to zero, will store procID later
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // get a snapshot of all the process running at the time the function is called, param TH32CS_SNAPPROCESS used for processes, 0 we dont need
    if (hSnap != INVALID_HANDLE_VALUE) { // checking if the handle is valid

        PROCESSENTRY32 procEntry; // initialize processentry32 struct (needed 
        procEntry.dwSize = sizeof(procEntry); // these functions (Process32First,Process32Next) won't work properly and will fail because they can't verify the structure's size and layout. 
        //It's like giving someone the dimensions of a container so they know how much to fill it.

        if (Process32First(hSnap, &procEntry)) { //&procEntry is a pointer to a PROCESSENTRY32 structure (line 9)
            //This function (Process32First) retrieves information about the first process in the snapshot and fills the procEntry structure with this information. 
            // This includes details like the process ID, the executable file name, etc.
            //If the function succeeds, it returns a nonzero value, and the code inside the if block will execute.
            //If the function fails(e.g., there are no processes in the snapshot), it returns zero, and the code inside the if block will not execute.
            do {//This loop continues to execute as long as Process32Next(hSnap, &procEntry) returns a nonzero value, indicating there are more processes to enumerate in the snapshot.

                if (!_wcsicmp(procEntry.szExeFile, procName)) { // The function _wcsicmp is used to compare two wide-character strings.  returns 0 if the strings are equal (ignoring case).
                    //procEntry.szExeFile is a snapshot, procName is the paramater i put in L"ac_client.exe"
                    procId = procEntry.th32ProcessID;
                    break;
                    //if those two match, the code in the if statement block will then execute, setting DWORD procId to procEntry.th32ProcessID then breaking the loop
                }

            } while (Process32Next(hSnap, &procEntry)); // do while looks nicer here, for loop looks cancer
            //for (; Process32Next(hSnap, &procEntry); ) {}

        }

    }
    CloseHandle(hSnap);
    return procId;
    // this will then close the handle and return procID
} // usage DWORD lol = GetProcId(L"something.exe");


uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    //initialize to zero for error checking
    uintptr_t modBaseAddr = 0;

    //get a handle to a snapshot of all modules
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

    //check if it's valid
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        //this struct holds the actual module information
        MODULEENTRY32 modEntry;

        //this is required for the function to work
        modEntry.dwSize = sizeof(modEntry);

        //If a module exists, get it's entry
        if (Module32First(hSnap, &modEntry))
        {
            //loop through the modules
            do
            {
                //compare the module name against ours
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    //copy the base address and break out of the loop
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }

                //each iteration we grab the next module entry
            } while (Module32Next(hSnap, &modEntry));
        }
    }

    //free the handle
    CloseHandle(hSnap);
    return modBaseAddr;
}


uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess) {
    DWORD oldprotect;
    VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    WriteProcessMemory(hProcess, dst, src, size, nullptr);
    VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}
void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProcess) {
    BYTE* nopArray = new BYTE[size];
    memset(nopArray, 0x90, size);

    PatchEx(dst, nopArray, size, hProcess);
    delete[] nopArray;
}




