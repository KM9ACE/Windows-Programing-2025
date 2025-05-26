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

// ���׸�Ʈ ��ġ�� ũ�� (��ǥ�� ����� ��ġ, ���� ũ�� ���� ����)
const float segLength = 0.1f;
const float segWidth = 0.02f;

// ���� �׸���
void drawLine(float x1, float y1, float x2, float y2) 
{
    glLineWidth(6.0f);  // �� ���� 2�ȼ��� ����
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawSegment(int segmentIndex, float x, float y) 
{
    switch (segmentIndex) 
    {
    case 0: // A
        drawLine(x, y + segLength, x + segLength, y + segLength);
        break;
    case 1: // B
        drawLine(x + segLength, y + segLength, x + segLength, y);
        break;
    case 2: // C
        drawLine(x + segLength, y, x + segLength, y - segLength);
        break;
    case 3: // D
        drawLine(x, y - segLength, x + segLength, y - segLength);
        break;
    case 4: // E
        drawLine(x, y, x, y - segLength);
        break;
    case 5: // F
        drawLine(x, y + segLength, x, y);
        break;
    case 6: // G
        drawLine(x, y, x + segLength, y);
        break;
    }
}

// ���ڸ� �׸��� �Լ�
void drawDigit(int digit, float x, float y) 
{
    if (digit < 0 || digit > 9) return;
    unsigned char segments = segmentTable[digit];
    
    int i = 0;
    
    for (i = 0; i < 7; i++) 
    {
        if (segments & (1 << (6 - i))) 
        {
            drawSegment(i, x, y);
        }
    }
}

// �ݷ�(:) �׸���
void drawColon(float x, float y, int visible)
{
    if (!visible) return;
    float radius = 0.01f;
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2f(x, y + 0.03f);
    glVertex2f(x, y - 0.03f);
    glEnd();
}

int main(void) 
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 200, "7-Segment Digital Clock", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1.0, 1.0, -0.5, 0.5, -1.0, 1.0); // 2D ���� ����
    glfwSwapInterval(1); // VSync Ȱ��ȭ (�ʴ� 60������ ����)

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f); // ���

        // ���� �ð� ��������
        time_t now = time(NULL);
        struct tm* t = localtime(&now);

        int hour = t->tm_hour;
        int minute = t->tm_min;
        int second = t->tm_sec;

        // ���� ��ġ �� ����
        float startX = -0.9f;
        float spacing = 0.18f;

        // ���� ��� (��: hh)
        drawDigit(hour / 10, startX, 0.0f);
        drawDigit(hour % 10, startX + spacing, 0.0f);

        // �ݷ� ������ (1�ʸ��� on/off)
        int colonVisible = (second % 2 == 0);
        drawColon(startX + spacing * 2 - 0.04f, 0.0f, colonVisible);

        // �� ��� (mm)
        drawDigit(minute / 10, startX + spacing * 2, 0.0f);
        drawDigit(minute % 10, startX + spacing * 3, 0.0f);

        // �ݷ� ������
        drawColon(startX + spacing * 4 - 0.04f, 0.0f, colonVisible);

        // �� ��� (ss)
        drawDigit(second / 10, startX + spacing * 4, 0.0f);
        drawDigit(second % 10, startX + spacing * 5, 0.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
