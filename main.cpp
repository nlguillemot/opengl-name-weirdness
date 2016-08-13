#include <SDL.h>

#include "opengl.h"

extern "C"
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_Window* window = SDL_CreateWindow("opengl-name-weirdness", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    OpenGL_Init();

    const float tri[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        +0.0f, +0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, 0x1337);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0xF000);
    glBindBuffer(GL_ARRAY_BUFFER, 0x1337);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);

    while (true)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                goto quit;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(0xF000);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }

quit:
    return 0;
}