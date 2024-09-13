#include "../neural_network.h"
#include "../../Lib/lib.h"

int main(int argc, char **argv)
{
    if (argc < 3)
	{
		errx(400, "The number of argment is invalid.");
	}

    if (argc >= 5)
    {
		// {directory/text_to_add} {csv_file} {nb_file} {start_num} 
		char buffer[100];
		for (int i = atoi(argv[4]); i < atoi(argv[3]); i++)
		{
			buffer = {0};
			sprintf(buffer, "%s%i.jpg", argv[1], i);
			add_to_dataset(buffer, argv[2]);
		}
    }
	else
	{
		add_to_dataset(argv[1], argv[2]);
	}
}
