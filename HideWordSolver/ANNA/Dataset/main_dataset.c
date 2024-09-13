#include "../neural_network.h"

int main(int argc, char **argv)
{
    if (argc < 3)
	{
		errx(400, "The number of argment is invalid.");
	}

    if (argc >= 4)
    {
        if (argv[3][0] == '1')
        {
            
        }
        else
        {
            add_to_dataset(argv[1], argv[2]);
        }
        
    }
}
