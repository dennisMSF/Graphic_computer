#include <vector>
#include <iostream>
#include <string>
#include "colors.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
class figurita{
public:
	unsigned int VBA, VBO;
	std::vector<float> vertices;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;
	float timeValue = glfwGetTime();
	figurita(){}
    figurita(std::vector<float> vertices, glm::vec3 cube_position) {
		this->vertices = vertices;
		glGenVertexArrays(1, &VBA);
	    glGenBuffers(1, &VBO);
        glBindVertexArray(VBA);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, &vertices.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
    }
	void draw(Shader shader_v, Textures texture_v) {
		texture_v.bind(GL_TEXTURE_2D);
		shader_v.use();
		shader_v.setMatrix("view", &view[0][0]);
		shader_v.setMatrix("projection", glm::value_ptr(projection));
		shader_v.setMatrix("model", glm::value_ptr(model));
		shader_v.setresolution("resolution", SCR_WIDTH, SCR_HEIGHT);
		shader_v.setFloat("time", timeValue);
		glBindVertexArray(VBA);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
	}
	void animate(glm::vec3 cube_position) {
		//model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
		model = glm::rotate(model, (float)glfwGetTime() *glm::radians(60.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		model = glm::translate(model, cube_position);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -7.0f));
		projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	}
	void rotate() {
		//model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0,0.0,1.0));
		glm::mat4 gr = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
		model = glm::rotate(gr, timeValue*glm::radians(40.0f), glm::vec3(0.0, 0.0, 1.0));
		//model =  model* gr;
	}
	void delbuf() {
		glDeleteVertexArrays(1, &VBA);
		glDeleteBuffers(1, &VBO);
	}
	~figurita() {
		delbuf();
	}
};
//=================Caras del Cubo=================//
std::vector<float> cara1 = {
		-0.5f, -0.5f, -0.5f, HEX_COLOR(orangered),  0.0,0.0,
		 0.5f, -0.5f, -0.5f, HEX_COLOR(orangered),  1.0,0.0,
		 0.5f,  0.5f, -0.5f, HEX_COLOR(orangered),  1.0,1.0,
		 0.5f,  0.5f, -0.5f, HEX_COLOR(orangered),  1.0,1.0,
		-0.5f,  0.5f, -0.5f, HEX_COLOR(orangered),  0.0,1.0,
		-0.5f, -0.5f, -0.5f, HEX_COLOR(orangered),  0.0,0.0,
};
std::vector<float> cara2 = {
	-0.5f, -0.5f,  0.5f, HEX_COLOR(lightcyan),  0.0,0.0,
	 0.5f, -0.5f,  0.5f, HEX_COLOR(lightcyan),  1.0,0.0,
	 0.5f,  0.5f,  0.5f, HEX_COLOR(lightcyan),  1.0,1.0,
	 0.5f,  0.5f,  0.5f, HEX_COLOR(lightcyan),  1.0,1.0,
	-0.5f,  0.5f,  0.5f, HEX_COLOR(lightcyan),  0.0,1.0,
	-0.5f, -0.5f,  0.5f, HEX_COLOR(lightcyan),  0.0,0.0
};
std::vector<float> cara3 = {
	-0.5f,  0.5f,  0.5f, HEX_COLOR(lightblue),  0.0,0.0,
	-0.5f,  0.5f, -0.5f, HEX_COLOR(lightblue),  1.0,0.0,
	-0.5f, -0.5f, -0.5f, HEX_COLOR(lightblue),  1.0,1.0,
	-0.5f, -0.5f, -0.5f, HEX_COLOR(lightblue),  1.0,1.0,
	-0.5f, -0.5f,  0.5f, HEX_COLOR(lightblue),  0.0,1.0,
	-0.5f,  0.5f,  0.5f, HEX_COLOR(lightblue),  0.0,0.0
};
std::vector<float> cara4 = {
	 0.5f,  0.5f,  0.5f, HEX_COLOR(lightseagreen), 0.0,0.0,
	 0.5f,  0.5f, -0.5f, HEX_COLOR(lightseagreen), 1.0,0.0,
	 0.5f, -0.5f, -0.5f, HEX_COLOR(lightseagreen), 1.0,1.0,
	 0.5f, -0.5f, -0.5f, HEX_COLOR(lightseagreen), 1.0,1.0,
	 0.5f, -0.5f,  0.5f, HEX_COLOR(lightseagreen), 0.0,1.0,
	 0.5f,  0.5f,  0.5f, HEX_COLOR(lightseagreen), 0.0,0.0
};
std::vector<float> cara5 = {
	-0.5f, -0.5f, -0.5f,HEX_COLOR(purple), 0.0,0.0,
	 0.5f, -0.5f, -0.5f,HEX_COLOR(purple), 1.0,0.0,
	 0.5f, -0.5f,  0.5f,HEX_COLOR(purple), 1.0,1.0,
	 0.5f, -0.5f,  0.5f,HEX_COLOR(purple), 1.0,1.0,
	-0.5f, -0.5f,  0.5f,HEX_COLOR(purple), 0.0,1.0,
	-0.5f, -0.5f, -0.5f,HEX_COLOR(purple), 0.0,0.0
};
std::vector<float> cara6 = {
	-0.5f,  0.5f, -0.5f,HEX_COLOR(lightgreen), 0.0,0.0,
	 0.5f,  0.5f, -0.5f,HEX_COLOR(lightgreen), 1.0,0.0,
	 0.5f,  0.5f,  0.5f,HEX_COLOR(lightgreen), 1.0,1.0,
	 0.5f,  0.5f,  0.5f,HEX_COLOR(lightgreen), 1.0,1.0,
	-0.5f,  0.5f,  0.5f,HEX_COLOR(lightgreen), 0.0,1.0,
	-0.5f,  0.5f, -0.5f,HEX_COLOR(lightgreen), 0.0,0.0
};
class cubo {
public:
	//std::string face_position;
	figurita c1;
	figurita c2;
	figurita c3;
	figurita c4;
	figurita c5;
	figurita c6;
	float pos_x;
	float pos_y;
	float pos_z;
	glm::vec3 cube_position;
	cubo(glm::vec3 position) : c1(cara1, position), c2(cara2, position)
							  ,c3(cara3, position), c4(cara4, position)
							  ,c5(cara5, position), c6(cara6, position) 
	{
		//face_position = name;
		pos_x = position.x;
		pos_y = position.y;
		pos_z = position.z;
		cube_position.x = pos_x;
		cube_position.y = pos_y;
		cube_position.z = pos_z;

	}
	void drawq(Shader shader_v, std::vector<Textures> texture_v, std::vector<int> text_bind) {
		c1.draw(shader_v,  texture_v[text_bind[0]]);
		c2.draw(shader_v,texture_v[text_bind[1]]);
		c3.draw(shader_v, texture_v[text_bind[2]]);
		c4.draw(shader_v, texture_v[text_bind[3]]);
		c5.draw(shader_v, texture_v[text_bind[4]]);
		c6.draw(shader_v, texture_v[text_bind[5]]);
	}
	void animateq() {
		c1.animate(cube_position);
		c2.animate(cube_position);
		c3.animate(cube_position);
		c4.animate(cube_position);
		c5.animate(cube_position);
		c6.animate(cube_position);
	}
	void rotateq() {
		c1.rotate();
		c2.rotate();
		c3.rotate();
		c4.rotate();
		c5.rotate();
		c6.rotate();
	}
	void move() {
		glm::mat4 rt = glm::mat4(1.0f);
		glm::vec3 as;
		rt = glm::rotate(rt, (float)glfwGetTime() * glm::radians(45.0f),glm::vec3(0.0,0.0,1.0));
		as.x = cube_position.x;
		as.y = cube_position.y;
		as.z = cube_position.z;
		glm::vec4 arr=glm::vec4(as,1.0);
		arr =  rt * arr;
		cube_position.x = arr.x;
		cube_position.y = arr.y;
		cube_position.z = arr.z;
	}
	void rotate() {
		float current_positionx = pos_x;
		float current_positiony = pos_y;
		float current_positionz = pos_z;
		glm::mat4 rt = glm::mat4(1.0f);
		glm::vec3 as;
		rt = glm::translate(rt, glm::vec3(0.0, 0.0, 0.0));
		rt = glm::rotate(rt, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
		as.x = current_positionx;
		as.y = current_positiony;
		as.z = current_positionz;
		glm::vec4 arr = glm::vec4(as, 1.0);
		arr = rt * arr;
		cube_position.x = arr.x;
		cube_position.y = arr.y;
		cube_position.z = arr.z;
		current_positionx = cube_position.x;
		current_positiony = cube_position.y;
		current_positionz = cube_position.z;
	}
	~cubo() {

	}
};