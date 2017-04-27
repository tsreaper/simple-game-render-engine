#include "../glew.h"
#include "renderer.h"

void Renderer::prepare()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 0, 0, 1);
}

void Renderer::render(RawModel& model)
{
    glBindVertexArray(model.getVaoId());
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, NULL);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
