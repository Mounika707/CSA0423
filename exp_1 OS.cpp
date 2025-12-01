#include <stdio.h>
#include <windows.h>

int main(){
	
	DWORD pid = GetCurrentProcessId();
	
	printf("Current Process ID: %lu\n", pid);
	printf("Parent Process ID : %lu\n", pid);
	
	return 0;
}