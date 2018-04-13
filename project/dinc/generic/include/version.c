#include <stdio.h>

void print_version(void) 
{
#ifdef DEBUG_MODE
	printf("Debug version: $REVISION_ID\n");
#else
	printf("Release version: $REVISION_ID\n");
#endif
	printf("Release Date: $RELEASE_DATE\n"
       		"\n"
       		"Copyright (C) Mobric Inc.\n");
}
