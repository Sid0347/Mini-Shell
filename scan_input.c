#include "header.h"

void scan_input(char *prompt, char *input_string)
{
	while(1)
	{
		printf("%s", prompt);
		scanf("%[^\n]", input_string);
		
	}
}
