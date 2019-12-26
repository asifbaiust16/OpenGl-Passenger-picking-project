#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
float posx=350;
float posy=350;
float posz=0;
float lx=-1/sqrt(2);
float ly=-1/sqrt(2);
float lz=0;
float rx=-1/sqrt(2);
float ry=-1/sqrt(2);
float rz=0;
float ux=0;
float uy=0;
float uz=1;
struct point
{
    double x,y,z;
};
void drawAxes()
{
    if(drawaxes==1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);

            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);

            glVertex3f(0,0, 100);
            glVertex3f(0,0,-100);
        }
        glEnd();
    }
}

void drawGrid()
{
    int i;
    if(drawgrid==1)
    {
        glColor3f(0.6, 0.6, 0.6);	//grey
        glBegin(GL_LINES);
        {
            for(i=-8; i<=8; i++)
            {

                if(i==0)
                    continue;	//SKIP the MAIN axes

                //lines parallel to Y-axis
                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);

                //lines parallel to X-axis
                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
                //lines parallal to z axis

                //glVertex3f( 0, 90, i*10);
                //glVertex3f(0, -90, i*10);


            }
        }
        glEnd();
    }
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a,0);
        glVertex3f( a,-a,0);
        glVertex3f(-a,-a,0);
        glVertex3f(-a, a,0);
    }
    glEnd();
}

//draws a cube of side length 2a
void drawCube(double a)
{
    glBegin(GL_QUADS);
    {


        glVertex3f( a, a, a);
        glVertex3f( a,-a, a);
        glVertex3f(-a,-a, a);
        glVertex3f(-a, a, a);


        glVertex3f( a, a,-a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a, a,-a);


        glVertex3f( a, a, a);
        glVertex3f( a, a,-a);
        glVertex3f( a,-a,-a);
        glVertex3f( a,-a, a);


        glVertex3f(-a, a, a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);


        glVertex3f( a, a, a);
        glVertex3f( a, a,-a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a, a, a);


        glVertex3f( a,-a, a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
    }
    glEnd();
}
//draws a cylinder of given radius and height
void drawCylinder(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw quads using generated points
    for(i=0; i<segments; i++)
    {

        glBegin(GL_QUADS);
        {
            glVertex3f(points[i].x,points[i].y,height/2);
            glVertex3f(points[i+1].x,points[i+1].y,height/2);
            glVertex3f(points[i].x,points[i].y,-height/2);
            glVertex3f(points[i+1].x,points[i+1].y,-height/2);
        }
        glEnd();
    }
}
void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0; i<segments; i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
    //generate points
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0; i<segments; i++)
    {
        glBegin(GL_QUADS);
        {
            glVertex3f(points[i].x,points[i].y,90);
            glVertex3f(points[i+1].x,points[i+1].y,90);
            glVertex3f(points[i].x,points[i].y,-90);
            glVertex3f(points[i+1].x,points[i+1].y,-90);
        }
        glEnd();
    }
}
void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0; i<segments; i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}
void drawSphere(double radius,int slices,int stacks)
{
    struct point points[100][100];
    int i,j;
    double h,r;
    //generate points
    for(i=0; i<=stacks; i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));
        r=radius*cos(((double)i/(double)stacks)*(pi/2));
        for(j=0; j<=slices; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }
    }
    //draw quads using generated points
    for(i=0; i<stacks; i++)
    {
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        for(j=0; j<slices; j++)
        {
            glBegin(GL_QUADS);
            {
                //upper hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
            }
            glEnd();
        }
    }
}
double speed= 0;
double k=0;
double z=0;


void drawshade()

{
    // passanger shade floor
    glPushMatrix();
    {
        glScalef(3,.1,2);
        glColor3f(1,1,0);
        glTranslatef(60,0,-55);
        drawCube(20);
    }
    glPopMatrix();

    //back side tin
    glPushMatrix();
    {
        glScalef(3,1.5,1);
        glColor3f(0,1,1);
        glTranslatef(60,20,-140);
        glRotatef(90,0,0,1);
        drawSquare(20);
    }
    glPopMatrix();

    ///// upside tin
    glPushMatrix();
    {
        glScalef(3,1.5,1);
        glColor3f(1,0,0);
        glTranslatef(60,40,-130);
        glRotatef(90,1,0,0);
        drawSquare(25);
    }
    glPopMatrix();

    //pillar passanger shade
    glPushMatrix();
    {
        glScalef(3,1.5,1);
        glColor3f(0,1,0);
        glTranslatef(45,10,-110);
        glRotatef(90,1,0,0);
        drawCylinder(1,60,10);
    }
    glPopMatrix();

    //pillar passanger shade
    glPushMatrix();
    {
        glScalef(3,1.5,1);
        glColor3f(0,1,0);
        glTranslatef(75,10,-110);
        glRotatef(90,1,0,0);
        drawCylinder(1,60,10);
    }
    glPopMatrix();


//footpath

    /* glPushMatrix();
    {
        glScalef(3,.1,2);
        glColor3f(1,0,0);
        glTranslatef(60,0,55);
        drawCube(20);
    }
    glPopMatrix();
    */

}


