#pragma comment(lib, "opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.1415926535f

typedef struct
{
    float x, y;
} Vec2;

typedef struct
{
    Vec2 position;
    float rotation;
    Vec2 scale;  // ¹ÝÁö¸§(ÇÈ¼¿ ´ÜÀ§)
} Transform;

typedef struct
{
    Transform transform;
    int segments;
} Ellipse;

void draw_ellipse(Ellipse* e, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(e->transform.position.x, e->transform.position.y);

    for (int i = 0; i <= e->segments; ++i)
    {
        float angle = 2.0f * PI * i / e->segments;
        float x = e->transform.position.x + cosf(angle) * e->transform.scale.x;
        float y = e->transform.position.y + sinf(angle) * e->transform.scale.y;
        glVertex2f(x, y);
    }
    glEnd();
}

void draw_line(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glLineWidth(55);  // ¼± µÎ²² 2ÇÈ¼¿ ¼³Á¤
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL Ellipses + Line", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glOrtho(0, 500, 0, 500, -1, 1); // ÇÈ¼¿ ÁÂÇ¥°è
    glClearColor(1, 1, 1, 1);  // ¹è°æ Èò»ö

    Ellipse borderEllipse = { { {250, 250}, 0, {211, 211} }, 64 }; // ÇÈ¼¿ »ó ÁÂÇ¥, È¸Àü, Å©±â, ¼¼±×¸ÕÆ®
    Ellipse mainEllipse = { { {250, 250}, 0, {195, 195} }, 64 };
    Ellipse centerEllipse = { { {250, 250}, 0, {10, 10} }, 64 };
    Ellipse subBorderEllipse = { { {250, 160}, 0, {60, 60} }, 64 };
    Ellipse subMainEllipse = { { {250, 160}, 0, {56, 56} }, 64 };
    Ellipse subCenterEllipse = { { {250, 160}, 0, {5, 5} }, 64 };

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_ellipse(&borderEllipse, 0.7f, 0.75f, 0.8f); // R, G, B
        draw_ellipse(&mainEllipse, 0.05f, 0.1f, 0.3f);
        draw_ellipse(&centerEllipse, 0.7f, 0.75f, 0.8f);
        draw_ellipse(&subBorderEllipse, 0.7f, 0.75f, 0.8f);
        draw_ellipse(&subMainEllipse, 0.9f, 0.9f, 1.0f);
        draw_ellipse(&subCenterEllipse, 0.7f, 0.75f, 0.8f);

        draw_line(250, 250, 250, 420, 0.7f, 0.75f, 0.8f);
        draw_line(250, 250, 370, 250, 0.7f, 0.75f, 0.8f);
        draw_line(250, 160, 250, 200, 0.7f, 0.75f, 0.8f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}