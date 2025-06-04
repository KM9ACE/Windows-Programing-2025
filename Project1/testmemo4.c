#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>

#pragma comment(lib, "opengl32.lib")  // OpenGL ���̺귯�� ��ũ (������ ȯ��)

#define PI 3.1415926535f  // ������ ����

// 2D ���� ����ü
typedef struct {
    float x, y;
} Vec2;

// ��ġ, ȸ��, ������ ������ ��� ����ü
typedef struct {
    Vec2 position;   // ��ġ
    float rotation;  // ȸ�� (����)
    Vec2 scale;      // ũ�� (x, y)
} Transform;

// �ﰢ�� ��ü ����ü (��ȯ ���� ����)
typedef struct {
    Transform transform;
} TriangleObject;

// �簢�� ��ü ����ü (��ȯ ���� ����)
typedef struct {
    Transform transform;
} SquareObject;

// �׷� ��ü ����ü
// �׷� ��ü�� ��ȯ(transform)�� �ְ�, �� �ȿ� �ﰢ���� �簢���� ����
typedef struct {
    Transform transform;   // �׷� ��ü ��ȯ
    TriangleObject triangle;  // �ﰢ�� �ڽ� ��ü
    SquareObject square;      // �簢�� �ڽ� ��ü
} GroupObject;

// �ﰢ�� �׸��� �Լ�
// ���� ��ǥ��(�߽��� 0,0) ���� �ﰢ���� �׸���
void draw_triangle_object(const TriangleObject* tri)
{
    glPushMatrix(); // ���� ��� ���� ����

    // �ﰢ���� ��ġ, ȸ��, ũ�� ����
    glTranslatef(tri->transform.position.x, tri->transform.position.y, 0.0f);
    glRotatef(tri->transform.rotation * 180.0f / PI, 0.0f, 0.0f, 1.0f);  // ������ �� ������ ��ȯ
    glScalef(tri->transform.scale.x, tri->transform.scale.y, 1.0f);

    // �ﰢ�� �׸��� (������)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);     // ������ ����
    glVertex2f(-0.5f, -0.5f);   // ���� �Ʒ�
    glVertex2f(0.5f, -0.5f);    // ������ �Ʒ�
    glEnd();

    glPopMatrix(); // ��� ���� ����
}

// �簢�� �׸��� �Լ�
// ���� ��ǥ��(�߽��� 0,0) ���� �簢���� �׸���
void draw_square_object(const SquareObject* sq)
{
    glPushMatrix(); // ���� ��� ���� ����

    // �簢���� ��ġ, ȸ��, ũ�� ����
    glTranslatef(sq->transform.position.x, sq->transform.position.y, 0.0f);
    glRotatef(sq->transform.rotation * 180.0f / PI, 0.0f, 0.0f, 1.0f);  // ������ �� ������ ��ȯ
    glScalef(sq->transform.scale.x, sq->transform.scale.y, 1.0f);

    // �簢�� �׸��� (�Ķ���)
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.5f, 0.5f);   // ���� ��
    glVertex2f(0.5f, 0.5f);    // ������ ��
    glVertex2f(0.5f, -0.5f);   // ������ �Ʒ�
    glVertex2f(-0.5f, -0.5f);  // ���� �Ʒ�
    glEnd();

    glPopMatrix(); // ��� ���� ����
}

// �׷� ��ü �׸��� �Լ�
// �׷� ��ȯ�� ������ �ڿ� �ڽ� �������� �׸���
void draw_group_object(const GroupObject* group)
{
    glPushMatrix();  // ���� ��� ���� ����

    // �׷��� ��ȯ�� ���� ���� (�̵�, ȸ��, ������)
    // �� ��ȯ�� �׷� ���� ��� �ڽ� ������ ������ �ش�.
    glTranslatef(group->transform.position.x, group->transform.position.y, 0.0f);
    glRotatef(group->transform.rotation * 180.0f / PI, 0.0f, 0.0f, 1.0f);
    glScalef(group->transform.scale.x, group->transform.scale.y, 1.0f);

    // �׷� �� �ﰢ�� �׸���
    draw_triangle_object(&group->triangle);

    // �׷� �� �簢�� �׸���
    draw_square_object(&group->square);

    glPopMatrix();  // ��� ���� ����
}

int main(void)
{
    // GLFW �ʱ�ȭ
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // ������ ���� (800x800 ũ��)
    GLFWwindow* window = glfwCreateWindow(800, 800, "Group Transform Example", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // OpenGL ���ؽ�Ʈ�� ���� �����쿡 ����

    // ����Ʈ ���� (������ ũ��� �����ϰ�)
    glViewport(0, 0, 800, 800);

    // ���� ��� ���� (2D ���� ��ǥ�� -2 ~ 2 ����)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -1, 1);  // ��ǥ�� ���� (����, ������, �Ʒ�, ��, ��, ��)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // �׷� ��ü �ʱ�ȭ
    GroupObject group = { 0 };

    // �׷��� ��ġ, ȸ��, ������ �ʱⰪ ����
    group.transform.position.x = 0.0f;
    group.transform.position.y = 0.0f;
    group.transform.rotation = 0.0f;
    group.transform.scale.x = 1.0f;
    group.transform.scale.y = 1.0f;

    // �ﰢ���� ���� ��ġ�� �׷� �������� ���ʿ� ��ġ
    group.triangle.transform.position.x = -1.0f;
    group.triangle.transform.position.y = 0.0f;
    group.triangle.transform.rotation = 0.0f;
    group.triangle.transform.scale.x = 1.0f;
    group.triangle.transform.scale.y = 1.0f;

    // �簢���� ���� ��ġ�� �׷� �������� �����ʿ� ��ġ
    group.square.transform.position.x = 1.0f;
    group.square.transform.position.y = 0.0f;
    group.square.transform.rotation = 0.0f;
    group.square.transform.scale.x = 1.0f;
    group.square.transform.scale.y = 1.0f;

    // ���� ���� (�����찡 ���� ������ �ݺ�)
    while (!glfwWindowShouldClose(window))
    {
        // ȭ�� �ʱ�ȭ (���� �ʱ�ȭ)
        glClear(GL_COLOR_BUFFER_BIT);

        // �׷� �̵� �� ȸ�� ������Ʈ
        group.transform.position.x += 0.001f;  // ���������� õõ�� �̵�
        group.transform.rotation += 0.01f;     // �ݽð� �������� ȸ�� (����)

        // �׷�� �ڽ� ������ �׸���
        draw_group_object(&group);

        // ȭ�� ���� ���� (���� ���۸�)
        glfwSwapBuffers(window);

        // �̺�Ʈ ó�� (Ű����, ���콺 ��)
        glfwPollEvents();
    }

    // �ڿ� ����
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
