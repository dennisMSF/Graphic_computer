#include <vector>
#include <iostream>
#include <string>
#include "colors.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
class Figure{
public:
	unsigned int VAO, VBO;
	std::vector<float> vertices;
	float timeValue = glfwGetTime();
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 rt = glm::mat4(1.0f);
	Figure(){}
	Figure(std::vector<float> vertices) {
		this->vertices = vertices;
    }
	void gen_buff() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, &vertices.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	void draw(Shader shader_v, glm::vec3 cube_position, Textures texture_v) {
		texture_v.bind(GL_TEXTURE_2D);
		model = glm::rotate(model, (float)glfwGetTime()*glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));
		model = glm::translate(model, cube_position);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -9.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		shader_v.use();
		shader_v.setMatrix("view", &view[0][0]);
		shader_v.setMatrix("projection", glm::value_ptr(projection));
		shader_v.setMatrix("model", glm::value_ptr(model));
		shader_v.setMatrix("transform", glm::value_ptr(rt));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
	}
	void rotate_vert(float angle, glm::vec3 axis_rotation) {
		//std::cout << "angle -> " << angle << std::endl;
		rt = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
		rt = glm::rotate(rt, glm::radians(angle), axis_rotation);
	}
	void rotate_reset_matrix() {
		rt = glm::mat4(1.0f);
	}
	void reset_matrix() {
		model = glm::mat4(1.0f);
		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);
	}
	void delbuf() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	~Figure() {
		delbuf();
	}
};
//=================Caras del Cubo=================//
std::vector<float> cara1 = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f
};
std::vector<float> cara2 = {
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f
};
std::vector<float> cara3 = {
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f
};
std::vector<float> cara4 = {
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f
};
std::vector<float> cara5 = {
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f
};
std::vector<float> cara6 = {
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
class cubo {
public:
	Figure c1;
	Figure c2;
	Figure c3;
	Figure c4;
	Figure c5;
	Figure c6;
	float pos_x;
	float pos_y;
	float pos_z;
	std::vector<int> color;
	glm::vec3 cube_position;
	glm::mat4 rot = glm::mat4(1.0f);
	cubo(glm::vec3 position) : c1(cara1), c2(cara2)
							  ,c3(cara3), c4(cara4)
							  ,c5(cara5), c6(cara6) 
	{
		pos_x = position.x;
		pos_y = position.y;
		pos_z = position.z;
		cube_position.x = position.x;
		cube_position.y = position.y;
		cube_position.z = position.z;

	}
	void cubbuff() {
		c1.gen_buff();
		c2.gen_buff();
		c3.gen_buff();
		c4.gen_buff();
		c5.gen_buff();
		c6.gen_buff();
	}
	void drawc(Shader shaders,std::vector<Textures> texture_v, std::vector<int> text_bind) {
		c1.draw(shaders, cube_position, texture_v[text_bind[0]]);
		c2.draw(shaders, cube_position, texture_v[text_bind[1]]);
		c3.draw(shaders, cube_position, texture_v[text_bind[2]]);
		c4.draw(shaders, cube_position, texture_v[text_bind[3]]);
		c5.draw(shaders, cube_position, texture_v[text_bind[4]]);
		c6.draw(shaders, cube_position, texture_v[text_bind[5]]);
	}
	/*void rotate(float angle, glm::vec3 inner_center, glm::vec3 ex_center, glm::vec3 axis_rotation) {
		glm::vec4 as(cube_position, 1.0);
		rot  = glm::translate(rot, inner_center);
		rot = glm::rotate(rot,glm::radians(angle), axis_rotation);
		rot  = glm::translate(rot, ex_center);
		as = rot * as;
		update_position(as,angle);
	}*/
	void move(glm::vec3 new_position) {
		glm::vec4 as(cube_position, 1.0);
		rot = glm::translate(rot, new_position);
		as = rot * as;
		update_position(as);
	}
	void update_position(glm::vec4 new_position) {
		cube_position.x = new_position.x;
		cube_position.y = new_position.y;
		cube_position.z = new_position.z;
		pos_x = new_position.x;
		pos_y = new_position.y;
		pos_z = new_position.z;	
	}
	void reset_position() {
		cube_position.x = pos_x;
		cube_position.y = pos_y;
		cube_position.z = pos_z;
		rot = glm::mat4(1.0f);
	}
	void reset_matrix() {
		c1.reset_matrix();
		c2.reset_matrix();
		c3.reset_matrix();
		c4.reset_matrix();
		c5.reset_matrix();
		c6.reset_matrix();
	}
	void reset_rotate_matrix() {
		c1.rotate_reset_matrix();
		c2.rotate_reset_matrix();
		c3.rotate_reset_matrix();
		c4.rotate_reset_matrix();
		c5.rotate_reset_matrix();
		c6.rotate_reset_matrix();
	}
	void rotate_vertex(float angle,glm::vec3 axis_rotation) {
		c1.rotate_vert(angle, axis_rotation);
		c2.rotate_vert(angle, axis_rotation);
		c3.rotate_vert(angle, axis_rotation);
		c4.rotate_vert(angle, axis_rotation);
		c5.rotate_vert(angle, axis_rotation);
		c6.rotate_vert(angle, axis_rotation);
	}
	void update_order(std::vector<int> new_color, int* order) {
		std::vector<int> real_colors;
		int cont = 0;
		for (int i = 0; i < color.size(); ++i) {
			if (color[i] != 6) {
				real_colors.push_back(color[i]);
			}
		}

		for (int i = 0; i < new_color.size(); ++i) {
			if (new_color[i] != 6) {
				color[i] = real_colors[order[cont]];
				cont++;
			}
			else {
				color[i] = 6;
			}
		}
	}
	
	~cubo() {

	}
};