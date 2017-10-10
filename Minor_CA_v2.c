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
int iteration;

float conversion(char input[]) { //check for the validity of value input
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
                printf("Invalid input! It contains non-digit character(s). Please input again.\n\n");
                return -1.0;
            }
        }
    }
    // it is likely input as integer, but we cast it to float
    return atof(input);
}

int checkLimit (char variable) {
    switch (variable) {
        case 'a':
            if(angle >= 0.0 && angle <90.0) {
                return 1;
            }
            else {
                printf("Angle should be within 0 to 90 degree. Please input again.\n\n");
                return 0;
            }
            break;
        case 'v':
            if (velocity > 0.0 && velocity <= 100) {
                return 1;
            }
            else {
                printf("Velocity should not be negative or too large. Please input again.\n\n");
                return 0;
            }
            break;
        case 'h':
            if (height >= 0) {
                return 1;
            }
            else {
                printf("Height should not be negative. Please input again.\n\n");
                return 0;
            }
    }
}

void singleInput(char* info1, char* info2, char background1, char background2) { // for fixed variable
    int i;
    char s[30];
    char* info[] = {info1, info2};
    char background[] = {background1, background2};

    for(i=0; i<2; i++) {
        do {
            printf("Input %s: ", info[i]);
            fflush(stdin);
            scanf("%s", &s);
        } while (conversion(s) == -1.0);

        switch (background[i]) {
            case 'a' :
                angle = conversion(s);
                if (!checkLimit('a')) {
                    i -= 1;
                    continue;
                }
                break;
            case 'h':
                height = conversion(s);
                if (!checkLimit('h')) {
                    i -= 1;
                    continue;
                }
                break;
            case 'v':
                velocity = conversion(s);
                if (!checkLimit('v')) {
                    i -= 1;
                    continue;
                }
                break;
        }
    }
}

void multiInput (char* info, char background) { //for manipulated variable
    int i;
    char s[30];

    printf("Varying parameter %s by inputting different values\n", info);
    printf("How many values you have? (Up to 5 values) ");
    scanf("%d", &iteration);
    while(iteration <0 && iteration > 5) {
        printf("Should not more than 5 values. Please input again.\n\n");
        printf("How many values you have? ");
        scanf("%d",&iteration);
    }
    for(i=0; i<iteration; i++) {
        do {
            fflush(stdin);
            printf("value %d: ", i+1);
            scanf("%s", &s);
        } while (conversion(s) == -1.0);
        varying[i] = conversion(s);
    }
}

float calculation (float v,float a,float h) { // v is input of mag of vel, a is input of angle, h is input of height
    float z,d;
    a = a * 3.141592654 / 180; //to convert degree into radian
    z = 1 + sqrt(1 + 2 * g * h / ( v * v * sin(a) * sin(a))); //z is to calculate the equation within the bracket first
    d = v * v / (2*g) * z * sin(2*a);
    return d;
}

void drange_cal() { //calculate the distance base on range of value of velocity and print them out in table form
    int i;
    printf("\nRange of distance from range of velocity\n");
    printf("velocity  angle     height    distance\n");
    for(i=0; i<iteration; i++) {
        if(varychoice=='0') {
            distance[i]=calculation(varying[i], angle, height);
            printf("%-10.2f %-10.2f %-10.2f %-10.2f\n", varying[i], angle, height, distance[i]);
        }
        else if(varychoice=='1') {
            distance[i]=calculation(velocity, varying[i], height);
            printf("%-10.2f %-10.2f %-10.2f %-10.2f\n", velocity, varying[i], height, distance[i]);
        }
        else {
            distance[i]=calculation(velocity, angle, varying[i]);
            printf("%-10.2f %-10.2f %-10.2f %-10.2f\n", velocity, angle, varying[i], distance[i]);
        }
    }
}

int main(void) {
    char s[30];
    printf("INSTRUCTION HERE\n");
    while (1) {
        do {
            fflush(stdin);
            printf("Select the variable you want to vary:(0 for velocity, 1 for angle, 2 for height): ");
            scanf("%c", &varychoice);
            fflush(stdin);
        } while(varychoice!='0' && varychoice!='1'&& varychoice!='2'); // make sure user only key in the correct information

        switch (varychoice) {
            case '0':
                singleInput("angle, a (degree)","height, h (m)", 'a', 'h');
                multiInput("velocity, v", 'v');
                break;
            case '1':
                singleInput("velocity, v (m/s)", "height, h (m)", 'v', 'h');
                multiInput("angle in degree, a", 'a');
                break;
            case '2':
                singleInput("velocity, v (m/s)", "angle, a (degree)", 'v', 'a');
                multiInput("height, h", 'h');
                break;
        }

        drange_cal();

        do {
            fflush(stdin);
            printf("Continue?(Y/n) ");
            scanf("%c",&respond);
            respond = tolower(respond);
            if (respond == 'n') return 0;
        } while(respond!='y');
        printf("\n");
    }
    return 0;
}
