#include <time.h>
#include <iostream>

using namespace std;

int nextStep(bool** locationMap, int* currentStep, int* coordinateX, int* coordinateY, int* targets, int height, int width) {
    int steps;
    float value = (*currentStep + 1.0) / 2.0;
    if ((value - (int)value) > 0.0) {
        steps = (int)value + 1;
    }
    int stepSide;
    int tempForDirection = *currentStep % 4;
    if (tempForDirection == 1) {
        stepSide = 2;
    }
    else if (tempForDirection == 2) {
        stepSide = 3;
    }
    else if (tempForDirection == 3) {
        stepSide = 1;
    }
    else {
        stepSide = 0;
    }
    (*currentStep)++;
    for (int i = 0; i < steps; i++)
        if (stepSide == 0) {
            if ((*coordinateY + 1) < height)
            {
                *coordinateY = *coordinateY + 1;
                if (locationMap[*coordinateX][*coordinateY] == 1)
                    (*targets)++;
            }
            else
                return -1;
        }
        else if (stepSide == 1) {
            if ((int)(*coordinateY - 1) >= 0) {
                *coordinateY = *coordinateY - 1;
                if (locationMap[*coordinateX][*coordinateY] == 1)  {
                    (*targets)++;
                }
            }
            else
                return -1;
        }
        else if (stepSide == 2)  {
            if ((int)(*coordinateX - 1) >= 0) {
                *coordinateX = *coordinateX - 1;
                if (locationMap[*coordinateX][*coordinateY] == 1)
                {
                    (*targets)++;
                }
            }
            else
                return -1;
        }
        else if (stepSide == 3)
        {
            if ((*coordinateX + 1) < width)
            {
                *coordinateX = *coordinateX + 1;
                if (locationMap[*coordinateX][*coordinateY] == 1)
                {
                    (*targets)++;
                }
            }
            else
                return -1;
        }
    return 0;
}

int main(int argc, char *argv[], char *enpv[])
{
    int width = 6, height = 6, mode = 2;
    bool** locationMap = (bool**)malloc(height * sizeof(bool*));
    for (int i = 0; i < height; ++i)
        locationMap[i] = (bool*)malloc(width);
    srand(time(NULL));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (mode == 1) {
                if ((i + j) % 2 == 0 and i > 0 and j < width - 1)
                    locationMap[i][j] = 1;
                else if ((i + j) % 2 == 0 and i == 0 and j > 1)
                    locationMap[i][j] = 1;
                else if (i == 0 and j == 5 or i == 4 and j == 5 or i == 5 and j == 1)
                    locationMap[i][j] = 1;
                else
                    locationMap[i][j] = 0;
            }
            else if (mode == 2) {
                locationMap[i][j] = rand() % 2;
            }
            printf("%d ", locationMap[i][j]);
        }
        cout << "\n";
    }

    int randomCoordinateX = rand() % width, randomCoordinateY = rand() % height;
    cout << "The way of the scout "
         << "\n" << randomCoordinateX << " " << randomCoordinateY << " ->";
    int currentStep = 0;
    int targets = 0;
    if (locationMap[randomCoordinateX][randomCoordinateY] == 1)
    {
        targets++;
    }
    int coordinateX = randomCoordinateX, coordinateY = randomCoordinateY;

    while (!nextStep(locationMap, &currentStep, &coordinateX, &coordinateY, &targets, height, width))
    {
        printf(" %d %d ->", coordinateX, coordinateY);
    }

    printf("Scout found  %d targets\n", targets);
    return 0;
}
