#include<iostream>
#include<Gl/glut.h>
#include<math.h>


const GLfloat factor = 0.2f;

void myDisplay(void)
{
	GLfloat x;

	glClear(GL_COLOR_BUFFER_BIT);

	{

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		{
			// x-axis
			glVertex3f(-100.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 0.0f, 0.0f);

			// y-axis
			glVertex3f(0.0f, -100.0f, 0.0f);
			glVertex3f(0.0f, 100.0f, 0.0f);

			glEnd();
			glBegin(GL_LINE_STRIP);
			for (x = -2.0f / factor; x < 2.0f / factor; x += 0.030f)
			{
				glVertex2f((x * factor) / 4, sin(3.14159 * x) / (3.14159 * x));
			}
			glEnd();
			glFlush();
		}
	}

	glFlush();
	glutSwapBuffers();
}




int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Sinc OpenGL program");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;

}
