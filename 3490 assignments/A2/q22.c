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

//finds the farthest point from p1 and p2 
//creates triangle between the 3 points
//all points outside the triangle are saved into leftAbove or rightAbove
//recursively call to repeat steps 1-3 untill all hull points are found
void findHull(struct Point points[], struct Point p1, struct Point p2, int count, int side, struct Point *hullPoints){
    
    //if array is empty break out of recursion
    if(count == 0){
        return;
    }

    struct Point leftAbove[count-1];
    struct Point rightAbove[count-1];

    int leftCounter = 0;
    int rightCounter = 0;

    double maxD = 0;
    double dist;
    int extremePoint;

    //find the point the farthest from the leftmost and rightmost points
    for(int i = 0; i < count; i++){
        dist = distanceCompare(p1, points[i]) + distanceCompare(p2, points[i]);
        if(dist > maxD){
            maxD = dist;
            extremePoint = i;
        }
    }

    //add hull point index to hullpoint array
    if(counter == size){
        size = size * 2;
        hullPoints = (struct Point*) realloc(hullPoints, sizeof(struct Point)*size);
    }
    hullPoints[counter] = points[extremePoint];
    counter = counter + 1;
    
    //side 1 for points above initial line between leftmost and rightmost points
    //side 0 for points below initial line between leftmost and rightmost points
    if(side == 1){
        //draw line between found hull point and p1 and p2 creating a triangle
        //points to the left of the triangle are added to leftAbove
        //points to the right of the triangle are added to rightAbove
        for(int i = 0; i < count; i++){
            //line from p1 to hull point
            if(orientation(p1,points[extremePoint],points[i]) == 1){
                leftAbove[leftCounter] = points[i];
                leftCounter = leftCounter + 1;
            }
            //line from hull point to p2
            if(orientation(points[extremePoint],p2,points[i]) == 1){
                rightAbove[rightCounter] = points[i];
                rightCounter = rightCounter + 1;
            }
        }
    }
    else{
        //draws line between hull point and p1 and p2 making a triangle
        //all points below the line from p1 to hull point go into leftAbove
        //all points below the line from hull to p2 go into rightAbove
        //all points within the triangle are discarded
        for(int i = 0; i < count; i++){
            if(orientation(p1,points[extremePoint],points[i]) == 2){
                leftAbove[leftCounter] = points[i];
                leftCounter = leftCounter + 1;
            }
            if(orientation(points[extremePoint],p2,points[i]) == 2){
                rightAbove[rightCounter] = points[i];
                rightCounter = rightCounter + 1;
            }
        }
    }

    //recursive calls to find next hull points
    findHull(leftAbove,p1,points[extremePoint],leftCounter, side, hullPoints);
    findHull(rightAbove,points[extremePoint],p2,rightCounter, side, hullPoints);
}


//finds all hull points using quick hull divide and conquer recursive method
void quickhull(struct Point points[], int n, struct Point *hullPoints){

    if(n < 3){
        return;
    }

    counter = 0;

    struct Point leftMost;
    struct Point rightMost;

    struct Point above[n];
    struct Point below[n];

    int belowCounter = 0;
    int aboveCounter = 0;
    
    leftMost.x = FLT_MAX;
    rightMost.x = -FLT_MAX;

    //find rightmost and leftmost points
    for (int i = 0; i < n; i++) {
        if (points[i].x < leftMost.x) {
            leftMost = points[i];
        }
        if (points[i].x > rightMost.x) {
            rightMost = points[i];
        }
    }

    //draw line between rightmost and leftmost point
    //put all points bellow line in below 
    //put all points above line in above
    for(int i = 0; i < n; i++){
        if(orientation(leftMost,rightMost,points[i]) == 1){
            below[belowCounter] = points[i];
            belowCounter = belowCounter + 1;
        }
        else{
            above[aboveCounter] = points[i];
            aboveCounter = aboveCounter + 1;
        }
    }

    //recursive calls to find hull points
    findHull(below, leftMost, rightMost, belowCounter, 1, hullPoints);
    findHull(above, rightMost, leftMost, aboveCounter, 0, hullPoints);

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

    printf("A Divide and Conquer program for the shortest path around\n");
    struct Point *convexHullDivide = malloc(sizeof(struct Point)*n);
    
    clock_t start = clock();
    quickhull(P,n,convexHullDivide);
    clock_t stop = clock();
    printf("Time for computing hull: %fs\n", (double)(stop - start)/CLOCKS_PER_SEC);

    
    printf("Extreme points in data set\n");
    for(int i = 0; i < counter; i++){
        printf("(%.1f, %.1f)\n", convexHullDivide[i].x, convexHullDivide[i].y);
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

    findPath(convexHullDivide,counter,p1,p2);

    fclose(file);

    free(convexHullDivide);

    return 0;
}