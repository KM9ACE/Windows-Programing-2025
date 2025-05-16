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
    Vec2 scale;  // 반지름(픽셀 단위)
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

int main() 
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(537, 445, "OpenGL Ellipses", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // 픽셀 좌표계로 설정
    glOrtho(0, 537, 0, 445, -1, 1);
    glClearColor(1, 1, 1, 1);  // 배경 흰색

    Ellipse borderEllipse = { { {537 / 2.0f, 445 / 2.0f}, 0, {215, 193.5f} }, 64 };
    Ellipse fillEllipse = { { {537 / 2.0f, 445 / 2.0f}, 0, {213, 191} }, 64 };
    Ellipse eyeEllipse1 = { { {89, 268}, 0, {15, 15.5f} }, 48 };
    Ellipse eyeEllipse2 = { { {428, 262}, 0, {16, 15} }, 48 };
    Ellipse whiteEllipse1 = { { {236, 157}, 0, {41.5f, 37.5f} }, 64 };
    Ellipse whiteEllipse2 = { { {314, 157}, 0, {41.5f, 37.5f} }, 64 };
    Ellipse whiteEllipse3 = { { {275, 191}, 0, {25, 20} }, 64 };
    Ellipse noseEllipse = { { {275, 201}, 0, {33, 27.5f} }, 64 };

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_ellipse(&borderEllipse, 0, 0, 0);
        draw_ellipse(&fillEllipse, 0, 0.439f, 0.753f);
        draw_ellipse(&eyeEllipse1, 0, 0, 0);
        draw_ellipse(&eyeEllipse2, 0, 0, 0);
        draw_ellipse(&whiteEllipse1, 1, 1, 1);
        draw_ellipse(&whiteEllipse2, 1, 1, 1);
        draw_ellipse(&whiteEllipse3, 1, 1, 1);  // 뒤에 있는 흰 타원
        draw_ellipse(&noseEllipse, 0, 0, 0);    // 앞에 있는 검은 타원

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
