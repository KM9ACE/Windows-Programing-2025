#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>  // GLFW ���̺귯�� (â ����, �Է�, OpenGL ���ؽ�Ʈ ����)
#include <math.h>        // �ﰢ�Լ� �� ���� �Լ�
#include <windows.h>     // GetAsyncKeyState �Լ� ��� (������ Ű �Է� ����)

// M_PI�� ���ǵǾ� ���� ���� ��츦 ����� ���� ���� (���� ��)
#define M_PI 3.14159265358979323846

// ������ ũ�� ����
int windowWidth = 800;
int windowHeight = 600;

// ��ũ ���� �÷��� (0 = ��ũ �ƴ�, 1 = ��ũ)
int isWinking = 0;

// �� ��� ���� (1=��, 2=�簢, 3=�ﰢ, 4=Ÿ��, 5=���̾Ƹ��)
int faceMode = 1;

// ���� �׸��� �Լ�
// cx, cy : �� �߽� ��ǥ
// r : ������
// num_segments : ���� �ٻ��� �� ���� (Ŭ���� �ε巯�� ��)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);  // �ﰢ�� �� ��� ���� (�߽ɿ��� �ֺ� ����� ä��)
    glVertex2f(cx, cy);        // �߽���
    for (int i = 0; i <= num_segments; ++i) {
        // ������ 0���� 2���̱��� �յ� ����
        float angle = 2.0f * M_PI * i / num_segments;
        // ���� �� �� ��ǥ ���
        float x = cx + cosf(angle) * r;
        float y = cy + sinf(angle) * r;
        glVertex2f(x, y);      // ���� �� �� ����
    }
    glEnd();
}

// �簢�� �׸��� �Լ�
// cx, cy : �簢�� �߽� ��ǥ
// size : �� ���� ����
void drawSquare(float cx, float cy, float size) {
    float half = size / 2.0f;  // �߽ɿ��� �� �� ������ �Ÿ�
    glBegin(GL_QUADS);         // �簢�� �׸��� ����
    glVertex2f(cx - half, cy - half);  // ���� �Ʒ�
    glVertex2f(cx + half, cy - half);  // ������ �Ʒ�
    glVertex2f(cx + half, cy + half);  // ������ ��
    glVertex2f(cx - half, cy + half);  // ���� ��
    glEnd();
}

// �ﰢ�� �׸��� �Լ� (���ﰢ���� �ƴ϶� ������ �ﰢ��)
// cx, cy : �ﰢ�� �߽� ��ǥ
// size : �غ� ����
void drawTriangle(float cx, float cy, float size) {
    float half = size / 2.0f;  // �غ��� �� ����
    glBegin(GL_TRIANGLES);     // �ﰢ�� �׸��� ����
    glVertex2f(cx, cy + half);      // ���� ������
    glVertex2f(cx - half, cy - half); // ���� �Ʒ� ������
    glVertex2f(cx + half, cy - half); // ������ �Ʒ� ������
    glEnd();
}

// Ÿ�� �׸��� �Լ�
// cx, cy : Ÿ�� �߽� ��ǥ
// rx, ry : x��� y�� ������
// num_segments : Ÿ���� �ٻ��� �� ����
void drawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);  // �ﰢ�� �� ��� ����
    glVertex2f(cx, cy);        // �߽���
    for (int i = 0; i <= num_segments; ++i) {
        float angle = 2.0f * M_PI * i / num_segments;
        float x = cx + cosf(angle) * rx;  // x�� ���� ������ ����
        float y = cy + sinf(angle) * ry;  // y�� ���� ������ ����
        glVertex2f(x, y);
    }
    glEnd();
}

// ���̾Ƹ�� ��� �׸��� �Լ� (�簢���� 45�� ȸ���� ���)
// cx, cy : ���̾Ƹ�� �߽� ��ǥ
// size : �밢�� ���� (���� �� ����)
void drawDiamond(float cx, float cy, float size) {
    float half = size / 2.0f;  // �߽ɿ��� ���������� �Ÿ�
    glBegin(GL_QUADS);         // �簢�� �׸��� ����
    glVertex2f(cx, cy + half);    // ���� ������
    glVertex2f(cx + half, cy);    // ������ ������
    glVertex2f(cx, cy - half);    // �Ʒ��� ������
    glVertex2f(cx - half, cy);    // ���� ������
    glEnd();
}

