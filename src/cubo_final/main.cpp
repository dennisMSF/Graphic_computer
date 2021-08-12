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
#include <mutex>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);
bool MOVES[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
//////////////////////////////////
float limitss = 0.0;
float limit_side = 0.0;
float limit_up = 0.0;
float limit_side_left = 0.0;
float limit_side_left_u = 0.0;
float limit_side_right_d = 0.0;
float limit_side_left_d = 0.0;
float limit_mid_d = 0.0;
float limit_side_right_d_2 = 0.0;
float limit_side_left_d_2 = 0.0;
float limit_mid_up = 0.0;
float limit_mid_down = 0.0;


bool flag_1 = true;
bool flag_2 = false;
bool flag_3 = false;
bool flag_4 = false;
bool flag_5 = false;
bool flag_6 = false;
bool flag_7 = false;
bool flag_8 = false;
bool flag_9 = false;
bool flag_10 = false;
bool flag_11 = false;
bool flag_12 = false;
bool flag_solve = false;
bool flag_scramble = false;
/////////////////////////////////

//////////////////////////////////
double angle_limit_i = -90.0;
double rotate_angle_i_limit = -90.0;
int rotate_vertex_i_angle = 0;
int angle_i = 0;
/////////////////////////////////
///************************************************************///
void switch_cube(cubo*& a, cubo*& b) {
	if (a == b) {
		return;
	}
	cubo* ptr = NULL;
	ptr = a;
	a = b;
	b = ptr;
}

int find(int& num, int* arr) {
	int* p = arr; int i = 0;

	while (*p != num && i < 9) {
		p++; i++;
	}

	return i;
}

void updates_cubes(std::vector<cubo*>& cubes, int* nums, int* aux) {
	bool verified[9] = { 0,0,0,0,0,0,0,0,0 };
	int cont = 0;
	int busqueda = nums[0];
	int inspector = nums[0];

	while (cont < 9) {
		//verifica si la posicion no fue ordenada todavia
		int i = find(busqueda, aux);//que cubo se va a mover a la posicion busqueda en cubes
		if (!verified[i]) {
			switch_cube(cubes[busqueda], cubes[nums[i]]);//swap
			verified[find(busqueda, nums)] = 1;
			busqueda = nums[i];//actualiza la busqueda en la posicion donde se posiciono el antiguo cubo
		}
		else {
			//condicion para verificar que todo esta ordenado
			verified[find(busqueda, nums)] = 1;
			cont++;
			inspector = nums[cont];
			busqueda = inspector;
		}
	}

}
///***************************************************************///
// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

int main()
{
	std::string base_dir = "";
	base_dir = "D:/UCSP/7semestre/CompuGrafica/GLFW_GLAD_GLUT_GLEW_cmake_project/src/cuboprueba";
	std::cout << "\n " << base_dir << "\n";
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
	glfwSetKeyCallback(window, key_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	std::string vertex_shader_path, fragment_shader_path, fragment_shader_path_2;
	vertex_shader_path = base_dir + "/vshader.fs";
	fragment_shader_path = base_dir + "/fshader.fs";
	fragment_shader_path_2 = base_dir + "/fshader_2.fs";
	//Shader shader_t("vshader.fs/vshader.fs", "fshader.fs/fshader.fs");
	Shader ourShader(
		vertex_shader_path.c_str(),
		fragment_shader_path.c_str());

	Shader shader_t_2(
		vertex_shader_path.c_str(),
		fragment_shader_path_2.c_str());


	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  1.0f,  0.0f),//edge arriba back
		glm::vec3(1.0f,  1.0f, 0.0f),//corner arriba derecha back
		glm::vec3(-1.0f, 1.0f, 0.0f),//corner arriba izquierda back
		glm::vec3(0.0f, 0.0f, 0.0f),//center back
		glm::vec3(1.0f, 0.0f, 0.0f),//edge back derecha
		glm::vec3(-1.0f,  0.0f, 0.0f),//edge back izquierda
		glm::vec3(0.0f, -1.0f, 0.0f),//edge abajo back
		glm::vec3(1.0f, -1.0f, 0.0f),//corner abajo derecha back
		glm::vec3(-1.0f, -1.0f, 0.0f),//corner abajo izquierda back

		glm::vec3(0.0f,  1.0f,  1.0f),//center arriba
		glm::vec3(1.0f,  1.0f, 1.0f),//edge arriba right
		glm::vec3(-1.0f, 1.0f, 1.0f),//edge arriba left
		glm::vec3(0.0f, 0.0f, 1.0f),//center_fake
		glm::vec3(1.0f, 0.0f, 1.0f),//center right
		glm::vec3(-1.0f,  0.0f, 1.0f),//center left
		glm::vec3(0.0f, -1.0f, 1.0f),//center abajo
		glm::vec3(1.0f, -1.0f, 1.0f),//edge abajo right
		glm::vec3(-1.0f, -1.0f, 1.0f),//edge abajo left

		glm::vec3(0.0f,  1.0f,  2.0f),//edge arriba front
		glm::vec3(1.0f,  1.0f, 2.0f),//corner arriba derecha front
		glm::vec3(-1.0f, 1.0f, 2.0f),//corner arriba izquierda front
		glm::vec3(0.0f, 0.0f, 2.0f),//center front
		glm::vec3(1.0f, 0.0f, 2.0f),//edge front derecha
		glm::vec3(-1.0f,  0.0f, 2.0f),//edge front izquierda
		glm::vec3(0.0f, -1.0f, 2.0f),//edge abajo front
		glm::vec3(1.0f, -1.0f, 2.0f),//corner abajo derecha front
		glm::vec3(-1.0f, -1.0f, 2.0f)//corner abajo izquierda front
	};
	
	std::vector<cubo*> cubos_pos(27);
	for (int i = 0; i < 27; i++) {
		cubos_pos[i] = new cubo(cubePositions[i]);
		cubos_pos[i]->cubbuff();
	}

	std::string  texture_path;
	texture_path = base_dir + "/amarillo.png";
	Textures texture_1(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/rojo.png";
	Textures texture_2(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/verde.png";
	Textures texture_3(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/blanco.png";
	Textures texture_4(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/azul.png";
	Textures texture_5(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/anaranjado.png";
	Textures texture_6(texture_path.c_str(), GL_TEXTURE_2D);
	texture_path = base_dir + "/negro.png";
	Textures texture_7(texture_path.c_str(), GL_TEXTURE_2D);
	std::vector<Textures> textures;
	textures.push_back(texture_1);
	textures.push_back(texture_2);
	textures.push_back(texture_3);
	textures.push_back(texture_4);
	textures.push_back(texture_5);
	textures.push_back(texture_6);
	textures.push_back(texture_7);
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
	int cubes_set_1[9] = {0,1,2,3,4,5,6,7,8};// back
	int cubes_set_2[9] = {18,19,20,21,22,23,24,25,26};
	int cubes_set_3[9] = {1,4,7,10,13,16,19,22,25 };
	int cubes_set_4[9] = {2,5,8,11,14,17,20,23,26 };
	int cubes_set_5[9] = { 6,7,8,15,16,17,24,25,26 };
	int cubes_set_6[9] = { 0,1,2,9,10,11,18,19,20 };


	std::cout << "Movimiento | Letra Asociada" << std::endl;
	std::cout << "F          | F" << std::endl;
	std::cout << "F'         | G" << std::endl;
	std::cout << "R          | R" << std::endl;
	std::cout << "R'         | T" << std::endl;
	std::cout << "U          | U" << std::endl;
	std::cout << "U'         | I" << std::endl;
	std::cout << "B          | B" << std::endl;
	std::cout << "B'         | N" << std::endl;
	std::cout << "L          | L" << std::endl;
	std::cout << "L'         | K" << std::endl;
	std::cout << "D          | D" << std::endl;
	std::cout << "D'         | S" << std::endl << std::endl;
	std::cout << "Scramble   | Z" << std::endl;
	std::cout << "Solve      | X" << std::endl << std::endl;

	/////////////////////////////////////////////////////////////////

	// render loop
	// -----------
	

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
		if (!flag_1 && !flag_2 && !flag_3 && !flag_4 && !flag_5 && !flag_6 && !flag_7 && !flag_8 && !flag_9 && !flag_10 && !flag_11 && !flag_12) {
			flag_scramble = true;
			flag_solve = true;
			flag_12 = true;
		}
		if (!flag_solve) {
			if (limitss >= 0.103) {

				flag_1 = false;
				flag_2 = true;
				limitss = 0.0;
			}
			if (limit_side <= -0.103) {
				flag_1 = false;
				flag_2 = false;
				flag_3 = true;
				limit_side = 0.0;
			}
			if (limit_up >= 0.103) {
				flag_1 = flag_2 = flag_3 = false;
				flag_4 = true;
				limit_up = 0.0;
			}
			if (limit_side_left >= 0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = false;
				flag_5 = true;
				limit_side_left = 0.0;
			}
			if (limit_side_left_u >= 0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = false;
				flag_6 = true;
				limit_side_left_u = 0.0;
			}
			if (limit_side_left_d >= 0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = false;
				flag_7 = true;
				limit_side_left_d = 0.0;
			}
			if (limit_side_right_d <= -0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = false;
				flag_8 = true;
				limit_side_right_d = 0.0;
			}
			if (limit_mid_d > 0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = false;
				flag_9 = true;
				limit_mid_d = 0.0;
			}
			if (limit_side_left_d_2 >= 0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = false;
				flag_10 = true;
				limit_side_left_d_2 = 0.0;
			}
			if (limit_side_right_d_2 <= -0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = flag_10 = false;
				flag_11 = true;
				limit_side_right_d_2 = 0.0;
			}
			//std::cout << limit_mid_d << std::endl;
			if (limit_mid_up > 0.103) {
				//std::cout << "entre" << std::endl;
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = flag_10 = flag_11 = false;
				flag_12 = true;
				limit_mid_up = 0.0;
			}
			if (limit_mid_down < -0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = flag_10 = flag_11 = flag_12 = false;
				limit_mid_down = 0.0;
			}
			if (flag_1) {//mid->DOWN
				//std::cout << flag_1 << std::endl;
				if (limitss < 0.1) {
					limitss = limitss + 0.0052;
				}
				for (int i = 0; i < 27; i++) {

					if (i == 3 || i == 4 || i == 5) {
						if (limitss < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, 0.0, limitss));
					}
				}
			}
			//std::cout << limit_side << std::endl;
			if (flag_2) {//Left -> MID
				if (limit_side > -0.1) {
					limit_side = limit_side - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 0 || i == 1 || i == 2) {
						if (limit_side > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side, 0.0));
					}
				}
			}
			//std::cout << limit_up << std::endl;
			if (flag_3) {//left->mid->DOWN
				if (limit_up < 0.1) {
					limit_up = limit_up + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 0 || i == 1 || i == 2) {
						if (limit_up < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, 0.0, limit_up));
					}
				}
			}
			if (flag_4) {//Right->LEFT
				if (limit_side_left <= 0.1) {
					limit_side_left = limit_side_left + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 6 || i == 7 || i == 8) {
						if (limit_side_left <= 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_left, 0.0));
					}
				}
			}
			if (flag_5) {//right->left->DOWN
				if (limit_side_left_u < 0.1) {
					limit_side_left_u = limit_side_left_u + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 6 || i == 7 || i == 8) {
						if (limit_side_left_u < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, 0.0, limit_side_left_u));
					}
				}
			}
			if (flag_6) {//left_d -> MID
				if (limit_side_left_d < 0.1) {
					limit_side_left_d = limit_side_left_d + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 15 || i == 16 || i == 17) {
						if (limit_side_left_d < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_left_d, 0.0));
					}
				}
			}
			if (flag_7) {//rigth_d-> MID
				if (limit_side_right_d > -0.1) {
					limit_side_right_d = limit_side_right_d - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 9 || i == 10 || i == 11) {
						if (limit_side_right_d > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_right_d, 0.0));
					}
				}
			}
			if (flag_8) {//mid_d -> DOWN
				if (limit_mid_d < 0.1) {
					limit_mid_d = limit_mid_d + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i >= 0 && i <= 17) {
						if (limit_mid_d < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, 0.0, limit_mid_d));
					}
				}
			}
			if (flag_9) {
				if (limit_side_left_d_2 < 0.1) {
					limit_side_left_d_2 = limit_side_left_d_2 + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 24 || i == 25 || i == 26) {
						if (limit_side_left_d_2 < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_left_d_2, 0.0));
					}
				}
			}
			if (flag_10) {
				if (limit_side_right_d_2 > -0.1) {
					limit_side_right_d_2 = limit_side_right_d_2 - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 18 || i == 19 || i == 20) {
						if (limit_side_right_d_2 > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_right_d_2, 0.0));
					}
				}
			}
			if (flag_11) {
				if (limit_mid_up < 0.1) {
					limit_mid_up = limit_mid_up + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 23 || i == 2 || i == 5 || i == 8 || i == 11 || i == 14 || i == 17 || i == 20 || i == 26) {
						if (limit_mid_up < 0.1)
							cubos_pos[i]->move(glm::vec3(limit_mid_up, 0.0, 0.0));
					}
				}
			}
			if (flag_12) {
				if (limit_mid_down > -0.1) {
					limit_mid_down = limit_mid_down - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19 || i == 22 || i == 25) {
						if (limit_mid_down > -0.1)
							cubos_pos[i]->move(glm::vec3(limit_mid_down, 0.0, 0.0));
					}
				}
			}
		}
		
