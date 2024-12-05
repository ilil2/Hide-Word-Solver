#include "neural_network.h"

// Recognizes a letter of the alphabet using a neural network
// The first argument is the part of the program to be executed (reset, start or train)
// reset to reset model parameters
// start to begin character recognition
// train to train the AI with the number of images in the dataset as the second parameter and the number of threads to be used as the third parameter
int main(int argc, char** argv)
{
    int seed = 42;
    if (seed == -1)
    {
        srand(time(NULL));
    }
    else
    {
        srand(seed);
    }

    if(argc > 1)
    {
        if (strcomp(argv[1], "reset"))
        {
            printf("Resetting ANNA parameters...\n");

            reset_all();

            printf("ANNA's parameters have been reset.\n");
        }
        else if (strcomp(argv[1], "start"))
        {
            // ./ANNA start (directory) (grid_width) (grid_height) (word_nb)

            printf("ANNA's character recognition activated !\n");

            HyperParam* hp = malloc(sizeof(HyperParam));
            Param* p = NULL;
            Adam* a = NULL;
            Info* i = malloc(sizeof(Info));
            Var* v = malloc(sizeof(Var));

            load_layer(i);
            v->threads = 1;
            hp->dropout_rate = 0;

            ANNA* anna = malloc(sizeof(ANNA));
            anna->hp = hp;
            anna->p = p;
            anna->a = a;
            anna->i = i;
            anna->v = v;

            predict(anna, argv[2], atoi(argv[3]), atoi(argv[4]),
                atoi(argv[5]));
        }
        else if (strcomp(argv[1], "train"))
        {
            if (argc > 1)
            {
                size_t max_train_data = 2600;
                size_t max_test_data = 68068;
                size_t max_batch_nb = 90;

                HyperParam* hp = malloc(sizeof(HyperParam));
                Param* p;
                Adam* a;
                Info* i = malloc(sizeof(Info));
                Var* v = malloc(sizeof(Var));

                if (argc > 2)
                {
                    v->train_data = atoi(argv[2]);
                    if (v->train_data < 1 || v->train_data > max_train_data)
                    {
                        v->train_data = max_train_data;
                    }

                    if (argc > 3)
                    {
                        v->test_data = atoi(argv[3]);
                        if (v->test_data < 1 || v->test_data > max_test_data)
                        {
                            v->test_data = max_test_data;
                        }

                        if (argc > 4)
                        {
                            v->batch_nb = atoi(argv[4]);
                            if (v->batch_nb < 1 || v->batch_nb > max_batch_nb)
                            {
                                v->batch_nb = max_batch_nb;
                            }

                            if (argc > 5)
                            {
                                v->threads = atoi(argv[5]);
                                if (v->threads < 1)
                                {
                                    v->threads = 2;
                                }
                            }
                            else
                            {
                                v->threads = 2;
                            }
                        }
                        else
                        {
                            v->batch_nb = max_batch_nb;
                            v->threads = 2;
                        }
                    }
                    else
                    {
                        v->test_data = max_test_data;
                        v->batch_nb = max_batch_nb;
                        v->threads = 2;
                    }
                }
                else
                {
                    v->train_data = max_train_data;
                    v->test_data = max_test_data;
                    v->batch_nb = max_batch_nb;
                    v->threads = 2;
                }

                load_layer(i);
                a = init_adam(i);
                load_hyperparameter(hp, a, v);
                p = init_param(i, v, 0);
                load_parameter(p, i);

                ANNA* anna = malloc(sizeof(ANNA));
                anna->hp = hp;
                anna->p = p;
                anna->a = a;
                anna->i = i;
                anna->v = v;

                printf("ANNA's training start.\n");

                train(anna);

                free_all(anna);
            }
            else
            {
                err(1, "The number of images to be taken has not been "
                    "indicated.");
            }
        }
        else
        {
            err(1, "Incorrect argument");
        }
    }
    else
    {
        err(1, "The number of arguments is invalid.");
    }

    return 0;
}
