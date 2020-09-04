#include <OGLML/DynamicQuadRender.h>

#include <glew.h>
#include <glfw3.h>

using namespace oglml;

DynamicQuadRender::DynamicQuadRender()
{
    const short int VERTEX_NUM = 4;
    const short int VERTEX_COORD_TEX_COORD_NUM = 5;
    const short int VERTEX_COORD_NUM = 3;
    const short int TEX_COORD_NUM = 2;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VERTEX_NUM * VERTEX_COORD_TEX_COORD_NUM, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, VERTEX_COORD_NUM, GL_FLOAT, GL_FALSE, VERTEX_COORD_TEX_COORD_NUM * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, TEX_COORD_NUM, GL_FLOAT, GL_FALSE, VERTEX_COORD_TEX_COORD_NUM * sizeof(float), (void*)(VERTEX_COORD_NUM * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

DynamicQuadRender::~DynamicQuadRender()
{
    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);
}

DynamicQuadRender& DynamicQuadRender::Get()
{
    static DynamicQuadRender quadRender;
    return quadRender;
}

void DynamicQuadRender::Draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void DynamicQuadRender::BindVAO()
{
    glBindVertexArray(VAO);
}

void DynamicQuadRender::BindBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

