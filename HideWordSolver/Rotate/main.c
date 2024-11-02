#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rotation.h"

int main(int argc, char *argv[]) 
{
    if (argc < 3) {
        printf("Usage: %s <image_path> <rotation_type> [angle]\n",
				argv[0]);
        return 1;
    }

    const char* image_path = argv[1];

    const char* rotation_type = argv[2];

    // Rotation manuelle
    if (strcmp(rotation_type, "manual") == 0) {
        if (argc < 4) {
            printf("Please provide an angle for manual rotation.\n");
            return 1;
        }
        float angle = atof(argv[3]);        
		manual_rotate(image_path, angle);
    }

    // Rotation automatique
    else if (strcmp(rotation_type, "auto") == 0) {
        auto_rotate(image_path);
    }

	//Erreur
    else {
        printf("Unknown rotation type: %s. Use 'manual' or 'auto'.\n",
				rotation_type);
        return 1;
    }

    return 0;
}
