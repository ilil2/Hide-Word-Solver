#include "main_dataset.h"

int main(int argc, char **argv)
{
	// {nb_file} {nb_per_csv} {nb_letter}

    if (argc < 4)
	{
		errx(400, "The number of argment is invalid.");
	}

	int nb_file = atoi(argv[1]);
	int nb_per_csv = atoi(argv[2]);
	int nb_letter = atoi(argv[3]);

	for (char j = 'A'; j <= 'Z'; j++)
	{
		char buffer[100];
		printf("File : %c\n", j);
		// Convert train upper letter image into csv file
		for (int i = 0; i < nb_file; i++)
		{
			sprintf(buffer, "../../../../16x16_test/%c/%i.jpg", j, i);
			printf("\tConvert train file: %i\n", i);
			add_to_dataset(buffer, i / nb_per_csv, j, 0);
		}

		char buffer2[100];
		// Convert test upper letter image into csv file
		for (int i = nb_file; i <= nb_letter; i++)
		{
			sprintf(buffer2, "../../../../16x16_test/%c/%i.jpg", j, i);
			printf("\tConvert test file: %i\n", i);
			add_to_dataset(buffer2, i / nb_per_csv, j, 1);
		}
	}

	for (char j = 'a'; j <= 'z'; j++)
	{
		char buffer[100];
		printf("File : _%c\n", j);
		// Convert train lower letter image into csv file
		for (int i = 0; i < nb_file; i++)
		{
			sprintf(buffer, "../../../../16x16_test/_%c/%i.jpg", j, i);
			printf("\tConvert train file: %i\n", i);
			add_to_dataset(buffer, i / nb_per_csv, j, 0);
		}

		char buffer2[100];
		// Convert test lower letter image into csv file
		for (int i = nb_file; i <= nb_letter; i++)
		{
			sprintf(buffer2, "../../../../16x16_test/_%c/%i.jpg", j, i);
			printf("\tConvert test file: %i\n", i);
			add_to_dataset(buffer2, i / nb_per_csv, j, 1);
		}
	}
}