// �� ��ü �׸��� �Լ�
// faceMode ���� ���� �پ��� ��� �׸���
void drawFace() {
    glColor3f(1.0f, 1.0f, 0.0f);  // ����� ����
    switch (faceMode) {
    case 1: drawCircle(0.0f, 0.0f, 0.8f, 360); break;      // ��
    case 2: drawSquare(0.0f, 0.0f, 1.6f); break;           // �簢��
    case 3: drawTriangle(0.0f, 0.0f, 1.6f); break;          // �ﰢ��
    case 4: drawEllipse(0.0f, 0.0f, 0.8f, 0.5f, 360); break; // Ÿ��
    case 5: drawDiamond(0.0f, 0.0f, 1.6f); break;           // ���̾Ƹ��
    }
}

// �� �׸��� �Լ�
// ��ũ ���¿� ���� ������ �� ��� ����
void drawEyes() {
    glLineWidth(5.0f);             // �� ���� 5.0���� ����
    glColor3f(0.0f, 0.0f, 0.0f);  // ������

    // ���� ��: �ܼ��� ������ ǥ��
    glBegin(GL_LINES);
    glVertex2f(-0.3f, 0.3f);       // ���� ��
    glVertex2f(-0.2f, 0.3f);       // ������ ��
    glEnd();

    // ������ ��
    glBegin(GL_LINES);
    if (isWinking) {
        // ��ũ ����: '<' ������� ���� ǥ�� (�� ���� ����)
        glVertex2f(0.2f, 0.32f);
        glVertex2f(0.25f, 0.3f);

        glVertex2f(0.25f, 0.3f);
        glVertex2f(0.2f, 0.28f);
    }
    else {
        // ���� ����: �ܼ� ������ �� ǥ��
        glVertex2f(0.2f, 0.3f);
        glVertex2f(0.3f, 0.3f);
    }
    glEnd();
}

// ���� �� �׸��� �Լ�
// �ݿ� ���·� ���� �����Ͽ� ���� �� ��� ����
void drawSmile() {
    glColor3f(0.0f, 0.0f, 0.0f);   // ������
    glLineWidth(5.0f);             // �� ���� 5.0
    glBegin(GL_LINE_STRIP);        // ����� �� �׸��� ����
    for (int i = 0; i <= 180; ++i) {
        // 0 ~ 180������ ���� ���� (0~���� ����)
        float angle = M_PI * i / 180.0f;
        // x�� �ݿ��� ������ * cos(����)
        float x = 0.4f * cosf(angle);
        // y�� -0.4 * sin(����) + �Ʒ��� �ణ �̵�(-0.2)
        float y = -0.4f * sinf(angle) - 0.2f;
        glVertex2f(x, y);
    }
    glEnd();
}

int main() {
    // GLFW �ʱ�ȭ (���� �� ���α׷� ����)
    if (!glfwInit()) return -1;

    // ������ ���� (ũ�� 800x600, ���� "Multi-Face Wink Extended")
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Multi-Face Wink Extended", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // ���� �������� OpenGL ���ؽ�Ʈ�� ����

    // ���� ����: â�� ���� ������ �ݺ�
    while (!glfwWindowShouldClose(window)) {
        // GetAsyncKeyState�� Ű ���� üũ
        // 'W'Ű�� ������ ��ũ ���·� ����, �ƴϸ� ����
        if (GetAsyncKeyState('W') & 0x8000) isWinking = 1;
        else isWinking = 0;

        // ����Ű 1~5 ���� ���ο� ���� �� ��� ����
        if (GetAsyncKeyState('1') & 0x8000) faceMode = 1;
        if (GetAsyncKeyState('2') & 0x8000) faceMode = 2;
        if (GetAsyncKeyState('3') & 0x8000) faceMode = 3;
        if (GetAsyncKeyState('4') & 0x8000) faceMode = 4;
        if (GetAsyncKeyState('5') & 0x8000) faceMode = 5;

        glClear(GL_COLOR_BUFFER_BIT);  // ȭ�� �����

        drawFace();   // �� ��� �׸���
        drawEyes();   // �� �׸��� (��ũ ���� �ݿ�)
        drawSmile();  // ���� �� �׸���

        glfwSwapBuffers(window);  // ���� ��ü (ȭ�鿡 ǥ��)
        glfwPollEvents();         // �̺�Ʈ ó�� (Ű���� ��)
    }

    // GLFW ����
    glfwTerminate();
    return 0;
}