/////////////////////////////////////////////////////////////desarmar//////////////////////////////////////////////////
		if (flag_scramble && flag_solve) {
			if (limit_mid_down > 0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = flag_10 = flag_12 = false;
				flag_11 = true;
				limit_mid_down = 0.0;
			}
			if (limit_mid_up < -0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = flag_12 = flag_11 = false;
				flag_10 = true;
				limit_mid_up = 0.0;
			}
			if (limit_side_right_d_2 >= 0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_12 = flag_10 = flag_11 = false;
				flag_9 = true;
				limit_side_right_d_2 = 0.0;
			}
			if (limit_side_left_d_2 <= -0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_12 = flag_9 =flag_10 = flag_11 = false;
				flag_8 = true;
				limit_side_left_d_2 = 0.0;
			}
			if (limit_mid_d < -0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_9 = flag_8 =flag_10=flag_11=flag_12= false;
				flag_7 = true;
				limit_mid_d = 0.0;
			}
			if (limit_side_right_d >= 0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_5 = flag_7 = flag_8=flag_9=flag_10=flag_11=flag_12 = false;
				flag_6 = true;
				limit_side_right_d = 0.0;
			}
			if (limit_side_left_d <= -0.103) {
				flag_1 = flag_2 = flag_3 = flag_4 = flag_6 = flag_7 = flag_8 = flag_9 = flag_10 = flag_11 = flag_12 = false;
				flag_5 = true;
				limit_side_left_d = 0.0;
			}
			if (limit_side_left_u <= -0.103) {
				flag_1 = flag_2 = flag_3 = flag_5 = flag_6=flag_7=flag_8=flag_9=flag_10=flag_11=flag_12 = false;
				flag_4 = true;
				limit_side_left_u = 0.0;
			}
			if (limit_side_left <= -0.103) {
				flag_1 = flag_2 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = flag_10 = flag_11 = flag_12 = false;
				flag_3 = true;
				limit_side_left = 0.0;
			}
			if (limit_up <= -0.103) {
				flag_1 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = flag_10 = flag_11 = flag_12 = false;
				flag_2 = true;
				limit_up = 0.0;
			}
			if (limit_side >= 0.103) {
				flag_2 = flag_3 = flag_4 = flag_5 = flag_6 = flag_7 = flag_8 = flag_9 = flag_10 = flag_11 = flag_12 = false;
				flag_1 = true;
				limit_side = 0.0;
			}
			//**********************************************************************************************************//
			if (flag_12) {
				if (limit_mid_down < 0.1) {
					limit_mid_down = limit_mid_down + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19 || i == 22 || i == 25) {
						if (limit_mid_down < 0.1)
							cubos_pos[i]->move(glm::vec3(limit_mid_down, 0.0, 0.0));
					}
				}
			}
			if (flag_11) {
				if (limit_mid_up > -0.1) {
					limit_mid_up = limit_mid_up - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 23 || i == 2 || i == 5 || i == 8 || i == 11 || i == 14 || i == 17 || i == 20 || i == 26) {
						if (limit_mid_up > -0.1)
							cubos_pos[i]->move(glm::vec3(limit_mid_up, 0.0, 0.0));
					}
				}
			}
			if (flag_10) {
				if (limit_side_right_d_2 < 0.1) {
					limit_side_right_d_2 = limit_side_right_d_2 + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 18 || i == 19 || i == 20) {
						if (limit_side_right_d_2 < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_right_d_2, 0.0));
					}
				}
			}
			if (flag_9) {
				if (limit_side_left_d_2 > -0.1) {
					limit_side_left_d_2 = limit_side_left_d_2 - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 24 || i == 25 || i == 26) {
						if (limit_side_left_d_2 > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_left_d_2, 0.0));
					}
				}
			}
			if (flag_8) {//mid_d -> DOWN
				if (limit_mid_d > -0.1) {
					limit_mid_d = limit_mid_d - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i >= 0 && i <= 17) {
						if (limit_mid_d > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, 0.0, limit_mid_d));
					}
				}
			}
			if (flag_7) {//rigth_d-> MID
				if (limit_side_right_d < 0.1) {
					limit_side_right_d = limit_side_right_d + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 9 || i == 10 || i == 11) {
						if (limit_side_right_d < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_right_d, 0.0));
					}
				}
			}
			if (flag_6) {//left_d -> MID
				if (limit_side_left_d > -0.1) {
					limit_side_left_d = limit_side_left_d - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 15 || i == 16 || i == 17) {
						if (limit_side_left_d > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_left_d, 0.0));
					}
				}
			}
			if (flag_5) {//right->left->DOWN
				if (limit_side_left_u > -0.1) {
					limit_side_left_u = limit_side_left_u - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 6 || i == 7 || i == 8) {
						if (limit_side_left_u > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, 0.0, limit_side_left_u));
					}
				}
			}
			if (flag_4) {//Right->LEFT
				if (limit_side_left >= -0.1) {
					limit_side_left = limit_side_left - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 6 || i == 7 || i == 8) {
						if (limit_side_left >= -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side_left, 0.0));
					}
				}
			}
			if (flag_3) {//left->mid->DOWN
				if (limit_up > -0.1) {
					limit_up = limit_up - 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 0 || i == 1 || i == 2) {
						if (limit_up > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, 0.0, limit_up));
					}
				}
			}
			if (flag_2) {//Left -> MID
				if (limit_side < 0.1) {
					limit_side = limit_side + 0.0052;
				}
				for (int i = 0; i < 27; i++) {
					if (i == 0 || i == 1 || i == 2) {
						if (limit_side < 0.1)
							cubos_pos[i]->move(glm::vec3(0.0, limit_side, 0.0));
					}
				}
			}
			if (flag_1) {//mid->DOWN
				//std::cout << flag_1 << std::endl;
				if (limitss > -0.1) {
					limitss = limitss - 0.0052;
				}
				for (int i = 0; i < 27; i++) {

					if (i == 3 || i == 4 || i == 5) {
						if (limitss > -0.1)
							cubos_pos[i]->move(glm::vec3(0.0, 0.0, limitss));
					}
				}
			}
		}


		for (int i = 0; i < 27;i++) {
			cubos_pos[i]->drawc(ourShader,textures,pintar[i]);
		}




		glfwSwapBuffers(window);
		glfwPollEvents();

		for (int i = 0; i < 27; i++) {
			cubos_pos[i]->reset_matrix();
			cubos_pos[i]->reset_position();
		}
		
		//flag_1 = false;
		//flag_2 = true;
	}
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 0) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
		
		
	}

	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 1) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 2) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 3) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 4) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 5) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
		if (angle_i < -90 && angle_i > -360) {
			angle_limit_i -= 90.0;
		}
		else {
			angle_limit_i = -90.0;
			angle_i = 0.0;
		}
		if (rotate_vertex_i_angle < -89 && rotate_vertex_i_angle > -360) {
			rotate_angle_i_limit -= 90.0;
		}
		else {
			rotate_angle_i_limit = -90.0;
			rotate_vertex_i_angle = 0.0;
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		/*movement = 'B';
		b = 1.0;*/
		for (int i = 0; i < 12; ++i) {
			if (i != 6) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
		
	}

	else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 7) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 8) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 9) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 10) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		for (int i = 0; i < 12; ++i) {
			if (i != 11) {
				MOVES[i] = 0;
			}
			else {
				MOVES[i] = 1;
			}
		}
	}


	else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {

	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
