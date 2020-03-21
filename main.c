#include <stdio.h>

void sort(double x[]){
    for(int i=0;i<(sizeof(x)-1);i++){
        for(int f=i;f<(sizeof(x));f++){
            if(x[i]<x[f]){
                double higher =x[f];
                double lower =x[i];
                x[i]=higher;
                x[f]=lower;
            }
        }
    }
    for(int z=0;z<(sizeof(x)-1);z++){
        printf("%lf ",x[z]);
    }
}

int main() {

    //VARIABLE DECLARATION
    FILE *laketemps;
    double sum[6] = {0, 0, 0, 0, 0, 0};
    double avgtemp[6] = {0, 0, 0, 0, 0, 0};
    double totalavgtemp = 0;
    //maxtemps-> row 0 for temp, row 1 for the lake it is, row 2 for the day it is.
    double maxavg, minavg, maxwarmtemp[3][1], maxcoldtemp[3][1];
    double warmestday[2][6], coldestday[2][6]= { {0,0,0,0,0,0}, { 10000, 10000, 10000, 10000, 10000, 10000}};
    char initials[6] = {'S', 'M', 'H', 'E', 'O', 'C'};
    double data[8][365];
    laketemps = fopen("glsea-temps2019_1024.txt","r"); //fix the directory

    //if the file doesnt exist or isnt in the right place, exit program
    if (laketemps == NULL) {
        printf("Cannot open file, does it exist?\n");
        return -1;
    }

    for (int i = 0; i < 365; i++) {
        //collect data from the file
        for (int j = 0; j < 8; j++) {
            fscanf(laketemps, "%lf", &data[j][i]);
        }
        //printf("%lf \n", data[1][i]);

        //calculate sum
        for (int j = 0; j < 6; j++) {
            sum[j] += data[j + 2][i];
            if(data[j+2][i]>warmestday[1][j]){
                warmestday[1][j]= data[j+2][i];
                warmestday[0][j] = i;
            }
            if(data[j+2][i]<coldestday[1][j]){
                coldestday[1][j]= data[j+2][i];
                coldestday[0][j] = i;
            }
        }
    }


    //calculate avg temp and total avg temp
    for (int i = 0; i < 6; i++) {
        maxavg = avgtemp[0];
        minavg = avgtemp[0];
        avgtemp[i] = sum[i] / 365;
        totalavgtemp += avgtemp[i];
        if (avgtemp[i] > maxavg) {
            maxavg = avgtemp[i];
        }
        if (avgtemp[i] < minavg) {
            minavg = avgtemp[i];
        }
    }
    totalavgtemp = totalavgtemp / 6;
    maxwarmtemp[0][0] = warmestday[1][0];
    maxcoldtemp[0][0] =  coldestday[1][0];
    //Find the warmest lake, and see which are above/below avg temp
    for (int i = 0; i < 6; i++) {
        if (avgtemp[i] > totalavgtemp) {
            printf("Lake %c is above the average temperature of all the lakes \n", initials[i]);
        } else if (avgtemp[i] < totalavgtemp) {
            printf("Lake %c is below the average temperature of all the lakes \n", initials[i]);
        }

        if(maxavg==avgtemp[i]){
            printf("The warmest lake is %c\n", initials[i]);
        }
        if(minavg==avgtemp[i]){
            printf("The coldest lake is %c\n", initials[i]);
        }
        printf("Warmest temperature for lake %c: %lf on day %lf \n", initials[i], warmestday[1][i], warmestday[0][i]+1);
        printf("Coldest temperature for lake %c: %lf on day %lf \n", initials[i], coldestday[1][i], coldestday[0][i]+1);

        if(warmestday[1][i]>maxwarmtemp[0][0]){
            maxwarmtemp[0][0] = warmestday[1][i];
            maxwarmtemp[1][0] = i;
            maxwarmtemp[2][0] = warmestday[0][i];
        }
        if(coldestday[1][i]<maxcoldtemp[0][0]) {
            maxcoldtemp[0][0] = coldestday[1][i];
            maxcoldtemp[1][0] = i;
            maxcoldtemp[2][0] = coldestday[0][i];
        }
    }
    int initial1 = maxwarmtemp[1][0];
    int initial2 = maxcoldtemp[1][0];
    printf("The warmest overall temperature is %lf at lake %c on day %lf\n",maxwarmtemp[0][0], initials[initial1], maxwarmtemp[2][0]+1);
    printf("The coldest overall temperature is %lf on multiple days in multiple lakes \n",maxcoldtemp[0][0]);

    double summersum[6] = {0,0,0,0,0,0};
    double summeravg[6] = {0,0,0,0,0,0};
    for(int i=171; i<265;i++){
        for (int j = 0; j < 6; j++) {
            summersum[j] += data[j + 2][i];
            }
        }
    for(int i=0;i<6;i++){
        summeravg[i] = summersum[i]/93;
        printf("%lf ", summeravg[i]);
    }
    printf("||||");
    sort(summeravg);




        return 0;
    }

