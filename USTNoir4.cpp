/*
 *Skeleton lighting program
 *COS490
 *Fall 2011
 **/

#include <GL/Angel.h>
#include <math.h>
#include "./matrix_stack.h"
#pragma comment(lib, "glew32.lib")

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

//store window width and height
//store window width and height
int ww=1500, wh=1100;
/////////////////////////
// stack
/////////////////////////
matrix_stack stack;

#define M_PI 3.14159265358979323846

GLuint program1, program2, program3;
GLuint carvao[1];
GLuint carvbo[2];
GLuint stagevao[1];
GLuint stagevbo[2];
GLuint vao[1];
GLuint vbo[2];
int spherevertcount;
int mode = 0;

int right_button_down = FALSE;
int left_button_down = FALSE;

int prevMouseX;
int prevMouseY;

double view_rotx = 0.0;
double view_roty = 0.0;
double view_rotz = 0.0;
double z_distance;
//these are the extra variables needed for the Stage
GLfloat tx, ty, tz;
GLfloat rx, ry, rz;

vec4 rightlampSource;
vec3 rightlampDest;

//////////////////////////////////////////////////
// // turn the wheel left/right angle
//////////////////////////////////////////////////
GLfloat turnAngle;
GLfloat turnCarAngle = 0;

GLfloat maxTurnWheel = 45.00f;

//////////////////////////////////////////////////
// current position of the car
//////////////////////////////////////////////////
GLfloat currentX;
GLfloat currentZ;
/////////////////////////
// move car
/////////////////////////
//GLfloat moveForward;
GLfloat moveStepZ = 0.0005;
GLfloat rollangle;
GLfloat turnEyeAngle;

GLfloat moveStepX, vectorLen;

GLboolean  bmoveForward;

GLint switchcamera;
GLint turnEyeRight;

//////////////////////////
GLboolean  pointCameraAt;
GLfloat lenszoom;
GLfloat dollyzoom;
GLfloat atX, atZ;

//our modelview and perspective matrices
mat4 mv, p;

//and we'll need pointers to our shader variables
GLuint model_view;
GLuint projection;


GLuint vPosition;
GLuint vNormal;


/////////////////////////
// wheel cylinder
/////////////////////////
vec4 wheelCylinderVers[414];
vec4 vWheelCylinderNormals[414];

vec4 wheelCylinderColors[500];

GLuint cylindervao[1];
GLuint cylindervbo[2];

/////////////////////////
// wheel side vertices
/////////////////////////
vec4 wheelSide1Verts[75];
vec4 wheelSide1Normals[75];

vec4 wheelSide2Verts[75];
vec4 wheelSide2Normals[75];

vec4 wheelside1Colors[75];
vec4 wheelside2Colors[75];

GLuint wheelside1vao[1];
GLuint wheelside1vbo[2];

GLuint wheelside2vao[1];
GLuint wheelside2vbo[2];

// WHEEEL
GLuint vWheelSide1AmbientColor;
GLuint vWheelSide1DiffuseColor; //Ambient and Diffuse can be the same for the material
GLuint vWheelSide1SpecularColor;
GLuint vWheelSide1Shininess;

// wheel2
GLuint vWheelSide2AmbientColor;
GLuint vWheelSide2DiffuseColor; //Ambient and Diffuse can be the same for the material
GLuint vWheelSide2SpecularColor;
GLuint vWheelSide2Shininess;

// cylinder
GLuint vWheelCylinderAmbientColor; //Ambient and Diffuse can be the same for the material
GLuint vWheelCylinderDiffuseColor; //Ambient and Diffuse can be the same for the material
GLuint vWheelCylinderSpecularColor;
GLuint vWheelCylinderShininess;

GLuint vAmbientDiffuseColor;
GLuint vSpecularColor;
GLuint vSpecularExponent;

GLuint vStageAmbientDiffuseColor;
GLuint vStageSpecularColor;
GLuint vStageSpecularExponent;


GLuint vCarAmbientDiffuseColor;
GLuint vCarSpecularColor;
GLuint vCarSpecularExponent;


GLuint moonlight_position;
GLuint moonlight_color;
GLuint moondiffuse_color;
GLuint moonspecular_color;
GLuint moonambient_light;
//GLuint spot_cutoff;
//GLuint spot_exponent;
//GLuint spot_direction;


GLuint headlight_position;
GLuint headlight_color;
GLuint headdiffuse_color;
GLuint headspecular_color;
GLuint headambient_light;
GLuint headspot_cutoff;
GLuint headspot_exponent;
GLuint headspot_direction;

struct lightSource
{
	vec4 ambient;
	vec4 position;
	vec4 diffuse;
	vec4 specular;
	float constantAttenuation, linearAttenuation, quadraticAttenuation;
	float spotCutoff, spotCosCutoff, spotExponent;
	vec3 spotDirection;
};
lightSource directionalLight, spotLightHeadLamp;
const int numberofLightSources = 2;
lightSource lights[numberofLightSources];

struct material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

vec4* sphere_verts;
vec3* sphere_normals;

vec4* stageVerts;
vec3* stageNormals;

vec4* carVerts;
vec3* carNormals;
vec4* carColors;

void reshape(int width, int height){
	ww= width;
	wh = height;
	//field of view angle, aspect ratio, closest distance from camera to object, largest distanec from camera to object
	p = Perspective(lenszoom, (float)width/(float)height, 1.0, 100.0);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p);
	glViewport( 0, 0, width, height );
		
}


