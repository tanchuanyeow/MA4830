#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float angle, height, velocity;
float varying[5];
char varychoice, respond;
float distance[5];
float g = 9.81;

float conversion(char input[]) { //check for the validity of value input.
    int i;

    for (i=0; i < strlen(input); i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            // check if it can be converted to a digit
            continue;
        }
        else {
            if (input[i] == '-' && i == 0) {
                continue;
            }
            else if (input[i] == '.' || input[i] == 'e' || input[i] == 'E') {
                // if they are one of the forms of floating point expressions
                return atof(input);
            }
            else {
                printf("Error! The input contains non-digit character(s).\n");
                return -1.0;
            }
        }
    }
    // it is likely input as integer, but we cast it to float
    return atof(input);
}

void singleInput(char info1[], char info2[], char background1, char background2) {
    int i;
    char *s[10];
    char *info[] = {info1, info2};
    char background[] = {background1, background2};

    for(i=0; i<2; i++) {
        printf("Input %s: ", info[i]);
        do {
            fflush(stdin);
            scanf("%s", &s);
            printf("%s\n", s);
        } while (conversion(s) == -1.0);

        switch (background[i]) {
            case 'a' :
                angle = conversion(s);
                break;
            case 'h':
                height = conversion(s);
                break;
            case 'v':
                velocity = conversion(s);
                break;
        }
    }
}

void multiInput (char info[], char background) {
    int i, iteration;
    char *s[10];

    printf("How many value you want to key in for %s? (max 5 values): ", info);
    scanf("%d", &iteration);
    while(iteration > 5) {
        printf("Please key the suitable value\n");
        scanf("%d",&iteration);
    }
    for(i=0; i<iteration; i++) {
        do {
            fflush(stdin);
            printf("value %d: ", i);
            scanf("%s", &s);
        } while (conversion(s) == -1.0);
        varying[i] = conversion(s);
    }
}

float calculation (float v,float a,float h) {// v is input of mag of vel, a is input of angle, h is input of height
    float z,d;
    a = a * 3.141592654 / 180; //to convert degree into radian
    z = 1 + sqrt(1 + 2 * g * h / ( v * v * sin(a) * sin(a))); //z is to calculation the equation within the bracket first
    d = v * v / (2*g) * z * sin(2*a);
    return d;
}

void drange_cal() { //calculate the distance base on range of value of velocity and printed out in table form
    int count;
    printf("\nRange of distance from range of velocity\n");
    printf("velocity  angle     height    distance\n");
    for(count=0; count<5; count++) {
        if(varychoice=='0') {
            distance[count]=calculation(varying[count], angle, height);
            printf("%-10.2f%-10.2f%-10.2f%-10.2f\n", varying[count], angle, height, distance[count]);
        }
        else if(varychoice=='1') {
            distance[count]=calculation(velocity, varying[count], height);
            printf("%-10.2f%-10.2f%-10.2f%-10.2f\n", velocity, varying[count], height, distance[count]);
        }
        else {
            distance[count]=calculation(velocity, angle, varying[count]);
            printf("%-10.2f%-10.2f%-10.2f%-10.2f\n", velocity, angle, varying[count], distance[count]);
        }
    }
}

int main(void) {
    char *s[10];
    while (1) {
        do {
            fflush(stdin);
            printf("Select the variable you want to vary:(0 for velocity, 1 for angle, 2 for height): ");
            scanf("%c", &varychoice);
            fflush(stdin);
        } while(varychoice!='0' && varychoice!='1'&& varychoice!='2'); // make sure user only key in the correct information

        switch (varychoice) {
            case '0':
                singleInput("angle in degree, a","height, h", 'h', 'a');
                multiInput("velocity, v", 'v');
                break;
            case '1':
                singleInput("velocity, v", "height, h", 'v', 'h');
                multiInput("angle in degree, a", 'a');
                break;
            case '2':
                singleInput("velocity, v", "angle in degree, a", 'v', 'a');
                multiInput("height, h", 'h');
                break;
        }

        //printf("velocity, %f\nheight, %f\nangle, %f\n", velocity, height, angle);

        drange_cal();

        //Ask for another input again or terminate the program
        do {
            fflush(stdin);
            printf("Continue?(Y/n) ");
            scanf("%c",&respond);
            respond = tolower(respond);
            if (respond == 'n') return 0;
        } while(respond!='y');

    }
    return 0;
}
