#include <GL/glut.h>
float xb, yb, xe, ye;
int first = 1;
int h, w, F, x, y;

void setPixel(int x, int y)
{
	glColor3f(1.0, 1.0, 0.0); //Set pixel to yellow
	glBegin(GL_POINTS);
	glVertex2i(x, y); //Set pixel coordinates 
	glEnd();
	glFlush(); //Render pixel
}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//background
	glColor3f(1.0f, 0.0f, 0.0f);
	glEnable(GL_COLOR_LOGIC_OP);//enables logic operations
	glLogicOp(GL_COPY);//copy mode while init
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//background load
	glLogicOp(GL_XOR);
	glFlush();

}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void rubber(int x, int y)
{
	//Drawing old line ( XOR mode) 
	 h = yb - yb;

	 w = xe - yb;

	 F = 2 * h - w;

	 x = xb, y = yb;

	for (x = xb; x <= xe; x++) {

		setPixel(x, y);

		if (F < 0)

			F = F + 2 * h;

		else {

			F = F + 2 * (h - w);

			y++;

		}

	}
	glFlush();

	xe = x;
	ye = 500 - y;
	//Draw new line (XOR Mode)
	 h = yb - yb;

	 w = xe - yb;

	 F = 2 * h - w;

	 x = xb, y = yb;

	for (x = xb; x <= xe; x++) {

		setPixel(x, y);

		if (F < 0)

			F = F + 2 * h;

		else {

			F = F + 2 * (h - w);

			y++;

		}

	}
	glFlush();
}


void mouse(int btn, int state, int x, int y)
{
	
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xb = x;
		yb = 500 - y;
		if (first) {
			xe = xb;
			ye = yb;
			first = 0;
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		/* Draw old line in XOR mode */
		 h = yb - yb;

		 w = xe - yb;

		 F = 2 * h - w;

		 x = xb, y = yb;

		for (x = xb; x <= xe; x++) {

			setPixel(x, y);

			if (F < 0)

				F = F + 2 * h;

			else {

				F = F + 2 * (h - w);

				y++;

			}

		}
		glFlush();

		glLogicOp(GL_COPY);
		xe = x;
		ye = 500 - y;
		/* Draw new line in XOR mode */
		h = yb - yb;

		 w = xe - yb;

		 F = 2 * h - w;

	 x = xb, y = yb;

		for (x = xb; x <= xe; x++) {

			setPixel(x, y);

			if (F < 0)

				F = F + 2 * h;

			else {

				F = F + 2 * (h - w);

				y++;

			}

		}
		glFlush();
		first = 1;
		glLogicOp(GL_XOR);
	}
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rubberband Bres Line");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);//when reshape
	glutMouseFunc(mouse);//when mouse is pressed
	glutMotionFunc(rubber);//when mouse is moved
	init();
	glutMainLoop();
}