/////////////////////////////////////////
// generateStage
/////////////////////////////////////////
void generateStage(){
	
	stageVerts = new vec4[6];
	stageNormals = new vec3[6];

	vec4 a = stageVerts[2] = vec4(1.0f, -1.0f, -1.0f, 1.0);
	vec4 b = stageVerts[1] = vec4(1.0f, -1.0f, 1.0f, 1.0);
	vec4 c = stageVerts[0] = vec4(-1.0f, -1.0f, 1.0f, 1.0);

	vec3 normals = normalize(cross(a-b, c-b));//cross(a-b,c-b));
	stageNormals[0] = normals;
	stageNormals[1] = normals;
	stageNormals[2] = normals;


	vec4 d = stageVerts[5] = vec4(-1.0f, -1.0f, 1.0f, 1.0);
	vec4 e = stageVerts[4] = vec4(-1.0f, -1.0f, -1.0f, 1.0);
	vec4 f = stageVerts[3] = vec4(1.0f, -1.0f, -1.0f, 1.0);

	//normals = normalize();//cross(d-e,f-e));
	stageNormals[3] = normals;
	stageNormals[4] = normals;
	stageNormals[5] = normals;

}

/////////////////////////////////////////
// generateCar
/////////////////////////////////////////

void generateCar(){

	carVerts = new vec4[36];
	carNormals = new vec3[36];


	int index = 0;
	//for(int i=0; i<6; i++){
	//	carColors[i] = vec4(0.0, 1.0, 1.0, 1.0); //front
	//}
	//
	carVerts[0] = vec4( 0.05f, -0.05f, 0.05f, 1.0);
	carVerts[1] = vec4( 0.05f,  0.05f, 0.05f, 1.0);
	carVerts[2] = vec4(-0.05f,  0.05f, 0.05f, 1.0);

	// calculate normal vectore for car
	vec3 normal = normalize(cross(carVerts[2] - carVerts[1], carVerts[0] - carVerts[1]));
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 


	carVerts[3] = vec4(-0.05f,  0.05f, 0.05f, 1.0);
	carVerts[4] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	carVerts[5] = vec4( 0.05f, -0.05f, 0.05f, 1.0);
	
	// calculate normal vectore for car
	//normal = normalize(cross( carVerts[5] - carVerts[4], carVerts[3] - carVerts[4]));
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 


	//for(int i=6; i<12; i++){
	//	carColors[i] = vec4(1.0, 0.0, 1.0, 1.0); //back
	//}
	carVerts[6] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	carVerts[7] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	carVerts[8] = vec4(0.05f, 0.05f, -0.05f, 1.0);


	// calculate normal vectore for car
	normal = normalize(cross(carVerts[7] - carVerts[6], carVerts[8] - carVerts[7]));
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 

	carVerts[9] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	carVerts[10] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	carVerts[11] = vec4(-0.05f, -0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	// normal = normalize(cross(carVerts[10] - carVerts[9], carVerts[11] - carVerts[10]));
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 


	//for(int i=12; i<18; i++){
	//	carColors[i] = vec4(1.0, 1.0, 0.0, 1.0); //left
	//}
	carVerts[12] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	carVerts[13] = vec4(0.05f, -0.05f, 0.05f, 1.0);
	carVerts[14] = vec4(0.05f, -0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	normal = normalize(cross(carVerts[13] - carVerts[12], carVerts[14] - carVerts[13]));
	carNormals[index++] = -normal; 
	carNormals[index++] = -normal; 
	carNormals[index++] = -normal; 

	carVerts[15] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	carVerts[16] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	carVerts[17] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	

	// calculate normal vectore for car
	// normal = normalize(cross(carVerts[16] - carVerts[15], carVerts[17] - carVerts[16]));
	carNormals[index++] = -normal; 
	carNormals[index++] = -normal; 
	carNormals[index++] = -normal; 


	//for(int i=18; i<24; i++){
	//	carColors[i] = vec4(1.0, 0.0, 0.0, 1.0); //right
	//}
	carVerts[18] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	carVerts[19] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	carVerts[20] = vec4(-0.05f, -0.05f, 0.05f, 1.0);

	// calculate normal vectore for car
	normal = normalize(cross(carVerts[19] - carVerts[18], carVerts[20] - carVerts[19]));
	carNormals[index++] = -normal; 
	carNormals[index++] = -normal; 
	carNormals[index++] = -normal; 


	carVerts[21] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	carVerts[22] = vec4(-0.05f, 0.05f, 0.05f, 1.0);
	carVerts[23] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	
	// calculate normal vectore for car
	// normal = normalize(cross(carVerts[22] - carVerts[21], carVerts[23] - carVerts[22]));
	carNormals[index++] = -normal; 
	carNormals[index++] = -normal; 
	carNormals[index++] = -normal; 


	//for(int i=24; i<30; i++){
	//	carColors[i] = vec4(0.0, 0.0, 1.0, 1.0); //top
	//}
	carVerts[24] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	carVerts[25] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	carVerts[26] = vec4(-0.05f, 0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	normal = normalize(cross(carVerts[26] - carVerts[25], carVerts[24] - carVerts[25]));
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 

	carVerts[27] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	carVerts[28] = vec4(-0.05f, 0.05f, 0.05f, 1.0);
	carVerts[29] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	
	// calculate normal vectore for car
	// normal = normalize(cross(carVerts[29] - carVerts[28], carVerts[28] - carVerts[27]));
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 
	carNormals[index++] = normal;

	//for(int i=30; i<36; i++){
	//	carColors[i] = vec4(0.0, 1.0, 0.0, 1.0); //bottom
	//}
	carVerts[30] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	carVerts[31] = vec4(0.05f, -0.05f, 0.05f, 1.0);
	carVerts[32] = vec4(-0.05f, -0.05f, 0.05f, 1.0);

	// calculate normal vectore for car
	normal = normalize(cross(carVerts[31] - carVerts[30], carVerts[32] - carVerts[31]));
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 
	carNormals[index++] = normal;

	carVerts[33] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	carVerts[34] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	carVerts[35] = vec4(0.05f, -0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	// normal = normalize(cross(carVerts[34] - carVerts[33], carVerts[35] - carVerts[34]));
	carNormals[index++] = normal; 
	carNormals[index++] = normal; 
	carNormals[index++] = normal;
	
}

/////////////////////////////////////////
// generateWheelSides
/////////////////////////////////////////
void generateWheelSides()
{
	int side = 1; // the outer side of the wheel
	
	int point = 0;
	double angleincrement = 15;
	for ( double angle = 0; angle <= 360; angle += angleincrement)
	{
		//wheelside1Colors[point] = vec4(1.0f, 1.0f, 1.0f, 1.0);
		point4 a = wheelSide1Verts[point++] = vec4(0.0f,side*(-1.0f), 0.0f, 1.0); //point 1
		
		//wheelside1Colors[point] = vec4(cos(angle*M_PI/180), -1.0f, -sin(angle*M_PI/180), 1.0); //point 2
		point4 b = wheelSide1Verts[point++] = vec4(cos(angle*M_PI/180), side*(-1.0f), -sin(angle*M_PI/180), 1.0); //point 2
		
		//wheelside1Colors[point] = vec4(cos((angle+angleincrement)*M_PI/180), -1.0f, -sin((angle+angleincrement)*M_PI/180), 1.0); //point 3
		point4 c = wheelSide1Verts[point++] = vec4(cos((angle+angleincrement)*M_PI/180), side*(-1.0f), -sin((angle+angleincrement)*M_PI/180), 1.0); //point 3
		
		vec3 normal = normalize(cross(c-b, a -b));

		wheelSide1Normals[point-3] = normal;
		wheelSide1Normals[point-2] = normal;
		wheelSide1Normals[point-1] = normal;

	}

	side = -1; // the inner side of the wheel
	point = 0;
	angleincrement = 15;
	for ( double angle = 0; angle <= 360; angle += angleincrement)
	{
		point4 a = wheelSide2Verts[point++] = vec4(0.0f,		side*(-1.0f), 0.0f, 1.0); 
		

		point4 b = wheelSide2Verts[point++] = vec4(cos(angle*M_PI/180), side*(-1.0f), -sin(angle*M_PI/180), 1.0); 
		wheelside2Colors[point] = vec4(0.5f,0.5f,0.5f, 1.0); 

		point4 c = wheelSide2Verts[point++] = vec4(cos((angle+angleincrement)*M_PI/180), side*(-1.0f), -sin((angle+angleincrement)*M_PI/180), 1.0); //point 3
		wheelside2Colors[point] = vec4(0.5f ,0.5f,0.5f, 1.0); 

		vec3 normal = normalize(cross(c-b, a -b));

		wheelSide2Normals[point-3] = normal;
		wheelSide2Normals[point-2] = normal;
		wheelSide2Normals[point-1] = normal;
	}


	//
	// cylinder of the wheel
	int p = 0;
	for ( int i = 0; i < 410 ; i += 6)
	{
	
		point4 a = wheelCylinderVers[i] =   wheelSide1Verts[(p+1)%3==0?(p+1+1+1):(p+1)];
		point4 b = wheelCylinderVers[i+1] = wheelSide1Verts[(p+2)%3==0?(p+2+1+1):(p+2)];
		point4 c = wheelCylinderVers[i+2] = wheelSide2Verts[(p+1)%3==0?(p+1+1+1):(p+1)];

		vec3 normal = normalize(cross(c - b, a - b));
		vWheelCylinderNormals[i] = normal;
		vWheelCylinderNormals[i+1] = normal;
		vWheelCylinderNormals[i+2] = normal;

		a = wheelCylinderVers[i+3] = wheelSide1Verts[(p+2)%3==0?(p+2+1+1):(p+2)];
		b = wheelCylinderVers[i+4] = wheelSide2Verts[(p+2)%3==0?(p+2+1+1):(p+2)];
		c = wheelCylinderVers[i+5] = wheelSide2Verts[(p+1)%3==0?(p+1+1+1):(p+1)];
		normal = normalize(cross(c - b, a - b));
		vWheelCylinderNormals[i+3] = normal;
		vWheelCylinderNormals[i+4] = normal;
		vWheelCylinderNormals[i+5] = normal;


		p++;

	}


	

	
}
/////////////////////////////////////////
// DrawTriagle
/////////////////////////////////////////
void DrawTriagle(GLuint vao[], int count)
{
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p);
	glBindVertexArray( vao[0] );
	glDrawArrays( GL_TRIANGLES, 0, count );
}

//In this particular case, our normal vectors and vertex vectors are identical since the sphere is centered at the origin
//For most objects this won't be the case, so I'm treating them as separate values for that reason
//This could also be done as separate triangle strips, but I've chosen to make them just triangles so I don't have to execute multiple glDrawArrays() commands
int generateSphere(float radius, int subdiv){
	float step = (360.0/subdiv)*(M_PI/180.0);

	int totalverts = ceil(subdiv/2.0)*subdiv * 6;

	if(sphere_normals){
		delete[] sphere_normals;
	}
	sphere_normals = new vec3[totalverts];
	if(sphere_verts){
		delete[] sphere_verts;
	}
	sphere_verts = new vec4[totalverts];

	int k = 0;
	for(float i = -M_PI/2; i<=M_PI/2; i+=step){
		for(float j = -M_PI; j<=M_PI; j+=step){
			//triangle 1
			sphere_normals[k]= vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
			sphere_verts[k]=   vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
			k++;
	
			sphere_normals[k]= vec3(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step));
			sphere_verts[k]=   vec4(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step), 1.0);
			k++;
			
			sphere_normals[k]= vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
			sphere_verts[k]=   vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
			k++;

			//triangle 2
			sphere_normals[k]= vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
			sphere_verts[k]=   vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
			k++;

			sphere_normals[k]= vec3(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i));
			sphere_verts[k]=   vec4(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i), 1.0);
			k++;

			sphere_normals[k]= vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
			sphere_verts[k]=   vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
			k++;
		}
	}
	return totalverts;
}

