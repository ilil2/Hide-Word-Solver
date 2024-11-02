#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "rotation.h"
#include <stdio.h>

double detectRotationAngle(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;

    double total_angle = 0;
    int count = 0;

    // Hough's transformation
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Uint32 pixel = *((Uint32*)image->pixels + y * width + x);
            
            if (pixel == SDL_MapRGB(image->format, 255, 255, 255))
			{
                for (int dy = -1; dy <= 1; ++dy)
                {
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        if (dy != 0 || dx != 0)
                        {
                            int nx = x + dx;
                            int ny = y + dy;

                            if (nx >= 0 && nx < width && ny >= 0
                                && ny < height)
                            {
                                Uint32 neighbor_pixel = 
                                    *((Uint32*)image->pixels + ny
                                    * width + nx);
                                if (neighbor_pixel ==
                                    SDL_MapRGB(image->format, 255, 255, 255))
                                {
                                    double angle = atan2(dy, dx)
                                        * (180.0 / M_PI);
                                    total_angle += angle;
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    double average_angle = count > 0 ? total_angle / count : 0;

    if (average_angle < 0)
        average_angle += 360;

    return 360 - average_angle;
}
