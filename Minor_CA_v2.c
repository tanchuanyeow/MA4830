#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float angle, height, velocity;
float varyTemp;
float varying[5];
char varyChoice, respond;
float distance[5];
float g = 9.81;
int iteration;

void init() {//to initialize all the array and other variable as 0 after every calculation.
    int i;
    for(i=0; i<5; i++) {
        varying[i] = 0;
        distance[i] = 0;
    }
    angle = 0;
    height = 0;
    velocity = 0;
    varyTemp = 0;
    varyChoice = '!';  // not to be the same with the intended input
    respond = '!';  // not to be the same with the intended input
}

float toFloat(char input[]) { //check for the validity of value input
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

int toInt(char input[]) { //check for the validity of value input and make sure user key in integer value
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
                printf("Seems like you are inputting floating point number. We need integer. Please input again.\n\n");
            }
            else {
                printf("Invalid input! It contains non-digit character(s). Please input again.\n\n");
                return -1;
            }
        }
    }
    return atoi(input);
}

char oneCharInput (char* input) {
    if (strlen(input) == 1) {
        return input[0];
    }
    else {
        printf("Seems like you are inputting a bunch of characters. Please input only one character.\n\n");
        return '!';
    }
}

int checkLimit (char variable, float check) {
    switch (variable) {
        case 'a':
            if(check > 0.0 && check < 90.0) {
                return 1;
            }
            else {
                printf("Angle should be within 0 to 90 degree. Please input again.\n\n");
                return 0;
            }
            break;
        case 'v':
            if (check > 0.0 && check <= 100.0) {
                return 1;
            }
            else {
                printf("Velocity should not be negative or too large. Please input again.\n\n");
                return 0;
            }
            break;
        case 'h':
            if (check >= 0.0) {
                return 1;
            }
            else {
                printf("Height should not be negative. Please input again.\n\n");
                return 0;
            }
            break;
        case 'i':
            check = (int)check;
            if (check > 0 && check <= 5) {
                return 1;
            }
            else {
                printf("The value should not be negative or larger than 5. Please input again.\n\n");
                return 0;
            }
            break;
    }
}

int repeatingValue (float element) {
    int i;

    for (i=0; i<iteration; i++) {
        if (element == varying[i]) {
            printf("You have keyed this value before. Please input different value to obtain better observation.\n\n");
            return 1;
        }
    }
    return 0;
}

void singleInput(char* info1, char* info2, char background1, char background2) { // for fixed variables
    int i;
    char s[30];
    char* info[] = {info1, info2};
    char background[] = {background1, background2};

    printf("Parameters %c and %c are maintained constant\n\n", background1, background2);

    for(i=0; i<2; i++) { //let user to input value of fixed variables one by one
        do {
            printf("Input %s: ", info[i]);
            fflush(stdin);
            scanf("%s", &s);
        } while (toFloat(s) == -1.0);

        switch (background[i]) {
            case 'a' :
                angle = toFloat(s);
                if (!checkLimit('a', angle)) {
                    i -= 1;
                    continue;
                }
                break;
            case 'h':
                height = toFloat(s);
                if (!checkLimit('h', height)) {
                    i -= 1;
                    continue;
                }
                break;
            case 'v':
                velocity = toFloat(s);
                if (!checkLimit('v', velocity)) {
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

    printf("\nVarying parameter, %s\n", info);

    do {  // let user to key in number of variable user have
        do {
            printf("How many values do you have? (Up to 5 values) ");
            fflush(stdin);
            scanf("%s", &s);
        } while (toInt(s) == -1);
        iteration = toInt(s);
    } while(!checkLimit('i', iteration));

    for(i=0; i<iteration; i++) { // let user to key in values of variable sequentially
        do {
            fflush(stdin);
            printf("value %d: ", i+1);
            scanf("%s", &s);
        } while (toFloat(s) == -1.0);
        varyTemp = toFloat(s);
        if (!checkLimit(background, varyTemp) || repeatingValue(varyTemp)) {
            i -= 1;
            continue;
        }
        else {
            varying[i] = varyTemp;
        }
    }
}

float calculation (float v, float a, float h) { // v is input of mag of vel, a is input of angle, h is input of height
    float z, d;
    a = a * 3.141592654 / 180; //to convert degree into radian
    z = 1 + sqrt(1 + 2 * g * h / ( v * v * sin(a) * sin(a))); //z is to calculate the equation within the bracket first
    d = v * v / (2*g) * z * sin(2*a);
    return d;
}

int compare (const void * a, const void * b) {
    // for sorting array use
    return ( *(int*)a - *(int*)b );
}

void rangeCalculation() { //calculate the distance base on range of value of velocity and print them out in table form
    int i;

    qsort (varying, iteration, sizeof(float), compare);  // to sort the different values input by user

    printf("\nTabulating in the table below...\n\n");
    printf("-----------------------------------------------------\n");
    printf("velocity    angle       height      distance\n");
    printf("-----------------------------------------------------\n");
    for(i=0; i<iteration; i++) {
        if(varyChoice=='0') {
            distance[i]=calculation(varying[i], angle, height);
            printf("%-11.2f %-11.2f %-11.2f %-11.2f\n", varying[i], angle, height, distance[i]);
        }
        else if(varyChoice=='1') {
            distance[i]=calculation(velocity, varying[i], height);
            printf("%-11.2f %-11.2f %-11.2f %-11.2f\n", velocity, varying[i], height, distance[i]);
        }
        else {
            distance[i]=calculation(velocity, angle, varying[i]);
            printf("%-11.2f %-11.2f %-11.2f %-11.2f\n", velocity, angle, varying[i], distance[i]);
        }
    }
}

int main(void) {
    char s[30];
    printf("********************\n");
    printf("********************\n\n");
    printf("This program is to compute the Trajectory of A Projectile\n");
    printf("The formula to calculate the horizontal distance travelled by the projectile, d has been derived.\n");
    printf("By inputting initial velocity, projectile height and projectile angle,\n");
    printf("while taking gravitational accelaration,g as 9.81 ms^-2\n");
    printf("the distance, d can be computed.\n\n");

    printf("In this program, you could observe the trajectory of the projectile,\n");
    printf("by maintaining two of the parameters constant,\n");
    printf("and varying the other parameter by inputting several values.\n");
    printf("All the results of parameters will be tabulated at the end of the program.\n\n");

    printf("Symbol and Unit of the parameters: (m -- metre) \n");
    printf("velocity, v -- m/s      height, h -- m\n");
    printf("angle, a -- degree      horizontal distance travelled, d -- m\n\n");

    printf("********************\n");
    printf("********************\n\n");

    while (1) {
        init();
        while(1) {
            fflush(stdin);
            printf("Select a parameter you want to vary\n(0 for velocity, 1 for projectile angle, 2 for height): ");
            scanf("%s", s);
            varyChoice = oneCharInput(s);  // make sure user only key in the correct information
            if (varyChoice < '3' && varyChoice >= '0') {
                break;
            }
            else {
                printf("Please choose among 0, 1 and 2.\n\n");
                continue;
            }
        }
        printf("\n");

        switch (varyChoice) {
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

        rangeCalculation();

        printf("\nYay!! Good Job!!\n");

        do {
            fflush(stdin);
            printf("Do you want to run the program again? (Y/n) ");
            scanf("%s", s);
            respond = tolower(oneCharInput(s));
        } while(!(respond == 'y' || respond == 'n'));

        if (respond == 'y') {
            printf("\n");
            continue;
        }
        if (respond == 'n') {
            break;
        }
    }
    printf("Program terminated. Thank you.\n\n");
    return 0;
}