void setupHeadLight()
{
	

	//stack.push(mv);

		/*mv = mv * Translate(rightlampSource.x, 0, rightlampSource.z);
		mv = mv * RotateY(turnCarAngle);*/

		glUniform4fv(headlight_position, 1, mv*rightlampSource); //1));
		glUniform4fv(headspot_direction, 1, mv*rightlampDest);//vec4(0, -10, 0));

	//mv = stack.pop();

	glUniform4fv(headlight_color, 1, vec4(1,.8f,.4f,1));
	glUniform4fv(headdiffuse_color, 1, vec4(0.8,.8f,.4f,1));
	glUniform4fv(headspecular_color, 1, vec4(1,.8f,.4f,1));
	glUniform4fv(headambient_light, 1, vec4(.2, .2, .2, 1));

	
	glUniform1f(headspot_cutoff, 30);
	glUniform1f(headspot_exponent, 10);

}
void setupMoonLight()
{
	glUniform4fv(moonlight_position, 1, mv*vec4(100, 100, 100, 0)); //1));
	glUniform4fv(moondiffuse_color, 1, vec4(0.8,.8f,.4f,1));
	glUniform4fv(moonspecular_color, 1, vec4(0.8,.8f,.4f,1));
	glUniform4fv(moonambient_light, 1, vec4(.2, .2, .2, 1));

	/*glUniform4fv(spot_direction, 1, mv*vec4(0, -10, 1));
	glUniform1f(spot_cutoff, 30);
	glUniform1f(spot_exponent, 10);*/

}
/////////////////////////////////////////
// displayStage
/////////////////////////////////////////
void displayStage(void)
{
	/*glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
  
	
	glUniform4fv(vStageAmbientColor,1, stage.ambient);
	glUniform4fv(vStageDiffuseColor,1, stage.diffuse);
	glUniform4fv(vStageSpecularColor,1, stage.specular);
	glUniform1i(vStageShininess, stage.shininess);

	DrawTriagle(stagevao, 36);

	stack.push(mv);*/

		//mv = mv * Translate(0, 10,0);
		//mv = mv * RotateX(90);

	glVertexAttrib4fv(vStageAmbientDiffuseColor, vec4(.5, 0.5, 0.5, 1));
	glVertexAttrib4fv(vStageSpecularColor, vec4(0.5f,0.5f,1.0f,1.0f));
	glVertexAttrib1f(vStageSpecularExponent, 10.0);

	glBindVertexArray( stagevao[0] );
	glDrawArrays( GL_TRIANGLES, 0, 6 );    // draw the sphere 
   
}

