#include "main_dataset.h"

int main(int argc, char **argv)
{
    if (argc < 4)
	{
		errx(400, "The number of argment is invalid.");
	}

    if (argc >= 5)
    {
		for (char j = 'A'; j <= 'Z'; j++)
		{
			// {directory/text_to_add} {nb_file} {nb_per_csv} {char}
			char buffer[100];
			printf("File : %c\n", j);
			for (int i = 0; i < atoi(argv[2]); i++)
			{
				sprintf(buffer, "../../../../16x16/%c/%i.jpg", j, i);
				printf("\tConvert file: %i\n", i);
				fflush(stdout);
				add_to_dataset(buffer, i / atoi(argv[3]), j);
			}
		}
    }
	else
	{
		//add_to_dataset(argv[1], argv[2]);
	}
}