void drawpassenger()
{


    glPushMatrix();
    {
        glTranslatef(175,22.5,-120);
        glScalef(2,.1,.3);
        glColor3f(0,1,0);
        drawCube(20);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glScalef(2,.5,1);
        glColor3f(0,0,1);
        glTranslatef(75,20,-120);
        glRotatef(90,1,0,0);
        drawCylinder(4,60,10);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glScalef(2,.5,1);
        glColor3f(0,0,1);
        glTranslatef(100,20,-120);
        glRotatef(90,1,0,0);
        drawCylinder(4,60,10);
    }
    glPopMatrix();


//passenger 1
glPushMatrix();
    {
        glTranslatef(0,0,z);

    glPushMatrix();
    {
        glTranslatef(175,10,-80);
        glScalef(1.5,1.5,1.5);

        glPushMatrix();
        {
            //head
            glScalef(1.5,1.5,1);
            glTranslatef(0,12,0);
            drawSphere(2,50,50);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //body
            glScalef(1.5,1.5,1);
            glTranslatef(0,5,0);
            drawSphere(4,50,50);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //neck
            glColor3f(1,1,0);
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-15);
            drawCylinder(1,5,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //leg
            glScalef(.8,1.5,.8);
            glColor3f(1,0,0);
            glRotatef(90,1,0,0);
            glTranslatef(-4,0,0);
            drawCylinder(1.5,5,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //leg
            glScalef(.8,1.5,.8);
            glColor3f(1,0,1);
            glRotatef(90,1,0,0);
            glTranslatef(4,0,0);
            drawCylinder(1.5,5,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //neck
            glColor3f(1,0,0);
            glScalef(4,.5,.5);
            glTranslatef(0,20,0);
            drawCube(2.5);
        }
        glPopMatrix();

    }
    glPopMatrix();
    }
    glPopMatrix();

    //passenger 2
    glPushMatrix();
    {
        glTranslatef(210,10,-80);
        glScalef(1.5,1.5,1.5);

        glPushMatrix();
        {
            //head
            glScalef(1.5,1.5,1);
            glTranslatef(0,12,0);
            drawSphere(2,50,50);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //body
            glScalef(1.5,1.5,1);
            glTranslatef(0,5,0);
            drawSphere(4,50,50);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //neck
            glColor3f(1,1,0);
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-15);
            drawCylinder(1,5,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //leg
            glScalef(.8,1.5,.8);
            glColor3f(1,0,0);
            glRotatef(90,1,0,0);
            glTranslatef(-4,0,0);
            drawCylinder(1.5,5,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //leg
            glScalef(.8,1.5,.8);
            glColor3f(1,0,1);
            glRotatef(90,1,0,0);
            glTranslatef(4,0,0);
            drawCylinder(1.5,5,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            //neck
            glColor3f(1,0,0);
            glScalef(4,.5,.5);
            glTranslatef(0,20,0);
            drawCube(2.5);
        }
        glPopMatrix();

    }
    glPopMatrix();


}

void drawroad()
{
    glPushMatrix();
    {
        glScalef(50,1,4);
        glColor3f(0,1,0);
        glRotatef(90,1,0,0);
        drawSquare(15);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(25,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-25,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(50,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-50,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(75,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-75,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(100,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-100,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(130,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-130,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(160,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-160,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(190,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-190,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(220,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-220,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(250,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-250,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(280,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-280,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(310,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-310,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(340,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-340,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(370,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-370,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(400,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-400,0,0);
        glScalef(4,1,1);
        glColor3f(1,1,1);
        drawCube(2);
    }
    glPopMatrix();

}
void drawcar()
{
    // left side Car

    glPushMatrix();
    {
        glTranslatef(k,0,0);
        glPushMatrix();
        {

            glScalef(2,.3,.5);
            glColor3f(1,0,0);
            glTranslatef(0,50,-65);
            drawCube(20);
        }
        glPopMatrix();

        // left side wheel
        glPushMatrix();
        {
            glColor3f(0,0,0);
            //glTranslatef(-speed,0,0);
            glTranslatef(-25,10,-32.5);
            //glRotatef(2*angle,0,0,1);
            drawCylinder(10,30,20);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor3f(0,0,0);
            //glTranslatef(-speed,0,0);
            glTranslatef(25,10,-32.5);
            //glRotatef(2*angle,0,0,1);
            drawCylinder(10,30,20);
        }
        glPopMatrix();
    }
    glPopMatrix();

    //right side car
    glPushMatrix();
    {
        glTranslatef(speed,0,0);
        glScalef(2,.3,.5);
        glColor3f(1,0,0);
        glTranslatef(0,50,65);
        drawCube(20);
    }
    glPopMatrix();
    //right side wheel
    glPushMatrix();
    {
        glColor3f(0,0,0);
        glTranslatef(speed,0,0);
        glTranslatef(-25,10,32.5);
        glRotatef(2*angle,0,0,-1);
        drawCylinder(10,30,20);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0,0,0);
        glTranslatef(speed,0,0);
        glTranslatef(25,10,32.5);
        glRotatef(2*angle,0,0,-1);
        drawCylinder(10,30,20);
    }
    glPopMatrix();


}

void minar()
{

    glPushMatrix();
    {
        glTranslatef(80,70,110);
        drawSphere(15,5,5);
    }
    glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(50,5,75);
        glScalef(.5,.8,.5);
        glPushMatrix();
        {
            glTranslatef(175,5,110);
            glColor3f(1,1,0);
            glScalef(2,.5,2);
            drawCube(10);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glColor3f(1,0,0);
            glTranslatef(175,25,110);
            glRotatef(90,1,0,0);
            glColor3f(0,1,1);
            drawCylinder(15,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glColor3f(1,0,0);
            glTranslatef(175,60,110);
            glRotatef(90,1,0,0);
            drawCylinder(13,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor3f(1,0,1);
            glTranslatef(175,80,110);
            glRotatef(90,1,0,0);
            drawCylinder(11,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(175,110,110);
            drawSphere(15,5,5);
        }
        glPopMatrix();
    }
    glPopMatrix();

    //
    glPushMatrix();
    {
        glTranslatef(-60,5,75);
        glScalef(.5,.8,.5);
        glPushMatrix();
        {
            glTranslatef(175,5,110);
            glColor3f(1,1,0);
            glScalef(2,.5,2);
            drawCube(10);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glColor3f(1,0,0);
            glTranslatef(175,25,110);
            glRotatef(90,1,0,0);
            glColor3f(0,1,1);
            drawCylinder(15,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glColor3f(1,0,0);
            glTranslatef(175,60,110);
            glRotatef(90,1,0,0);
            drawCylinder(13,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor3f(1,0,1);
            glTranslatef(175,80,110);
            glRotatef(90,1,0,0);
            drawCylinder(11,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(175,110,110);
            drawSphere(15,5,5);
        }
        glPopMatrix();
    }
    glPopMatrix();

    //

    glPushMatrix();
    {
        glTranslatef(-60,5,25);
        glScalef(.5,.8,.5);
        glPushMatrix();
        {
            glTranslatef(175,5,110);
            glColor3f(1,1,0);
            glScalef(2,.5,2);
            drawCube(10);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glColor3f(1,0,0);
            glTranslatef(175,25,110);
            glRotatef(90,1,0,0);
            glColor3f(0,1,1);
            drawCylinder(15,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glColor3f(1,0,0);
            glTranslatef(175,60,110);
            glRotatef(90,1,0,0);
            drawCylinder(13,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor3f(1,0,1);
            glTranslatef(175,80,110);
            glRotatef(90,1,0,0);
            drawCylinder(11,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(175,110,110);
            drawSphere(15,5,5);
        }
        glPopMatrix();
    }
    glPopMatrix();
    //
    glPushMatrix();
    {
        glTranslatef(50,5,25);
        glScalef(.5,.8,.5);
        glPushMatrix();
        {
            glTranslatef(175,5,110);
            glColor3f(1,1,0);
            glScalef(2,.5,2);
            drawCube(10);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glColor3f(1,0,0);
            glTranslatef(175,25,110);
            glRotatef(90,1,0,0);
            glColor3f(0,1,1);
            drawCylinder(15,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glColor3f(1,0,0);
            glTranslatef(175,60,110);
            glRotatef(90,1,0,0);
            drawCylinder(13,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor3f(1,0,1);
            glTranslatef(175,80,110);
            glRotatef(90,1,0,0);
            drawCylinder(11,50,75);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(175,110,110);
            drawSphere(15,5,5);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void masjid()
{

    glPushMatrix();
    {
        glTranslatef(75,15,110);

        //floor

        glPushMatrix();
        {
            glTranslatef(0,-15,0);
            glScalef(1,.1,1);
            glColor3f(1,0,1);
            drawCube(35);
        }
        glPopMatrix();
        //  One Story
        glPushMatrix();
        {
            glTranslatef(0,15,0);
            glScalef(1,.1,1);
            glColor3f(1,0,0);
            drawCube(31);
        }
        glPopMatrix();
        //
        glPushMatrix();
        {
            glColor3f(0,0,1);
            glScalef(1,.5,1);
            drawCube(30);
        }
        glPopMatrix();
        //
        glPushMatrix();
        {
            glTranslatef(-19,0,31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();
        //
        glPushMatrix();
        {
            glTranslatef(0,0,31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();
        //

        glPushMatrix();
        {
            glTranslatef(19,0,31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();
        //
        glPushMatrix();
        {
            glTranslatef(-19,0,-31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();

        //
        glPushMatrix();
        {
            glTranslatef(0,0,-31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();
        //
        glPushMatrix();
        {
            glTranslatef(19,0,-31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();
        //
        glPushMatrix();
        {
            glTranslatef(31,0,20);
            glColor3f(0,1,1);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(31,0,0);
            glColor3f(0,1,1);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(31,0,-20);
            glColor3f(0,1,1);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();

        //2nd floor

        glPushMatrix();
        {
            glTranslatef(0,45,0);
            glScalef(1,.1,1);
            glColor3f(1,0,0);
            drawCube(31);
        }
        glPopMatrix();
        //
        glPushMatrix();
        {
            glTranslatef(0,30,0);
            glScalef(1,.5,1);
            glColor3f(0,0,1);
            drawCube(30);
        }
        glPopMatrix();
        //

        glPushMatrix();
        {
            glTranslatef(-19,30,31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(19,30,31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();

        //
        glPushMatrix();
        {
            glTranslatef(0,30,31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0,30,-31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();

        //

        glPushMatrix();
        {
            glTranslatef(-19,30,-31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(19,30,-31);
            glColor3f(0,1,1);
            drawSquare(5);
        }
        glPopMatrix();

        //
        glPushMatrix();
        {
            glTranslatef(31,30,20);
            glColor3f(0,1,1);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(31,30,0);
            glColor3f(0,1,1);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(31,30,-20);
            glColor3f(0,1,1);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();
    }
    glPopMatrix();

}
void bari()
{


    glPushMatrix();
    {

        glTranslatef(0,15,-110);
        // underground

        glPushMatrix();
        {
            glTranslatef(0,-15,0);
            glScalef(1,.1,1);
            glColor3f(1,0,1);
            drawCube(35);
        }
        glPopMatrix();
        //1st floor of building
        glPushMatrix();
        {
            glTranslatef(0,15,0);
            glScalef(1,.1,1);
            glColor3f(1,0,0);
            drawCube(31);
        }
        glPopMatrix();
        //base
        glPushMatrix();
        {
            glColor3f(1,1,1);
            glScalef(1,.6,1);
            drawCube(30);
        }
        glPopMatrix();
        //1st floor left side 1st window

        glPushMatrix();
        {
            glTranslatef(-19,0,31);
            glColor3f(1,0,0);
            drawSquare(5);
        }
        glPopMatrix();

        //1st floor left side last window
        glPushMatrix();
        {
            glTranslatef(19,0,31);
            glColor3f(1,0,0);
            drawSquare(5);
        }
        glPopMatrix();

        //backside 1st window

        glPushMatrix();
        {
            glTranslatef(-19,0,-31);
            glColor3f(1,0,0);
            drawSquare(5);
        }


        glPopMatrix();
 //backside last window
        glPushMatrix();
        {
            glTranslatef(19,0,-31);
            glColor3f(1,0,0);
            drawSquare(5);
        }
        glPopMatrix();

        //1st floor front side 1st window
        glPushMatrix();
        {
            glTranslatef(31,0,20);
            glColor3f(1,0,0);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();


        //1st floor front side last window
        glPushMatrix();
        {
            glTranslatef(31,0,-20);
            glColor3f(1,0,0);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();

        //2nd floor building


        glPushMatrix();
        {
            glTranslatef(0,45,0);
            glScalef(1,.1,1);
            glColor3f(1,0,0);
            drawCube(31);
        }
        glPopMatrix();
        //
        glPushMatrix();
        {
            glTranslatef(0,30,0);
            glScalef(1,.5,1);
            glColor3f(1,1,1);
            drawCube(30);
        }
        glPopMatrix();
        //

        glPushMatrix();
        {
            glTranslatef(-19,30,31);
            glColor3f(1,0,0);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(19,30,31);
            glColor3f(1,0,0);
            drawSquare(5);
        }
        glPopMatrix();


        //

        glPushMatrix();
        {
            glTranslatef(-19,30,-31);
            glColor3f(1,0,0);
            drawSquare(5);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(19,30,-31);
            glColor3f(1,0,0);
            drawSquare(5);
        }
        glPopMatrix();

        //front building first window
        glPushMatrix();
        {
            glTranslatef(31,30,20);
            glColor3f(0,0,1);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();


        glPushMatrix();
        {
            glTranslatef(31,30,-20);
            glColor3f(0,0,1);
            glRotatef(90,0,1,0);
            drawSquare(5);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void undergroundcolor()

{
    glPushMatrix();
    {
        glTranslatef(0,-30,0);
        glColor3f(.3,0,0);
        glScalef(250,.1,500);
        glRotatef(90,1,0,0);
        drawSquare(100);
    }
    glPopMatrix();


}
void keyboardListener(unsigned char key, int x,int y)
{

    switch(key)
    {

    case '1':
        drawgrid=1-drawgrid;
        break;
    case 'w':
        k+=5;
        break;
    case 's':
        k-=5;
        break;

        case 'p':
        z+=5;
        break;
    case 'q':
        z-=5;
        break;

    case 'f':
        posx+=lx;
        posy+=ly;
        posz+=lz;
        break;

    case 'b':
        posx-=lx;
        posy-=ly;
        posz-=lz;
        break;

    case 'd':
        posx+=rx;
        posy+=ry;
        posz+=rz;
        break;

    case 'u':
        posx-=rx;
        posy-=ry;
        posz-=rz;
        break;

    case 'l':
        posx+=ux;
        posy+=uy;
        posz+=uz;
        break;

    case 'r':
        posx-=ux;
        posy-=uy;
        posz-=uz;
        break;


    default:
        break;
    }
}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:		//down arrow key
        cameraHeight -= 3.0;
        break;
    case GLUT_KEY_UP:		// up arrow key
        cameraHeight += 3.0;
        break;

    case GLUT_KEY_RIGHT:
        cameraAngle += 0.03;
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= 0.03;
        break;

    case GLUT_KEY_PAGE_UP:
        break;
    case GLUT_KEY_PAGE_DOWN:
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
}
void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) 		// 2 times?? in ONE click? -- solution is checking DOWN or UP
        {
            drawaxes=1-drawaxes;
        }
        break;

    case GLUT_RIGHT_BUTTON:
        //........
        break;

    case GLUT_MIDDLE_BUTTON:
        //........
        break;

    default:
        break;
    }
}
void display()
{
    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?

    //gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    gluLookAt(posx,posy,posz, posx+lx, posy+ly, posz+lz,	0,1,0);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawAxes();
    drawGrid();


    drawroad();
    drawcar();
    drawshade();
    drawpassenger();


    bari();
    minar();
    masjid();
    undergroundcolor();


    glutSwapBuffers();
}
void animate()
{

    speed+=((2*pi*10)/360)*5;
    if(speed>200)
    {
        speed=-200;
    }
    angle+=0.2;

     if(z>30)
    {
        z=-300;
    }

    //codes for any changes in Models, Camera
    glutPostRedisplay();
}
void init()
{
    //codes for initialization

    drawaxes=1;
    cameraHeight=100.0;
    cameraAngle=1.0;
    angle=0;

    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80,	1,	1,	1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
