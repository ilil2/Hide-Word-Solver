#include "main_dataset.h"

int main(int argc, char **argv)
{
    if (argc < 4)
	{
		errx(400, "The number of argment is invalid.");
	}

	for (char j = 'A'; j <= 'Z'; j++)
	{
		// {directory/text_to_add} {nb_file} {nb_per_csv} {char}
		char buffer[100];
		printf("File : %c\n", j);
		// Convert image into csv file
		for (int i = 0; i < atoi(argv[2]); i++)
		{
			sprintf(buffer, "../../../../16x16/%c/%i.jpg", j, i);
			printf("\tConvert file: %i\n", i);
			add_to_dataset(buffer, i / atoi(argv[3]), j);
		}
	}
}
