#pragma comment(lib, "opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>

#define PI 3.1415926535f

//----아날로그----

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

void draw_rotated_line(float x1, float y1, float x2, float y2, float r, float g, float b, float thickness, float angle, float cx, float cy)
{
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

    for (int i = 0; i < 4; ++i)
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
    for (int i = 0; i < 4; ++i)
        glVertex2f(quad[i][0], quad[i][1]);
    glEnd();
}

void draw_tick_marks(float cx, float cy, float radius, int count, float length, float r, float g, float b, float thickness)
{
    float angle_step = 360.0f / count;

    int i = 0;

    for (i = 0; i < count; ++i)
    {
        float angle = i * angle_step * (PI / 180.0f);

        float x1 = cx + cosf(angle) * (radius - length);
        float y1 = cy + sinf(angle) * (radius - length);

        float x2 = cx + cosf(angle) * radius;
        float y2 = cy + sinf(angle) * radius;

        draw_line(x1, y1, x2, y2, r, g, b, thickness);
    }
}

void draw_rect(float x, float y, float width, float height, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

//----디지털----

const unsigned char segmentTable[10] =
{
    0b1111110, // 0
    0b0110000, // 1
    0b1101101, // 2
    0b1111001, // 3
    0b0110011, // 4
    0b1011011, // 5
    0b1011111, // 6
    0b1110000, // 7
    0b1111111, // 8
    0b1111011  // 9
};

// 세그먼트 길이 및 두께 (픽셀 단위)
const float baseSegLength = 50.0f;
const float baseSegWidth = 10.0f;

void drawLine(float x1, float y1, float x2, float y2, float lineWidth)
{
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawSegment(int segmentIndex, float x, float y, float segLength, float segWidth)
{
    switch (segmentIndex)
    {
    case 0: // A (윗가로)
        drawLine(x, y + segLength, x + segLength, y + segLength, segWidth);
        break;
    case 1: // B (오른쪽 위 세로)
        drawLine(x + segLength, y + segLength, x + segLength, y, segWidth);
        break;
    case 2: // C (오른쪽 아래 세로)
        drawLine(x + segLength, y, x + segLength, y - segLength, segWidth);
        break;
    case 3: // D (아랫가로)
        drawLine(x, y - segLength, x + segLength, y - segLength, segWidth);
        break;
    case 4: // E (왼쪽 아래 세로)
        drawLine(x, y, x, y - segLength, segWidth);
        break;
    case 5: // F (왼쪽 위 세로)
        drawLine(x, y + segLength, x, y, segWidth);
        break;
    case 6: // G (중앙 가로)
        drawLine(x, y, x + segLength, y, segWidth);
        break;
    }
}

void drawDigit(int digit, float baseX, float baseY, float scale)
{
    if (digit < 0 || digit > 9) return;

    unsigned char segments = segmentTable[digit];
    float segLength = baseSegLength * scale;
    float segWidth = baseSegWidth * scale;

    int i = 0;
    
    for (i = 0; i < 7; i++)
    {
        if (segments & (1 << (6 - i)))
        {
            drawSegment(i, baseX, baseY, segLength, segWidth);
        }
    }
}

void drawColon(float baseX, float baseY, int visible, float scale)
{
    if (!visible) return;

    float radius = 8.0f * scale; // 점 크기
    glPointSize(radius);
    glBegin(GL_POINTS);
    glVertex2f(baseX, baseY + 20.0f * scale);
    glVertex2f(baseX, baseY - 20.0f * scale);
    glEnd();
}

void drawClock(int hour, int minute, int second, float baseX, float baseY, float scale)
{
    float spacing = 100.0f * scale;

    drawDigit(hour / 10, baseX, baseY, scale);
    drawDigit(hour % 10, baseX + spacing, baseY, scale);

    int colonVisible = (second % 2 == 0);
    drawColon(baseX + spacing * 2 - 22.0f * scale, baseY, colonVisible, scale);

    drawDigit(minute / 10, baseX + spacing * 2, baseY, scale);
    drawDigit(minute % 10, baseX + spacing * 3, baseY, scale);

    drawColon(baseX + spacing * 4 - 22.0f * scale, baseY, colonVisible, scale);

    drawDigit(second / 10, baseX + spacing * 4, baseY, scale);
    drawDigit(second % 10, baseX + spacing * 5, baseY, scale);
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

    glfwSwapInterval(1); // VSync 활성화

    //----아날로그----

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

        draw_rect(175, 270, 150, 60, 0.0f, 0.0f, 0.0f);

        draw_tick_marks(250, 250, 190.0f, 60, 10.0f, 0.7f, 0.75f, 0.8f, 2.0f); // 분 단위 눈금
        draw_tick_marks(250, 250, 190.0f, 12, 20.0f, 0.7f, 0.75f, 0.8f, 4.0f); // 시간 단위 눈금
        draw_tick_marks(250, 160, 60.0f, 12, 13.0f, 0.7f, 0.75f, 0.8f, 3.5f); // 초 단위 눈금 ( 좌표, 좌표, 지름, 눈금 갯수, 눈금 길이, R, G, B, 눈금 두께)

        draw_rotated_line(250, 250, 250, 400, 0.7f, 0.75f, 0.8f, 8.0f, angle1, 250, 250); // 시침
        draw_rotated_line(250, 250, 350, 250, 0.7f, 0.75f, 0.8f, 6.0f, angle2, 250, 250); // 분침
        draw_rotated_line(250, 160, 250, 200, 0.7f, 0.75f, 0.8f, 3.0f, angle3, 250, 160); // 초침 ( 시작점, 끝점, R, G, B, 회전 속도, 중심축)

        angle1 -= 0.5f;
        angle2 -= 0.3f;
        angle3 -= 0.1f;

        // 360도 회전 후, 각도를 0으로 초기화하여 계속 회전하도록 처리
        if (angle1 >= 360.0f) angle1 -= 360.0f;
        if (angle2 >= 360.0f) angle2 -= 360.0f;
        if (angle3 >= 360.0f) angle3 -= 360.0f;

        //----디지털----

        float scale = 0.25f;
        float clockPosX = 182.0f;
        float clockPosY = 300.0f;

        time_t now = time(NULL);
        struct tm* t = localtime(&now);

        int hour = t->tm_hour;
        int minute = t->tm_min;
        int second = t->tm_sec;

        drawClock(hour, minute, second, clockPosX, clockPosY, scale);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