void moveHeadLight()
{
	//stack.push(mv);
		
	
	/*vec4 rightlampSource = vec4(currentX,-0.93,currentZ,1); 
	vec3 rightlampDest   = vec3(currentX,-0.99,currentZ + 0.05); 
	
	glUniform4fv(headlight_position, 1, mv*rightlampSource); 
	glUniform4fv(headspot_direction, 1, mv*rightlampDest);*/
	
	//mv = stack.pop();
}
/////////////////////////////////////////
// displayCar
/////////////////////////////////////////
void displayCar(void)
{
	
	stack.push(mv);
	
	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
	 
	mv = mv * Translate(0, -0.93, 0.0005); 
	//mv = mv * Scale(1.0,0.5,3);
	mv = mv * Scale(0.5,0.25,1.5 );
	
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glVertexAttrib4fv(vCarAmbientDiffuseColor, vec4(1.0f, 1.0f, 0.0f, 1));
	glVertexAttrib4fv(vCarSpecularColor, vec4(1.0f, 1.0f,0.0f,1.0f));
	glVertexAttrib1f(vCarSpecularExponent, 10.0);


	DrawTriagle(carvao, 36);

	mv = stack.pop();
   
}
/////////////////////////////////////////
// DrawWheels
/////////////////////////////////////////
void DrawWheels(GLuint wheelside1vao[1],
				  GLuint wheelside2vao[2],
				  GLuint cylindervao[1], 
				  GLsizei sidecount, GLsizei cylindercount)
{
	
	
	/*glUniform4fv(vWheelSide1AmbientColor,1, wheelside.ambient);
	glUniform4fv(vWheelSide1DiffuseColor,1, wheelside.diffuse);
	glUniform4fv(vWheelSide1SpecularColor,1, wheelside.specular);
	glUniform1i(vWheelSide1Shininess, wheelside.shininess);*/

	DrawTriagle(wheelside1vao, sidecount);

	/*glUniform4fv(vWheelSide2AmbientColor,1, wheelside.ambient);
	glUniform4fv(vWheelSide2DiffuseColor,1, wheelside.diffuse);
	glUniform4fv(vWheelSide2SpecularColor,1, wheelside.specular);
	glUniform1i(vWheelSide2Shininess, wheelside.shininess);*/

	DrawTriagle(wheelside2vao, sidecount);
	
	
	// draw cylinder

	/*glUniform4fv(vWheelCylinderAmbientColor,1, cylinder.ambient);
	glUniform4fv(vWheelCylinderDiffuseColor,1, cylinder.diffuse);
	glUniform4fv(vWheelCylinderSpecularColor,1, cylinder.specular);
	glUniform1i(vWheelCylinderShininess, cylinder.shininess);
*/
	
	DrawTriagle(cylindervao, cylindercount);

}
/////////////////////////////////////////
// displayWheels
/////////////////////////////////////////
void displayWheels()
{

	/////////////////////
	// First wheel : driver wheel
	////////////////////
	stack.push(mv);

	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
		
		
	mv = mv * Translate(0.04, -0.97f, 0.0405); //0.065); // 0.04);
	mv = mv * RotateZ(90);
	mv = mv * RotateX(turnAngle);
    mv = mv * RotateY(-rollangle);
	mv = mv * Scale(0.025,0.007,0.025);

    
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glVertexAttrib4fv(vCarAmbientDiffuseColor, vec4(0.5f, 0.5f, 0.0f, 1));
	glVertexAttrib4fv(vCarSpecularColor, vec4(1.0f, 0.0f,0.0f,1.0f));
	glVertexAttrib1f(vCarSpecularExponent, 10.0);

	
	DrawWheels(wheelside1vao,wheelside2vao,cylindervao, 75, 414);

	
	mv = stack.pop();


	/////////////////////////////////
	// seconf wheel: passenger wheel
	/////////////////////////////////
	stack.push(mv);


	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
	
	
	mv = mv * Translate(-0.04, -0.97f, 0.0405);
	mv = mv * RotateZ(-90);
	mv = mv * RotateX(-turnAngle);
	mv = mv * RotateY(rollangle);
	mv = mv * Scale(0.025,0.007,0.025);

	glVertexAttrib4fv(vCarAmbientDiffuseColor, vec4(0.5f, 0.5f, 0.0f, 1));
	glVertexAttrib4fv(vCarSpecularColor, vec4(1.0f, 0.0f,0.0f,1.0f));
	glVertexAttrib1f(vCarSpecularExponent, 10.0);

	DrawWheels(wheelside1vao,wheelside2vao,cylindervao, 75, 414);

	mv = stack.pop();

	/////////////////////////////////
	// third wheel
	/////////////////////////////////
	stack.push(mv);
	
	
	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
	
		
	mv = mv * Translate(0.04, -0.97f, -0.0595); //-0.06 + 0.0005);
	mv = mv * RotateZ(90);
	
	mv = mv * RotateY(-rollangle);
	mv = mv * Scale(0.025,0.007,0.025);

	DrawWheels(wheelside1vao,wheelside2vao,cylindervao, 75, 414);
	
	mv = stack.pop();

	/////////////////////////////////
	// fourth wheel
	/////////////////////////////////
	stack.push(mv);
		
	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
	
	
	mv = mv * Translate(-0.04, -0.97f, -0.0595);
	mv = mv * RotateZ(-90);
	
	mv = mv * RotateY(rollangle);
	mv = mv * Scale(0.025,0.007,0.025);
		
	DrawWheels(wheelside1vao,wheelside2vao,cylindervao, 75, 414);
		 

	mv = stack.pop();


}
void display(void)
{
  /*clear all pixels*/
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //mv = LookAt(vec4(0, 0, 10+z_distance, 1.0), vec4(0, 0, 0, 1.0), vec4(0, 1, 0, 0.0));

	mv = LookAt(vec4(0, 0, dollyzoom, 1.0), vec4(atX, 0, atZ, 1.0), vec4(0, 1, 0, 0.0));

	//mv = mv * Translate(tx, ty, tz);
	mv = mv *RotateX(rx);
	//mv = mv * RotateY(ry);
	//mv = mv * RotateZ(rz);

	mv = mv * RotateX(view_rotx) * RotateY(view_roty) * RotateZ(view_rotz);

	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
	
	setupMoonLight();
	setupHeadLight();

	if(mode == 0){
		//glBindVertexArray( vao[0] );

		//glDrawArrays( GL_TRIANGLES, 0, spherevertcount );    // draw the sphere 


		displayStage();
		moveHeadLight();
		displayCar();
		displayWheels();
		

	}else{
		glBindVertexArray(0);
		glutSolidTeapot(2); //not very bandwidth efficient
	}
    
    glFlush();
  /*start processing buffered OpenGL routines*/
  glutSwapBuffers();
}

