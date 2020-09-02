#include <OGLML/QuadRender.h>

#include <glew.h>
#include <glfw3.h>

using namespace oglml;

QuadRender::QuadRender()
{
    // 1/4of screen
    {
        float vertices[] = {
            // positions        // texture Coords
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &quadVAOv1);
        glGenBuffers(1, &VBO);
        glBindVertexArray(quadVAOv1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

QuadRender::~QuadRender()
{
    glDeleteVertexArrays(1, &quadVAOv1);
    glDeleteVertexArrays(1, &quadVAOfull);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VBOfull);
}

QuadRender& QuadRender::Get()
{
    static QuadRender quadRender;
    return quadRender;
}

void QuadRender::Draw()
{
    glBindVertexArray(quadVAOv1);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void QuadRender::DrawArraysInstanced(unsigned int instancedNumber)
{
    glBindVertexArray(quadVAOv1);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, instancedNumber);
    glBindVertexArray(0);
}

void QuadRender::BindVAO()
{
    glBindVertexArray(quadVAOv1);
}

void QuadRender::DrawFullQuad()
{
    if (!VBOfull)
    {
        float vertices[] = {
            // positions        // texture Coords
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &quadVAOfull);
        glGenBuffers(1, &VBOfull);
        glBindVertexArray(quadVAOfull);
        glBindBuffer(GL_ARRAY_BUFFER, VBOfull);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }

    glBindVertexArray(quadVAOfull);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

