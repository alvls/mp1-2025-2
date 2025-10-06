#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int main(void) {
    int back_s = 5;
    int side_s = 15;
    int door_s = 100;
    int shelf_s = 15;
    int DSP, DVP, wood;
    int h, d, w, weight;
    printf("enter h, d, w in mm, DSP, DVP and wood density");
    scanf("%d %d %d %d %d %d", &h, &d, &w, &DSP, &DVP, &wood);
    weight = back_s * h * w * DVP + side_s * 2 * DSP * h * d + 15 * DSP * w * d + h * w * door_s + shelf_s * w * d * (h / (400 + shelf_s));
    printf("weight = %d", weight);
    return 0;
}