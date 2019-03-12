#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

double w=500,h=300;
double view[3]={2,2,12.9};
double look[3]={2,2,2};
int flag=-1;
void steps(void);
void window(void);
void gate(void);
double angle=0,speed=5,maino=0,romo=0,tro=0,mgo=0,sgo=0;
GLUquadricObj *Cylinder;
GLfloat angle1;

void myinit(void)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-1.0,1.0,-1*w/h,1*w/h,1,200.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
Cylinder = gluNewQuadric();
gluQuadricDrawStyle( Cylinder, GLU_FILL);
gluQuadricNormals( Cylinder,GLU_SMOOTH);
GLfloat gam[]={0.2,.2,.2,1};
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,gam);}

void matprop(GLfloat amb[],GLfloat dif[],GLfloat spec[],GLfloat shi[])
{
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shi);
}

//2 types of walls
void wall(double thickness)                               //house wall
{
glPushMatrix();
glTranslated(2,.5*thickness,2);
glScaled(4.0,thickness,4.0);
glutSolidCube(1.0);
glPopMatrix();}
void wall2(double thickness)                           //compound wall
{
glPushMatrix();
glTranslated(.8,.5*thickness*4,3.5);
glScaled(1.6,thickness*4,7.0);
glutSolidCube(1.0);
glPopMatrix();}

void earth(void)                                     //ground or earth
{
GLfloat ambient[]={1,0,0,1};  GLfloat specular[]={0,0,1,1};
GLfloat diffuse[]={.5,.5,.5,1};  GLfloat shininess[]={50};
matprop(ambient,diffuse,specular,shininess);
GLfloat lightIntensity[]={.7,.7,.7,1};
GLfloat light_position[]={2,5,-3,0};
glLightfv(GL_LIGHT0,GL_POSITION,light_position);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
glPushMatrix();
glTranslated(0,-.25,0);
glScaled(10000,.5,1000000);
glutSolidCube(1.0);
glPopMatrix();
glFlush();}

void compound(void)                                         //compound
{
GLfloat ambient[]={1,0,0,1};  GLfloat specular[]={0,1,1,1};
GLfloat diffuse[]={.7,1,.7,1};  GLfloat shininess[]={50};
matprop(ambient,diffuse,specular,shininess);
GLfloat lightIntensity[]={.7,.7,.7,1};
GLfloat light_position[]={2,6,1.5,0};
glLightfv(GL_LIGHT0,GL_POSITION,light_position);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
glPushMatrix();
glPushMatrix();                                //left wall of compound
glTranslated(-4,0,-1-.04);
glRotated(90.0,0,0,1);
wall2(0.08);
glPopMatrix();
glPushMatrix();                               //right wall of compound
glTranslated(8,0,-1-.02);
glRotated(90.0,0,0,1);
wall2(0.08);
glPopMatrix();
glPushMatrix();                                //back wall of compound
glTranslated(2,.8,-1);
glRotated(-90,1,0,0);
glScaled(12,.02*4,1.6);
glutSolidCube(1.0);
glPopMatrix();
glPushMatrix();                          //front left wall of compound
glTranslated(-2,.8,6-.08);
glRotated(-90,1,0,0);
glScaled(4.4,.02*4,1.6);
glutSolidCube(1.0);
glPopMatrix();
glPushMatrix();                         //front right wall of compound
glTranslated(5.4,.8,6-.08);
glRotated(-90,1,0,0);
glScaled(5.3,.02*4,1.6);
glutSolidCube(1.0);
glPopMatrix();
glPopMatrix();
GLfloat ambient2[]={0,1,0,1};  GLfloat specular2[]={1,1,1,1};
GLfloat diffuse2[]={.2,.6,0.1,1};  GLfloat shininess2[]={50};
matprop(ambient2,diffuse2,specular2,shininess2);
glPushMatrix();                                                //floor
glTranslated(-4,-0.05,-1);
glScaled(3,3,1.7);
wall(0.08);
glPopMatrix();
gate();
glFlush();}