void setupShader(GLuint prog){
	
	// Create a vertex array object
    glGenVertexArrays( 1, &vao[0] );

    // Create and initialize any buffer objects
	glBindVertexArray( vao[0] );
	glGenBuffers( 2, &vbo[0] );
    glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
    glBufferData( GL_ARRAY_BUFFER, spherevertcount*sizeof(vec4), sphere_verts, GL_STATIC_DRAW);
	

	//and now our colors for each vertex
	glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
	glBufferData( GL_ARRAY_BUFFER, spherevertcount*sizeof(vec3), sphere_normals, GL_STATIC_DRAW );


	glUseProgram( prog );
	//glLinkProgram( prog);
	model_view = glGetUniformLocation(prog, "model_view");
	projection = glGetUniformLocation(prog, "projection");
	
	vStageAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vStageSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vStageSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");


	// setup moonlight
	moonlight_position = glGetUniformLocation(prog, "lights[0].position");
	moondiffuse_color = glGetUniformLocation(prog, "lights[0].diffuse");
	moonspecular_color = glGetUniformLocation(prog, "lights[0].specular");
	moonambient_light = glGetUniformLocation(prog, "ambient_light");

	//setup headlight
	headlight_position = glGetUniformLocation(prog, "lights[1].position");
	headdiffuse_color = glGetUniformLocation(prog, "lights[1].diffuse");
	headspecular_color = glGetUniformLocation(prog, "lights[1].specular");
	headambient_light = glGetUniformLocation(prog, "ambient_light");

	headspot_direction = glGetUniformLocation(prog, "lights[1].spot_direction");
	headspot_cutoff = glGetUniformLocation(prog, "lights[1].spot_cutoff");
	headspot_exponent = glGetUniformLocation(prog, "lights[1].spot_exponent");
 

	glBindVertexArray( vao[0] );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
	vNormal = glGetAttribLocation(prog, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupCarShader(GLuint prog)
{
	vCarAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vCarSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vCarSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");

		// Create a vertex array object
    glGenVertexArrays( 1, &carvao[0] );
	glBindVertexArray( carvao[0] );
	glGenBuffers( 2, &carvbo[0] );
    glBindBuffer( GL_ARRAY_BUFFER, carvbo[0] );
	glBufferData( GL_ARRAY_BUFFER, 36*sizeof(vec4), carVerts, GL_STATIC_DRAW);
	glBindBuffer( GL_ARRAY_BUFFER, carvbo[1] );
	glBufferData( GL_ARRAY_BUFFER, 36*sizeof(vec3), carNormals, GL_STATIC_DRAW );


	glBindVertexArray( carvao[0] );
	glBindBuffer( GL_ARRAY_BUFFER, carvbo[0] );
	vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer( GL_ARRAY_BUFFER, carvbo[1] );
	vNormal = glGetAttribLocation(prog, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
void setupWheelShader(GLuint prog)
{
	// Create a vertex array object
    glGenVertexArrays( 1, &wheelside1vao[0] );
	glBindVertexArray( wheelside1vao[0] );

	glGenBuffers( 2, &wheelside1vbo[0] );
    glBindBuffer( GL_ARRAY_BUFFER, wheelside1vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, 75*sizeof(vec4), wheelSide1Verts, GL_STATIC_DRAW);
	glBindBuffer( GL_ARRAY_BUFFER, wheelside1vbo[1] );
	glBufferData( GL_ARRAY_BUFFER, 75*sizeof(vec3), wheelSide1Normals, GL_STATIC_DRAW );

	glBindVertexArray( wheelside1vao[0] );
	glBindBuffer( GL_ARRAY_BUFFER, wheelside1vbo[0] );
	vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer( GL_ARRAY_BUFFER, wheelside1vbo[1] );
	vNormal = glGetAttribLocation(prog, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);


	// wheelside 2
	glGenVertexArrays( 1, &wheelside2vao[0] );
	glBindVertexArray( wheelside2vao[0] );

	glGenBuffers( 2, &wheelside2vbo[0] );
    glBindBuffer( GL_ARRAY_BUFFER, wheelside2vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, 75*sizeof(vec4), wheelSide2Verts, GL_STATIC_DRAW);
	glBindBuffer( GL_ARRAY_BUFFER, wheelside2vbo[1] );
	glBufferData( GL_ARRAY_BUFFER, 75*sizeof(vec3), wheelSide2Normals, GL_STATIC_DRAW );

	glBindVertexArray( wheelside2vao[0] );
	glBindBuffer( GL_ARRAY_BUFFER, wheelside2vbo[0] );
	vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer( GL_ARRAY_BUFFER, wheelside2vbo[1] );
	vNormal = glGetAttribLocation(prog, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);


	// cylinder
	glGenVertexArrays( 1, &cylindervao[0] );
	glBindVertexArray( cylindervao[0] );

	glGenBuffers( 2, &cylindervbo[0] );
    glBindBuffer( GL_ARRAY_BUFFER, cylindervbo[0] );
	glBufferData( GL_ARRAY_BUFFER, 414*sizeof(vec4), wheelCylinderVers, GL_STATIC_DRAW);
	glBindBuffer( GL_ARRAY_BUFFER, wheelside2vbo[1] );
	glBufferData( GL_ARRAY_BUFFER, 414*sizeof(vec3), vWheelCylinderNormals, GL_STATIC_DRAW );

	glBindVertexArray( cylindervao[0] );
	glBindBuffer( GL_ARRAY_BUFFER, cylindervbo[0] );
	vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer( GL_ARRAY_BUFFER, cylindervbo[1] );
	vNormal = glGetAttribLocation(prog, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);


}
void setupStageShader(GLuint prog)
{
	
	// Create a vertex array object
    glGenVertexArrays( 1, &stagevao[0] );
	glBindVertexArray( stagevao[0] );
	
	glGenBuffers( 2, &stagevbo[0] );
    glBindBuffer( GL_ARRAY_BUFFER, stagevbo[0] );
	glBufferData( GL_ARRAY_BUFFER, 6*sizeof(vec4), stageVerts, GL_STATIC_DRAW);
	glBindBuffer( GL_ARRAY_BUFFER, stagevbo[1] );
	glBufferData( GL_ARRAY_BUFFER, 6*sizeof(vec3), stageNormals, GL_STATIC_DRAW );


	glBindVertexArray( stagevao[0] );
	glBindBuffer( GL_ARRAY_BUFFER, stagevbo[0] );
	vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer( GL_ARRAY_BUFFER, stagevbo[1] );
	vNormal = glGetAttribLocation(prog, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

/////////////////////////////////////////
// myIdle
/////////////////////////////////////////
void myIdle()
{

	GLint moveF = 1;
	if ( bmoveForward == true )
	{
		moveF = 1;
	}
	else
	{
		moveF = -1;
	}

	

	//chasecamlookdirection = RotateY((moveF)*0.2*(turnAngle)/maxTurnWheel) * chasecamlookdirection;
	//viewpointcam = RotateY((moveF)*0.2*(turnAngle)/maxTurnWheel) * viewpointcam;

		
	if ( pointCameraAt == true ) // point the stage
	{
		atX = 0;
		atZ = 0;
	}
	else // point at the car
	{
		atX = currentX;
		atZ = currentZ;
	}

	if ( currentX > -1 && currentX < 1 &&
		 currentZ > -1 && currentZ < 1 ) 
	{
		if ( bmoveForward == true )
		{
		
			if ( turnAngle < 0)
			{
				turnCarAngle -= 0.2*abs(turnAngle)/maxTurnWheel;
			}
			else if ( turnAngle > 0)
			{
				turnCarAngle += 0.2*abs(turnAngle)/maxTurnWheel;
			}
			
	
			moveStepX = vectorLen * sin(turnCarAngle*M_PI/180);
			moveStepZ  = vectorLen * cos(turnCarAngle*M_PI/180);

			currentX = currentX + moveStepX;
			currentZ = currentZ + moveStepZ;

			rightlampSource.x = rightlampSource.x + moveStepX;
			rightlampSource.z = rightlampSource.z + moveStepZ;

			rightlampDest.x = rightlampDest.x + moveStepX;
			rightlampDest.z = rightlampDest.z + moveStepZ;

			rightlampSource = vec4(rightlampSource.x,-0.90,rightlampSource.z,1); 
			rightlampDest   = vec3(rightlampDest.x,-0.99,rightlampDest.z); 

			if ( currentX < -1.0 )
			{
				currentX = -1.00f;
			}
			else if ( currentX > 1.0 )
			{
				currentX = 1.00f;
			}
			else if ( currentZ > 1.0 )
			{
				currentZ = 1.00f;
			}
			else if ( currentZ < -1.0 )
			{
				currentZ = -1.00f;
			}
			else
			{
			
			}

			rollangle += (vectorLen * 360)/(0.05*M_PI);
		}
		else
		{
			if ( turnAngle < 0)
			{
				turnCarAngle += 0.2*abs(turnAngle)/maxTurnWheel;;
			}
			else if ( turnAngle > 0)
			{
				turnCarAngle -= 0.2*abs(turnAngle)/maxTurnWheel;;
			}
		
			moveStepX = vectorLen * sin(turnCarAngle*M_PI/180);
			moveStepZ  = vectorLen * cos(turnCarAngle*M_PI/180);

			currentX = currentX - moveStepX;
			currentZ = currentZ - moveStepZ;

			rightlampSource.x = rightlampSource.x - moveStepX;
			rightlampSource.z = rightlampSource.z - moveStepZ;

			rightlampDest.x = rightlampDest.x - moveStepX;
			rightlampDest.z = rightlampDest.z - moveStepZ;

			rightlampSource = vec4(rightlampSource.x,-0.90,rightlampSource.z,1); 
			rightlampDest   = vec3(rightlampDest.x,-0.99,rightlampDest.z); 

			if ( currentX < -1.0 )
			{
				currentX = -1.00f;
			}
			else if ( currentX > 1.0 )
			{
				currentX = 1.00f;
			}
			else if ( currentZ > 1.0 )
			{
				currentZ = 1.00f;
			}
			else if ( currentZ < -1.0 )
			{
				currentZ = -1.00f;
			}
		

			rollangle -= (vectorLen * 360)/(0.05*M_PI);
		}

		glutPostRedisplay();
	}
} 
void Keyboard(unsigned char key, int x, int y) {
	/*exit when the escape key is pressed*/
	if (key == 27)
		exit(0);

	if (key == 'w' || key == 'W' ) // dolly in
	{
		dollyzoom += 1;
	}
	else if (key == 'q' || key == 'Q' ) // to dolly out in
	{
		dollyzoom -= 1;
	}
	if (key == 'g'){
		setupShader(program1);
		setupStageShader(program3);
	}
	if (key == 'p'){
		setupShader(program2);
		setupStageShader(program3);
	}
	if (key == 'c'){
		setupShader(program3);
		setupStageShader(program3);
	}
	if (key == 's'){
		mode = 0;
	}
	if (key == 't'){
		mode = 1;
	}
	if (key == 'r' || key == 'R' )
	{
		 ///////////////////
		  // assighment 3
		  ///////////////////
		  atX = atZ = 0;
		  dollyzoom = 20.0f;
		  lenszoom = 45.0;

		  reshape(ww, wh);
	}
	else if (key == 'c' || key == 'C' )
	{
		/*if ( switchcamera == 0 )
		{
			p = Perspective(45.0, (float)ww/(float)wh, 1.0, 100.0);
			switchcamera = 1;
		}
		else if ( switchcamera == 1 )
		{
			p = Perspective(45.0, (float)ww/(float)wh, 1.0, 100.0);
			switchcamera = 2;
		}
		else if ( switchcamera == 2 )
		{
			reshape(ww, wh);
			switchcamera = 0;
		}
*/
	}
	else if (key == 'f' || key == 'F' ) // toggle b/t look at origin or current car postion
	{
		if ( pointCameraAt == true )
		{
			pointCameraAt = false;
			
		}
		else
		{
			pointCameraAt = true;
			
		}
	}
	else if (key == 's' || key == 'S' ) // to zoom out
	{


		/*if ( switchcamera == 0)
		{
			lenszoom += 1;
			reshape(ww, wh);
		}
		else
			p = Perspective(45.0, (float)ww/(float)wh, 1.0, 100.0);*/
			
	}
	else if (key == 'a' || key == 'A' ) // to zoom in
	{
		
		/*if ( switchcamera == 0)
		{
			lenszoom -= 1;
			reshape(ww, wh);
		}
		else
			p = Perspective(45.0, (float)ww/(float)wh, 1.0, 100.0);*/
	}
	else if (key == 'w' || key == 'W' ) // dolly in
	{
		dollyzoom += 1;
	}
	else if (key == 'q' || key == 'Q' ) // to dolly out in
	{
		dollyzoom -= 1;
	}
	if ( key == 'b' || key == 'B' ) // to start the car
	{
		glutIdleFunc(myIdle);
	}

	if ( key == 32 ) // to stop car moving
	{
		glutIdleFunc(NULL);
	}
	else if(key == 'z')
	{
		//turnEyeRight = 1;
		//turnEyeAngle += 1;
	}
	else if(key == 'x')
	{
		//turnEyeRight = -1;
		//turnEyeAngle -= 1;
	}
	else if(key == 'i')
	{
		rx += 5;
		if(rx > 360)
			rx -= 360;
	}
	else if(key == 'j'){
		rx -= 5;
		if(rx < 0)
			rx += 360;
	}
	else if(key == 'o'){
		ry += 5;
		if(ry > 360)
			ry -= 360;
	}
	else if(key == 'k'){
		ry -= 5;
		if(ry < 0)
			ry += 360;
	}else if(key == 'p'){
		rz += 5;
		if(rz > 360)
			rz -= 360;
	}else if(key == 'l'){
		rz -= 5;
		if(rz < 0)
			rz += 360;
	}

	printf("rx = %f\n", rx);
	printf("ry = %f\n", ry);
	printf("rz = %f\n", rz);


	printf("tx = %f\n", tx);
	printf("ty = %f\n", ty);
	printf("tz = %f\n", tz);

	reshape(ww,wh);
	glutPostRedisplay();

}

void mouse_dragged(int x, int y) {
	double thetaY, thetaX;
	if (left_button_down) {
		thetaY = 360.0 *(x-prevMouseX)/ww;    
		thetaX = 360.0 *(prevMouseY - y)/wh;
		prevMouseX = x;
		prevMouseY = y;
		view_rotx += thetaX;
		view_roty += thetaY;
	}
	else if (right_button_down) {
		z_distance = 5.0*(prevMouseY-y)/wh;
	}
  glutPostRedisplay();
}


void mouse(int button, int state, int x, int y) {
  //establish point of reference for dragging mouse in window
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      left_button_down = TRUE;
	  prevMouseX= x;
      prevMouseY = y;
    }

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
      right_button_down = TRUE;
      prevMouseX = x;
      prevMouseY = y;
    }
    else if (state == GLUT_UP) {
      left_button_down = FALSE;
	  right_button_down = FALSE;
	}
}


void init() {

  /*select clearing (background) color*/
  glClearColor(1.0, 1.0, 1.0, 1.0);


  //set up transformation defaults
  //start with no translation or rotation
  tx = ty = tz = rx = ry = rz = 0;

   atX = atZ = 0;
  dollyzoom = 3.0f;
  lenszoom = 45.0;
   rx = 30;
  ty = 0.8;
  tz = 19.2;
  // TRUE: point camear at the center, 
  // False: point at the car
  pointCameraAt = true;
  switchcamera = 0; //
  ///////////////////
  // assighment 2
  ///////////////////
  bmoveForward = true;
  moveStepZ = 0.0005;
  currentX = currentZ = 0;

  rightlampDest.x = rightlampSource.x = -0.02;
  rightlampSource.z = 0.1;
  rightlampDest.z = 0.2;

  rightlampSource = vec4(rightlampSource.x,-0.90,rightlampSource.z,1); 
  rightlampDest   = vec3(rightlampDest.x,-0.99,rightlampDest.z); 

  turnCarAngle = 0;
  turnAngle = 0;
  rollangle = 0;
  turnEyeAngle = 0;
    // caculate movestepX and vector len for moving car
  moveStepX = tan(M_PI/180) * moveStepZ;
  vectorLen = sqrt(moveStepX*moveStepX + moveStepZ*moveStepZ);

  //populate our arrays
  spherevertcount = generateSphere(2, 30);
    generateStage();
	generateCar();
	generateWheelSides();

   // Load shaders and use the resulting shader program
    program1 = InitShader( "vshader-lighting.glsl", "fshader-lighting.glsl" );
	program2 = InitShader( "vshader-phongshading.glsl", "fshader-phongshading.glsl" );
	program3 = InitShader( "vshader-celshading.glsl", "fshader-celshading.glsl" );
    glUseProgram(0 );
		
	setupShader(program2);
	setupStageShader(program2);
	setupCarShader(program2);
	setupWheelShader(program2);

  //Only draw the things in the front layer
	glEnable(GL_DEPTH_TEST);
}

/////////////////////////////////////////
// special keys
/////////////////////////////////////////
void special(int key, int x, int y){

	// restart the game
	if (key == GLUT_KEY_F2)
	{
		init();
		glutIdleFunc(NULL);
	}
	else if(key == GLUT_KEY_UP) // car move forward
	{
		bmoveForward = true;
				
		if ( currentZ >= 1 )
		{
			currentZ = 0.999;
		}
		else if ( currentZ <= -1 )
		{
			currentZ = -0.999;
		}

		if ( currentX >= 1 )
		{
			currentX = 0.999;
		}
		else if ( currentX <= -1 )
		{
			currentX = -0.999;
		}

	}
	else if(key == GLUT_KEY_DOWN) // car moves backward
	{
		bmoveForward = false;
		if ( currentZ >= 1 )
		{
			currentZ = 0.999;
		}
		else if ( currentZ <= -1 )
		{
			currentZ = -0.999;
		}

		if ( currentX >= 1 )
		{
			currentX = 0.999;
		}
		else if ( currentX <= -1 )
		{
			currentX = -0.999;
		}
	}
	else if(key == GLUT_KEY_LEFT) // move wheels to left
	{
		if ( turnAngle >= maxTurnWheel )
		{
			turnAngle = maxTurnWheel;
		}
		else
		{
			turnAngle += 1;
		}
		
	}
	else if(key == GLUT_KEY_RIGHT) // move wheels to right
	{
	
		if ( turnAngle <= -maxTurnWheel )
		{
			turnAngle = -maxTurnWheel;
		}
		else
		{
			turnAngle -= 1;
		}

		
	}
	
	printf("=============================\n");
	printf("moveStepX : %f\n", moveStepX);
	printf("moveStepZ : %f\n", moveStepZ);
	printf("vectorLen : %f\n", vectorLen);
	printf("currentX : %f\n", currentX);
	printf("currentZ : %f\n", currentZ);
	printf("turnCarAngle : %f\n", turnCarAngle);
	printf("turnAngle : %f\n", turnAngle);
 	

	//don't forget to request a new frame since parameters have changed
	glutPostRedisplay();
}
int main(int argc, char **argv)
{
  /*set up window for display*/
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0); 
  glutInitWindowSize(ww, wh);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("UST Noir");  

  glewExperimental = GL_TRUE;

	glewInit();
  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(special);
  glutReshapeFunc(reshape);
  //glutIdleFunc(idle);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_dragged);

  glutMainLoop();
  return 0;
}