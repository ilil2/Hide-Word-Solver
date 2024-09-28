#include "manual_rotation.h"
#include "display.h"

void manual_rotate(const char* image_path, float angle) {
    display_image(image_path, angle);
}
