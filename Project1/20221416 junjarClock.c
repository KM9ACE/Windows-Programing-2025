#include <GLFW/glfw3.h>
#include <time.h>

#pragma comment(lib, "Opengl32.lib")

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

// 기본 세그먼트 길이와 두께 (픽셀 기준)
const float baseSegLength = 50.0f;
const float baseSegWidth = 10.0f;

// 픽셀 좌표계에서 직선 그리기 (두께 반영)
void drawLine(float x1, float y1, float x2, float y2, float lineWidth)
{
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// 세그먼트 그리기
void drawSegment(int segmentIndex, float x, float y, float segLength, float segWidth)
{
    // 세그먼트는 7개
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

// 숫자 그리기
void drawDigit(int digit, float baseX, float baseY, float scale)
{
    if (digit < 0 || digit > 9) return;

    unsigned char segments = segmentTable[digit];
    float segLength = baseSegLength * scale;
    float segWidth = baseSegWidth * scale;

    for (int i = 0; i < 7; i++)
    {
        if (segments & (1 << (6 - i)))
        {
            drawSegment(i, baseX, baseY, segLength, segWidth);
        }
    }
}

// 콜론 그리기
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

// 전체 시계 그리기 함수
void drawClock(int hour, int minute, int second, float baseX, float baseY, float scale)
{
    float spacing = 70.0f * scale;

    drawDigit(hour / 10, baseX, baseY, scale);
    drawDigit(hour % 10, baseX + spacing, baseY, scale);

    int colonVisible = (second % 2 == 0);
    drawColon(baseX + spacing * 2 - 20.0f * scale, baseY, colonVisible, scale);

    drawDigit(minute / 10, baseX + spacing * 2, baseY, scale);
    drawDigit(minute % 10, baseX + spacing * 3, baseY, scale);

    drawColon(baseX + spacing * 4 - 20.0f * scale, baseY, colonVisible, scale);

    drawDigit(second / 10, baseX + spacing * 4, baseY, scale);
    drawDigit(second % 10, baseX + spacing * 5, baseY, scale);
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "7-Segment Digital Clock", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // 픽셀 좌표계 설정 (왼쪽 아래 0,0 / 오른쪽 위 500,500)
    glOrtho(0, 500, 0, 500, -1, 1);

    glfwSwapInterval(1); // VSync 활성화

    float clockPosX = 50.0f;  // 시계 시작 위치 X (픽셀)
    float clockPosY = 250.0f; // 시계 시작 위치 Y (픽셀)
    float scale = 1.0f;       // 크기 조절 (1.0 = 기본 크기)

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f); // 흰색

        // 현재 시간
        time_t now = time(NULL);
        struct tm* t = localtime(&now);

        int hour = t->tm_hour;
        int minute = t->tm_min;
        int second = t->tm_sec;

        // 시계 그리기
        drawClock(hour, minute, second, clockPosX, clockPosY, scale);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


