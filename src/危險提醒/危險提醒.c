#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int main(void)
{ 
	int i;
	
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
	
	return 0;
}
	