void terece(void)                                             //terece
{
GLfloat ambient1[]={1,0,1,1};  GLfloat specular1[]={1,1,1,1};
GLfloat diffuse1[]={0.5,0.5,0.5,1};  GLfloat mat_shininess[]={50};
matprop(ambient1,diffuse1,specular1,mat_shininess);
glPushMatrix();
glTranslated(0,4,0);
glScaled(1,.1,1);
glPushMatrix();                                            //left wall
glTranslated(-2.2,0,-.2);
glScaled(1,1,1.1);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
glPushMatrix();                                           //right wall
glTranslated(6+.12,0,-.02-.27);
glScaled(1,1,1.1);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
glPushMatrix();                                            //back wall
glTranslated(-2.08,0,-.21);
glScaled(2+.05,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                                           //front wall
glTranslated(-2.08,0,4+.11);
glScaled(2+.05,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();
glTranslated(-2.14,2,4);
glScaled(0.5,4,.1);
glutSolidCube(1);
glPopMatrix();
glPopMatrix();}

void window(void)
{
GLfloat lightIntensity[]={.7,.7,.7,1};  int i;
GLfloat light_position[]={-20,4,-60,0};
glLightfv(GL_LIGHT1,GL_POSITION,light_position);
glLightfv(GL_LIGHT1,GL_DIFFUSE,lightIntensity);
glEnable(GL_LIGHT1);
glPushMatrix();
glTranslated(3.185,1,3.95);
glPushMatrix();                                  //left edge of window
glTranslated(.02,1,.02);
glScaled(.04,2.2,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                                           //right edge
glTranslated(1.6+.02,1,0.02);
glScaled(.04,2.2,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                                             //top edge
glTranslated(.9,2+.02,0.02);
glScaled(1.8,.04,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                                          //bottom edge
glTranslated(.8,.02,0.02);
glScaled(1.8,.04,.04);
glutSolidCube(1);
glPopMatrix();
for(i=1;i<=3;i++)
{
glPushMatrix();
glTranslated(.4*i,0,0);
glRotated(-90,1,0,0);
gluCylinder(Cylinder,.01,.01,2,32,32);
glPopMatrix();
}
for(i=1;i<=3;i++)
{
glPushMatrix();
glTranslated(.1+.4*i,0,0);
glRotated(-90,1,0,0);
gluCylinder(Cylinder,.01,.01,2,32,32);
glPopMatrix();
}
for(i=1;i<=4;i++)
{
glPushMatrix();
glTranslated(0,.4*i,0);
glRotated(90,0,1,0);
gluCylinder(Cylinder,.03,.03,1.6,32,32);
glPopMatrix();}
glPopMatrix();}

void winsmall(void)
{GLfloat lightIntensity[]={.7,.7,.7,1}; int i;
GLfloat light_position[]={-20,4,-60,0};
glLightfv(GL_LIGHT1,GL_POSITION,light_position);
glLightfv(GL_LIGHT1,GL_DIFFUSE,lightIntensity);
glEnable(GL_LIGHT1);
glPushMatrix();
glTranslated(3.185,1,3.95);
glPushMatrix();                                  //left edge of window
glTranslated(-4.5,1,.02);
glScaled(.04,2.2,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                                           //right edge
glTranslated(-2.9,1,0.02);
glScaled(.04,2.2,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                                             //top edge
glTranslated(-3.7,2+.03,0.02);
glScaled(1.7,.04,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                                          //bottom edge
glTranslated(-3.7,.02,0.02);
glScaled(1.8,.04,.04);
glutSolidCube(1);
glPopMatrix();
for(i=1;i<=3;i++)
{
glPushMatrix();
glTranslated(-4.5+.4*i,0,0);
glRotated(-90,1,0,0);
gluCylinder(Cylinder,.01,.01,2,32,32);
glPopMatrix();
}
for(i=1;i<=4;i++)
{
glPushMatrix();
glTranslated(-4.5,.4*i,0);
glRotated(90,0,1,0);
gluCylinder(Cylinder,.03,.03,1.6,32,32);
glPopMatrix();}}

void gate(void)                                                 //gate
{int i;
GLfloat ambient1[]={1,.5,1,1};  GLfloat specular1[]={1,1,1,1};
GLfloat diffuse1[]={.5,.5,.5,1};  GLfloat mat_shininess[]={120};
matprop(ambient1,diffuse1,specular1,mat_shininess);
glPushMatrix();
if(mgo==1)                          //if flag mgo=1 open the main gate
glTranslated(2.5,0,0);
glTranslated(-1.3,0,6);
glPushMatrix();                           //top frame of the main gate
glTranslated(2.8,1.6,0);
glScaled(2.5,.07,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                            //bottom frame of main gate
glTranslated(2.8,.05,0);
glScaled(2.5,.07,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                          //left frame of the main gate
glTranslated(1.55,.85,0);
glScaled(.04,1.6,.04);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();                         //right frame of the main gate
glTranslated(4.05,.85,0);
glScaled(.04,1.6,.04);
glutSolidCube(1);
glPopMatrix();
for(i=1;i<=3;i++)                                   //horizantal pipes
{
glPushMatrix();
glTranslated(1.55,.4*i,0);
glRotated(90,0,1,0);
gluCylinder(Cylinder,.02,.02,2.5,32,32);
glPopMatrix();
}
for(i=1;i<=8;i++)                                    //vertical strips
{
glPushMatrix();
glTranslated(1.45+.3*i,.85,0);
glScaled(.2,1.5,.02);
glutSolidCube(1);
glPopMatrix();
}
glPopMatrix();}

void house(void)                                               //house
{
GLfloat mat_ambient[]={1,0,0,1};  GLfloat mat_specular[]={1,1,1,1};
GLfloat mat_diffuse[]={1,1,.7,1};  GLfloat mat_shininess[]={50};
matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
GLfloat lightIntensity4[]={.7,.7,.7,.7};
GLfloat light_position4[]={3,1,.5,1};
glLightfv(GL_LIGHT6,GL_POSITION,light_position4);
glLightfv(GL_LIGHT6,GL_DIFFUSE,lightIntensity4);
glEnable(GL_LIGHT6);
glPushMatrix();
glTranslated(0,.15,0);
glPushMatrix();                                                 //roof
glTranslated(-1.95,3.9,-.01*4-.25);
glScaled(2,1.5,1.1);
wall(0.08);
glPopMatrix();
GLfloat ambient2[]={1,0,0,1};  GLfloat specular2[]={1,1,1,1};
GLfloat diffuse2[]={.7,1,0.8,1};   GLfloat shininess[]={50};
matprop(ambient2,diffuse2,specular2,shininess);
glPushMatrix();                                                //floor
glTranslated(-2,-0.05,-.01*4);
glScaled(2,1.5,1);
wall(0.08);
glPopMatrix();
GLfloat ambient1[]={.9,1,.5,1};  GLfloat specular1[]={1,1,1,1};
GLfloat diffuse1[]={1,1,.7,1};  GLfloat shininess1[]={50};
matprop(ambient1,diffuse1,specular1,shininess1);
glPushMatrix();                                            //left wall
glTranslated(-2,0,0);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
glPushMatrix();                                           //right wall
glTranslated(6,0,0);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
glPushMatrix();                                            //back wall
glTranslated(-.08,0,0);
glScaled(1.5+.02,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                                      //wall back right
glTranslated(-2,0,0);
glScaled(1.5+.02,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                                   //room vertical wall
glTranslated(4,0,0);
glScaled(1,1,.5);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
glPushMatrix();                                 //room horizantal wall
glTranslated(4.4,0,2);
glScaled(.4,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                             //wall above the room door
glTranslated(4,3,2);
glScaled(.11,.25,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                            //left room horizantal wall
glTranslated(-0.4,0,2);
glScaled(.4,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                                  //lroom vertical wall
glTranslated(1.2,0,0);
glScaled(1,1,.35);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
glPushMatrix();                             //entrance room right wall
glTranslated(1.2,0,2.59);
glScaled(1,1,.35);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
glPushMatrix();                                 //wall above main door
glTranslated(1.2,3.3,4);
glScaled(.16,.17,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                             //wall right to the window
glTranslated(4.8,0,4);
glScaled(.3,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                             //wall left to left window
glTranslated(-2.1,0,4);
glScaled(.2,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                            //wall right to left window
glTranslated(0.3,0,4);
glScaled(.21,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                              //wall right to main door
glTranslated(1.8,0,4);
glScaled(.35,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                                //wall below the window
glTranslated(3.2,0,4);
glScaled(.4,.25,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                               //wall below left window
glTranslated(-1.35,0,4);
glScaled(.5,.25,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                                //wall above the window
glTranslated(3.2,3.03,4);
glScaled(.4,.25,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();                               //wall above left window
glTranslated(-1.35,3.03,4);
glScaled(.45,.25,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
terece();
window();
winsmall();

GLfloat ambient[]={1,0.5,.5,1};  GLfloat specular[]={1,1,1,1};
GLfloat diffuse[]={1,.5,.5,1};
matprop(ambient,diffuse,specular,mat_shininess);
glPushMatrix();                                            //main door
glTranslated(-2,-1,0.125);
glScaled(1.38,1.15,1);
glRotated(maino,0,1,0);
glTranslated(0,0,-4);
glPushMatrix();
glTranslated(0,0,4);
glScaled(.12,.75,1);
glRotated(-90.0,1,0,0);
wall(0.04);
glPopMatrix();
glPopMatrix();
glPushMatrix();                                      //below room door
glTranslated(4,0,(2-.025));
glRotated(romo,0,1,0);
glTranslated(-4,0,-(2-.025));
glPushMatrix();
glTranslated(4,0,2);
glScaled(.099,.75,1);
glRotated(-90.0,1,0,0);
wall(0.01);
glPopMatrix();
glPushMatrix();
glTranslated(4.01,0,2-.025);
glScaled(.5,1,.6);
glRotated(-90,1,0,0);
gluCylinder(Cylinder, 0.05, 0.05, 3, 16, 16);
glPopMatrix();glPopMatrix();
glPopMatrix();
glFlush();
}

void display(void)
{
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
gluLookAt(view[0],view[1],view[2],look[0],look[1],look[2],0.0,1,0.0);
earth();
compound();
house();
glFlush();
glutSwapBuffers();
glutPostRedisplay();
}

void Keyboard(unsigned char key,int x,int y)
{
switch(key)
{
case '4':                        //to move the camera along -ve x axis
view[0]-=.1;
glutPostRedisplay();
break;
case '6':                        //to move the camera along +ve x axis
view[0]+=.1;
glutPostRedisplay();
break;
case '7':                        //to move the camera along +ve y axis
view[1]+=.1;
glutPostRedisplay();
break;
case '1':                        //to move the camera along -ve y axis
if(view[1]>1.9)
view[1]-=.1;
glutPostRedisplay();
break;
case '8':                        //to move the camera along -ve z axis
view[2]-=.1;
glutPostRedisplay();
break;
case '2':                        //to move the camera along +ve z axis
view[2]+=.1;
glutPostRedisplay();
break;
case 'r':                 //to move the look position along +ve x axis
case 'R':
look[0]+=.1;
break;
case 'l':                 //to move the look position along -ve x axis
case 'L':
look[0]-=.1;
break;
case 'U':                 //to move the look position along +ve y axis
case 'u':
look[1]+=.1;
break;
case 'D':                 //to move the look position along -ve y axis
case 'd':
look[1]-=.1;
break;
case 'f':                 //to move the look position along +ve z axis
case 'F':
look[2]+=.1;
break;
case 'B':                 //to move the look position along -ve z axis
case 'b':
look[2]-=.1;
break;
case 'q':                            //to open and close the main door
case 'Q':
if(maino==0)
maino=85;
else
maino=0;
break;
case 'O':                      //to open and close the below room door
case 'o':
if(romo==0)
romo=75;
else
romo=0;
break;
case 'g':                            //to open and close the main gate
case 'G':
if(mgo==0)
mgo=1;
else
mgo=0;
break;
case 'i':                                                //inside view
case 'I':
view[0]=2.8;  view[1]=2;
view[2]=4.8;  look[0]=2.8;
look[1]=2;  look[2]=1;
break;
case 'T':                                                   //top view
case 't':
view[0]=6;  view[1]=12;
view[2]=10;  look[0]=2;
look[1]=4;  look[2]=2;
break;
case 'j':                                                 //front view
case 'J':
view[0]=2;  view[1]=2;
view[2]=12.9;  look[0]=3;
look[1]=2;  look[2]=3;
break;
case 'k':                                                  //back view
case 'K':
view[0]=1;  view[1]=6;
view[2]=-7;  look[0]=2;
look[1]=4;  look[2]=2;
break;}}

void main_menu(int m)
{
switch(m)
{
case 1:
exit(0);}}

void door_menu(int m)
{
switch(m)
{
case 1:
if(maino==0)
maino=85;
else
maino=0;
break;
case 2:
if(romo==0)
romo=75;
else
romo=0;
break;}}

void gate_menu(int m)
{
switch(m)
{
case 1:
if(mgo==0)
mgo=1;
else
mgo=0;
break;
case 2:
if(sgo==0)
sgo=50;
else
sgo=0;
break;}}

void house_view(int m)
{
switch(m)
{
case 1:
view[0]=2.8;  view[1]=2;
view[2]=4.8;  look[0]=2.8;
look[1]=2;  look[2]=1;
break;
case 2:
view[0]=6;  view[1]=12;
view[2]=10;  look[0]=2;
look[1]=8;  look[2]=2;
break;
case 3:
view[0]=2;  view[1]=2;
view[2]=12.9;  look[0]=3;
look[1]=2;  look[2]=3;
break;
case 4:
view[0]=1;  view[1]=6;
view[2]=-7;  look[0]=2;
look[1]=4;  look[2]=2;
break;}}

void menu()
{
int sub_menu2=glutCreateMenu(door_menu);
glutAddMenuEntry("main door(q)",1);
glutAddMenuEntry("ground floor room door(o)",2);
int sub_menu3=glutCreateMenu(gate_menu);
glutAddMenuEntry("main gate(g)",1);int sub_menu4=glutCreateMenu(house_view);
glutAddMenuEntry("front view(j)",3);
glutAddMenuEntry("top view(t)",2);
glutAddMenuEntry("inside view(i)",1);
glutAddMenuEntry("back view(k)",4);
glutCreateMenu(main_menu);
glutAddMenuEntry("quit",1);
glutAddSubMenu("open/close door",sub_menu2);
glutAddSubMenu("open/close gate",sub_menu3);
glutAddSubMenu("house view",sub_menu4);
glutAttachMenu(GLUT_RIGHT_BUTTON);}

int main(int argc,char**argv)
{
glutInit(&argc,argv);                 glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(w,h);
glutInitWindowPosition(0,0);
glutCreateWindow("er");
myinit();
glutDisplayFunc(display);
glutKeyboardFunc(Keyboard);
menu();
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH);                               //smooth shaded
glEnable(GL_DEPTH_TEST);                    //to remove hidden surface
glEnable(GL_NORMALIZE);         //to make normal vector to unit vector
glClearColor(0,.3,.8,0);
glViewport(0,0,w,h);
glutMainLoop();
return 0;
}






