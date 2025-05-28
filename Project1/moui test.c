#include <GLFW/glfw3.h>
#include <math.h>

#pragma comment(lib, "Opengl32.lib")  // OpenGL ���̺귯�� ��ũ

#define PI 3.1415926535f  // ������ ����

// 2D ���� ����ü (x, y ��ǥ)
typedef struct
{
    float x, y;
} Vec2;

// ��ȯ ����ü (��ġ, ȸ��, ũ��)
typedef struct
{
    Vec2 position;  // ��ü�� ��ġ (x, y)
    float rotation;  // ��ü�� ȸ�� ���� (����)
    Vec2 scale;  // ��ü�� ũ�� (x, y)
} Transform;

// �簢�� ����ü (��ȯ ���� ����)
typedef struct
{
    Transform transform;  // �簢���� ��ġ, ȸ��, ũ�� ����
} Square;

// �簢���� �׸��� �Լ�
void draw_square(Square* sq, float r, float g, float b)
{
    glPushMatrix();  // ���� ��ȯ ��� ����

    // ��ġ ��ȯ (�̵�)
    glTranslatef(sq->transform.position.x, sq->transform.position.y, 0.0f);
    // ȸ�� ��ȯ (ȸ��)
    glRotatef(sq->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    // ũ�� ��ȯ (������)
    glScalef(sq->transform.scale.x, sq->transform.scale.y, 1.0f);

    glBegin(GL_QUADS);  // �簢�� �׸��� ����
    glColor3f(r, g, b); // �簢�� ������ �ʷϻ�
    // �簢���� 4���� ������ ����
    glVertex2f(-0.5f, 0.5f);  // ���� �� ������
    glVertex2f(0.5f, 0.5f);  // ������ �� ������
    glVertex2f(0.5f, -0.5f);  // ������ �Ʒ� ������
    glVertex2f(-0.5f, -0.5f);  // ���� �Ʒ� ������
    glEnd();  // �簢�� �׸��� ����
    
    glPopMatrix();  // ����� ��ȯ ��� ����
}

// �� ����ü (��ȯ ���� ����)
typedef struct
{
    Transform transform;  // ���� ��ġ, ȸ��, ũ�� ����
    int segments;  // ���� �׸��� ���� ���׸�Ʈ �� (���ָ� �� ���� �ﰢ������ ������ �׸���)
} Circle;

// ���� �׸��� �Լ�
void draw_circle(Circle* c, float r, float g, float b)
{
    glPushMatrix();  // ���� ��ȯ ��� ����

    // ��ġ ��ȯ (�̵�)
    glTranslatef(c->transform.position.x, c->transform.position.y, 0.0f);
    // ȸ�� ��ȯ (ȸ��)
    glRotatef(c->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    // ũ�� ��ȯ (������)
    glScalef(c->transform.scale.x, c->transform.scale.y, 1.0f);

    glBegin(GL_TRIANGLE_FAN);  // ���� �׸��� ���� (�� ����)
    glColor3f(r, g, b);  // ���� ������ �Ķ���
    glVertex2f(0.0f, 0.0f);  // ���� �߽�

    // ���� �׸��� ���� ���� ��� (���׸�Ʈ ���� ���� ���� ����)
    for (int i = 0; i <= c->segments; ++i)
    {
        float angle = 2.0f * PI * i / c->segments;  // ���� ���
        glVertex2f(cosf(angle) * 0.5f, sinf(angle) * 0.5f);  // ���� ���� �� ���
    }

    glEnd();  // �� �׸��� ����

    glPopMatrix();  // ����� ��ȯ ��� ����
}

// �̵� ����



// main �Լ�
int main()
{
    if (!glfwInit())  // GLFW �ʱ�ȭ ���н� ����
        return -1;

    // ������ ũ�� ����
    int width = 500, height = 500;
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL C Demo", NULL, NULL);
    if (!window)  // ������ ���� ���н� ����
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // OpenGL ���ؽ�Ʈ ����

    // �ȼ� ���� ��ǥ�� ���� (���� ����� (0, 0))
    glOrtho(0, width, height, 0, -1, 1);  // 2D ���� ���� ����
    glClearColor(1, 1, 1, 1);

    // ��ü �ʱ�ȭ (�ﰢ��, �簢��, ��)
    Square eye1 = { {{50, 220}, 0, {5, 20}} };  // �簢��: (100, 100) ��ġ, ũ�� 100x100
    Square eye2 = { {{150, 220}, 0, {5, 20}} };
    Circle cir1 = { {{100, height / 2}, 0, {200, 200}}, 64 };  // ��: ȭ�� �߾ӿ� ��ġ, ũ�� 100x100, ���׸�Ʈ 32��
    Square cut = { {{100, 260}, 0, {100, 50}} };
    Circle cir2 = { {{100, 280}, 0, {90, 90}}, 64 };
    
    // ���� ������ ����
    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();  // �ð� ���� ������

        glClear(GL_COLOR_BUFFER_BIT);  // ȭ���� ���� (����� ������� �ʱ�ȭ)

        // ��ü�� �׸���
        draw_circle(&cir1, 1.0f, 1.0f, 0.0f);  // �� �׸���
        draw_square(&eye1, 0.0f, 0.0f, 0.0f);
        draw_square(&eye2, 0.0f, 0.0f, 0.0f);
        draw_circle(&cir2, 0.0f, 0.0f, 0.0f);
        draw_square(&cut, 1.0f, 1.0f, 0.0f);

        glfwSwapBuffers(window);  // ȭ�� ���� (������ ���۸� ��ȯ)
        glfwPollEvents();  // ������ �̺�Ʈ ó�� (��: Ű����, ���콺 �̺�Ʈ)
    }

    glfwTerminate();  // GLFW ����
    return 0;
}
