#ifdef WIN32
    #include <windows.h>
#endif

#include "base.h"
#include <iostream>

using namespace std;

GLint width     = 400,
      height    = 400;

GLfloat ortho2D_minX = -400.0f,
        ortho2D_maxX =  400.0f,
        ortho2D_minY = -400.0f,
        ortho2D_maxY =  400.0f;

Point p1, p2;

BBox box;

GLfloat radiusMajor = 120.0f,
        radiusMinor = 40.0f;

int ZOOM = 100;

// BBox color.
float r = 0.0f,
      g = 1.0f,
      b = 0.0f;

bool isMouseOK = false;

void display()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluOrtho2D(ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Eixo X e Y.
    DrawXYAxes();

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.2f);
    // Circulo maior.
    DrawCircle(p1.X, p1.Y, radiusMajor, 250);

    // BBox circulo maior.
    glColor3f(r, g, b);
    glLineWidth(1.0f);
    DrawRectangle(box.minX, box.maxX, box.minY, box.maxY);

    glColor3f(0.0, 0.0, 0.0);
    // Circulo menor.
    DrawCircle(p2.X, p2.Y, radiusMinor, 250);
    // Ponto no centro do circulo menor.
    glPointSize(4.0f);
    glBegin(GL_POINTS);
        glVertex2f(p2.X, p2.Y);
    glEnd();

    glutSwapBuffers();
}

bool isInside()
{
    if (p2.X < box.minX &&
        p2.X > box.maxX &&
        p2.Y > box.minY &&
        p2.Y < box.maxY)
    {
        r = 0.0f;
        g = 1.0f;
        b = 0.0f;

        return true;
    }

    double d = euclideanDistance(p1.X, p1.Y, p2.X, p2.Y);
    bool outRadius = d <= radiusMajor * radiusMajor;

    // Fora da BBox e Dentro do raio.
    if (outRadius)
    {
        r = 1.0f;
        g = 1.0f;
        b = 0.0f;
    }
    else
    {
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
    }

    return outRadius;
}

void initialize()
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_LIGHTING);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Circulo maior.
    p1.X = 150;
    p1.Y = 150;
    // Circulo menor.
    p2.X = 150;
    p2.Y = 150;

    box.minX = p1.X + calculateX(315, radiusMajor);
    box.maxX = p1.X + calculateX(225, radiusMajor);
    box.minY = p1.Y + calculateY(225, radiusMajor);
    box.maxY = p1.Y + calculateY(135, radiusMajor);
}

void zoom_in()
{
    ZOOM = ZOOM + 5 * 100 / 400;
}

void zoom_out()
{
    ZOOM = ZOOM - 5 * 100 / 400;
}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY)
{
    switch (key)
    {
        case KEY_ESCAPE:
            exit(0);
        break;

        case 'I':
        case 'i':
            if (ZOOM < 180) // Inverte
            {
                ortho2D_minX += 5.0f;
                ortho2D_maxX -= 5.0f;
                ortho2D_minY += 5.0f;
                ortho2D_maxY -= 5.0f;
                zoom_in();
                cout << "ZOOM: " << ZOOM << "%%\n";
                glutPostRedisplay();
            }
        break;

        case 'O':
        case 'o':
            if (ZOOM > 0)
            {
                ortho2D_minX -= 5.0f;
                ortho2D_maxX += 5.0f;
                ortho2D_minY -= 5.0f;
                ortho2D_maxY += 5.0f;
                zoom_out();
                cout << "ZOOM: " << ZOOM << "%%\n";
                glutPostRedisplay();
            }
        break;

        case 'E':
        case 'e':
            p2.X--;

            if (!isInside())
            {
                p2.X += 2;
            }

            glutPostRedisplay();
        break;

        case 'D':
        case 'd':
            p2.X++;

            if (!isInside())
            {
                p2.X -= 2;
            }

            glutPostRedisplay();
        break;

        case 'C':
        case 'c':
            p2.Y++;

            if (!isInside())
            {
                p2.Y -= 2;
            }

            glutPostRedisplay();
        break;

        case 'B':
        case 'b':
            p2.Y--;

            if (!isInside())
            {
                p2.Y += 2;
            }

            glutPostRedisplay();
        break;

        default:
            cout << "Invalid key pressed: " << key << "\n";
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    isMouseOK = false;

    // Release mouse button.
    if (/*button == 0 && */state == GLUT_UP)
    {
        p2.X = 150;
        p2.Y = 150;

        r = 0.0f;
        g = 1.0f;
        b = 0.0f;

        glutPostRedisplay();
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        isMouseOK = true;
    }
}

void motion(int x, int y)
{
    if (!isMouseOK) return;

    float oldX = p2.X,
          oldY = p2.Y;

    p2.X = (x * 2) - width;
    p2.Y = (y * -2) + height;

    if (!isInside())
    {
        p2.X = oldX;
        p2.Y = oldY;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(300, 250);
    glutInitWindowSize(width, height);

    glutCreateWindow("N2 - Exercicio 6");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    initialize();
    glutMainLoop();

    return 0;
}
