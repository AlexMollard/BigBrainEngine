#include <chrono>
#include <thread>
#include "window.h"
#include "Shapes.h"


#define xRES 720
#define yRES 480

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

float X = 1.0f;

void EngineLoop(float delta)
{


}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// Destroy the window and free memory
		Window_destroy();
		exit(0);
	}

	if (key == GLFW_KEY_W && action == GLFW_REPEAT)
	{
		X += 0.5f;
	}

	if (key == GLFW_KEY_S && action == GLFW_REPEAT)
	{
		X -= 0.5f;
	}
}

int main(int argc)
{
	srand(time(NULL));

	ShaderManager *shaderManager = new ShaderManager();

	// Shader Uniforms
	static float Scale = 1.0f;
	float timer = 0.0f;

	GLuint vBuffer;
	GLuint iBuffer;

	// Creating a window
	if (!Window_intit(xRES, yRES, (char*)"Big Brain"))
	{
		std::cout << "Failed to load window" << std::endl;
		return 1;
	}

	// Initializing Glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew is not havig a bad time" << std::endl;
	}

	// Outputting OpenGL Version and build
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	Cube3D newCube;

	static GLfloat g_color_buffer_data[12 * 3 * 3];
	for (int v = 0; v < 12 * 3; v++) 
	{
		float u = (rand() % 10000) / 10000.0;
		round(u);
		g_color_buffer_data[3 * v + 0] = u;
		 u = (rand() % 10000) / 10000.0;
		 round(u);

		g_color_buffer_data[3 * v + 1] = u;
		 u = (rand() % 10000) / 10000.0;
		 round(u);

		 g_color_buffer_data[3 * v + 2] = u;
	}

	glShadeModel(GL_FLAT);

	//Set up for model, can go in model file
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &vBuffer); // Vertex buffer
	glGenBuffers(1, &iBuffer); // indices buffer
	
	size_t vSize = sizeof(newCube.vertices);

	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferData(GL_ARRAY_BUFFER, vSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, newCube.vertices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(newCube.indices), newCube.indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// bind VBOs before drawing - unique per model, would to happen every frame
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);

	// enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);

	// specify vertex arrays with their offsets
	glVertexPointer(3, GL_FLOAT, 0, nullptr);

	// Get user input
	glfwSetKeyCallback(Window, key_callback);

	// Model ,View, Projection Matrix
	glm::mat4 mvp;
	glm::mat4 Projection = glm::perspective((float)glm::radians(45.0f), (float)xRES / (float)yRES, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	glm::mat4 Model = glm::mat4(1.0f);

	mvp = Projection * View * Model;

	// Get shader source
	ShaderPROSource source = shaderManager->ParseShader("Basic.shader");

	// Create shader program - init
	GLuint shader = shaderManager->CreateShader(source.VertexSource, source.FragmentSource);

	// Assign shader uniform variables
	GLuint colourID = glGetUniformLocation(shader, "triColour");
	GLuint iResolution = glGetUniformLocation(shader, "iResolution");
	GLuint iTime = glGetUniformLocation(shader, "iTime");
	GLuint MatrixID = glGetUniformLocation(shader, "MVP");

	// Use this shader - per frame
	glUseProgram(shader);

	// Binding buffers
	//glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

	glEnableVertexAttribArray(1);

	GLuint attribVertex = GL_VERTEX_ARRAY;

	// activate vertex attribs
	glEnableVertexAttribArray(attribVertex);

	// set attrib offsets using glVertexAttribPointer()
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	// Allow GPU to not draw vert over other verts
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Color buffer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Change uniforms
	glUniform2f(iResolution, xRES, yRES);
	glUniform1f(iTime, timer);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);


	// If the window is not closed enable the engine loop
	while (!Window_shouldClose())
	{
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		Window_update(EngineLoop);
		timer += 0.01f;

		View = glm::lookAt(
			glm::vec3(1, 1, 4), // Camera is at in World Space
			glm::vec3(X, 0, 1), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up
		);

		mvp = Projection * View * Model;

		// Change colour
		//glUniform3f(colourID, 1.0f, 1.0f, 0.0f);

		glUniform1f(iTime, timer);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);               
	}

	// disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);

	// deactivate vertex attribs
	glDisableVertexAttribArray(attribVertex);

	// unbind VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteProgram(shader);
//	glDeleteProgram(shaderTwo);
	delete shaderManager;

	// Destroy the window and free memory
	Window_destroy();

	return 0;
}
