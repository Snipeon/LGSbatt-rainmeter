#include <stdio.h>
#include <windows.h>

int main()
{
	int value, offno;
	UINT_PTR offset;
	char text[32] = {0};
	
	FILE *f = fopen("Offset.txt", "w");
	if (!f)
    {
        printf("Error opening file!\n");
		exit(1);
    }
    
	printf("Enter the base address offset:");
	scanf("%x", &offset);
	
	printf("Enter the number of pointer offsets:");
	scanf("%d", &value);
	fprintf(f, "%d\n%d\n", value, offset);
	
    
	for(offno = 0; offno < value - 1; offno++)
	{
		printf("Enter offset %d:", offno);
		scanf("%x", &offset);
		fprintf(f, "%d\n", offset);
	}
	
	printf("Enter offset %d:", offno);
	scanf("%x", &offset);
	fprintf(f, "%d", offset);
	
	fclose(f); 
	
	return 0;
}
