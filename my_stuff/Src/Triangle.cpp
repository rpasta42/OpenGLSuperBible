// Triangle.cpp
// Our first OpenGL program that will just draw a triangle on the screen.
#include <GLTools.h>
// OpenGL toolkit
#include <GLShaderManager.h> // Shader Manager Class

#define FREEGLUT_STATIC
#include <GL/glut.h>

GLBatch triangleBatch;
GLShaderManager shaderManager;


// This function does any needed initialization on the rendering context.
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC() {
   // Blue background
   glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
   shaderManager.InitializeStockShaders();
   // Load up a triangle
   GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
                        0.5f, 0.0f, 0.0f,
                        0.0f, 0.5f, 0.0f };
   triangleBatch.Begin(GL_TRIANGLES, 3);
   triangleBatch.CopyVertexData3f(vVerts);
   triangleBatch.End();
}

// Called to draw scene
void RenderScene(void) {
   // Clear the window with current clearing color
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
   shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
   triangleBatch.Draw();
   // Perform the buffer swap to display the back buffer
   glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[]) {
   gltSetWorkingDirectory(argv[0]);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
   glutInitWindowSize(800, 600);
   glutCreateWindow("Triangle");
   glutReshapeFunc([](int w, int h) { glViewport(0, 0, w, h); } );
   glutDisplayFunc(RenderScene);
   GLenum err = glewInit();
   if (GLEW_OK != err) {
      fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
      return 1;
   }
   SetupRC();
   glutMainLoop();
   return 0;
}

