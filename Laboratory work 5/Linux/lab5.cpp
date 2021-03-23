#include <stdlib.h>
#include <unistd.h>
#include <random>
#include <mutex>
#include <iostream>
pthread_mutex_t m;

#define numberThreads 100
static pthread_t tid[numberThreads];
using namespace std;
struct taskArguments {
    bool** locationMap;
    int mapHeight;
    int mapWidth;
    int randomCoordinateX;
    int randomCoordinateY;
};

int nextStep(bool** locationMap, int* currentStep, int* coordinateX, int* coordinateY,  
	int* targets, int mapHeight, int mapWidth, struct taskArguments* tv) {
    int stepSize = ceil(((double)*currentStep + 1.1) / 2.1);
    int stepSide;
    int tempForDirection = *currentStep % 4;
    if (tempForDirection == 1) {
        stepSide = 3;
    } else if (tempForDirection == 2) {
        stepSide = 1;
    } else if (tempForDirection == 3) {
        stepSide = 2;
    } else {
        stepSide = 0;
    }
    (*currentStep)++;
    for (int i = 0; i < stepSize; ++i)
        if (stepSide == 0) {
            if ((*coordinateY + 1) < mapHeight) {
                *coordinateY = *coordinateY + 1;
                if (locationMap[*coordinateX][*coordinateY] == 1)
                    (*targets)++;
            } else
                return -1;
        }
        else if (stepSide == 1) {
            if ((int)(*coordinateY - 1) >= 0) {
                *coordinateY = *coordinateY - 1;
                if (locationMap[*coordinateX][*coordinateY] == 1) {
                    (*targets)++;
                }
            } else
                return -1;
        }
        else if (stepSide == 2) {
            if ((int)(*coordinateX - 1) >= 0) {
                *coordinateX = *coordinateX - 1;
                if (locationMap[*coordinateX][*coordinateY] == 1) {
                    (*targets)++;
                }
            } else
                return -1;
        }
        else if (stepSide == 3) {
            if ((*coordinateX + 1) < mapWidth) {
                *coordinateX = *coordinateX + 1;
                if (locationMap[*coordinateX][*coordinateY] == 1) {
                    (*targets)++;
                }
            } else
                return -1;
        }
    return 0;
}
void* findTargets(void* in)
{
    struct taskArguments* argsInFindMethod = (struct taskArguments*)in;
    argsInFindMethod->randomCoordinateX = rand() % argsInFindMethod->mapWidth % 20;
    argsInFindMethod->randomCoordinateY = rand() % argsInFindMethod->mapHeight % 20;
    cout << "Scout information:\npid=" << getpid() << "\ntid=" << pthread_self()
         << "\nStart point (" << argsInFindMethod->randomCoordinateX << "; "
         << argsInFindMethod->randomCoordinateY << ")\n";
    int currentStep = 0;
    int targets = 0;

    if (argsInFindMethod->locationMap[argsInFindMethod->randomCoordinateY][argsInFindMethod->randomCoordinateX]== 1){
        targets++;
    }

    int coordinateX = argsInFindMethod->randomCoordinateX,
           coordinateY = argsInFindMethod->randomCoordinateY;

    while (!nextStep(argsInFindMethod->locationMap, &currentStep, 
    	&coordinateX, &coordinateY, &targets, argsInFindMethod->mapHeight,
        argsInFindMethod->mapWidth, argsInFindMethod)) {}
    cout << "Scout " << pthread_self() << " found " << targets << " targets\n\n";
    delete argsInFindMethod;
    return 0;
}
int main()
{
    pthread_t tid[numberThreads];
    int mapWidth = 20, mapHeight = 20, mode = 2;
    bool** locationMap = (bool**)malloc(mapHeight * sizeof(bool*));
    for (int i = 0; i < mapHeight; ++i)
        locationMap[i] = (bool*)malloc(mapWidth);
    srand(time(NULL));
   
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (mode == 1) {
                if ((i + j) % 2 == 0 and i > 0 and j < mapWidth - 1)
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
        }
    }

    for (int currentThread = 0; currentThread < numberThreads; currentThread++) {
        taskArguments* args = (struct taskArguments*) malloc(sizeof(struct taskArguments));
        args->mapHeight = mapHeight;
        args->mapWidth = mapWidth;
        args->locationMap = locationMap;
        sleep(0.3);
        int status = pthread_create(&tid[currentThread], NULL, findTargets, (void*)args);
        if (status != 0)
            perror("pthread_create"), exit(EXIT_FAILURE);
    }

    for (int currentThread = 0; currentThread < numberThreads; currentThread++) {
        pthread_join(tid[currentThread], NULL);
    }
    for (int currentThread = 0; currentThread < mapHeight; currentThread++) {
        delete[] locationMap[currentThread];
    }

    return 0;
}

