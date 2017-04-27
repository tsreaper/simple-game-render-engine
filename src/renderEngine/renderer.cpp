#include "../glew.h"
#include "../models/rawModel.h"
#include "renderer.h"
#include <iostream>

using namespace std;

void Renderer::prepare()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 0, 0, 1);
}

void Renderer::render(TexturedModel* model)
{
    RawModel* raw = model->getRaw();
    glBindVertexArray(raw->getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model->getTexture()->getId());
    glDrawElements(GL_TRIANGLES, raw->getVertexCount(), GL_UNSIGNED_INT, NULL);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
