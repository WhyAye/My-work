#include "my_view.hpp"
#include <tygra/FileHelper.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

//#include <SDL/SDL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>



glm::vec3 CubicBezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float u)
{
	return (1 - u) * (1 - u) * (1 - u) * p0
		+ 3 * u * (1 - u) * (1 - u) * p1
		+ 3 * u * u * (1 - u) * p2
		+ u * u * u * p3;
}

glm::vec3 BezierSurface(std::vector<glm::vec3> cps, float u, float v)
{
	std::vector<glm::vec3> curve{ 4 };
	for (int j = 0; j < 4; j++)
	{
		curve[j] = CubicBezier(cps[j * 4], cps[j * 4 + 1], cps[j * 4 + 2], cps[j * 4 + 3], u);
	}
	return CubicBezier(curve[0], curve[1], curve[2], curve[3], v);
}



MyView::MyView()
{
}

MyView::~MyView() {
}

void MyView::setScene(const scene::Context * scene)
{
	scene_ = scene;
}

void MyView::toggleShading()
{
	shade_normals_ = !shade_normals_;
}

void MyView::windowViewWillStart(tygra::Window * window)
{
	assert(scene_ != nullptr);

	GLint compile_status = 0;
	GLint link_status = 0;

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertex_shader_string
		= tygra::createStringFromFile("resource:///terrain_vs.glsl");
	const char *vertex_shader_code = vertex_shader_string.c_str();
	glShaderSource(vertex_shader, 1,
		(const GLchar **)&vertex_shader_code, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE) {
		const int string_length = 1024;
		GLchar log[string_length] = "";
		glGetShaderInfoLog(vertex_shader, string_length, NULL, log);
		std::cerr << log << std::endl;
	}

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragment_shader_string
		= tygra::createStringFromFile("resource:///terrain_fs.glsl");
	const char *fragment_shader_code = fragment_shader_string.c_str();
	glShaderSource(fragment_shader, 1,
		(const GLchar **)&fragment_shader_code, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE) {
		const int string_length = 1024;
		GLchar log[string_length] = "";
		glGetShaderInfoLog(fragment_shader, string_length, NULL, log);
		std::cerr << log << std::endl;
	}

	terrain_sp_ = glCreateProgram();
	glAttachShader(terrain_sp_, vertex_shader);
	glDeleteShader(vertex_shader);
	glAttachShader(terrain_sp_, fragment_shader);
	glDeleteShader(fragment_shader);
	glLinkProgram(terrain_sp_);

	glGetProgramiv(terrain_sp_, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		const int string_length = 1024;
		GLchar log[string_length] = "";
		glGetProgramInfoLog(terrain_sp_, string_length, NULL, log);
		std::cerr << log << std::endl;
	}


	// X and -Z are on the ground, Y is up
	const float sizeX = scene_->getTerrainSizeX();
	const float sizeY = scene_->getTerrainSizeY();
	const float sizeZ = scene_->getTerrainSizeZ();


	const auto& bezier_patches = scene_->getTerrainPatches();
	const size_t number_of_patches = bezier_patches.size();
	// below is an example of accessing a control point from the second patch
	//glm::vec3 cp = bezier_patches[1].at(2, 3);


	tygra::Image displace_image =
		tygra::createImageFromPngFile(scene_->getTerrainDisplacementMapName());

	// below is an example of reading the red component of pixel(x,y) as a byte [0,255]
	//uint8_t displacement = *(uint8_t*)displace_image.pixel(x, y);


	// create the cell numbers etc...
	// the -1 is to take in acount the extra vertex at the end
	int numCellsX{ (int)displace_image.width() - 1 };
	int numCellsZ{ (int)displace_image.height() - 1 };

	//number of verticies will be one more in each dimention 
	int numVertsX{ numCellsX + 1 };
	int numVertsZ{ numCellsZ + 1 };
	int numVerts{ numVertsX * numVertsZ };



	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> positions;
	std::vector<GLuint> elements;
	std::vector<glm::vec3> cpsAlong1{ 100 };
	std::vector<glm::vec3> cpsAlong2{ 100 };

	normals.resize(numVerts);
	positions.resize(numVerts);
	uv.resize(numVerts);
	int numbelements = (numCellsX * 2) * (numCellsZ) * 3;
	elements.resize(numbelements);



	std::vector<glm::vec3> cp1{ 16 };
	std::vector<glm::vec3> cp2{ 16 };



	int countC = { 0 };
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			cp1[countC] = bezier_patches[0].at(x, y);
			cp2[countC++] = bezier_patches[1].at(x, y);
		}
	}
	assert(countC == 16);



	int countD{ 0 };

	for (int i = 0; i < numCellsZ; i++)
	{
		for (int j = 0; j < numCellsX; j++)
		{
			unsigned int bl = j + i * numVertsX;
			unsigned int br = bl + 1;
			unsigned int tl = bl + numVertsX;
			unsigned int tr = tl + 1;

			elements[countD++] = bl;
			elements[countD++] = br;
			elements[countD++] = tr;
			elements[countD++] = bl;
			elements[countD++] = tr;
			elements[countD++] = tl;

		}


	}

	int count = 0;

	for (int iz = 0; iz < numVertsZ; iz++)
	{
		for (int ix = 0; ix < numVertsX; ix++)
		{
			// UV values varying from 0 to 1
			uv[count].x = ix / float(numVertsX);
			uv[count].z = iz / float(numVertsZ);

			if (uv[count].x < 0.5f)
			{
				positions[count] = BezierSurface(cp1, uv[count].x * 2, uv[count].z);
			}
			else
			{
				positions[count] = BezierSurface(cp2, (uv[count].x - 0.5f) * 2, uv[count].z);
			}






			// sets normal to up temporarylly
			normals[count] = { 0, 1, 0 };
			count++;
		}
	}



	//int countB = { 0 };

	//for (int z = 0; z < numVertsX; z++)
	//{
	//	for (int x = 0; x < numVertsZ; x++)
	//	{
	//		glm::vec3 Pos;

	//		uv[countB].x = z / float(numVertsX);
	//		uv[countB].z = z / float(numVertsZ);

	//		positions[countB] = BezierSurface(cp1, uv[countB].x, uv[countB].z);

	//		normals[z] = { 0,1,0 };

	//		countB++;
	//	}

	//}


	// below is placeholder code to create a tessellated quad
	// replace the hardcoded values with algorithms to create a tessellated quad

	//std::vector<glm::vec3> positions = { { 0, 0, 0 }, { sizeX, 0, 0 },
	//                                     {sizeX, 0, -sizeZ}, { 0, 0, -sizeZ} };

	//std::vector<glm::vec3> normals = { { 0, 10, 0 }, { 0, 1, 0 },
	//                                   { 0, 10, 0 }, { 0, 1, 0 } };

	//std::vector<GLuint> elements = { 0, 1, 2, 0, 2, 3 };


	// below is indicative code for initialising a terrain VAO.

	glGenBuffers(1, &terrain_mesh_.element_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_mesh_.element_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		elements.size() * sizeof(GLuint),
		elements.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	terrain_mesh_.element_count = elements.size();

	glGenBuffers(1, &terrain_mesh_.position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_mesh_.position_vbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3),
		positions.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &terrain_mesh_.normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_mesh_.normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),
		normals.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &terrain_mesh_.vao);
	glBindVertexArray(terrain_mesh_.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_mesh_.element_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_mesh_.position_vbo);
	glEnableVertexAttribArray(kVertexPosition);
	glVertexAttribPointer(kVertexPosition, 3, GL_FLOAT, GL_FALSE,
		sizeof(glm::vec3), TGL_BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, terrain_mesh_.normal_vbo);
	glEnableVertexAttribArray(kVertexNormal);
	glVertexAttribPointer(kVertexNormal, 3, GL_FLOAT, GL_FALSE,
		sizeof(glm::vec3), TGL_BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MyView::windowViewDidReset(tygra::Window * window,
	int width,
	int height)
{
	glViewport(0, 0, width, height);
}

void MyView::windowViewDidStop(tygra::Window * window)
{
	glDeleteProgram(terrain_sp_);
	glDeleteBuffers(1, &terrain_mesh_.position_vbo);
	glDeleteBuffers(1, &terrain_mesh_.normal_vbo);
	glDeleteBuffers(1, &terrain_mesh_.element_vbo);
	glDeleteVertexArrays(1, &terrain_mesh_.vao);
}

void MyView::windowViewRender(tygra::Window * window)
{
	assert(scene_ != nullptr);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	const float aspect_ratio = viewport[2] / (float)viewport[3];

	const auto& camera = scene_->getCamera();
	glm::mat4 projection_xform = glm::perspective(
		glm::radians(camera.getVerticalFieldOfViewInDegrees()),
		aspect_ratio,
		camera.getNearPlaneDistance(),
		camera.getFarPlaneDistance());
	glm::vec3 camera_pos = camera.getPosition();
	glm::vec3 camera_at = camera.getPosition() + camera.getDirection();
	glm::vec3 world_up{ 0, 1, 0 };
	glm::mat4 view_xform = glm::lookAt(camera_pos, camera_at, world_up);


	glClearColor(0.f, 0.f, 0.25f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, shade_normals_ ? GL_FILL : GL_LINE);

	glUseProgram(terrain_sp_);

	GLuint shading_id = glGetUniformLocation(terrain_sp_, "use_normal");
	glUniform1i(shading_id, shade_normals_);



	glm::mat4 world_xform = glm::mat4(1);
	glm::mat4 view_world_xform = view_xform * world_xform;

	GLuint projection_xform_id = glGetUniformLocation(terrain_sp_,
		"projection_xform");
	glUniformMatrix4fv(projection_xform_id, 1, GL_FALSE,
		glm::value_ptr(projection_xform));

	GLuint view_world_xform_id = glGetUniformLocation(terrain_sp_,
		"view_world_xform");
	glUniformMatrix4fv(view_world_xform_id, 1, GL_FALSE,
		glm::value_ptr(view_world_xform));

	if (terrain_mesh_.vao) {
		glBindVertexArray(terrain_mesh_.vao);
		glDrawElements(GL_TRIANGLES, terrain_mesh_.element_count,
			GL_UNSIGNED_INT, 0);
	}
}

//std::vector<std::vector<float>> heights;

//void MyView::loadHeightMap(const char * name)// this function loads in the image that will be used as the height map
//{
	//bool loadHeightMap(const char* fileName, std::vector<float>& heightMap, 
	//std::vector<unsigned int>& index, float tileSize, float maxHeight)
	


	////Load image with SDL
	//SDL_Surface* img = SDL_LoadBMP(name);
	//if (!img)
	//{
	//	std::cout << "Failed to load " << name << "." << std::endl;
	//	return;
	//}

	////Store height values in heights vector.
	//std::vector<float> tmp;
	//std::vector<std::vector<float>> heights;
	//for (int i = 0; i < img->h; i++)
	//{
	//	tmp.clear();
	//	for (int j = 0; j < img->w; j++)
	//	{
	//		Uint32 pixel = ((Uint32*)img->pixels)[i * img->pitch / 4 + j];
	//		Uint8 r, g, b;
	//		SDL_GetRGB(pixel, img->format, &r, &g, &b);

	//		tmp.push_back((float)r / 255.0);
	//	}
	//		heights.push_back(tmp);
	//}
	//}

//void rendeHeightMap(float size, float h)
//{
//
//	//for(int i = 0;i < heights.size() - 1; i++)
//	//	for (int j; j < heights[0].size(); j++)
//	//	{
//	//		glBegin(GL_TRIANGLE_STRIP);
//	//			glVertex3f(i*size,heights[i][j] * h,j*size);
//	//			glVertex3f((i+1)*size,heights[i+1][j]*h,j*size);
//	//			glVertex3f(i+size,heights[i][j+1]*h,(j+1)*size);
//	//			glVertex3f((i + 1)*size,heights[i+1][j+1]*h,(j+1)
//	//*size);
//	//		glEnd();
//	//	}

//}

//void changeToGrayScale(int windowWidth, int windowHeight, int buffer) {
//
//	// set component scales before get pixels
//	glPixelTransferf(GL_RED_SCALE, 0.299f);
//	glPixelTransferf(GL_GREEN_SCALE, 0.587f);
//	glPixelTransferf(GL_BLUE_SCALE, 0.114f);
//
//	// read pixels as grayscale
//	glReadBuffer(GL_BACK);
//	glReadPixels(0, 0, windowWidth, windowHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, (GLvoid*)buffer);
//
//	// must restore scales to default values
//	glPixelTransferf(GL_RED_SCALE, 1);
//	glPixelTransferf(GL_GREEN_SCALE, 1);
//	glPixelTransferf(GL_BLUE_SCALE, 1);
//
//
//}
//



//Fill the vertex data and index data.
//for (int z = 0; z < img->h; z++)
//{
//	for (int x = 0; x < img->w; x++)
//	{
//		heightMap.push_back((float)x * tileSize);
//		heightMap.push_back((float)heights[x][z] * maxHeight);
//		heightMap.push_back((float)z * tileSize);

//		heightMap.push_back((float)heights[x][z]);
//		heightMap.push_back((float)heights[x][z]);
//		heightMap.push_back((float)heights[x][z]);


//		if (x < img->w - 1 && z < img->h - 1)
//		{
//			int top = z * img->w + x;
//			int bottom = (z + 1)*img->w + x;

//			index.push_back(top);
//			index.push_back(bottom);
//			index.push_back(top + 1);

//			index.push_back(top + 1);
//			index.push_back(bottom);
//			index.push_back(bottom + 1);
//		}
//	}
//}
