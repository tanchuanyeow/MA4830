#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char s[10];
const char *order[5] = {"first","Second","Third","Fourth","Fifth"};
int value;
float vel,height,theta;
const float g = 9.81;
float range[5];
float distance[5]; //to store range of distance based on range of velocity
char userchoice;

void init() //to initialize all the array and other variable as 0 after every calculation.
{
    int count1;
    for(count1=0;count1<5;count1++)
    {
            range[count1]=0;
            distance[count1]=0;
    }
    vel=0;
    height=0;
    theta=0;
    value=0;
}

float calculation (float v,float a,float h) // v is input of mag of vel, a is input of angle, h is input of height
{
    float z,d;
    a = a * 3.141592654 / 180; //to convert degree into radian
    z = 1 + sqrt(1 + 2 * g * h / ( v * v * sin(a) * sin(a))); //z is to calculation the equation within the bracket first
    d = v * v / (2*g) * z * sin(2*a);
    return d;
}

void drange_cal() //calculate the distance base on range of value of velocity and printed out in table form
{
    int count;
    printf("\nRange of distance from range of velocity\n");
    printf("velocity angle height distance\n");
    for(count=0;count<5;count++)
    {
        if(userchoice=='v')
        {
            distance[count]=calculation(range[count],theta,height);
            printf("%.2f\t%.2f\t%.2f\t%.2f\n",range[count],theta,height,distance[count]);
        }
        else if(userchoice=='a')
        {
            distance[count]=calculation(vel,range[count],height);
            printf("%.2f\t%.2f\t%.2f\t%.2f\n",vel,range[count],height,distance[count]);
        }
        else
        {
            distance[count]=calculation(vel,theta,range[count]);
            printf("%.2f\t%.2f\t%.2f\t%.2f\n",vel,theta,range[count],distance[count]);
        }

    }
}

/*void velocity_table()
{
    int j;
    printf("Range of distance from range of velocity\n");
    printf("velocity\tangle\theight\tdistance\n");
    for(j=0;j<5;j++)
        printf("%f\t%f\t%f\t%f\n",launch_vel[i],theta,height,distance[i]);
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
}*/

float checkInput(char input[]) //check for the validity of value input.
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

void velocitycompile()
{
    int z;

    printf("Please key in the constant angle: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of angle: ");
        scanf("%s",&s);
    }
    theta = checkInput(s);
    printf("Initial angle: %f degree\n", theta);
    fflush(stdin);

    printf("Please key in the constant height y0: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of height y0: ");
        scanf("%s",&s);
    }
    height = checkInput(s);
    printf("launch height y0: %f m\n", height);
    fflush(stdin);

    printf("How many value you want to key in for velocity v? (max 5 values): ");
    scanf("%d",&value);
    while(value>5)
    {
        printf("Please key the suitable value\n");
        scanf("%d",&value);
    }

    for(z=0;z<value;z++)
    {
        printf("Please key in %s value of velocity v: ",order[z]);
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
            printf("Please key in the correct value of velocity v: ");
            scanf("%s",&s);
        }
        range[z] = checkInput(s);
    printf("Initial velocity: %f m/s\n", range[z]);
    fflush(stdin);
    }

    drange_cal();
}

void anglecompile()
{
    int y;

    printf("Please key in the constant velocity v: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of velocity v: ");
        scanf("%s",&s);
    }
    vel = checkInput(s);
    printf("Initial velocity: %f m/s\n", vel);
    fflush(stdin);


    printf("Please key in the constant height y0: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of launch height y0: ");
        scanf("%s",&s);
    }
    height = checkInput(s);
    printf("launch height y0: %f m\n", height);
    fflush(stdin);
    printf("How many value you want to key in for launch angle? (max 5 values): ");
    scanf("%d",&value);
    while(value>5||value==0)
    {
        printf("Please key the suitable value\n");
        scanf("%d",&value);
    }

    for(y=0;y<value;y++)
    {
        printf("Please key in %s value of launch angle: ",order[y]);
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
            printf("Please key in the correct value of launch angle: ");
            scanf("%s",&s);
        }
        range[y] = checkInput(s);
    printf("Initial angle: %f degree\n", range[y]);
    fflush(stdin);
    }

    drange_cal();
}

void heightcompile()
{
    int x;

    printf("Please key in the constant velocity v: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of velocity v: ");
        scanf("%s",&s);
    }
    vel = checkInput(s);
    printf("Initial velocity: %f m/s\n", vel);
    fflush(stdin);

    printf("Please key in the constant launch angle: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of launch angle: ");
        scanf("%s",&s);
    }
    theta = checkInput(s);
    printf("launch angle: %f degree\n", theta);
    fflush(stdin);


    printf("How many value you want to key in for height y0? (max 5 values): ");
    scanf("%d",&value);
    while(value>5)
    {
        printf("Please key the suitable value\n");
        scanf("%d",&value);
    }

    for(x=0;x<value;x++)
    {
        printf("Please key in %s value of height y0: ",order[x]);
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
            printf("Please key in the correct value of height y0: ");
            scanf("%s",&s);
        }
        range[x] = checkInput(s);
    printf("Initial height: %f m\n", range[x]);
    fflush(stdin);
    }

    drange_cal();
}

int main()
{
    char respond;
    while(1)
    {
        //Let user to choose the value they want to vary
        init();
        printf("Select the value you want to vary:(v for velocity, a for angle, h for height): ");
        scanf("%c",&userchoice);
        fflush(stdin);
        while(userchoice!='v'&&userchoice!='a'&&userchoice!='h')
        {
            printf("Please key the correct choice ");
            scanf("%c",&userchoice);
            fflush(stdin);
        }
        switch(userchoice)
        {
            case 'v': velocitycompile();
                break;
            case 'a': anglecompile();
                break;
            case 'h': heightcompile();
                break;
        }

         //Ask for another input again or terminate the program
        /*printf("Continue?(y/n) ");
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
        break;*/
    }
    printf("Program terminated");
    return 1;
}
