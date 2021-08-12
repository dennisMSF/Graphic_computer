//Integrantes:
//Dennis Marcell Sumiri Fernandez
//Jose Miguel Guzman Chauca
//Alexandra Jalixto Pacora

#define _USE_MATH_DEFINES
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include "colors.h"
#include "shaders.h"
#include <iostream>
#include <Windows.h>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
std::vector<float> dibujar_circulo(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
void mover_punto(float *vertices, int x, int y, float new__x, float new_y) {
	if (new__x < 1.0 || new_y < 1.0) {
		vertices[x] = new__x;
		vertices[y] = new_y;
	}
	else {
		return;
	}
}

void circle_vertices(float cv[], float Xo, float Yo, float radius, int triangleAmount) {
	for (int i = 0; i <= triangleAmount; i++) {
		cv[i * 3] = Xo + (radius * cos(i * 2 * 3.14 / triangleAmount));
		cv[i * 3 + 1] = Yo + (radius * sin(i * 2 * 3.14 / triangleAmount));
		cv[i * 3 + 2] = 0.0f;
	}
	cv[triangleAmount * 3] = cv[0];
	cv[triangleAmount * 3 + 1] = cv[1];
	cv[triangleAmount * 3 + 2] = cv[2];
}

int main() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	Shader myshader("vshader.fs/vshader.fs", "fshader.fs/fshader.fs");


	// this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	float vertices[] = {
		//TOP: IZQ -> DER (0-6)
		-0.56f, 0.75f, 0.0f,    // 0
		-0.4f, 0.75f, 0.0f,     // 1
		0.0f, 0.75f, 0.0f,      // 2
		0.2f, 0.75f, 0.0f,      // 3
		0.42f, 0.75f, 0.0f,     // 4
		0.48f, 0.75f, 0.0f,     // 5
		0.56f, 0.75f, 0.0f,     // 6

		//DOWN: IZQ -> DER (7-12)
		-0.56f, -0.75f, 0.0f,   // 7
		-0.39f, -0.75f, 0.0f,   // 8
		-0.26f, -0.75f, 0.0f,   // 9
		0.0f, -0.75f, 0.0f,     // 10
		0.4f, -0.75f, 0.0f,     // 11
		0.56f, -0.75f, 0.0f,    // 12

		//RIGHT: TOP -> DOWN (13-17)
		0.56f, 0.66f, 0.0f,     // 13
		0.56f, 0.42f, 0.0f,     // 14
		0.56f, 0.33f, 0.0f,     // 15
		0.56f, 0.0f, 0.0f,      // 16
		0.56f, -0.23f, 0.0f,    // 17

		//LEFT: TOP -> DOWN (18-25)
		-0.56f, 0.53f, 0.0f,    // 18
		-0.56f, 0.44f, 0.0f,    // 19
		-0.56f, 0.14f, 0.0f,    // 20
		-0.56f, 0.0f, 0.0f,     // 21
		-0.56f, -0.13f, 0.0f,   // 22
		-0.56f, -0.36f, 0.0f,   // 23
		-0.56f, -0.53f, 0.0f,   // 24
		-0.56f, -0.62f, 0.0f,   // 25

		//OTHERS: TOP-IZQ -> DOWN-DER (26-36)
		-0.08f, 0.66f, 0.0f,    // 26
		0.08f, 0.61f, 0.0f,     // 27
		-0.46f, 0.52f, 0.0f,    // 28
		-0.2f, 0.48f, 0.0f,		// 29
		-0.4f, 0.28f, 0.0f,     // 30
		0.28f, 0.19f, 0.0f,     // 31
		-0.36f, 0.0f, 0.0f,     // 32
		0.18f, -0.24f, 0.0f,    // 33
		-0.35f, -0.4f, 0.0f,    // 34
		0.07f, -0.59f, 0.0f,    // 35
		0.47f, -0.6f, 0.0f,     // 36
	};

	std::vector<float> aureola = dibujar_circulo(0.0f, 0.43f, 0.3f, 40, 4, 0.0f, 0.0f);
	std::cout << "empieza aqui" << std::endl;
	float circulo_contorno[]{
		0.26302, 0.293803, 0,
		0.285317, 0.337295, 0,
		0.296307, 0.38307, 0,
		0.3, 0.43, 0,
		0.296307, 0.47693, 0,
		0.285317, 0.522705, 0,
		0.267302, 0.566197, 0,
		0.242705, 0.606336, 0,
		0.212132, 0.642132, 0,
		0.176336, 0.672705, 0,
		0.136197, 0.697302, 0,
		0.0927051, 0.715317, 0,
		0.0469303, 0.726306, 0,
		1.83697e-17, 0.73, 0,
		-0.0469303, 0.726306, 0,
		-0.0927051, 0.715317, 0,
		-0.136197, 0.697302, 0,
		-0.176336, 0.672705, 0,
		-0.212132, 0.642132, 0,
		-0.242705, 0.606336, 0,
		-0.267302, 0.566197, 0,
		-0.285317, 0.522705, 0,
		-0.296307, 0.47693, 0,
		-0.3, 0.43, 0,
		-0.296307, 0.38307, 0,
		-0.285317, 0.337295, 0,
		-0.267302, 0.293803, 0,
		-0.242705, 0.253664, 0,
		-0.212132, 0.217868, 0,
		-0.176336, 0.187295, 0,
		-0.136197, 0.162698, 0,
		-0.0927051, 0.144683, 0,
		-0.0469303, 0.133693, 0,
		-5.51091e-17, 0.13, 0

	};
	float circulo_2_contorno[] = {
		0.0326585, -0.0636474, 0,
		0.023651, -0.0419014, 0,
		0.0113526, -0.0218322, 0,
		-0.00393398, -0.00393398, 0,
		-0.0218322, 0.0113526, 0,
		-0.0419014, 0.023651, 0,
		-0.0636474, 0.0326585, 0,
		-0.0865348, 0.0381533, 0,
		-0.11, 0.04, 0,
		-0.133465, 0.0381533, 0,
		-0.156353, 0.0326585, 0,
		-0.178099, 0.023651, 0,
		-0.198168, 0.0113526, 0,
		-0.216066, -0.00393398, 0,
		-0.231353, -0.0218322, 0,
		-0.243651, -0.0419014, 0,
		-0.252658, -0.0636474, 0,
		-0.258153, -0.0865348, 0,
		-0.26, -0.11, 0,
		-0.258153, -0.133465, 0,
		-0.252658, -0.156353, 0,
		-0.243651, -0.178099, 0,
		-0.231353, -0.198168, 0,
		-0.216066, -0.216066, 0
	};



	std::vector<float> aureola_2 = dibujar_circulo(-0.11f, -0.11f, 0.15f, 40, 4, 0.0f, 0.0f);



	float contorno[] = {
		//8, 34, 32, 30, 28, 0,
		-0.39f, -0.75f, 0.0f,   // 8
		-0.35f, -0.4f, 0.0f,    // 34
		-0.36f, 0.0f, 0.0f,     // 32
		-0.4f, 0.28f, 0.0f,     // 30
		-0.46f, 0.52f, 0.0f,    // 28
		-0.56f, 0.75f, 0.0f,    // 0

		//1, 28, 19, 18, 28, 29, 30, 20,
		-0.4f, 0.75f, 0.0f,     // 1
		-0.46f, 0.52f, 0.0f,    // 28
		-0.56f, 0.44f, 0.0f,    // 19
		-0.56f, 0.53f, 0.0f,    // 18
		-0.46f, 0.52f, 0.0f,    // 28
		-0.2f, 0.48f, 0.0f,    // 29
		-0.4f, 0.28f, 0.0f,     // 30
		-0.56f, 0.14f, 0.0f,    // 20

		//21, 32, 22, 23, 34, 31, 32, 33,
		-0.56f, 0.0f, 0.0f,     // 21
		-0.36f, 0.0f, 0.0f,     // 32
		-0.56f, -0.13f, 0.0f,   // 22
		-0.56f, -0.36f, 0.0f,   // 23
		-0.35f, -0.4f, 0.0f,    // 34
		0.28f, 0.19f, 0.0f,     // 31
		-0.36f, 0.0f, 0.0f,     // 32
		0.18f, -0.24f, 0.0f,    // 33

		//35, 10, 9, 25, 24, 34, 35, 17,
		0.07f, -0.59f, 0.0f,    // 35
		0.0f, -0.75f, 0.0f,     // 10
		-0.26f, -0.75f, 0.0f,   // 9
		-0.56f, -0.62f, 0.0f,   // 25
		-0.56f, -0.53f, 0.0f,   // 24
		-0.35f, -0.4f, 0.0f,    // 34
		0.07f, -0.59f, 0.0f,    // 35
		0.56f, -0.23f, 0.0f,    // 17

		//31, 33, 36, 11, 12, 36, 17,
		0.28f, 0.19f, 0.0f,     // 31
		0.18f, -0.24f, 0.0f,    // 33
		0.47f, -0.6f, 0.0f,     // 36
		0.4f, -0.75f, 0.0f,     // 11
		0.56f, -0.75f, 0.0f,    // 12
		0.47f, -0.6f, 0.0f,     // 36
		0.56f, -0.23f, 0.0f,    // 17

		//16, 31, 29, 26, 1, 2, 26, 27,
		0.56f, 0.0f, 0.0f,      // 16
		0.28f, 0.19f, 0.0f,     // 31
		-0.2f, 0.48f, 0.0f,    // 29
		-0.08f, 0.66f, 0.0f,    // 26
		-0.4f, 0.75f, 0.0f,     // 1
		0.0f, 0.75f, 0.0f,      // 2
		-0.08f, 0.66f, 0.0f,    // 26
		0.08f, 0.61f, 0.0f,     // 27

		//15, 16, 5, 6, 13, 14, 31, 27, 3,
		0.56f, 0.33f, 0.0f,     // 15
		0.56f, 0.0f, 0.0f,      // 16
		0.42f, 0.75f, 0.0f,     // 4
		0.48f, 0.75f, 0.0f,     // 5
		0.56f, 0.66f, 0.0f,     // 13
		0.56f, 0.42f, 0.0f,     // 14
		0.28f, 0.19f, 0.0f,     // 31
		0.08f, 0.61f, 0.0f,     // 27
		0.2f, 0.75f, 0.0f,      // 3

		//6, 12, 7, 0, 6
		0.56f, 0.75f, 0.0f,     // 6
		0.56f, -0.75f, 0.0f,    // 12
		-0.56f, -0.75f, 0.0f,   // 7
		-0.56f, 0.75f, 0.0f,    // 0
		0.56f, 0.75f, 0.0f     // 6
	};
	unsigned int indices[] = {
		8, 34, 32, 30, 28, 0,
		1, 28, 19, 18, 28, 29, 30, 20,
		21, 32, 22, 23, 34, 31, 32, 33,
		35, 10, 9, 25, 24, 34, 35, 17,
		31, 33, 36, 11, 12, 36, 17,
		16, 31, 29, 26, 1, 2, 26, 27,
		15, 16, 5, 6, 13, 14, 31, 27, 3,
		6, 12, 7, 0, 6
	};
	float v_color_fondo[] = {
		// Amarillo (0-3) //
		0.48f, 0.75f, 0.0f,
		0.56f, 0.75f, 0.0f,
		0.56f, 0.66f, 0.0f,

		// Amarillo Anaranjado (3-21) //
		0.48f, 0.75f, 0.0f,
		0.56f, 0.66f, 0.0f,
		0.56f, 0.33f, 0.0f,

		0.48f, 0.75f, 0.0f,
		0.56f, 0.33f, 0.0f,
		0.2f, 0.75f, 0.0f,

		0.56f, 0.33f, 0.0f,
		0.2f, 0.75f, 0.0f,
		0.08f, 0.61f, 0.0f,

		0.2f, 0.75f, 0.0f,
		0.08f, 0.61f, 0.0f,
		0.0f, 0.75f, 0.0f,

		0.0f, 0.75f, 0.0f,
		0.08f, 0.61f, 0.0f,
		-0.08f, 0.66f, 0.0f,

		-0.08f, 0.66f, 0.0f,
		0.0f, 0.75f, 0.0f,
		-0.4f, 0.75f, 0.0f,

		// Rojo (21-45) //
		-0.56f, 0.53f, 0.0f,
		-0.56f, 0.75f, 0.0f,
		-0.46f, 0.52f, 0.0f,

		-0.56f, 0.75f, 0.0f,
		-0.46f, 0.52f, 0.0f,
		-0.4f, 0.75f, 0.0f,

		-0.46f, 0.52f, 0.0f,
		-0.4f, 0.75f, 0.0f,
		-0.2f, 0.48f, 0.0f,

		-0.4f, 0.75f, 0.0f,
		-0.2f, 0.48f, 0.0f,
		-0.08f, 0.66f, 0.0f,

		-0.08f, 0.66f, 0.0f,
		-0.2f, 0.48f, 0.0f,
		0.08f, 0.61f, 0.0f,

		-0.2f, 0.48f, 0.0f,
		0.08f, 0.61f, 0.0f,
		0.28f, 0.19f, 0.0f,

		0.08f, 0.61f, 0.0f,
		0.28f, 0.19f, 0.0f,
		0.56f, 0.33f, 0.0f,

		0.28f, 0.19f, 0.0f,
		0.56f, 0.33f, 0.0f,
		0.56f, -0.23f, 0.0f,

		// Fucsia (45-60) //
		0.0f, -0.75f, 0.0f,
		0.4f, -0.75f, 0.0f,
		0.07f, -0.59f, 0.0f,

		0.4f, -0.75f, 0.0f,
		0.07f, -0.59f, 0.0f,
		0.47f, -0.6f, 0.0f,

		0.47f, -0.6f, 0.0f,
		0.07f, -0.59f, 0.0f,
		0.18f, -0.24f, 0.0f,

		0.18f, -0.24f, 0.0f,
		0.47f, -0.6f, 0.0f,
		0.56f, -0.23f, 0.0f,

		0.18f, -0.24f, 0.0f,
		0.56f, -0.23f, 0.0f,
		0.28f, 0.19f, 0.0f,

		// Morado (60-66) //
		0.56f, -0.75f, 0.0f,
		0.4f, -0.75f, 0.0f,
		0.47f, -0.6f, 0.0f,

		0.47f, -0.6f, 0.0f,
		0.56f, -0.75f, 0.0f,
		0.56f, -0.23f, 0.0f,

		// Celeste (66-81) //
		-0.35f, -0.4f, 0.0f,
		0.07f, -0.59f, 0.0f,
		0.18f, -0.24f, 0.0f,

		-0.35f, -0.4f, 0.0f,
		0.18f, -0.24f, 0.0f,
		-0.36f, 0.0f, 0.0f,

		0.18f, -0.24f, 0.0f,
		-0.36f, 0.0f, 0.0f,
		0.28f, 0.19f, 0.0f,

		-0.36f, 0.0f, 0.0f,
		0.28f, 0.19f, 0.0f,
		-0.4f, 0.28f, 0.0f,

		0.28f, 0.19f, 0.0f,
		-0.4f, 0.28f, 0.0f,
		-0.2f, 0.48f, 0.0f,

		// Azul1 (81-90) //
		-0.56f, -0.36f, 0.0f,
		-0.56f, 0.14f, 0.0f,
		-0.36f, 0.0f, 0.0f,

		-0.56f, 0.14f, 0.0f,
		-0.36f, 0.0f, 0.0f,
		-0.4f, 0.28f, 0.0f,

		-0.36f, 0.0f, 0.0f,
		-0.56f, -0.36f, 0.0f,
		-0.35f, -0.4f, 0.0f,

		// Azul2 (90-99) //
		-0.56f, 0.14f, 0.0f,
		-0.4f, 0.28f, 0.0f,
		-0.56f, 0.53f, 0.0f,

		-0.56f, 0.53f, 0.0f,
		-0.46f, 0.52f, 0.0f,
		-0.4f, 0.28f, 0.0f,

		-0.46f, 0.52f, 0.0f,
		-0.4f, 0.28f, 0.0f,
		-0.2f, 0.48f, 0.0f,

		// Verde1 (99-111) //
		-0.56f, -0.62f, 0.0f,
		-0.56f, -0.36f, 0.0f,
		-0.35f, -0.4f, 0.0f,

		-0.56f, -0.62f, 0.0f,
		-0.26f, -0.75f, 0.0f,
		-0.35f, -0.4f, 0.0f,

		-0.26f, -0.75f, 0.0f,
		-0.35f, -0.4f, 0.0f,
		0.07f, -0.59f, 0.0f,

		-0.26f, -0.75f, 0.0f,
		0.07f, -0.59f, 0.0f,
		0.0f, -0.75f, 0.0f,

		// Azul2 (111-114) //
		-0.56f, -0.75f, 0.0f,
		-0.56f, -0.62f, 0.0f,
		-0.26f, -0.75f, 0.0f,
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////VIRGEN////////////////////////////////////////////////////

	float contorno_imagen[] = {
		/////////////////////gris_pecho(7)
		0.03f, -0.09f, 0.0f,
		0.07f, 0.08f, 0.0f,
		0.05f, 0.17f, 0.0f,

		0.01f, 0.15f, 0.0f,
		-0.03f, 0.09f, 0.0f,
		-0.06f, 0.03f, 0.0f,

		0.03f, -0.09f, 0.0f,

		////////////////////piel_cuello(5)
		0.0f, 0.2f, 0.0f,
		0.04f, 0.22f, 0.0f,
		0.05f, 0.17f, 0.0f,

		0.01f, 0.15f, 0.0f,
		0.0f, 0.2f, 0.0f,

		//////////////////////Piel_cara_virgen(12)
		-0.19f, 0.43f, 0.0f,
		-0.19, 0.39f, 0.0f,
		-0.17f, 0.33f, 0.0f,

		-0.13f, 0.3f, 0.0f,
		-0.13f, 0.25f, 0.0f,
		-0.1f, 0.25f, 0.0f,

		-0.07f, 0.21f, 0.0f,
		0.0f, 0.2f, 0.0f,
		0.04f, 0.22f, 0.0f,

		0.01f, 0.33f, 0.0f,
		-0.06f, 0.41f, 0.0f,
		-0.19f, 0.43f, 0.0f,

		//////////////////////cafe_cabello_virgen(8)
		-0.2f, 0.48f, 0.0f,
		-0.15f, 0.51f, 0.0f,
		-0.08f, 0.51f, 0.0f,

		-0.01f, 0.43f, 0.0f,
		0.01f, 0.33f, 0.0f,
		-0.06f, 0.41f, 0.0f,

		-0.19f, 0.43f, 0.0f,
		-0.2f, 0.48f, 0.0f,

		////////////////////gris_centro(10)
		0.04f, -0.64f, 0.0f,
		0.09f, -0.59f, 0.0f,
		0.20f, -0.27f, 0.0f,

		0.19f, 0.13f, 0.0f,
		-0.01f, 0.43f, 0.0f,
		0.01f, 0.33f, 0.0f,

		0.07f, 0.08f, 0.0f,
		0.00f, -0.19f, 0.0f,
		0.06f, -0.44f, 0.0f,

		0.04f, -0.64f, 0.0f,

		////////////////////celeste_arriba(11)
		-0.2f, 0.48f, 0.0f,
		-0.15f, 0.51f, 0.0f,
		-0.08f, 0.51f, 0.0f,

		-0.01f, 0.43f, 0.0f,
		0.19f, 0.13f, 0.0f,
		0.2f, -0.27f, 0.0f,

		0.31f, 0.17f, 0.0f,
		0.21f, 0.33f, 0.0f,
		0.09f, 0.48f, 0.0f,

		-0.12f, 0.58f, 0.0f,
		-0.2f, 0.48f, 0.0f,

		////////////////////gris_arriba_derecha(9)
		-0.12f, 0.58f, 0.0f,
		-0.02f, 0.62f, 0.0f,
		0.08f, 0.61f, 0.0f,

		0.14f, 0.57f, 0.0f,
		0.26f, 0.37f, 0.0f,
		0.31f, 0.17f, 0.0f,

		0.21f, 0.33f, 0.0f,
		0.09f, 0.48f, 0.0f,
		-0.12f, 0.58f, 0.0f,

		////////////////////Celeste Abajo Der(7)
		0.35f, 0.03f, 0.0f,
		0.33f, -0.27f, 0.0f,
		0.3f, -0.5f, 0.0f,

		0.2f, -0.72f, 0.0f,
		0.39f, -0.61f, 0.0f,
		0.4f, -0.23f, 0.0f,

		0.35f, 0.03f, 0.0f,

		////////////////////gris_abajo_derecha(11)
		-0.05f, -0.73f, 0.0f,
		0.08f, -0.75f, 0.0f,
		0.20f, -0.72f, 0.0f,

		0.30f, -0.50f, 0.0f,
		0.33f, -0.27f, 0.0f,
		0.35f, 0.03f, 0.0f,

		0.31f, 0.17f, 0.0f,
		0.20f, -0.27f, 0.0f,
		0.09f, -0.59f, 0.0f,

		0.04f, -0.64f, 0.0f,
		-0.05f, -0.73f, 0.0f,

		////////////////////Celeste Abajo Izq(7)
		0.0f, -0.19f, 0.0f,
		-0.07f, -0.52f, 0.0f,
		-0.23f, -0.64f, 0.0f,

		-0.05f, -0.73f, 0.0f,
		0.04f, -0.64f, 0.0f,
		0.06f, -0.44f, 0.0f,

		0.0f, -0.19f, 0.0f,

		////////////////////gris_abajo_izquierda(7)
		-0.23f, -0.64f, 0.0f,
		-0.07f, -0.52f, 0.0f,
		0.00f, -0.19f, 0.0f,

		-0.12f, -0.45f, 0.0f,
		-0.22f, -0.49f, 0.0f,
		-0.31f, -0.49f, 0.0f,

		-0.23f, -0.64f, 0.0f,

		////////////////////Piel Mano Virgen(22)
		-0.31f, -0.49f, 0.0f,
		-0.22f, -0.49f, 0.0f,
		-0.12f, -0.45f, 0.0f,

		-0.19f, -0.43f, 0.0f,
		-0.23f, -0.39f, 0.0f,
		-0.23f, -0.3f, 0.0f,

		-0.19f, -0.28f, 0.0f,
		-0.15f, -0.27f, 0.0f,
		-0.09f, -0.24f, 0.0f,

		-0.08f, -0.21f, 0.0f,
		-0.1f, -0.2f, 0.0f,
		-0.14f, -0.22f, 0.0f,

		-0.21f, -0.23f, 0.0f,
		-0.22f, -0.21f, 0.0f,
		-0.16f, -0.09f, 0.0f,

		-0.1f, -0.04f, 0.0f,
		-0.11f, -0.02f, 0.0f,
		-0.14f, -0.02f, 0.0f,

		-0.21f, -0.09f, 0.0f,
		-0.29f, -0.27f, 0.0f,
		-0.31f, -0.37f, 0.0f,

		-0.31f, -0.49f, 0.0f,

		////////////////////Piel Cuerpo Niño(18)
		-0.12f, -0.45f, 0.0f,
		-0.02f, -0.24f, 0.0f,
		-0.06f, -0.19f, 0.0f,

		-0.07f, -0.18f, 0.0f,
		-0.13f, -0.17f, 0.0f,
		-0.16f, -0.16f, 0.0f,

		-0.22f, -0.21f, 0.0f,
		-0.21f, -0.23f, 0.0f,
		-0.14f, -0.22f, 0.0f,

		-0.1f, -0.2f, 0.0f,
		-0.08f, -0.21f, 0.0f,
		-0.09f, -0.24f, 0.0f,

		-0.15f, -0.27f, 0.0f,
		-0.19f, -0.28f, 0.0f,
		-0.23f, -0.30f, 0.0f,

		-0.23f, -0.39f, 0.0f,
		-0.19f, -0.43f, 0.0f,
		-0.12f, -0.45f, 0.0f,

		////////////////////Piel Cara Ni�o(10)
		-0.02f, -0.1f, 0.0f,
		-0.05f, -0.11f, 0.0f,
		-0.09f, -0.11f, 0.0f,

		-0.13f, -0.17f, 0.0f,
		-0.07f, -0.18f, 0.0f,
		-0.06f, -0.19f, 0.0f,

		-0.045f, -0.18f, 0.0f,
		-0.04f, -0.15f, 0.0f,
		-0.02f, -0.13f, 0.0f,

		-0.02f, -0.1f, 0.0f,

		//////////////////// Cafe Pelo Ni�o(11)
		-0.16f, -0.16f, 0.0f,
		-0.17f, -0.11f, 0.0f,
		-0.16f, -0.09f, 0.0f,

		-0.1f, -0.04f, 0.0f,
		-0.06f, -0.05f, 0.0f,
		-0.02f, -0.07f, 0.0f,

		-0.02f, -0.1f, 0.0f,
		-0.05f, -0.11f, 0.0f,
		-0.09f, -0.11f, 0.0f,

		-0.13f, -0.17f, 0.0f,
		-0.16f, -0.16f, 0.0f
	};
	float v_piel[] = {
		//Mano & Niño
		-0.11f, -0.02f, 0.0f,
		-0.14f, -0.02f, 0.0f,
		-0.1f, -0.04f, 0.0f,

		-0.14f, -0.02f, 0.0f,
		-0.1f, -0.04f, 0.0f,
		-0.21f, -0.09f, 0.0f,

		-0.1f, -0.04f, 0.0f,
		-0.21f, -0.09f, 0.0f,
		-0.16f, -0.09f, 0.0f,

		-0.16f, -0.09f, 0.0f,
		-0.17f, -0.11f, 0.0f,
		-0.21f, -0.09f, 0.0f,

		-0.17f, -0.11f, 0.0f,
		-0.21f, -0.09f, 0.0f,
		-0.22f, -0.21f, 0.0f,

		-0.21f, -0.09f, 0.0f,
		-0.22f, -0.21f, 0.0f,
		-0.29f, -0.27f, 0.0f,

		-0.29f, -0.27f, 0.0f,
		-0.31f, -0.37f, 0.0f,
		-0.31f, -0.49f, 0.0f,

		-0.29f, -0.27f, 0.0f,
		-0.22f, -0.21f, 0.0f,
		-0.31f, -0.49f, 0.0f,

		-0.31f, -0.49f, 0.0f,
		-0.22f, -0.21f, 0.0f,
		-0.22f, -0.49f, 0.0f,

		-0.22f, -0.49f, 0.0f,
		-0.22f, -0.21f, 0.0f,
		-0.12f, -0.45f, 0.0f,

		-0.12f, -0.45f, 0.0f,
		-0.22f, -0.21f, 0.0f,
		-0.02f, -0.24f, 0.0f,

		-0.22f, -0.21f, 0.0f,
		-0.02f, -0.24f, 0.0f,
		-0.16f, -0.16f, 0.0f,

		-0.02f, -0.24f, 0.0f,
		-0.13f, -0.17f, 0.0f,
		-0.16f, -0.16f, 0.0f,

		-0.02f, -0.24f, 0.0f,
		-0.06f, -0.19f, 0.0f,
		-0.13f, -0.17f, 0.0f,

		-0.13f, -0.17f, 0.0f,
		-0.09f, -0.11f, 0.0f,
		-0.06f, -0.19f, 0.0f,

		-0.09f, -0.11f, 0.0f,
		-0.04f, -0.18f, 0.0f,
		-0.06f, -0.19f, 0.0f,

		-0.09f, -0.11f, 0.0f,
		-0.04f, -0.15f, 0.0f,
		-0.04f, -0.18f, 0.0f,

		-0.02f, -0.13f, 0.0f,
		-0.09f, -0.11f, 0.0f,
		-0.04f, -0.15f, 0.0f,

		-0.09f, -0.11f, 0.0f,
		-0.02f, -0.13f, 0.0f,
		-0.05f, -0.11f, 0.0f,

		-0.02f, -0.13f, 0.0f,
		-0.05f, -0.11f, 0.0f,
		-0.02f, -0.1f, 0.0f,

		// Cara Virgen
		-0.19f, 0.43f, 0.0f,
		-0.06f, 0.41f, 0.0f,
		-0.19, 0.39f, 0.0f,

		-0.17f, 0.33f, 0.0f,
		-0.06f, 0.41f, 0.0f,
		-0.19, 0.39f, 0.0f,

		-0.17f, 0.33f, 0.0f,
		-0.06f, 0.41f, 0.0f,
		0.01f, 0.33f, 0.0f,

		-0.17f, 0.33f, 0.0f,
		0.01f, 0.33f, 0.0f,
		-0.13f, 0.3f, 0.0f,

		-0.13f, 0.3f, 0.0f,
		-0.13f, 0.25f, 0.0f,
		-0.1f, 0.25f, 0.0f,

		-0.13f, 0.3f, 0.0f,
		-0.1f, 0.25f, 0.0f,
		0.01f, 0.33f, 0.0f,

		0.01f, 0.33f, 0.0f,
		-0.1f, 0.25f, 0.0f,
		-0.07f, 0.21f, 0.0f,

		0.01f, 0.33f, 0.0f,
		-0.07f, 0.21f, 0.0f,
		0.0f, 0.2f, 0.0f,

		0.01f, 0.33f, 0.0f,
		0.0f, 0.2f, 0.0f,
		0.04f, 0.22f, 0.0f,

		0.0f, 0.2f, 0.0f,
		0.04f, 0.22f, 0.0f,
		0.01f, 0.15f, 0.0f,

		0.04f, 0.22f, 0.0f,
		0.01f, 0.15f, 0.0f,
		0.05f, 0.17f, 0.0f
	};
	float v_celeste_ropa[] = {
		//Celeste Abajo Der(12)
		0.2f, -0.72f, 0.0f,
		0.39f, -0.61f, 0.0f,
		0.3f, -0.5f, 0.0f,

		0.39f, -0.61f, 0.0f,
		0.3f, -0.5f, 0.0f,
		0.33f, -0.27f, 0.0f,

		0.33f, -0.27f, 0.0f,
		0.39f, -0.61f, 0.0f,
		0.4f, -0.23f, 0.0f,

		0.33f, -0.27f, 0.0f,
		0.4f, -0.23f, 0.0f,
		0.35f, 0.03f, 0.0f,

		//Celeste Abajo Izq(12)
		0.0f, -0.19f, 0.0f,
		0.06f, -0.44f, 0.0f,
		-0.07f, -0.52f, 0.0f,

		0.06f, -0.44f, 0.0f,
		-0.07f, -0.52f, 0.0f,
		0.04f, -0.64f, 0.0f,

		-0.07f, -0.52f, 0.0f,
		0.04f, -0.64f, 0.0f,
		-0.05f, -0.73f, 0.0f,

		-0.05f, -0.73f, 0.0f,
		-0.07f, -0.52f, 0.0f,
		-0.23f, -0.64f, 0.0f,

		//celeste_arriba(24)
		0.2f, -0.27f, 0.0f,
		0.19f, 0.13f, 0.0f,
		0.31f, 0.17f, 0.0f,

		0.19f, 0.13f, 0.0f,
		0.31f, 0.17f, 0.0f,
		0.21f, 0.33f, 0.0f,

		0.21f, 0.33f, 0.0f,
		0.19f, 0.13f, 0.0f,
		0.09f, 0.48f, 0.0f,

		0.19f, 0.13f, 0.0f,
		0.09f, 0.48f, 0.0f,
		-0.01f, 0.43f, 0.0f,

		0.09f, 0.48f, 0.0f,
		-0.01f, 0.43f, 0.0f,
		-0.08f, 0.51f, 0.0f,

		-0.08f, 0.51f, 0.0f,
		0.09f, 0.48f, 0.0f,
		-0.12f, 0.58f, 0.0f,

		-0.12f, 0.58f, 0.0f,
		-0.08f, 0.51f, 0.0f,
		-0.15f, 0.51f, 0.0f,

		-0.15f, 0.51f, 0.0f,
		-0.12f, 0.58f, 0.0f,
		-0.2f, 0.48f, 0.0f,
	};
	float v_cafe[] = {
		// Cabello Niño
		-0.17f, -0.11f, 0.0f,
		-0.16f, -0.16f, 0.0f,
		-0.13f, -0.17f, 0.0f,

		-0.17f, -0.11f, 0.0f,
		-0.13f, -0.17f, 0.0f,
		-0.09, -0.11f, 0.0f,

		-0.09, -0.11f, 0.0f,
		-0.17f, -0.11f, 0.0f,
		-0.16f, -0.09f, 0.0f,

		-0.16f, -0.09f, 0.0f,
		-0.09, -0.11f, 0.0f,
		-0.1f, -0.04f, 0.0f,

		-0.09, -0.11f, 0.0f,
		-0.1f, -0.04f, 0.0f,
		-0.05f, -0.11f, 0.0f,

		-0.1f, -0.04f, 0.0f,
		-0.05f, -0.11f, 0.0f,
		-0.02f, -0.1f, 0.0f,

		-0.02f, -0.1f, 0.0f,
		-0.1f, -0.04f, 0.0f,
		-0.06f, -0.05f, 0.0f,

		-0.06f, -0.05f, 0.0f,
		-0.02f, -0.1f, 0.0f,
		-0.02f, -0.07f, 0.0f,

		//Cabello Virgen
		-0.2f, 0.48f, 0.0f,
		-0.15f, 0.51f, 0.0f,
		-0.19f, 0.43f, 0.0f,

		-0.15f, 0.51f, 0.0f,
		-0.19f, 0.43f, 0.0f,
		-0.08f, 0.51f, 0.0f,

		-0.19f, 0.43f, 0.0f,
		-0.08f, 0.51f, 0.0f,
		-0.06f, 0.41f, 0.0f,

		-0.08f, 0.51f, 0.0f,
		-0.06f, 0.41f, 0.0f,
		-0.01f, 0.43f, 0.0f,

		-0.06f, 0.41f, 0.0f,
		-0.01f, 0.43f, 0.0f,
		0.01f, 0.33f, 0.0f
	};
	float v_gris[] = {
		//gris_pecho(12)
		0.03f, -0.09f, 0.0f,
		0.07f, 0.08f, 0.0f,
		-0.06f, 0.03f, 0.0f,

		0.07f, 0.08f, 0.0f,
		-0.06f, 0.03f, 0.0f,
		-0.03f, 0.09f, 0.0f,

		-0.03f, 0.09f, 0.0f,
		0.07f, 0.08f, 0.0f,
		0.01f, 0.15f, 0.0f,

		0.07f, 0.08f, 0.0f,
		0.01f, 0.15f, 0.0f,
		0.05f, 0.17f, 0.0f,

		//gris_centro(18)
		0.04f, -0.64f, 0.0f,
		0.09f, -0.59f, 0.0f,
		0.06f, -0.44f, 0.0f,

		0.09f, -0.59f, 0.0f,
		0.06f, -0.44f, 0.0f,
		0.20f, -0.27f, 0.0f,

		0.06f, -0.44f, 0.0f,
		0.20f, -0.27f, 0.0f,
		0.00f, -0.19f, 0.0f,

		0.20f, -0.27f, 0.0f,
		0.00f, -0.19f, 0.0f,
		0.19f, 0.13f, 0.0f,

		0.19f, 0.13f, 0.0f,
		0.07f, 0.08f, 0.0f,
		0.00f, -0.19f, 0.0f,

		0.19f, 0.13f, 0.0f,
		0.07f, 0.08f, 0.0f,
		-0.01f, 0.43f, 0.0f,

		//gris_arriba_derecha(18)
		0.26f, 0.37f, 0.0f,
		0.31f, 0.17f, 0.0f,
		0.21f, 0.33f, 0.0f,

		0.26f, 0.37f, 0.0f,
		0.21f, 0.33f, 0.0f,
		0.14f, 0.57f, 0.0f,

		0.21f, 0.33f, 0.0f,
		0.14f, 0.57f, 0.0f,
		0.09f, 0.48f, 0.0f,

		0.14f, 0.57f, 0.0f,
		0.09f, 0.48f, 0.0f,
		0.08f, 0.61f, 0.0f,

		0.09f, 0.48f, 0.0f,
		0.08f, 0.61f, 0.0f,
		-0.02f, 0.62f, 0.0f,

		-0.02f, 0.62f, 0.0f,
		0.09f, 0.48f, 0.0f,
		-0.12f, 0.58f, 0.0f,

		//gris_abajo_derecha(21)
		-0.05f, -0.73f, 0.0f,
		0.09f, -0.59f, 0.0f,
		0.08f, -0.75f, 0.0f,

		0.09f, -0.59f, 0.0f,
		0.08f, -0.75f, 0.0f,
		0.20f, -0.72f, 0.0f,

		0.09f, -0.59f, 0.0f,
		0.20f, -0.72f, 0.0f,
		0.30f, -0.50f, 0.0f,

		0.09f, -0.59f, 0.0f,
		0.30f, -0.50f, 0.0f,
		0.20f, -0.27f, 0.0f,

		0.30f, -0.50f, 0.0f,
		0.20f, -0.27f, 0.0f,
		0.33f, -0.27f, 0.0f,

		0.20f, -0.27f, 0.0f,
		0.33f, -0.27f, 0.0f,
		0.35f, 0.03f, 0.0f,

		0.20f, -0.27f, 0.0f,
		0.35f, 0.03f, 0.0f,
		0.31f, 0.17f, 0.0f,

		//gris_abajo_izquierda(12)
		-0.07f, -0.52f, 0.0f,
		0.00f, -0.19f, 0.0f,
		-0.12f, -0.45f, 0.0f,

		-0.12f, -0.45f, 0.0f,
		-0.07f, -0.52f, 0.0f,
		-0.22f, -0.49f, 0.0f,

		-0.07f, -0.52f, 0.0f,
		-0.22f, -0.49f, 0.0f,
		-0.23f, -0.64f, 0.0f,

		-0.22f, -0.49f, 0.0f,
		-0.23f, -0.64f, 0.0f,
		-0.31f, -0.49f, 0.0f, };

	float circle[63];
	int triangleAmount_ = 20;
	float Xo_ = 0.0f; float Yo_ = 0.0f; float radius_ = 0.5f;
	circle_vertices(circle, Xo_, Yo_, radius_, triangleAmount_);

	////////////////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window)) {
	unsigned int VBOs[11], VAOs[11];
	glGenVertexArrays(11, VAOs);
	glGenBuffers(11, VBOs);

	// Colores setup
	// --------------------
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_color_fondo), v_color_fondo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Contorno setup
	// --------------------
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(contorno), contorno, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Contorno_imagen setup
	// --------------------
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(contorno_imagen), contorno_imagen, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//aureola 1
	// --------------------
	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, aureola.size() , &aureola.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//aureola 2
	// --------------------
	glBindVertexArray(VAOs[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
	glBufferData(GL_ARRAY_BUFFER, aureola_2.size() , &aureola_2.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Color piel
	// --------------------
	glBindVertexArray(VAOs[5]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_piel), v_piel, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Color CelesteRopa
	// --------------------
	glBindVertexArray(VAOs[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_celeste_ropa), v_celeste_ropa, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Color Cafe
	// --------------------
	glBindVertexArray(VAOs[7]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_cafe), v_cafe, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Color Gris
	// --------------------
	glBindVertexArray(VAOs[8]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_gris), v_gris, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[9]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circulo_contorno), circulo_contorno, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[10]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[10]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circulo_2_contorno), circulo_2_contorno, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// render loop
	// -----------

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		myshader.use();
		///////////////////5 6 7 8
		float timeValue = glfwGetTime();

		///////////////////
		myshader.setColor("ourColor",HEX_COLOR(yellow));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		myshader.setColor("ourColor", HEX_COLOR(lightyellow));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 3, 18);

		myshader.setColor("ourColor", HEX_COLOR(red));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 21, 24);

		myshader.setColor("ourColor", HEX_COLOR(fuchsia));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 45, 15);

		myshader.setColor("ourColor", HEX_COLOR(purple));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 60, 6);

		myshader.setColor("ourColor", HEX_COLOR(skyblue));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 66, 15);

		myshader.setColor("ourColor", HEX_COLOR(blue));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(100);
		glDrawArrays(GL_TRIANGLES, 81, 9);

		myshader.setColor("ourColor", HEX_COLOR(lightblue));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 90, 9);

		myshader.setColor("ourColor", HEX_COLOR(green));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 99, 12);

		myshader.setColor("ourColor", HEX_COLOR(lightgreen));
		glBindVertexArray(VAOs[0]);
		mover_punto(v_color_fondo, (rand() % sizeof(v_color_fondo) / 4), (rand() % sizeof(v_color_fondo) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 111, 3);

		myshader.setColor("ourColor", HEX_COLOR(yellow));
		glBindVertexArray(VAOs[3]);
		glDrawArrays(GL_TRIANGLES, 0, 120);

		myshader.setColor("ourColor", HEX_COLOR(black));
		glBindVertexArray(VAOs[1]);
		glLineWidth(4.5f);
		glDrawArrays(GL_LINE_STRIP, 0, 59);

		myshader.setColor("ourColor", HEX_COLOR(gray));
		glBindVertexArray(VAOs[8]);
		glDrawArrays(GL_TRIANGLES, 0, 12);

		myshader.setColor("ourColor", HEX_COLOR(black));
		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_LINE_STRIP, 0, 7);

		myshader.setColor("ourColor", HEX_COLOR(yellow));
		glBindVertexArray(VAOs[4]);
		glDrawArrays(GL_TRIANGLES, 0, 120);

		myshader.setColor("ourColor", HEX_COLOR(black));
		glBindVertexArray(VAOs[9]);
		glLineWidth(4.5f);

		glDrawArrays(GL_LINE_STRIP, 0, 34);//borde aureola1
		glBindVertexArray(VAOs[10]);
		glLineWidth(4.5f);
		glDrawArrays(GL_LINE_STRIP, 0, 24);//borde aureola2
		////////////////////////////////////////////////////////////////////////////////

		myshader.setColor("ourColor", HEX_COLOR(lightpink));
		glBindVertexArray(VAOs[5]);
		mover_punto(v_piel, (rand() % sizeof(v_piel)/4), (rand() % sizeof(v_piel) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(v_piel));

		myshader.setColor("ourColor", HEX_COLOR(brown));
		glBindVertexArray(VAOs[7]);
		mover_punto(v_cafe, (rand() % sizeof(v_cafe) / 4), (rand() % sizeof(v_cafe) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(v_cafe));

		myshader.setColor("ourColor", HEX_COLOR(gray));
		glBindVertexArray(VAOs[8]);
		mover_punto(v_gris, (rand() % sizeof(v_gris) / 4), (rand() % sizeof(v_gris) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 12, sizeof(v_gris));

		myshader.setColor("ourColor", HEX_COLOR(skyblue));
		glBindVertexArray(VAOs[6]);
		//Sleep(100);
		mover_punto(v_celeste_ropa, (rand() % sizeof(v_celeste_ropa) / 4), (rand() % sizeof(v_celeste_ropa) / 4), timeValue*double(rand() / 10e+4), timeValue*double(rand() / 10e+4));
		Sleep(50);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(v_celeste_ropa));

		myshader.setColor("ourColor", HEX_COLOR(black));
		glBindVertexArray(VAOs[2]);
		glLineWidth(4.5f);
		glDrawArrays(GL_LINE_STRIP, 7, 5);
		glDrawArrays(GL_LINE_STRIP, 12, 12);
		glDrawArrays(GL_LINE_STRIP, 24, 8);
		glDrawArrays(GL_LINE_STRIP, 32, 10);
		glDrawArrays(GL_LINE_STRIP, 42, 11);
		glDrawArrays(GL_LINE_STRIP, 53, 9);
		glDrawArrays(GL_LINE_STRIP, 62, 7);
		glDrawArrays(GL_LINE_STRIP, 69, 11);
		glDrawArrays(GL_LINE_STRIP, 80, 7);
		glDrawArrays(GL_LINE_STRIP, 87, 7);
		glDrawArrays(GL_LINE_STRIP, 94, 22);
		glDrawArrays(GL_LINE_STRIP, 116, 18);
		glDrawArrays(GL_LINE_STRIP, 134, 10);
		glDrawArrays(GL_LINE_STRIP, 144, 11);
		
		/*
		glUseProgram(shaderProgramCelesteRopa);
		glBindVertexArray(VAOs[5]);
		glLineWidth(4.5f);
		glDrawArrays(GL_LINE_STRIP, 0, 21);*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(11, VAOs);
	//glDeleteBuffers(11, VBOs);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

std::vector<float> dibujar_circulo(GLfloat inix, GLfloat iniy, GLfloat rad, GLfloat lad, GLfloat vert, GLfloat offsetx, GLfloat offsety) {
	float radio = rad;
	float iniciox = inix;
	float inicioy = iniy;
	float lados = lad;
	std::vector<float> circulitox(lados * 4);
	std::vector<float> circulitoy(lados * 4);
	std::vector<float> circulitoz(lados * 4);
	int j = 0;

	for (int i = 0; i < lados * 4; i++) {
		if (i == 0 || i % 3 == 0) {
			circulitox[i] = iniciox;
			circulitoy[i] = inicioy;
			if (j != 0) {
				j--;
			}
		}
		else {
			circulitox[i] = iniciox + (radio * cos((j + offsetx) * 2 * M_PI / lados));
			circulitoy[i] = inicioy + (radio * sin((j + offsety) * 2 * M_PI / lados));
			j++;
		}
	}
	for (int i = 0; i < lados * 4; i++) { circulitoz[i] = 0.0f; }
	std::vector<float> circulito_general(lados * 3 * 4);
	for (int i = 0; i < lados * 4; i++) {
		circulito_general[i * 3] = circulitox[i];
		circulito_general[(i * 3) + 1] = circulitoy[i];
		circulito_general[(i * 3) + 2] = circulitoz[i];
	}
	return circulito_general;
}