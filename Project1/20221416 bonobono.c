#pragma comment(lib, "opengl32.lib")
// F I R S T  I N  L A S T  O U T  !!  정 예 전 투 공 병 육 성 // 
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

void draw_line(float x1, float y1, float x2, float y2, float r, float g, float b) 
{
    glColor3f(r, g, b);
    glLineWidth(2.0f);  // 선 두께 2픽셀 설정
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int main() 
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(537, 445, "OpenGL Ellipses + Line", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glOrtho(0, 537, 0, 445, -1, 1); // 픽셀 좌표계
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

        draw_ellipse(&borderEllipse, 0, 0, 0); //테두리용 큰 원
        draw_ellipse(&fillEllipse, 0, 0.439f, 0.753f); // 얼굴
		draw_ellipse(&eyeEllipse1, 0, 0, 0); // 왼쪽 눈
		draw_ellipse(&eyeEllipse2, 0, 0, 0); // 오른쪽 눈
        draw_ellipse(&whiteEllipse1, 1, 1, 1); // 왼쪽 인중
        draw_ellipse(&whiteEllipse2, 1, 1, 1); // 오른쪽 인중
        draw_ellipse(&whiteEllipse3, 1, 1, 1); // 가운데 인중 빈 공간
        draw_ellipse(&noseEllipse, 0, 0, 0); // 코

        // 왼쪽 수염
        draw_line(155, 195, 216, 179, 0, 0, 0);
        draw_line(156, 154, 214, 159, 0, 0, 0);
        draw_line(157, 125, 221, 144, 0, 0, 0);
        // 오른쪽 수염
        draw_line(324, 175, 387, 194, 0, 0, 0);
        draw_line(324, 157, 391, 157, 0, 0, 0);
        draw_line(323, 139, 389, 125, 0, 0, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
