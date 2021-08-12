#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <time.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "shaders.h"
#include "cubos.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);
typedef glm::vec2 point2;
std::vector<float> new_tri;
bool L_W = 0;

int main()
{
	std::cout << "Please enter the base directory: \n";
	std::string base_dir = "";
	// Aqui coloco algo asi: D:\Documents\Manuel\UCSP\Docencia\2021-I\Cursos\CG\Laboratorio\Project_Base\src\Cubos_Dennis
	// En esa direccion deben estar las imagenes y los shaders
	//std::cin >> base_dir;
	base_dir = "D:/UCSP/7semestre/CompuGrafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Cubos";
	std::cout << "\n " << base_dir << "\n";

	srand(time(NULL));
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
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	std::string vertex_shader_path, fragment_shader_path, fragment_shader_path_2;
	vertex_shader_path = base_dir + "/vshader.fs";
	fragment_shader_path = base_dir + "/fshader.fs";
	fragment_shader_path_2 = base_dir + "/fshader_2.fs";
	//Shader shader_t("vshader.fs/vshader.fs", "fshader.fs/fshader.fs");
	Shader shader_t(
		vertex_shader_path.c_str(),
		fragment_shader_path.c_str());

	Shader shader_t_2(
		vertex_shader_path.c_str(),
		fragment_shader_path_2.c_str());
	//=================Caras del Cubo=================//
	//==================================================================================================================//
	//glm::vec3 v(0.5f, 0.3f, 0.5f);

	std::string  texture_path;
	texture_path = base_dir + "/amarillo.jpg";
	Textures texture_1(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/rojo.jpg";
	Textures texture_2(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/verde.jpg";
	Textures texture_3(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/blanco.jpg";
	Textures texture_4(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/azul.jpg";
	Textures texture_5(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/anaranjado.jpg";
	Textures texture_6(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/negro.jpg";
	Textures texture_7(texture_path.c_str(), GL_TEXTURE_2D);
	std::vector<Textures> textures;
	textures.push_back(texture_1);
	textures.push_back(texture_2);
	textures.push_back(texture_3);
	textures.push_back(texture_4);
	textures.push_back(texture_5);
	textures.push_back(texture_6);
	textures.push_back(texture_7);
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  1.0f,  0.0f),//edge
	glm::vec3(1.0f,  1.0f, 0.0f),//corner
	glm::vec3(-1.0f, 1.0f, 0.0f),//corner
	glm::vec3(0.0f, 0.0f, 0.0f),//center
	glm::vec3(1.0f, 0.0f, 0.0f),//edge
	glm::vec3(-1.0f,  0.0f, 0.0f),//edge
	glm::vec3(0.0f, -1.0f, 0.0f),//edge
	glm::vec3(1.0f, -1.0f, 0.0f),//corner
	glm::vec3(-1.0f, -1.0f, 0.0f),//corner

	glm::vec3(0.0f,  1.0f,  1.0f),//edge
	glm::vec3(1.0f,  1.0f, 1.0f),//edge
	glm::vec3(-1.0f, 1.0f, 1.0f),//edge
	glm::vec3(0.0f, 0.0f, 1.0f),//center_fake
	glm::vec3(1.0f, 0.0f, 1.0f),//edge
	glm::vec3(-1.0f,  0.0f, 1.0f),//edge
	glm::vec3(0.0f, -1.0f, 1.0f),//edge
	glm::vec3(1.0f, -1.0f, 1.0f),//edge
	glm::vec3(-1.0f, -1.0f, 1.0f),//edge

	glm::vec3(0.0f,  1.0f,  2.0f),//edge
	glm::vec3(1.0f,  1.0f, 2.0f),//corner
	glm::vec3(-1.0f, 1.0f, 2.0f),//corner
	glm::vec3(0.0f, 0.0f, 2.0f),//center
	glm::vec3(1.0f, 0.0f, 2.0f),//edge
	glm::vec3(-1.0f,  0.0f, 2.0f),//edge
	glm::vec3(0.0f, -1.0f, 2.0f),//edge
	glm::vec3(1.0f, -1.0f, 2.0f),//corner
	glm::vec3(-1.0f, -1.0f, 2.0f)//corner
	};
	std::vector<std::vector<int>>pintar = {
		{0,6,6,6,6,1},{0,6,6,3,6,1},{0,6,2,6,6,1},
		{0,6,6,6,6,6},{0,6,6,3,6,6},{0,6,2,6,6,6},
		{0,6,6,6,4,6},{0,6,6,3,4,6},{0,6,2,6,4,6},
		
		{6,6,6,6,6,1},{6,6,6,3,6,1},{6,6,2,6,6,1},
		{6,6,6,6,6,6},{6,6,6,3,6,6},{6,6,2,6,6,6},
		{6,6,6,6,4,6},{6,6,6,3,4,6},{6,6,2,6,4,6},
		
		{6,5,6,6,6,1},{6,5,6,3,6,1},{6,5,2,6,6,1},
		{6,5,6,6,6,6},{6,5,6,3,6,6},{6,5,2,6,6,6},
		{6,5,6,6,4,6},{6,5,6,3,4,6},{6,5,2,6,4,6},
	};
	std::vector<cubo*> cubes(27);
	/*for (int i = 0; i < 27; i++) {
		cubes[i] = new cubo(cubePositions[i]);
	}*/
	while (!glfwWindowShouldClose(window)) {
	
		//===================================================================================================================//
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < 27; i++) {
			//cubo* qube = new cubo(cubePositions[i]);
			cubes[i] = new cubo(cubePositions[i]);
			if (i >= 0 && i <=0 ) {
				//cubes[i]->rotateq();
				//cubes[i]->move();
				cubes[i]->rotate();
				//cubes[i]->rotate(glm::vec3(0.0, 0.0, 0.0));
			}
			cubes[i]->animateq();
			cubes[i]->drawq(shader_t, textures,pintar[i]);
			//cubes[i]->eliminate();
			delete cubes[i];
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		L_W = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}