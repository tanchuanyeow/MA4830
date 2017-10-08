#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char s[10];
float vel,height,theta;
float g = 9.81;
float launch_vel[5];
float launch_ang[5];
float launch_height[5];
float distance1[5]; //to store range of distance based on range of velocity
float distance2[5]; //to store range of distance based on range of angle
float distance3[5]; //to store range of distance based on range of height

float calculation (float v,float a,float h) // v is input of mag of vel, a is input of angle, h is input of height
{
    float z,d;
    a = a * 3.141592654 / 180;
    //printf("%f\n", sin(a));
    z = 1 + sqrt(1 + 2 * g * h / ( v * v * sin(a) * sin(a)));
    //printf("%f\n", z);
    d = v * v / (2*g) * z * sin(2*a);
    return d;
}

/*void velrange_cal(float start,float end)//auto calculate 5 samples of range of values of velocity magnitude
{
    int range = 1;
    for(range=1;range<=3;range++)
    {
        launch_vel[range]= launch_vel[range-1]+((end-start)/4);
    }
}
void angrange_cal(float start,float end)//auto calculate 5 samples of range of values of launch angle
{
    int range = 1;
    for(range=1;range<=3;range++)
    {
        launch_ang[range]= launch_ang[range-1]+((end-start)/4);
    }
}
void heightrange_cal(float start,float end)//auto calculate 5 samples of range of values of launch height
{
    int range = 1;
    for(range=1;range<=3;range++)
    {
        launch_height[range]= launch_height[range-1]+((end-start)/4);
    }
}*/
void drange_cal() //auto calculate 5 samples of range of distance based on different kind of range input
{
    int count;
    for(count=0;count<5;count++)
    {
        distance1[count]=calculation(launch_vel[count],theta,height);
        distance2[count]=calculation(vel,launch_ang[count],height);
        distance3[count]=calculation(vel,theta,launch_height[count]);
    }
}
void velocity_table()
{
    printf("Range of distance from range of velocity\n");
    printf("velocity\t%f\t%f\t%f\t%f\t%f\n",launch_vel[0],launch_vel[1],launch_vel[2],launch_vel[3],launch_vel[4]);
    printf("angle   \t%f\t%f\t%f\t%f\t%f\n",theta,theta,theta,theta,theta);
    printf("height  \t%f\t%f\t%f\t%f\t%f\n",height,height,height,height,height);
    printf("Distance\t%f\t%f\t%f\t%f\t%f\n",distance1[0],distance1[1],distance1[2],distance1[3],distance1[4]);
}
void angular_table()
{
    printf("Range of distance from range of velocity\n");
    printf("velocity\t%f\t%f\t%f\t%f\t%f\n",vel,vel,vel,vel,vel);
    printf("angle   \t%f\t%f\t%f\t%f\t%f\n",launch_ang[0],launch_ang[1],launch_ang[2],launch_ang[3],launch_ang[4]);
    printf("height  \t%f\t%f\t%f\t%f\t%f\n",height,height,height,height,height);
    printf("Distance\t%f\t%f\t%f\t%f\t%f\n",distance2[0],distance2[1],distance2[2],distance2[3],distance2[4]);
}
void height_table()
{
    printf("Range of distance from range of height\n");
    printf("velocity\t%f\t%f\t%f\t%f\t%f\n",vel,vel,vel,vel,vel);
    printf("angle   \t%f\t%f\t%f\t%f\t%f\n",theta,theta,theta,theta,theta);
    printf("height  \t%f\t%f\t%f\t%f\t%f\n",launch_height[0],launch_height[1],launch_height[2],launch_height[3],launch_height[4]);
    printf("Distance\t%f\t%f\t%f\t%f\t%f\n",distance1[0],distance1[1],distance1[2],distance1[3],distance1[4]);
}

float checkInput(char input[])
{
    int i;

    for (i=0; i < strlen(input); i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            // check if it can be converted to a digit
        }
        else {
            if (input[i] == '-' && i == 0) {
                // it is a negative sign
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

int main()
{
    char respond;
    while(1)
    {
        //Single value input and output
        printf("This program is to compute the trajectory of a projectile.\n");

        printf("Enter the magnitude of launch velocity v: ");
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
                printf("Enter the magnitude of launch velocity v: ");
                scanf("%s",&s);
        }
        vel = checkInput(s);
        printf("Initial velocity: %f m/s\n", vel);
        fflush(stdin);

        printf("Enter launch angle theta in degree: ");
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
                printf("Enter launch angle theta in degree: ");
                scanf("%s",&s);
        }
        theta = checkInput(s);
        printf("Projectile angle in degree: %f\n", theta);
        fflush(stdin);

        printf("Enter the magnitude of launch height y0: ");
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
                printf("Enter the magnitude of launch height y0: ");
                scanf("%s",&s);
        }
        height = checkInput(s);
        printf("launch height y0: %f m\n", height);
        fflush(stdin);

        printf("The total horizontal distance traveled by the projectile is %f\n", calculation(vel,theta,height));

        //Range of value of input and output
        printf("Enter 5 values of launch velocity: ");
        scanf("%f %f %f %f %f",&launch_vel[0],&launch_vel[1],&launch_vel[2],&launch_vel[3],&launch_vel[4]);
        fflush(stdin);
        printf("Enter 5 values of launch angle: ");
        scanf("%f %f %f %f %f",&launch_ang[0],&launch_ang[1],&launch_ang[2],&launch_ang[3],&launch_ang[4]);
        fflush(stdin);
        printf("Enter 5 values of launch height: ");
        scanf("%f %f %f %f %f",&launch_height[0],&launch_height[1],&launch_height[2],&launch_height[3],&launch_height[4]);
        fflush(stdin);
        drange_cal();
        velocity_table();
        angular_table();
        height_table();

        //Ask for another input again or terminate the program
        printf("Continue?(y/n) ");
        fflush(stdin);
        scanf("%c",&respond);
        while(respond!='y' && respond!='n')
        {
            printf("Please press the correct key\n");
            printf("Continue? dont key wrong again! (y/n)");
            scanf("%c",&respond);
            if(respond=='n')
            {
                printf("Program terminated");
                return 0;
            }
            else if(respond=='y')
                break;
        }
        if(respond=='n')
        break;
    }
    printf("Program terminated");
    return 1;
}
