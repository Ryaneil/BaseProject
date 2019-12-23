#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int main(void)
{ 
	int i,cmd;
	
	printf("輸入1時模擬發生地震(輸入0時代表沒有發生):");
	scanf("%d", &cmd);
	
	if(cmd) {
	
	for (i=0; i<10; i++) {	 
		Beep(2093, 400);
	}
	for (i=0; i<20; i++) {	 
		Beep(2093, 300);
	}
	for (i=0; i<30; i++) {	 
		Beep(2093, 200);
	}
	for (i=0; i<40; i++) {	 
		Beep(2093, 100);
	}
	
	}
		
	return 0;
}
	
