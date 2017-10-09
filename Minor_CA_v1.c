#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char s[10];
const string order[5]
order[0] = "first";
order[1] = "Second";
order[2] = "Third";
order[3] = "Fourth";
order[4] = "Fifth";
int value:
float vel,height,theta;
float g = 9.81;
float range[5];
float distance[5]; //to store range of distance based on range of velocity

void init() //to initialize all the array and other variable as 0 after every calculation.
{
    int count1;
    for(count1=0;count<5;count++)
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

void drange_cal_vel() //calculate the distance base on range of value of velocity and printed out in table form
{
    int count;
    printf("Range of distance from range of velocity\n");
    printf("velocity\tangle\theight\tdistance\n");
    for(count=0;count<5;count++)
    {
        distance[count]=calculation(launch_vel[count],theta,height);
        printf("%f\t%f\t%f\t%f\n",launch_vel[i],theta,height,distance[i]);
        //distance[count]=calculation(vel,launch_ang[count],height);
        //distance[count]=calculation(vel,theta,launch_height[count]);
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
   
    printf("How many value you want to key in? (max 5 values): ");
    scanf("%d",&value);
    while(value>5)
    {
        printf("Please key the suitable value\n");
        scanf("%d",&value);
    }
    
    for(z=0;z<value,z++)
    {
        printf("Please key in %c value of velocity: ",&order[z]);
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
            printf("Please key in the correct value of velocity: ");
            scanf("%s",&s);
        }
        range[z] = checkInput(s);
    printf("Initial velocity: %f m/s\n", range[z]);
    fflush(stdin);
    }
    
    printf("Please key in the angle: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of angle: ");
        scanf("%s",&s);
    }
    theta = checkInput(s);
    printf("Initial angle: %f m/s\n", theta);
    fflush(stdin);
    
    printf("Please key in the height y0: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of height y0: ");
        scanf("%s",&s);
    }
    height = checkInput(s);
    printf("launch height y0: %f m\n", height);
    fflush(stdin);
    
    drange_cal_vel(); 
}

void anglecompile()
{
    int y;
   
    printf("How many value you want to key in? (max 5 values): ");
    scanf("%d",&value);
    while(value>5||value=0)
    {
        printf("Please key the suitable value\n");
        scanf("%d",&value);
    }
    
    for(y=0;y<value,y++)
    {
        printf("Please key in %c value of angle: ",&order[y]);
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
            printf("Please key in the correct value of angle v: ");
            scanf("%s",&s);
        }
        range[y] = checkInput(s);
    printf("Initial angle: %f m/s\n", range[y]);
    fflush(stdin);
    }
    
    printf("Please key in the velocity: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of velocity v: ");
        scanf("%s",&s);
    }
    vel = checkInput(s);
    printf("Initial velocity: %f m/s\n", vel);
    fflush(stdin);
    
    printf("Please key in the height y0: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of launch height y0: ");
        scanf("%s",&s);
    }
    height = checkInput(s);
    printf("launch height y0: %f m\n", height);
    fflush(stdin);
    
    drange_cal_vel();    
}

void heightcompile()
{
    int x;
   
    printf("How many value you want to key in? (max 5 values): ");
    scanf("%d",&value);
    while(value>5)
    {
        printf("Please key the suitable value\n");
        scanf("%d",&value);
    }
    
    for(x=0;x<value,x++)
    {
        printf("Please key in %c value of angle: ",&order[x]);
        scanf("%s",&s);
        while (checkInput(s) == -1.0)
        {
            printf("Please key in the correct value of height y0: ");
            scanf("%s",&s);
        }
        range[x] = checkInput(s);
    printf("Initial angle: %f m/s\n", range[x]);
    fflush(stdin);
    }
    
    printf("Please key in the velocity: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of velocity v: ");
        scanf("%s",&s);
    }
    vel = checkInput(s);
    printf("Initial velocity: %f m/s\n", vel);
    fflush(stdin);
    
    printf("Please key in the launch angle: ");
    scanf("%s",&s);
    while (checkInput(s) == -1.0)
    {
        printf("Please key in the correct value of launch angle: ");
        scanf("%s",&s);
    }
    theta = checkInput(s);
    printf("launch angle: %f m\n", theta);
    fflush(stdin);
    
    drange_cal_vel();    
}

int main()
{
    char userchoice;
    char respond;
    while(1)
    {
        //Let user to choose the value they want to vary
        printf("Select the value you want to vary:(v for velocity, a for angle, h for height): ");
        scanf("%c",&userchoice);
        while(userchoice!='c'&&userchoice!='a'&&userchoice!='h')
        {
            printf("Please key the correct choice\n");
            scanf("%c",userchoice);
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
