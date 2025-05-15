#pragma comment(lib, "Opengl32.lib")
// ! F I R S T  IN  L A S T  O U T ! //
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
    Vec2 scale;
} Transform;

typedef struct
{
    Transform transform;
    int segments;
} Ellipse;

void draw_ellipse(Ellipse* e)
{
    glPushMatrix();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.439f, 0.749f);  // #0070c0 색상 설정
    glVertex2f(0.0f, 0.0f);  // 중심점

    for (int i = 0; i <= e->segments; ++i)
    {
        float angle = 2.0f * PI * i / e->segments;
        glVertex2f(cosf(angle) * e->transform.scale.x, sinf(angle) * e->transform.scale.y);
    }

    glEnd();

    glPopMatrix();
}

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL C Demo", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1, 1, -1, 1, -1, 1); // 2D

    Ellipse ell = { {{0.0f, 0.0f}, 0, {430.0f / 800.0f, 387.0f / 600.0f}}, 32 };

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        draw_ellipse(&ell);  // 타원 그리기

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
