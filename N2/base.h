#if defined(__APPLE__) || defined(MACOSX)
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#include <math.h>

/*
    Funcões Auxiliares

    Utilizadas nos exercícios.
*/

#define KEY_ESCAPE 27
#define KEY_SPACE  32

struct Point
{
    float X, Y;
};

struct BBox
{
    float minX, maxX, minY, maxY;
};

double euclideanDistance(float x1, float y1, float x2, float y2)
{
    /*
    double x = x1 - x2;
    double y = y1 - y2;
    double dist;

    dist = pow(x, 2) + pow(y, 2);
    dist = sqrt(dist);

    return dist; // floor(dist);
    */

    double x = x1 - x2;
    double y = y1 - y2;

    return abs(pow(x, 2) + pow(y, 2));
}

double calculateX(double angle, double radius)
{
    return (radius * cos(M_PI * angle / 180.0));
}
double calculateY(double angle, double radius)
{
    return (radius * sin(M_PI * angle / 180.0));
}

inline void DrawCircle(float cx, float cy, float radius, int points, GLenum primitive = GL_LINE_LOOP)
{
    glBegin(primitive);

        for(int i = 0; i < points; i++)
        {
            float angle = 2.0f * M_PI * float(i) / float(points);

            float x = radius * cos(angle);
            float y = radius * sin(angle);

            glVertex2f(x + cx, y + cy);
        }

    glEnd();
}

inline void DrawTriangle(Point p1, Point p2, Point p3, GLenum primitive = GL_LINE_LOOP)
{
    glBegin(primitive);
        glVertex2f(p1.X, p1.Y);
        glVertex2f(p2.X, p2.Y);
        glVertex2f(p3.X, p3.Y);
    glEnd();
}

inline void DrawRectangle(float minX, float maxX, float minY, float maxY)
{
    glBegin(GL_LINE_LOOP);
        // Linha inferior.
        glVertex2f(minX, minY);
        // Linha lateral esquerda.
        glVertex2f(minX, maxY);
        // Linha superior.
        glVertex2f(maxX, maxY);
        // Linha lateral direita.
        glVertex2f(maxX, minY);
    glEnd();
}

inline void DrawRectangle(Point p1, Point p2, Point p3, Point p4)
{
    glBegin(GL_LINE_LOOP);
        // Linha inferior.
        glVertex2f(p1.X, p1.Y);
        // Linha lateral esquerda.
        glVertex2f(p2.X, p2.Y);
        // Linha superior.
        glVertex2f(p3.X, p3.Y);
        // Linha lateral direita.
        glVertex2f(p4.X, p4.Y);
    glEnd();
}

inline void DrawXYAxes()
{
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        // Eixo X.
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-200.0f, 0.0f);
        glVertex2f(200.0f, 0.0f);
        // Eixo Y.
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.0f, -200.0f);
        glVertex2f(0.0f, 200.0f);
    glEnd();
}