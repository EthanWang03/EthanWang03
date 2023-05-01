/*
Ethan Wang
1184940
A2 cis 3490
feb 14th 2023
*/

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// A structure to represent a Point on a 2D plane
struct Point
{
    float x;
    float y;
};

int size = 4;
int counter = 0;

// https://www.desmos.com/calculator/r27ah3u1bg
//returns the distance from P1 to P2
float distanceCompare(struct Point P1, struct Point P2){
    return sqrt((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y));
}

//return 0 if points are collinear
//return 1 if point nextPoint is clockwise relative to points p1 and p2
//return 2 if point nextPoint is counter clockwise relative to points p1 and p2
int orientation(struct Point p1,struct Point p2,struct Point nextPoint) {
    float val = (p2.y - p1.y) * (nextPoint.x - p2.x) - (p2.x - p1.x) * (nextPoint.y - p2.y);

    //collinear
    if (val == 0){
        return 0;
    }
    //clockwise
    if(val > 0){
        return 1;
    }
    //counter clockwise
    else{
        return 2;
    }
}

//returns array with indexes of all hull points
//jarvis march brute force
int * convexHullBruteForce(struct Point points[], int n) {
    //There must be at least 3 points
    if (n < 3){
        return 0;
    }
    // Find the leftmost point
    int leftMost = 0;
    for (int i = 1; i < n; i++){
        if (points[i].x < points[leftMost].x){
            leftMost = i;
        }
    }

    int *extremePoints = (int*) malloc(sizeof(int)*size);

    //Start from leftmost point, keep moving counterclockwise
    //until reach the start point again
    int previousPoint = leftMost;
    int nextPoint;
    do {
        //find next point
        nextPoint = (previousPoint + 1) % n;

        //manually check each point to see if its part of the convex hull
        for (int i = 0; i < n; i++){
            //if point is part of convext hull
            if (orientation(points[previousPoint], points[i], points[nextPoint]) == 2){
                nextPoint = i;
            }
        }
        //Adds index of extreme point to array
        if(counter == size){
            size = size * 2;
            extremePoints = (int*) realloc(extremePoints, sizeof(int)*size);
        }
        extremePoints[counter] = nextPoint;
        counter = counter + 1;

        //new extreme point set to previous extreme point
        previousPoint = nextPoint;

    //stop when left most point is reached again
    } while (previousPoint != leftMost);

    return extremePoints;
}

//compare point a with point b to see who is closer to 0,0
int compare(const void * a, const void * b){
    
    struct Point *X_ptr_a;
    struct Point *X_ptr_b;
    struct Point zero = {0,0};

    X_ptr_a = (struct Point*)a;
    X_ptr_b = (struct Point*)b;

    //if a < b
    if(distanceCompare(zero, *X_ptr_a) < distanceCompare(zero, *X_ptr_b)){
        return -1;
    }
    //if a > b
    else if(distanceCompare(zero, *X_ptr_a) > distanceCompare(zero, *X_ptr_b)){
        return 1;
    }
    //if a == b
    else{
        return 0;
    }
}

//finds the shortest path from point start and point end
void findPath(struct Point *hullPoints, int numPoints, struct Point start, struct Point end){

    struct Point above[numPoints];
    struct Point below[numPoints];

    int belowCounter = 0;
    int aboveCounter = 0;

    float distance = 0;

    //draw line between start and end point
    //all points below line go into below 
    //all points above line go into above
    for(int i = 0; i < numPoints; i++){
        if(orientation(start,end,hullPoints[i]) == 1){
            below[belowCounter] = hullPoints[i];
            belowCounter = belowCounter + 1;
        }
        else if(orientation(start,end,hullPoints[i]) == 2){
            above[aboveCounter] = hullPoints[i];
            aboveCounter = aboveCounter + 1;
        }
    }

    //add end point
    below[belowCounter] = end;
    belowCounter = belowCounter + 1;

    above[aboveCounter] = end;
    aboveCounter = aboveCounter + 1;

    //sort by distance from 0,0
    qsort(below,belowCounter,sizeof(struct Point),compare);
    qsort(above,aboveCounter,sizeof(struct Point),compare);

    //if final element in array is end point path must be shortest path
    if(above[aboveCounter-1].x == end.x && above[aboveCounter-1].y == end.y){
        printf("(%.1f, %.1f)\n", start.x, start.y);
        distance = distanceCompare(start,above[0]);
        
        printf("(%.1f, %.1f)\n", above[0].x, above[0].y);
        for(int i = 1; i < aboveCounter; i++){
            printf("(%.1f, %.1f)\n", above[i].x, above[i].y);
            distance = distance + distanceCompare(above[i-1],above[i]);
        }
        
        printf("The number of points: %d\n", aboveCounter+1);
        printf("The distance: %.1f", distance);
    }
    else if(below[belowCounter-1].x == end.x && below[belowCounter-1].y == end.y){
        
        //print starting points
        printf("(%.1f, %.1f)\n", start.x, start.y);
        distance = distanceCompare(start,below[0]);

        printf("(%.1f, %.1f)\n", below[0].x, below[0].y);
        for(int i = 1; i < belowCounter; i++){
            printf("(%.1f, %.1f)\n", below[i].x, below[i].y);
            distance = distance + distanceCompare(below[i-1],below[i]);
        }

        printf("The number of points: %d\n", belowCounter+1);
        printf("The distance: %.1f\n", distance);
    }
}

int main(){
    FILE *file;
    file = fopen("Data_A2_Q2.txt","r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }
    struct Point P[30000];
    double i;
    int index = 0;
    while(i != EOF){
        i = fscanf(file, "  %f   %f", &P[index].x, &P[index].y);
        index = index + 1;
    }

    int n = sizeof(P)/sizeof(P[0]);

    struct Point p1; //= {145.7,517.0};
    struct Point p2; //= {5961.6,6274.5};
    
    float x;
    float y;

    printf("A Brute force program for the shortest path around\n");
    clock_t begin = clock();
    int *extremePoints = convexHullBruteForce(P, n);
    clock_t end = clock();

    printf("Time for computing hull: %fs\n", (double)(end - begin)/CLOCKS_PER_SEC);

    //struct Point convexHullBrute[counter];
    struct Point *convexHullBrute = malloc(sizeof(struct Point)*counter);

    printf("Extreme points in data set\n");
    for(int i = 0; i < counter; i++){
        convexHullBrute[i].x = P[extremePoints[i]].x;
        convexHullBrute[i].y = P[extremePoints[i]].y;
        printf("(%.1f, %.1f)\n", convexHullBrute[i].x, convexHullBrute[i].y);
    }
    printf("Ext Points: %d\n\n",counter);

    printf("Enter the x and y coordinates of s1: ");
    scanf(" %f %f", &x, &y);
    p1.x = x;
    p1.y = y;

    printf("\nEnter the x and y coordinates of s2: ");
    scanf(" %f %f", &x, &y);
    p2.x = x;
    p2.y = y;

    printf("\nshortest path around\n");

    findPath(convexHullBrute,counter,p1,p2);

    fclose(file);

    free(convexHullBrute);

    return 0;
}