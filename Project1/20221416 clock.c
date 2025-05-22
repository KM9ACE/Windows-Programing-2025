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
    Vec2 scale;
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

    int i = 0;

    for (i = 0; i <= e->segments; ++i)
    {
        float angle = 2.0f * PI * i / e->segments;
        float x = e->transform.position.x + cosf(angle) * e->transform.scale.x;
        float y = e->transform.position.y + sinf(angle) * e->transform.scale.y;
        glVertex2f(x, y);
    }
    glEnd();
}

void draw_line(float x1, float y1, float x2, float y2, float r, float g, float b, float thickness)
{
    glColor3f(r, g, b);

    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = sqrtf(dx * dx + dy * dy);

    float nx = -dy / length;
    float ny = dx / length;

    float offsetX = (thickness / 2.0f) * nx;
    float offsetY = (thickness / 2.0f) * ny;

    float x1a = x1 + offsetX;
    float y1a = y1 + offsetY;
    float x1b = x1 - offsetX;
    float y1b = y1 - offsetY;

    float x2a = x2 + offsetX;
    float y2a = y2 + offsetY;
    float x2b = x2 - offsetX;
    float y2b = y2 - offsetY;

    glBegin(GL_POLYGON);
    glVertex2f(x1a, y1a);
    glVertex2f(x2a, y2a);
    glVertex2f(x2b, y2b);
    glVertex2f(x1b, y1b);
    glEnd();
}

void draw_rotated_line(float x1, float y1, float x2, float y2, float r, float g, float b, float thickness, float angle)
{
    float cx = 250.0f;
    float cy = 250.0f;

    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = sqrtf(dx * dx + dy * dy);

    float nx = -dy / len;
    float ny = dx / len;

    float offsetX = (thickness / 2.0f) * nx;
    float offsetY = (thickness / 2.0f) * ny;

    float quad[4][2] = 
    {
        { x1 + offsetX, y1 + offsetY },
        { x2 + offsetX, y2 + offsetY },
        { x2 - offsetX, y2 - offsetY },
        { x1 - offsetX, y1 - offsetY }
    };

    float rad = angle * (PI / 180.0f);

    int i = 0;

    for (i = 0; i < 4; ++i)
    {
        float ox = quad[i][0] - cx;
        float oy = quad[i][1] - cy;

        float rotatedX = ox * cosf(rad) - oy * sinf(rad);
        float rotatedY = ox * sinf(rad) + oy * cosf(rad);

        quad[i][0] = rotatedX + cx;
        quad[i][1] = rotatedY + cy;
    }

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    
    for (i = 0; i < 4; ++i)
        glVertex2f(quad[i][0], quad[i][1]);
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

    glOrtho(0, 500, 0, 500, -1, 1); // 픽셀 좌표계
    glClearColor(1, 1, 1, 1);  // 배경 흰색

    Ellipse borderEllipse = { { {250, 250}, 0, {211, 211} }, 64 }; // 픽셀 상 좌표, 회전, 크기, 세그먼트
    Ellipse mainEllipse = { { {250, 250}, 0, {195, 195} }, 64 };
    Ellipse centerEllipse = { { {250, 250}, 0, {10, 10} }, 64 };
    Ellipse subBorderEllipse = { { {250, 160}, 0, {60, 60} }, 64 };
    Ellipse subMainEllipse = { { {250, 160}, 0, {56, 56} }, 64 };
    Ellipse subCenterEllipse = { { {250, 160}, 0, {5, 5} }, 64 };

    float angle1 = 0.0f;
    float angle2 = 0.0f;
    float angle3 = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_ellipse(&borderEllipse, 0.7f, 0.75f, 0.8f); // R, G, B
        draw_ellipse(&mainEllipse, 0.05f, 0.1f, 0.3f);
        draw_ellipse(&centerEllipse, 0.7f, 0.75f, 0.8f);
        draw_ellipse(&subBorderEllipse, 0.7f, 0.75f, 0.8f);
        draw_ellipse(&subMainEllipse, 0.9f, 0.9f, 1.0f);
        draw_ellipse(&subCenterEllipse, 0.7f, 0.75f, 0.8f);

        draw_rotated_line(250, 250, 250, 400, 0.7f, 0.75f, 0.8f, 8.0f, angle1); // 분침 회전
        draw_rotated_line(250, 250, 350, 250, 0.7f, 0.75f, 0.8f, 6.0f, angle2); // 시침 회전
        draw_rotated_line(250, 160, 250, 200, 0.7f, 0.75f, 0.8f, 3.0f, angle3); // 초침 회전
        //초침 중심축 다시 잡아야함!!!! ㅅㅂ

        angle1 -= 0.5f;
        angle2 -= 0.3f;
        angle3 -= 0.1f;

        // 360도 회전 후, 각도를 0으로 초기화하여 계속 회전하도록 처리
        if (angle1 >= 360.0f) angle1 -= 360.0f;
        if (angle2 >= 360.0f) angle2 -= 360.0f;
        if (angle3 >= 360.0f) angle3 -= 360.0f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
