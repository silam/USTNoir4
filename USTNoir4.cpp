/*
 UST Noir
 Si Lam
 **/

#include <GL/Angel.h>
#include <math.h>
#include "./matrix_stack.h"
#pragma comment(lib, "glew32.lib")

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

//store window width and height
//store window width and height
int ww=1700, wh=1100;
/////////////////////////
// stack
/////////////////////////
matrix_stack stack;

#define M_PI 3.14159265358979323846

GLuint program;

vec4 lightOn = vec4(0,0,0,1);
vec4 lightOff = vec4(0,0,0,0);
GLuint vPoliceIsOn;

/////////////////////////
// the chase camera
/////////////////////////

vec4 viewportcamlookdirection = vec4(0, 0, 0.07f, 0);
vec4 viewpointcam;

vec4 * chasecamVers;
GLuint chasecamvao[1];
GLuint chasecamvbo[2];
int totalchasecamverts;
vec4 chasecamlookdirection;

GLboolean startcar;


////////////////////////////////
// police light variables
////////////////////////////////
vec4* policeLightVers;
vec3* policeLightNormals;

GLuint * policelightvao;
GLuint * policelightvbo;

//GLuint * policeredvao;
//GLuint * policeredvbo;
//GLuint * policebluevao;
//GLuint * policebluevbo;
GLfloat turnPoliceLampAngle;
GLboolean turnOnPoliceLight;
vec4 policeredlightlampSource;
vec4 policeredlightlampDest;
vec4 policebluelightlampSource;
vec4 policebluelightlampDest;

////////////////////////////////
// simple objects variables
////////////////////////////////
GLuint * simpleObjvao;
GLuint * simpleObjvbo;
vec4* simpleObjVers;
vec3* simpleObjNormals;
GLint totalobjverts;


////////////////////////////////
// driver head variables
////////////////////////////////
GLuint * headvao;
GLuint * headvbo;
vec4* headVers;
vec3* headNormals;
GLint totalheadverts;
GLuint vHeadAmbientDiffuseColor;
GLuint vHeadSpecularColor;
GLuint vHeadSpecularExponent;

////////////////////////////////
// car variables
////////////////////////////////
GLuint * carvao;
GLuint * carvbo;


GLuint * headLightLampsvao;
GLuint * headLightLampsvbo;
//////////////////////////////////////////////////
// // turn the wheel left/right angle
//////////////////////////////////////////////////
GLfloat turnAngle;
GLfloat turnCarAngle = 0;
GLfloat maxTurnWheel = 45.00f;

////////////////////////////////
// stage variables
////////////////////////////////
GLuint * stagevao;
GLuint * stagevbo;



////////////////////////////////
// head lights variables
////////////////////////////////
vec4 rightlampSource;
vec4 rightlampDest;
vec4 leftlampSource;
vec4 leftlampDest;


/////////////////////////
// wheel cylinder
/////////////////////////
vec4 * wheelCylinderVers;
vec3 * vWheelCylinderNormals;
GLuint * cylindervao;
GLuint * cylindervbo;


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
GLfloat currentlenszoom;
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
// eye
/////////////////////////
vec4 * eyeVerts;
vec3 * eyeNormals;
GLuint * eyevao;
GLuint * eyevbo;
GLuint vEyeAmbientDiffuseColor;
GLuint vEyeSpecularColor;
GLuint vEyeSpecularExponent;

/////////////////////////
// wheel side vertices
/////////////////////////
vec4 * wheelSide1Verts;
vec3 * wheelSide1Normals;

vec4 * wheelSide2Verts;
vec3 * wheelSide2Normals;

GLuint * wheelside1vao;
GLuint * wheelside1vbo;

GLuint * wheelside2vao;
GLuint * wheelside2vbo;
////////////////////////
// WHEEEL
/////////////////////////
GLuint vWheelSide1AmbientDiffuseColor;
GLuint vWheelSide1AmbientColor;
GLuint vWheelSide1DiffuseColor; //Ambient and Diffuse can be the same for the material
GLuint vWheelSide1SpecularColor;
GLuint vWheelSide1Shininess;
GLuint vWheelSide1SpecularExponent;

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

//////////////////////////////
// police
/////////////////////////////

GLuint vPoliceLampAmbientDiffuseColor;
GLuint vPoliceLampSpecularColor;
GLuint vPoliceLampSpecularExponent;


//GLuint vPoliceRedAmbientDiffuseColor;
//GLuint vPoliceRedSpecularColor;
//GLuint vPoliceRedSpecularExponent;
//
//GLuint vPoliceBlueAmbientDiffuseColor;
//GLuint vPoliceBlueSpecularColor;
//GLuint vPoliceBlueSpecularExponent;

vec4* policeLampRedVerts;
vec3* policeLampRedNormals;
vec4* policeLampBlueVerts;
vec3* policeLampBlueNormals;



//vec4* policeLampBlueVerts;
//vec3* policeLampBlueNormals;




//////////////////////////////
// Stage
/////////////////////////////

GLuint vStageAmbientDiffuseColor;
GLuint vStageSpecularColor;
GLuint vStageSpecularExponent;

vec4* stageVerts;
vec3* stageNormals;


//////////////////////////////
// car
/////////////////////////////
GLuint vCarAmbientDiffuseColor;
GLuint vCarSpecularColor;
GLuint vCarSpecularExponent;

vec4* carVerts;
vec3* carNormals;

//////////////////////////////
vec4* lampVerts;
vec3* lampNormals;
/////////////////////////////////
//////////////////////////////
// simple objects
/////////////////////////////
GLuint vSimpleObjAmbientDiffuseColor;
GLuint vSimpleObjSpecularColor;
GLuint vSimpleObjSpecularExponent;

//////////////////////////////
// moon light
//////////////////////////////
GLuint moonlight_position;
GLuint moondiffuse_color;
GLuint moonspecular_color;
GLuint moonambient_light;


//////////////////////////////
// head light
//////////////////////////////
GLuint headrightlight_position;
GLuint headrightdiffuse_color;
GLuint headrightambient_light;
GLuint headrightspot_cutoff;
GLuint headrightspot_exponent;
GLuint headrightspot_direction;
GLuint headrightspecular_color;

GLuint headrightOn;


GLuint headleftlight_position;
GLuint headleftdiffuse_color;
GLuint headleftspecular_color;
GLuint headleftambient_light;
GLuint headleftspot_cutoff;
GLuint headleftspot_exponent;
GLuint headleftspot_direction;
GLuint headleftOn;

//////////////////////////////
// police light
//////////////////////////////
GLuint policeredlight_position;
GLuint policereddiffuse_color;
GLuint policeredspecular_color;
GLuint policeredambient_light;
GLuint policeredspot_cutoff;
GLuint policeredspot_exponent;
GLuint policeredspot_direction;
//GLuint policeRedOn;

GLuint policebluelight_position;
GLuint policebluediffuse_color;
GLuint policebluespecular_color;
GLuint policeblueambient_light;
GLuint policebluespot_cutoff;
GLuint policebluespot_exponent;
GLuint policebluespot_direction;
//GLuint policeBlueOn;

//////////////////////////////
// lightsouce structure
//////////////////////////////
//struct lightSource
//{
//	vec4 ambient;
//	vec4 position;
//	vec4 diffuse;
//	vec4 specular;
//	float constantAttenuation, linearAttenuation, quadraticAttenuation;
//	float spotCutoff, spotCosCutoff, spotExponent;
//	vec4 spotDirection;
//};

//lightSource directionalLight, spotLightHeadLamp;
//const int numberofLightSources = 5;
//lightSource lights[numberofLightSources];

//////////////////////////////
// material structure
//////////////////////////////
//struct material
//{
//	vec4 ambient;
//	vec4 diffuse;
//	vec4 specular;
//	float shininess;
//};

/////////////////////////////////////////
//reshape
/////////////////////////////////////////
void reshape(int width, int height){
	ww= width;
	wh = height;
	//field of view angle, aspect ratio, closest distance from camera to object, largest distanec from camera to object
	
	p = Perspective(lenszoom, (float)width/(float)height, 1.0, 100.0);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p);
	glViewport( 0, 0, width, height );
		
}
/////////////////////////////////////////
//generateEyes
/////////////////////////////////////////
void generateEyes()
{
		
	int point = 0;
	double angleincrement = 15;

	eyeVerts = new vec4[75];
	eyeNormals = new vec3[75];


	for ( double angle = 0; angle <= 360; angle += angleincrement)
	{
		eyeNormals[point] = vec3(0,0,1);
		eyeVerts[point++] = vec4(0.0f,	0.0f, 0.0f, 1.0); //point 1
		
		eyeNormals[point] = vec3(0,0,1);
		eyeVerts[point++] = vec4(cos(angle*M_PI/180), 0.0f, -sin(angle*M_PI/180), 1.0); //point 2
		
		eyeNormals[point] = vec3(0,0,1);
		eyeVerts[point++] = vec4(cos((angle+angleincrement)*M_PI/180), 0.0f, -sin((angle+angleincrement)*M_PI/180), 1.0); //point 3
		
		
	}
}
/////////////////////////////////////////
// generateChaseCamera
/////////////////////////////////////////
void generateSimpleObject()
{
	
	int subdiv = 10;
	int radius = 1;

	float step = (360.0/subdiv)*(M_PI/180.0);

	totalobjverts = ceil(subdiv/2.0)*subdiv * 6;

	if(simpleObjVers){
		delete[] simpleObjVers;
	}

	simpleObjVers = new vec4[totalobjverts];

	if(simpleObjNormals){
		delete[] simpleObjNormals;
	}
	simpleObjNormals = new vec3[totalobjverts];

	int k = 0;
	for(float i = -M_PI/2; i<=M_PI/2; i+=step){
		for(float j = -M_PI; j<=M_PI; j+=step){
			//triangle 1
			simpleObjNormals[k]= vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
			simpleObjVers[k]=   vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
			
			k++;
	
			simpleObjNormals[k]= vec3(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step));
			simpleObjVers[k]=   vec4(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step), 1.0);
			
			k++;
			simpleObjNormals[k]= vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
			simpleObjVers[k]=   vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
			
			k++;

			//triangle 2
			simpleObjNormals[k]= vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
			simpleObjVers[k]=   vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
			
			k++;
			simpleObjNormals[k]= vec3(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i));
			simpleObjVers[k]=   vec4(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i), 1.0);
			
			k++;
			simpleObjNormals[k]= vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
			simpleObjVers[k]=   vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
			
			k++;
		}
	}
}

/////////////////////////////////////////
// generateChaseCamera
/////////////////////////////////////////
void generatePoliceLights()
{
	
	int subdiv = 10;
	int radius = 1;

	float step = (360.0/subdiv)*(M_PI/180.0);

	totalobjverts = ceil(subdiv/2.0)*subdiv * 6;

	if(policeLightVers){
		delete[] policeLightVers;
	}

	policeLightVers = new vec4[totalobjverts];

	if(policeLightNormals){
		delete[] policeLightNormals;
	}
	policeLightNormals = new vec3[totalobjverts];

	int k = 0;
	for(float i = -M_PI/2; i<=M_PI/2; i+=step){
		for(float j = -M_PI; j<=M_PI; j+=step){
			//triangle 1
			policeLightNormals[k]= -vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
			policeLightVers[k]=   vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
			
			k++;
	
			policeLightNormals[k]= -vec3(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step));
			policeLightVers[k]=   vec4(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step), 1.0);
			
			k++;
			policeLightNormals[k]= -vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
			policeLightVers[k]=   vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
			
			k++;

			//triangle 2
			policeLightNormals[k]= -vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
			policeLightVers[k]=   vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
			
			k++;
			policeLightNormals[k]= -vec3(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i));
			policeLightVers[k]=   vec4(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i), 1.0);
			
			k++;
			policeLightNormals[k]= -vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
			policeLightVers[k]=   vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
			
			k++;
		}
	}
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
	stageNormals[0] = vec3(0,1,0);
	stageNormals[1] = vec3(0,1,0);
	stageNormals[2] = vec3(0,1,0);


	vec4 d = stageVerts[5] = vec4(-1.0f, -1.0f, 1.0f, 1.0);
	vec4 e = stageVerts[4] = vec4(-1.0f, -1.0f, -1.0f, 1.0);
	vec4 f = stageVerts[3] = vec4(1.0f, -1.0f, -1.0f, 1.0);

	//normals = normalize();//cross(d-e,f-e));
	stageNormals[3] = vec3(0,1,0);
	stageNormals[4] = vec3(0,1,0);
	stageNormals[5] = vec3(0,1,0);

}

/////////////////////////////////////////
// generateHead
/////////////////////////////////////////
void generateHead()
{
	

	int subdiv = 10;
	int radius = 1;

	float step = (360.0/subdiv)*(M_PI/180.0);

	totalheadverts = ceil(subdiv/2.0)*subdiv * 6;

	if(headNormals){
		delete[] headNormals;
	}
	headNormals = new vec3[totalheadverts];
	if(headVers){
		delete[] headVers;
	}
	headVers = new vec4[totalheadverts];

	int k = 0;
	for(float i = -M_PI/2; i<=M_PI/2; i+=step){
		for(float j = -M_PI; j<=M_PI; j+=step){
			//triangle 1
			headNormals[k]= vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
			headVers[k]=   vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
			k++;
	
			headNormals[k]= vec3(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step));
			headVers[k]=   vec4(radius*sin(j)*cos(i+step), radius*cos(j)*cos(i+step), radius*sin(i+step), 1.0);
			k++;
			
			headNormals[k]= vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
			headVers[k]=   vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
			k++;

			//triangle 2
			headNormals[k]= vec3(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step));
			headVers[k]=   vec4(radius*sin((j+step))*cos((i+step)), radius*cos(j+step)*cos(i+step), radius*sin(i+step), 1.0);
			k++;

			headNormals[k]= vec3(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i));
			headVers[k]=   vec4(radius*sin(j+step)*cos(i), radius*cos(j+step)*cos(i), radius*sin(i), 1.0);
			k++;

			headNormals[k]= vec3(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i));
			headVers[k]=   vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
			k++;
		}
	}
}
/////////////////////////////////////////
// generateCar
/////////////////////////////////////////

void generateCar(){


	if ( carVerts )
		delete [] carVerts;

	carVerts = new vec4[36];

	if ( carNormals )
		delete [] carNormals;

	carNormals = new vec3[36];


	int index = 0;
	///////////////////
	// front 
	//////////////////
	carVerts[0] = vec4( 0.05f, -0.05f, 0.05f, 1.0);
	carVerts[1] = vec4( 0.05f,  0.05f, 0.05f, 1.0);
	carVerts[2] = vec4(-0.05f,  0.05f, 0.05f, 1.0);

	
	carNormals[index++] = vec3(0,0,1); //normal; 
	carNormals[index++] = vec3(0,0,1); //normal; 
	carNormals[index++] = vec3(0,0,1); //normal; 


	carVerts[3] = vec4(-0.05f,  0.05f, 0.05f, 1.0);
	carVerts[4] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	carVerts[5] = vec4( 0.05f, -0.05f, 0.05f, 1.0);
	
	
	carNormals[index++] = vec3(0,0,1); //normal; 
	carNormals[index++] = vec3(0,0,1); //normal; 
	carNormals[index++] = vec3(0,0,1); //normal; 


	///////////////////
	// back 
	//////////////////
	carVerts[6] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	carVerts[7] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	carVerts[8] = vec4(0.05f, 0.05f, -0.05f, 1.0);

		
	carNormals[index++] = vec3(0,0,-1); //normal; 
	carNormals[index++] = vec3(0,0,-1);; 
	carNormals[index++] = vec3(0,0,-1);; 

	carVerts[9] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	carVerts[10] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	carVerts[11] = vec4(-0.05f, -0.05f, -0.05f, 1.0);

	
	carNormals[index++] = vec3(0,0,-1); 
	carNormals[index++] = vec3(0,0,-1); 
	carNormals[index++] = vec3(0,0,-1);

		///////////////////
	// right hand of me
	//////////////////
	carVerts[12] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	carVerts[13] = vec4(0.05f, -0.05f, 0.05f, 1.0);
	carVerts[14] = vec4(0.05f, -0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	
	carNormals[index++] = vec3(1,0,0); //-normal; 
	carNormals[index++] = vec3(1,0,0);//-normal; 
	carNormals[index++] = vec3(1,0,0);//-normal; 

	carVerts[15] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	carVerts[16] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	carVerts[17] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	

	// calculate normal vectore for car
	
	carNormals[index++] = vec3(1,0,0);//-normal; 
	carNormals[index++] = vec3(1,0,0);//-normal; 
	carNormals[index++] = vec3(1,0,0);//-normal; 

	///////////////////
	// left hand of me (left car)
	//////////////////
	
	carVerts[18] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	carVerts[19] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	carVerts[20] = vec4(-0.05f, -0.05f, 0.05f, 1.0);

	// calculate normal vectore for car
	
	carNormals[index++] = vec3(-1,0,0);//-normal; 
	carNormals[index++] = vec3(-1,0,0);//-normal; 
	carNormals[index++] = vec3(-1,0,0);//-normal; 


	carVerts[21] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	carVerts[22] = vec4(-0.05f, 0.05f, 0.05f, 1.0);
	carVerts[23] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	
	// calculate normal vectore for car
	
	carNormals[index++] = vec3(-1,0,0);//-normal; 
	carNormals[index++] = vec3(-1,0,0);//-normal; 
	carNormals[index++] = vec3(-1,0,0);//-normal; 

		
	///////////////////
	// top car
	//////////////////
	
	carVerts[24] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	carVerts[25] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	carVerts[26] = vec4(-0.05f, 0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	
	carNormals[index++] = vec3(0,1,0); //normal; 
	carNormals[index++] = vec3(0,1,0); //normal; 
	carNormals[index++] = vec3(0,1,0); //normal; 

	carVerts[27] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	carVerts[28] = vec4(-0.05f, 0.05f, 0.05f, 1.0);
	carVerts[29] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	
	// calculate normal vectore for car
	
	carNormals[index++] = vec3(0,1,0); //normal; 
	carNormals[index++] = vec3(0,1,0); //normal; 
	carNormals[index++] = vec3(0,1,0); //normal;

	///////////////////
	// bottom car
	//////////////////
	carVerts[30] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	carVerts[31] = vec4(0.05f, -0.05f, 0.05f, 1.0);
	carVerts[32] = vec4(-0.05f, -0.05f, 0.05f, 1.0);

	// calculate normal vectore for car
	
	carNormals[index++] = vec3(0,-1,0); //normal; 
	carNormals[index++] = vec3(0,-1,0);//normal; 
	carNormals[index++] = vec3(0,-1,0);//normal;

	carVerts[33] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	carVerts[34] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	carVerts[35] = vec4(0.05f, -0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	
	carNormals[index++] = vec3(0,-1,0);//normal; 
	carNormals[index++] = vec3(0,-1,0);//normal; 
	carNormals[index++] = vec3(0,-1,0);//normal;
	
}


/////////////////////////////////////////
// generateCar
/////////////////////////////////////////

void generateHeadLightLamps(){

	if ( lampVerts )
		delete [] lampVerts;

	lampVerts = new vec4[36];

	if ( lampNormals )
		delete [] lampNormals;

	lampNormals = new vec3[36];


	int index = 0;
	///////////////////
	// front 
	//////////////////
	lampVerts[0] = vec4( 0.05f, -0.05f, 0.05f, 1.0);
	lampVerts[1] = vec4( 0.05f,  0.05f, 0.05f, 1.0);
	lampVerts[2] = vec4(-0.05f,  0.05f, 0.05f, 1.0);

	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(0,0,-1); //normal; 
	lampNormals[index++] = vec3(0,0,-1);//normal; 
	lampNormals[index++] = vec3(0,0,-1);//normal; 


	lampVerts[3] = vec4(-0.05f,  0.05f, 0.05f, 1.0);
	lampVerts[4] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	lampVerts[5] = vec4( 0.05f, -0.05f, 0.05f, 1.0);
	
	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(0,0,-1);//normal; 
	lampNormals[index++] = vec3(0,0,-1);//normal; 
	lampNormals[index++] = vec3(0,0,-1);//normal; 


	///////////////////
	// back 
	//////////////////
	lampVerts[6] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	lampVerts[7] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	lampVerts[8] = vec4(0.05f, 0.05f, -0.05f, 1.0);


	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(0,0,1); 
	lampNormals[index++] = vec3(0,0,1); 
	lampNormals[index++] = vec3(0,0,1); 

	lampVerts[9] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	lampVerts[10] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	lampVerts[11] = vec4(-0.05f, -0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(0,0,1); 
	lampNormals[index++] = vec3(0,0,1); 
	lampNormals[index++] = vec3(0,0,1); 


	lampVerts[12] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	lampVerts[13] = vec4(0.05f, -0.05f, 0.05f, 1.0);
	lampVerts[14] = vec4(0.05f, -0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(-1,0,0); 
	lampNormals[index++] = vec3(-1,0,0); 
	lampNormals[index++] = vec3(-1,0,0);

	lampVerts[15] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	lampVerts[16] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	lampVerts[17] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	

	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(-1,0,0);
	lampNormals[index++] = vec3(-1,0,0);
	lampNormals[index++] = vec3(-1,0,0);


	
	lampVerts[18] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	lampVerts[19] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	lampVerts[20] = vec4(-0.05f, -0.05f, 0.05f, 1.0);

	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(1,0,0); 
	lampNormals[index++] = vec3(1,0,0); 
	lampNormals[index++] = vec3(1,0,0); 


	lampVerts[21] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	lampVerts[22] = vec4(-0.05f, 0.05f, 0.05f, 1.0);
	lampVerts[23] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	
	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(1,0,0); 
	lampNormals[index++] = vec3(1,0,0); 
	lampNormals[index++] = vec3(1,0,0); 

	// top
		
	lampVerts[24] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	lampVerts[25] = vec4(0.05f, 0.05f, -0.05f, 1.0);
	lampVerts[26] = vec4(-0.05f, 0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(0,1,0); 
	lampNormals[index++] = vec3(0,1,0); 
	lampNormals[index++] = vec3(0,1,0); 

	lampVerts[27] = vec4(-0.05f, 0.05f, -0.05f, 1.0);
	lampVerts[28] = vec4(-0.05f, 0.05f, 0.05f, 1.0);
	lampVerts[29] = vec4(0.05f, 0.05f, 0.05f, 1.0);
	
	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(0,1,0); 
	lampNormals[index++] = vec3(0,1,0); 
	lampNormals[index++] = vec3(0,1,0);


	// bottom
	lampVerts[30] = vec4(0.05f, -0.05f, -0.05f, 1.0);
	lampVerts[31] = vec4(0.05f, -0.05f, 0.05f, 1.0);
	lampVerts[32] = vec4(-0.05f, -0.05f, 0.05f, 1.0);

	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(0,-1,0); 
	lampNormals[index++] = vec3(0,-1,0); 
	lampNormals[index++] = vec3(0,-1,0);

	lampVerts[33] = vec4(-0.05f, -0.05f, 0.05f, 1.0);
	lampVerts[34] = vec4(-0.05f, -0.05f, -0.05f, 1.0);
	lampVerts[35] = vec4(0.05f, -0.05f, -0.05f, 1.0);

	// calculate normal vectore for car
	
	lampNormals[index++] = vec3(0,-1,0); 
	lampNormals[index++] = vec3(0,-1,0); 
	lampNormals[index++] = vec3(0,-1,0);
	
}



/////////////////////////////////////////
// generateWheelSides
/////////////////////////////////////////
void generateWheelSides()
{
	if ( wheelSide1Verts )
		delete [] wheelSide1Verts;

	wheelSide1Verts  = new vec4[75];

	if ( wheelSide2Verts )
		delete [] wheelSide2Verts;

	if ( wheelSide1Normals )
		delete [] wheelSide1Normals;

	if ( wheelSide2Normals )
		delete [] wheelSide2Normals;

	wheelSide1Normals  = new vec3[75];

	wheelSide2Verts  = new vec4[75];
	wheelSide2Normals  = new vec3[75];


	if ( wheelCylinderVers )
		delete [] wheelCylinderVers;

	if ( vWheelCylinderNormals )
		delete [] vWheelCylinderNormals;

	wheelCylinderVers  = new vec4[414];
	vWheelCylinderNormals  = new vec3[414];

	

	int side = 1; // the Left side of the wheel
	
	int point = 0;
	double angleincrement = 15;
	for ( double angle = 0; angle <= 360; angle += angleincrement)
	{
		point4 a = wheelSide1Verts[point++] = vec4(0.0f,side*(-1.0f), 0.0f, 1.0); //point 1
		
		point4 b = wheelSide1Verts[point++] = vec4(cos(angle*M_PI/180), side*(-1.0f), -sin(angle*M_PI/180), 1.0); //point 2
		
		point4 c = wheelSide1Verts[point++] = vec4(cos((angle+angleincrement)*M_PI/180), side*(-1.0f), -sin((angle+angleincrement)*M_PI/180), 1.0); //point 3
		
		

		wheelSide1Normals[point-3] = vec3(0.0, -1.0, 0.0);//vec3(0.0, 0.0, 1.0); // normal;
		wheelSide1Normals[point-2] = vec3(0.0, -1.0, 0.0);//vec3(0.0, 0.0, 1.0);;
		wheelSide1Normals[point-1] = vec3(0.0, -1.0, 0.0);//vec3(0.0, 0.0, 1.0);;

	}

	side = -1; // the Right side of the wheel
	point = 0;
	angleincrement = 15;
	for ( double angle = 0; angle <= 360; angle += angleincrement)
	{
		point4 a = wheelSide2Verts[point++] = vec4(0.0f,		side*(-1.0f), 0.0f, 1.0); 
		
		point4 b = wheelSide2Verts[point++] = vec4(cos(angle*M_PI/180), side*(-1.0f), -sin(angle*M_PI/180), 1.0); 
		
		point4 c = wheelSide2Verts[point++] = vec4(cos((angle+angleincrement)*M_PI/180), side*(-1.0f), -sin((angle+angleincrement)*M_PI/180), 1.0); //point 3
		

		wheelSide2Normals[point-3] = vec3(0.0, 1.0, 0.0);//vec3(0.0, 0.0, -1.0);;
		wheelSide2Normals[point-2] = vec3(0.0, 1.0, 0.0);//vec3(0.0, 0.0, -1.0);;
		wheelSide2Normals[point-1] = vec3(0.0, 1.0, 0.0);//vec3(0.0, 0.0, -1.0);;
	}


	//
	// cylinder of the wheel
	int p = 0;
	for ( int i = 0; i < 410 ; i += 6)
	{
	
		point4 a = wheelCylinderVers[i] =   wheelSide1Verts[(p+1)%3==0?(p+1+1+1):(p+1)];
		point4 b = wheelCylinderVers[i+1] = wheelSide1Verts[(p+2)%3==0?(p+2+1+1):(p+2)];
		point4 c = wheelCylinderVers[i+2] = wheelSide2Verts[(p+1)%3==0?(p+1+1+1):(p+1)];


		point4 va = a - point4(0,-1,0,1);
		vWheelCylinderNormals[i]   =  vec3(va.x, va.y, va.z); //normal;

		point4 vb = b - point4(0,-1,0,1);
		vWheelCylinderNormals[i+1] = vec3(vb.x, vb.y, vb.z); //normal;

		point4 vc = c - point4(0,1,0,1);
		vWheelCylinderNormals[i+2] = vec3(vc.x, vc.y, vc.z); // normal;

		a = wheelCylinderVers[i+3] = wheelSide1Verts[(p+2)%3==0?(p+2+1+1):(p+2)];
		b = wheelCylinderVers[i+4] = wheelSide2Verts[(p+2)%3==0?(p+2+1+1):(p+2)];
		c = wheelCylinderVers[i+5] = wheelSide2Verts[(p+1)%3==0?(p+1+1+1):(p+1)];
		
		va = a - point4(0,-1,0,1);
		vWheelCylinderNormals[i+3] =  vec3(va.x, va.y, va.z); //normal;;

		vb = b - point4(0,1,0,1);
		vWheelCylinderNormals[i+4] = vec3(vb.x, vb.y, vb.z); //normal;;;

		vc = c - point4(0,1,0,1);
		vWheelCylinderNormals[i+5] = vec3(vc.x, vc.y, vc.z); // normal;;


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


/////////////////////////////////////////
//generatePoliceLamp
/////////////////////////////////////////
//void generatePoliceLamp()
//{
//		
//	if ( carVerts )
//		delete [] carVerts;
//
//	policeLampRedVerts = new vec4[144];
//	policeLampRedNormals = new vec3[144];
//
//	policeLampBlueVerts = new vec4[144];
//	policeLampBlueNormals = new vec3[144];
//
//	int point = 0;
//	double angleincrement = 15;
//	for ( double angle = 0; angle <= 360; angle += angleincrement)
//	{
//		
//		point4 a = policeLampRedVerts[point++] = vec4(0.0f,	0.0f, 0.0f, 1.0); //point 1
//		
//		point4 b = policeLampRedVerts[point++] = vec4(cos(angle*M_PI/180), 0.0f, -sin(angle*M_PI/180), 1.0); //point 2
//				
//		point4 c = policeLampRedVerts[point++] = vec4(cos((angle+angleincrement)*M_PI/180), 0.0f, -sin((angle+angleincrement)*M_PI/180), 1.0); //point 3
//		
//		//vec3 normal = normalize(cross(c-b, a -b));
//
//		policeLampRedNormals[point-3] = vec3(0.0, 0.0, -1.0);
//		policeLampRedNormals[point-2] = vec3(0.0, 0.0, -1.0);
//		policeLampRedNormals[point-1] = vec3(0.0, 0.0, -1.0);
//	}
//
//	
//	 point = 0;
//	 angleincrement = 15;
//
//	for ( double angle = 0; angle <= 360; angle += angleincrement)
//	{
//	
//		point4 a = policeLampBlueVerts[point++] = vec4(0.0f,	0.0f, 0.0f, 1.0); //point 1
//		point4 b = policeLampBlueVerts[point++] = vec4(cos(angle*M_PI/180), 0.0f, -sin(angle*M_PI/180), 1.0); //point 2
//		point4 c = policeLampBlueVerts[point++] = vec4(cos((angle+angleincrement)*M_PI/180), 0.0f, -sin((angle+angleincrement)*M_PI/180), 1.0); //point 3
//		
//		//vec3 normal = normalize(cross(c-b, a -b));
//
//		policeLampBlueNormals[point-3] = vec3(0.0, 0.0, 1.0);
//		policeLampBlueNormals[point-2] = vec3(0.0, 0.0, 1.0);
//		policeLampBlueNormals[point-1] = vec3(0.0, 0.0, 1.0);
//	}
//
//	
//
//}

//////////////////////////////////////////
// setupPoliceLight
//////////////////////////////////////////
void setupPoliceLight()
{
	// police red light
	glUniform4fv(policeredlight_position, 1, mv*Translate(currentX, 0, currentZ)*RotateY(turnCarAngle)*policeredlightlampSource); 
	glUniform4fv(policeredspot_direction, 1, mv*Translate(currentX, 0, currentZ)*RotateY(turnCarAngle)*RotateY(turnPoliceLampAngle)*policeredlightlampDest);
		
	glUniform4fv(policereddiffuse_color,  1, vec4(1.0f, 0.0f,0.0f,1));
	glUniform4fv(policeredspecular_color, 1, vec4(1.0f,1.0f,1.0f,1));
	glUniform4fv(policeredambient_light,  1, vec4(0.01, 0.01, 0.01, 1));

	glUniform1f(policeredspot_cutoff, 45);
	glUniform1f(policeredspot_exponent, 120);
	

	// blue light

	glUniform4fv(policebluelight_position, 1, mv*Translate(currentX, 0, currentZ)*RotateY(turnCarAngle)*policebluelightlampSource); 
	glUniform4fv(policebluespot_direction, 1, mv*Translate(currentX, 0, currentZ)*RotateY(turnCarAngle)*RotateY(turnPoliceLampAngle)*policebluelightlampDest);
		
	glUniform4fv(policebluediffuse_color,  1, vec4(0.0f,0.0f,1.0f,1));
	glUniform4fv(policebluespecular_color, 1, vec4(0.0f,0.0f,1.0f,1));
	glUniform4fv(policeblueambient_light,  1, vec4(.01, .01, .01, 1));

	glUniform1f(policebluespot_cutoff, 45);
	glUniform1f(policebluespot_exponent, 120);
	
	
}
//////////////////////////////////////////
// setup head lights
//////////////////////////////////////////
void setupHeadLight()
{
	
	// right lamp
	glUniform4fv(headrightlight_position, 1, mv*Translate(currentX, 0, currentZ)* RotateY(turnCarAngle)*rightlampSource);
	glUniform4fv(headrightspot_direction, 1, mv*Translate(currentX, 0, currentZ)* RotateY(turnCarAngle)*rightlampDest);

	glUniform4fv(headrightdiffuse_color, 1, vec4(1.0,1.0f,1.0f,1));
	glUniform4fv(headrightspecular_color, 1, vec4(1.0,1.0f,1.0f,1));
	glUniform4fv(headrightambient_light, 1, vec4(.01, .01, .01, 1));
	glUniform1f(headrightspot_cutoff, 85);
	glUniform1f(headrightspot_exponent, 120);
	glUniform1i(headrightOn, 1);

	// left lamp
	glUniform4fv(headleftlight_position, 1, mv*Translate(currentX, 0, currentZ)* RotateY(turnCarAngle)*leftlampSource);
	glUniform4fv(headleftspot_direction, 1, mv*Translate(currentX, 0, currentZ)* RotateY(turnCarAngle)*leftlampDest);


	glUniform4fv(headleftdiffuse_color, 1, vec4(1.0f,1.0f,1.0f,1));
	glUniform4fv(headleftspecular_color, 1, vec4(1.0,1.0f,1.0f,1));
	glUniform4fv(headleftambient_light, 1, vec4(.01, .01, .01, 1));
	glUniform1f(headleftspot_cutoff, 85);
	glUniform1f(headleftspot_exponent, 120);
	glUniform1i(headleftOn, 1);


}
//////////////////////////////////////////
// setup moon light (directional light)
//////////////////////////////////////////
void setupMoonLight()
{
	glUniform4fv(moonlight_position, 1, mv*vec4(100, 100, 100, 0)); //1));
	glUniform4fv(moondiffuse_color, 1, vec4(0.4,.4f,.4f,1));
	glUniform4fv(moonspecular_color, 1, vec4(0.4,.4f,.4f,1));
	glUniform4fv(moonambient_light, 1, vec4(.01, .01, .01, 1));
		
}
/////////////////////////////////////////
// displayStage
/////////////////////////////////////////
void displayStage(void)
{
	
	glVertexAttrib4fv(vStageAmbientDiffuseColor, vec4(.4, 0.4, 0.4, 1));
	glVertexAttrib4fv(vStageSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
	glVertexAttrib1f(vStageSpecularExponent, 10.0);

	glBindVertexArray( stagevao[0] );
	glDrawArrays( GL_TRIANGLES, 0, 6 );    // draw the sphere 
   
}
/////////////////////////////////////////
// displayPoliceLights
/////////////////////////////////////////
void displayPoliceLights()
{
	if ( turnOnPoliceLight == true )
		glVertexAttrib4fv(vPoliceIsOn, lightOn);
	else
		glVertexAttrib4fv(vPoliceIsOn, lightOff);

	stack.push(mv);
		
	
	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);

	mv = mv * Translate(0.0, -0.83, -0.08); // 0.05
	mv = mv * Scale(0.02,0.05,0.02);
	
	glVertexAttrib4fv(vPoliceLampAmbientDiffuseColor, vec4(0.3, 0.1, 0.3, 1));
	glVertexAttrib4fv(vPoliceLampSpecularColor, vec4(1.f,1.f,1.f,1.0f));
	glVertexAttrib1f(vPoliceLampSpecularExponent, 10.0);

	DrawTriagle(policelightvao, totalobjverts);

	mv = stack.pop();

}

/////////////////////////////////////////
// displayHeadLights
/////////////////////////////////////////
//void displayHeadLights()
//{
//	
//	stack.push(mv);
//	
//	mv = mv * Translate(currentX, 0, currentZ);
//	mv = mv * RotateY(turnCarAngle);
//
//	mv = mv * Translate(0.0, -0.95, 0.10); // 0.05
//	mv = mv * Scale(0.05,0.08,0.04);
//	
//	glVertexAttrib4fv(vPoliceLampAmbientDiffuseColor, vec4(1, 1.0, 1.0, 1));
//	glVertexAttrib4fv(vPoliceLampSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
//	glVertexAttrib1f(vPoliceLampSpecularExponent, 10.0);
//
//	DrawTriagle(policeredvao, totalsimpleobjverts);
//
//	mv = stack.pop();
//
//}
/////////////////////////////////////////
// displaySimpleObj
/////////////////////////////////////////
void displaySimpleObj()
{
	
	stack.push(mv);
		
	mv = mv * Translate(0.8, -0.9, 0.8); // 0.05
	mv = mv * Scale(0.2,0.9,0.2);
	
	glVertexAttrib4fv(vSimpleObjAmbientDiffuseColor, vec4(0, 1.0, 1.0, 1));
	glVertexAttrib4fv(vSimpleObjSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
	glVertexAttrib1f(vSimpleObjSpecularExponent, 10.0);

	DrawTriagle(simpleObjvao, totalobjverts);

	mv = stack.pop();

	//////////

	stack.push(mv);
		
	mv = mv * Translate(-0.8, -0.9, 0.8); // 0.05
	mv = mv * Scale(0.1,0.5,0.2);
	
	glVertexAttrib4fv(vSimpleObjAmbientDiffuseColor, vec4(1, 0.0, .5, 1));
	glVertexAttrib4fv(vSimpleObjSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
	glVertexAttrib1f(vSimpleObjSpecularExponent, 10.0);

	DrawTriagle(simpleObjvao, totalobjverts);

	mv = stack.pop();

	//////////

	stack.push(mv);
		
	mv = mv * Translate(-0.8, -0.9, -0.8); // 0.05
	mv = mv * Scale(0.2,0.5,0.1);
	
	glVertexAttrib4fv(vSimpleObjAmbientDiffuseColor, vec4(0.0, 1.0, .5, 1));
	glVertexAttrib4fv(vSimpleObjSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
	glVertexAttrib1f(vSimpleObjSpecularExponent, 10.0);

	DrawTriagle(simpleObjvao, totalobjverts);

	mv = stack.pop();

	//////////

	stack.push(mv);
		
	mv = mv * Translate(0.8, -0.9, -0.8); // 0.05
	mv = mv * Scale(0.1,0.5,0.1);
	
	glVertexAttrib4fv(vSimpleObjAmbientDiffuseColor, vec4(1.0, 0.0, 1.0, 1));
	glVertexAttrib4fv(vSimpleObjSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
	glVertexAttrib1f(vSimpleObjSpecularExponent, 10.0);

	DrawTriagle(simpleObjvao, totalobjverts);

	mv = stack.pop();
		

}
/////////////////////////////////////////
// displayEye
/////////////////////////////////////////
void displayEye()
{
	
	// left eye
	stack.push(mv);
	
	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
	
		mv = mv * Translate(0.0, -0.88, 0.0);
	mv = mv * RotateY(turnEyeAngle);
	mv = mv * Translate(0.02, 0.00, 0.05);
	mv = mv * RotateX(90);
	mv = mv * Scale(0.010f,0.010f,0.010f);

	glVertexAttrib4fv(vEyeAmbientDiffuseColor, vec4(0, 0, 0.0, 1));
	glVertexAttrib4fv(vEyeSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
	glVertexAttrib1f(vEyeSpecularExponent, 10.0);

	DrawTriagle(eyevao, 144);

	mv = stack.pop();

	// right eye
	stack.push(mv);
	
	
	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
	
	mv = mv * Translate(0.0, -0.88, 0.0);
	mv = mv * RotateY(turnEyeAngle);
	mv = mv * Translate(-0.02, 0.00, 0.05);
	mv = mv * RotateX(90);
	mv = mv * Scale(0.010f,0.010f,0.010f);

	glVertexAttrib4fv(vEyeAmbientDiffuseColor, vec4(0, 0, 0.0, 1));
	glVertexAttrib4fv(vEyeSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
	glVertexAttrib1f(vEyeSpecularExponent, 10.0);
	
	DrawTriagle(eyevao, 144);

	mv = stack.pop();
}
/////////////////////////////////////////
// displayHead
/////////////////////////////////////////
void displayHead()
{
	
	stack.push(mv);

	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);

	mv = mv * Translate(0, -0.90, -0.01); // 0.05
	// mv = mv * RotateY(turnEyeAngle); // rotate head even head is just a white sphere
	mv = mv * Scale(0.03,0.03,0.03);
	
	glVertexAttrib4fv(vHeadAmbientDiffuseColor, vec4(1, 1, 1.0, 1));
	glVertexAttrib4fv(vHeadSpecularColor, vec4(0.4f,0.4f,0.4f,1.0f));
	glVertexAttrib1f(vHeadSpecularExponent, 10.0);

	DrawTriagle(headvao, totalheadverts);

	mv = stack.pop();


}
/////////////////////////////////////////
// displayHeadLightLamps
/////////////////////////////////////////
void displayHeadLightLamps(void)
{
	
	stack.push(mv);
	
	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
	 
	mv = mv * Translate(0, -0.93, 0.085); 
	mv = mv * Scale(0.5,0.25,0.2 );
	
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glVertexAttrib4fv(vCarAmbientDiffuseColor, vec4(1.0f, 1.0f, 0.0f, 1));
	glVertexAttrib4fv(vCarSpecularColor, vec4(0.4f, 0.4f,0.4f,1.0f));
	glVertexAttrib1f(vCarSpecularExponent, 1.0);


	DrawTriagle(headLightLampsvao, 36);

	mv = stack.pop();
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
	
	mv = mv * Scale(0.5,0.25,1.5 );
	
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glVertexAttrib4fv(vCarAmbientDiffuseColor, vec4(1.0f, 1.0f, 0.0f, 1));
	glVertexAttrib4fv(vCarSpecularColor, vec4(0.4f, 0.4f,0.4f,1.0f));
	glVertexAttrib1f(vCarSpecularExponent, 1.0);


	DrawTriagle(carvao, 36);

	mv = stack.pop();
	
	// upper stage

	stack.push(mv);
	
	mv = mv * Translate(currentX, 0, currentZ);
	mv = mv * RotateY(turnCarAngle);
	 
	mv = mv * Translate(0, -0.90, -0.08); //-0.0090); 
	
	mv = mv * Scale(0.5,1,.5 );
	
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glVertexAttrib4fv(vCarAmbientDiffuseColor, vec4(1, 1, 0.0f, 1));
	glVertexAttrib4fv(vCarSpecularColor, vec4(0.4f, 0.4f,0.4f,1.0f));
	glVertexAttrib1f(vCarSpecularExponent, 1.0);


	DrawTriagle(carvao, 36);

	mv = stack.pop();
   
}
/////////////////////////////////////////
// DrawWheels
/////////////////////////////////////////
void DrawWheels(GLuint * wheelside1vao,
				  GLuint * wheelside2vao,
				  GLuint * cylindervao, 
				  GLsizei sidecount, GLsizei cylindercount)
{
	
	
	
	DrawTriagle(wheelside1vao, sidecount);

	DrawTriagle(wheelside2vao, sidecount);
			
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
		
		
	mv = mv * Translate(0.04, -0.97f, 0.0405); 
	mv = mv * RotateZ(90);
	mv = mv * RotateX(turnAngle);
    mv = mv * RotateY(-rollangle);
	mv = mv * Scale(0.025,0.007,0.025);

    
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	glVertexAttrib4fv(vWheelSide1AmbientDiffuseColor, vec4(0.0f, 0.f, 0.0f, 1));
	glVertexAttrib4fv(vWheelSide1SpecularColor, vec4(0.4f, 0.0f,.0f,1.0f));
	glVertexAttrib1f(vWheelSide1SpecularExponent, 1.0);

	
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

	glVertexAttrib4fv(vWheelSide1AmbientDiffuseColor,vec4(0.0f, 0.f, 0.0f, 1));
	glVertexAttrib4fv(vWheelSide1SpecularColor, vec4(0.4f, 0.0f,.0f,1.0f));
	glVertexAttrib1f(vWheelSide1SpecularExponent, 1.0);

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


	
	glVertexAttrib4fv(vWheelSide1AmbientDiffuseColor, vec4(0.0f, 0.f, 0.0f, 1));
	glVertexAttrib4fv(vWheelSide1SpecularColor, vec4(0.4f, 0.0f,.0f,1.0f));
	glVertexAttrib1f(vWheelSide1SpecularExponent, 1.0);

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
		
	glVertexAttrib4fv(vWheelSide1AmbientDiffuseColor, vec4(0.0f, 0.f, 0.0f, 1));
	glVertexAttrib4fv(vWheelSide1SpecularColor, vec4(0.4f, 0.0f,.0f,1.0f));
	glVertexAttrib1f(vWheelSide1SpecularExponent, 1.0);

	DrawWheels(wheelside1vao,wheelside2vao,cylindervao, 75, 414);
		 

	mv = stack.pop();


}
////////////////////////////////////////////
//// police lamp
////////////////////////////////////////////
//	
//void displayPoliceLamps()
//{
//	
//	if ( turnOnPoliceLight == true )
//		glVertexAttrib4fv(vPoliceIsOn, lightOn);
//	else
//		glVertexAttrib4fv(vPoliceIsOn, lightOff);
//
//	// left lamp
//	stack.push(mv);
//	
//	mv = mv * Translate(currentX, 0, currentZ);
//	mv = mv * RotateY(turnCarAngle);
//	mv = mv * Translate(0.015, -0.84, -0.07); // -0.905
//	mv = mv * RotateY(turnPoliceLampAngle);
//	mv = mv * RotateX(-90);
//	mv = mv * Scale(0.010f,0.040f,0.040f);
//
//	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
//
//	glVertexAttrib4fv(vPoliceRedAmbientDiffuseColor, vec4(1.0f, 0.0f, 0.0f, 1));
//	glVertexAttrib4fv(vPoliceRedSpecularColor, vec4(0.4f, 0.0f,0.0f,1.0f));
//	glVertexAttrib1f(vPoliceRedSpecularExponent, 1.0);
//		
//
//	DrawTriagle(policeredvao, 144);
//
//	mv = stack.pop();
//
//	// Blue lamp
//	stack.push(mv);
//	
//	mv = mv * Translate(currentX, 0, currentZ);
//	mv = mv * RotateY(turnCarAngle);
//
//	
//	mv = mv * Translate(-0.015, -0.84, -0.07); // -0.905
//	
//	mv = mv * RotateY(turnPoliceLampAngle);
//	mv = mv * RotateX(-90);
//	mv = mv * Scale(0.010f,0.040f,0.040f);
//
//	glVertexAttrib4fv(vPoliceBlueAmbientDiffuseColor, vec4(0.0f, 0.0f, 1.0f, 1));
//	glVertexAttrib4fv(vPoliceBlueSpecularColor, vec4(0.0f, 0.0f,1.0f,1.0f));
//	glVertexAttrib1f(vPoliceBlueSpecularExponent, 1.0);
//
//
//	DrawTriagle(policebluevao, 144);
//
//	mv = stack.pop();
//
//}

void display(void)
{
	/*clear all pixels*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

	if ( switchcamera == 0 ) // static cam
	{
		mv = LookAt(vec4(0, 0, dollyzoom, 1.0), vec4(atX, 0, atZ, 1.0), vec4(0, 1, 0, 0.0));
		mv = mv*Translate(0,1,0);
		
		mv = mv *RotateX(rx);
		
		// this is for me to see the scene all around
		mv = mv * RotateX(view_rotx) * RotateY(view_roty) * RotateZ(view_rotz);

	}
	else if (switchcamera == 1) // chase cam
	{
		
		mv = LookAt(vec4(currentX, -0.91, currentZ, 1.0), // eye
			       vec4(chasecamlookdirection.x*10, -0.91, chasecamlookdirection.z*10, 1.0), // at
				   vec4(0, 1, 0, 0.0));    // up
	}
	else // viewport cam
	{
		vec4 viewpoint = vec4(0,0,1,0);
		vec4 view = vec4(0,0,1,0);

		if ( turnEyeRight != 0)
		{
			
			viewpoint = RotateY(turnEyeAngle) * viewpointcam;
			view = viewpoint;
			
		}
		else
		{
			view = viewpointcam;
		}
		

		mv = LookAt(vec4(currentX, -0.90, currentZ, 1.0), // eye
			       vec4(view.x*10, -0.90, view.z*10, 1.0), // at
				   vec4(0, 1, 0, 0.0));    // up
	}


	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
	
	setupMoonLight();
	setupHeadLight();
	setupPoliceLight();

	displayStage();
	displaySimpleObj();
	displayCar();
	displayHeadLightLamps();
	displayHead();
	displayEye();
	displayPoliceLights();
	displayWheels();
		
    glFlush();
  /*start processing buffered OpenGL routines*/
  glutSwapBuffers();
}

//////////////////////////////////////
// Set up properties for all lights
//////////////////////////////////////
void setupShader(GLuint prog){
	
	
	glUseProgram( prog );

	model_view = glGetUniformLocation(prog, "model_view");
	projection = glGetUniformLocation(prog, "projection");
	 
	
	///////////////////////////////////////////////////
	// setup moonlight
	///////////////////////////////////////////////////
	moonlight_position	= glGetUniformLocation(prog, "lights[0].position");
	moondiffuse_color	= glGetUniformLocation(prog, "lights[0].diffuse");
	moonspecular_color	= glGetUniformLocation(prog, "lights[0].specular");
	moonambient_light	= glGetUniformLocation(prog, "lights[0].ambient");

	///////////////////////////////////////////////////
	//setup right headlight
	///////////////////////////////////////////////////
	headrightlight_position		= glGetUniformLocation(prog, "lights[1].position");
	headrightdiffuse_color		= glGetUniformLocation(prog, "lights[1].diffuse");
	headrightspecular_color		= glGetUniformLocation(prog, "lights[1].specular");
	headrightambient_light		= glGetUniformLocation(prog, "lights[1].ambient");
	headrightspot_direction		= glGetUniformLocation(prog, "lights[1].spot_direction");
	headrightspot_cutoff		= glGetUniformLocation(prog, "lights[1].spot_cutoff");
	headrightspot_exponent		= glGetUniformLocation(prog, "lights[1].spot_exponent");
 

	///////////////////////////////////////////////////
	//setup left headlight
	///////////////////////////////////////////////////
	headleftlight_position	= glGetUniformLocation(prog, "lights[2].position");
	headleftdiffuse_color		= glGetUniformLocation(prog, "lights[2].diffuse");
	headleftspecular_color		= glGetUniformLocation(prog, "lights[2].specular");
	headleftambient_light		= glGetUniformLocation(prog, "lights[2].ambient");
	headleftspot_direction	= glGetUniformLocation(prog, "lights[2].spot_direction");
	headleftspot_cutoff			= glGetUniformLocation(prog, "lights[2].spot_cutoff");
	headleftspot_exponent		= glGetUniformLocation(prog, "lights[2].spot_exponent");
 
	///////////////////////////////////////////////////
	// setup red police light
	//////////////////////////////////////////////////
	
	policeredlight_position = glGetUniformLocation(prog, "lights[3].position");
	policereddiffuse_color  = glGetUniformLocation(prog, "lights[3].diffuse");
	policeredspecular_color = glGetUniformLocation(prog, "lights[3].specular");
	policeredambient_light  = glGetUniformLocation(prog, "lights[3].ambient");
	policeredspot_direction = glGetUniformLocation(prog, "lights[3].spot_direction");
	policeredspot_cutoff    = glGetUniformLocation(prog, "lights[3].spot_cutoff");
	policeredspot_exponent  = glGetUniformLocation(prog, "lights[3].spot_exponent");
 
	///////////////////////////////////////////////////
	// setup blue police light
	//////////////////////////////////////////////////
	policebluelight_position	= glGetUniformLocation(prog, "lights[4].position");
	policebluediffuse_color		= glGetUniformLocation(prog, "lights[4].diffuse");
	policebluespecular_color	= glGetUniformLocation(prog, "lights[4].specular");
	policeblueambient_light		= glGetUniformLocation(prog, "lights[4].ambient");
	policebluespot_direction	= glGetUniformLocation(prog, "lights[4].spot_direction");
	policebluespot_cutoff		= glGetUniformLocation(prog, "lights[4].spot_cutoff");
	policebluespot_exponent		= glGetUniformLocation(prog, "lights[4].spot_exponent");

	

}

//////////////////////
// Setup shader for VAO and VBO for each object
///////////////////////
void setupShader(GLuint prog, GLuint * vao, GLuint * vbo, vec4 * verts, vec3* normals, int totalcount)
{
	// Create a vertex array object
    glGenVertexArrays( 1, &vao[0] );
	glBindVertexArray( vao[0] );
	
	glGenBuffers( 2, &vbo[0] );
    glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, totalcount*sizeof(vec4), verts, GL_STATIC_DRAW);
	glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
	glBufferData( GL_ARRAY_BUFFER, totalcount*sizeof(vec3), normals, GL_STATIC_DRAW );


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
///////////////////////////////////////////////////
// setupHeadShader
//////////////////////////////////////////////////
void setupHeadShader(GLuint prog)
{
	vHeadAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vHeadSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vHeadSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");

	headvao = new GLuint[1];
	headvbo = new GLuint[2];
	setupShader(prog, headvao, headvbo, headVers, headNormals, totalheadverts);

	
}
///////////////////////////////////////////////////
// setupHeadShader
//////////////////////////////////////////////////
void setupSimpleObjShader(GLuint prog)
{
	vSimpleObjAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vSimpleObjSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vSimpleObjSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");

	simpleObjvao = new GLuint[1];
	simpleObjvbo = new GLuint[2];
	setupShader(prog, simpleObjvao, simpleObjvbo, simpleObjVers, simpleObjNormals, totalobjverts);


}

///////////////////////////////////////////////////
// setupCarShader
//////////////////////////////////////////////////
void setupCarShader(GLuint prog)
{
	vCarAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vCarSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vCarSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");

	carvao = new GLuint[1];
	carvbo = new GLuint[2];
	setupShader(prog, carvao, carvbo, carVerts, carNormals, 36);

}

///////////////////////////////////////////////////
// setupCarShader
//////////////////////////////////////////////////
void setupHeadLightLampsShader(GLuint prog)
{
	vCarAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vCarSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vCarSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");
	
	headLightLampsvao = new GLuint[1];
	headLightLampsvbo = new GLuint[2];
	setupShader(prog, headLightLampsvao, headLightLampsvbo, lampVerts, lampNormals, 36);


}
///////////////////////////////////////////////////
// setupPoliceLightShader
//////////////////////////////////////////////////
void setupPoliceLightsShader(GLuint prog)
{
	vPoliceLampAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vPoliceLampSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vPoliceLampSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");
	vPoliceIsOn =  glGetAttribLocation(prog, "vIsOn");


	policelightvao = new GLuint[1];
	policelightvbo = new GLuint[2];
	setupShader(prog, policelightvao, policelightvbo, policeLightVers, policeLightNormals, totalheadverts);
	

}

///////////////////////////////////////////////////
// setupPoliceLightShader
//////////////////////////////////////////////////
//void setupPoliceLightShader(GLuint prog)
//{
//	vPoliceRedAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
//	vPoliceRedSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
//	vPoliceRedSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");
//	vPoliceIsOn =  glGetAttribLocation(prog, "vIsOn");
//
//
//	policeredvao = new GLuint[1];
//	policeredvbo = new GLuint[2];
//	setupShader(prog, policeredvao, policeredvbo, policeLampRedVerts, policeLampRedNormals, 144);
//
//	
//
//	// blue
//	vPoliceBlueAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
//	vPoliceBlueSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
//	vPoliceBlueSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");
//	vPoliceIsOn =  glGetAttribLocation(prog, "vIsOn");
//
//
//	policebluevao = new GLuint[1];
//	policebluevbo = new GLuint[2];
//	setupShader(prog, policebluevao, policebluevbo, policeLampBlueVerts, policeLampBlueNormals, 144);
//
//
//}

///////////////////////////////////////////////////
// setupEyeShader
//////////////////////////////////////////////////
void setupEyeShader(GLuint prog)
{
	vEyeAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vEyeSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vEyeSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");

	eyevao = new GLuint[1];
	eyevbo = new GLuint[2];
	setupShader(prog, eyevao, eyevbo, eyeVerts, eyeNormals, 75);

}
///////////////////////////////////////////////////
// setupWheelShader
//////////////////////////////////////////////////
void setupWheelShader(GLuint prog)
{
	vWheelSide1AmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vWheelSide1SpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vWheelSide1SpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");

	wheelside1vao = new GLuint[1];
	wheelside1vbo = new GLuint[2];
	setupShader(prog, wheelside1vao, wheelside1vbo, wheelSide1Verts, wheelSide1Normals, 75);


	// wheelside 2

	wheelside2vao = new GLuint[1];
	wheelside2vbo = new GLuint[2];
	setupShader(prog, wheelside2vao, wheelside2vbo, wheelSide2Verts, wheelSide2Normals, 75);


	// cylinder

	cylindervao = new GLuint[1];
	cylindervbo = new GLuint[2];
	setupShader(prog, cylindervao, cylindervbo, wheelCylinderVers, vWheelCylinderNormals, 414);

}

///////////////////////////////////////////////////
// setupStageShader
//////////////////////////////////////////////////
void setupStageShader(GLuint prog)
{
	vStageAmbientDiffuseColor = glGetAttribLocation(prog, "vAmbientDiffuseColor");
	vStageSpecularColor = glGetAttribLocation(prog, "vSpecularColor");
	vStageSpecularExponent = glGetAttribLocation(prog, "vSpecularExponent");

	stagevao = new GLuint[1];
	stagevbo = new GLuint[2];
	setupShader(prog, stagevao, stagevbo, stageVerts, stageNormals, 6);

}

/////////////////////////////////////////
// myIdle
/////////////////////////////////////////
void myIdle()
{
	if ( turnOnPoliceLight == true )
	{
		if ( turnPoliceLampAngle > 360 )
		{
			turnPoliceLampAngle = 0;
		}
	
		turnPoliceLampAngle += 1;
	}

	
	GLint moveF = 1;
	if ( bmoveForward == true )
	{
		moveF = 1;
	}
	else
	{
		moveF = -1;
	}

	chasecamlookdirection = RotateY((moveF)*0.2*(turnAngle)/maxTurnWheel) * chasecamlookdirection;
	viewpointcam = RotateY((moveF)*0.2*(turnAngle)/maxTurnWheel) * viewpointcam;
			
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
		if ( startcar == true )
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
		}

		glutPostRedisplay();
	}
	
}
/////////////////////////////////////////////
// keyboard
/////////////////////////////////////////////

void Keyboard(unsigned char key, int x, int y) {
	/*exit when the escape key is pressed*/
	if (key == 27)
		exit(0);

	if (key == 'L' || key == 'l' ) // turnon/off police lights
	{
		if ( turnOnPoliceLight == true )
		{
			turnOnPoliceLight = false;
		}
		else
		{
			turnOnPoliceLight = true;
		}


		glutIdleFunc(myIdle);
	}
	else if (key == 'w' || key == 'W' ) // dolly in
	{
		dollyzoom += 1;
	}
	else if (key == 'q' || key == 'Q' ) // to dolly out in
	{
		dollyzoom -= 1;
	}
	else if (key == 'r' || key == 'R' )
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
		if ( switchcamera == 0 )
		{
			currentlenszoom = lenszoom;
			
			p = Perspective(lenszoom, (float)ww/(float)wh, 1.0, 100.0);
			switchcamera = 1;
		}
		else if ( switchcamera == 1 )
		{
			currentlenszoom = lenszoom;
			
			p = Perspective(lenszoom, (float)ww/(float)wh, 1.0, 100.0);
			switchcamera = 2;
		}
		else if ( switchcamera == 2 )
		{
			reshape(ww, wh);
			switchcamera = 0;
		}

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
		if ( switchcamera == 0)
		{
			lenszoom += 1;
			reshape(ww, wh);
		}
		else{
			p = Perspective(1.0, (float)ww/(float)wh, 1.0, 100.0);
		}
			
	}
	else if (key == 'a' || key == 'A' ) // to zoom in
	{
		
		if ( switchcamera == 0)
		{
			lenszoom -= 1;
			reshape(ww, wh);
		}
		else
		{
			p = Perspective(1.0, (float)ww/(float)wh, 1.0, 100.0);
		}
	}
	else if (key == 'w' || key == 'W' ) // dolly in
	{
		dollyzoom += 1;
	}
	else if (key == 'q' || key == 'Q' ) // to dolly out in
	{
		dollyzoom -= 1;
	}
	else if ( key == 'b' || key == 'B' ) // to start the car
	{
		startcar = true;
		glutIdleFunc(myIdle);
	}

	else if ( key == 32 ) // to stop car moving
	{
		startcar = false;
		glutIdleFunc(myIdle);
	}
	else if(key == 'z')
	{
		turnEyeRight = 1;
		turnEyeAngle += 1;
	}
	else if(key == 'x')
	{
		turnEyeRight = -1;
		turnEyeAngle -= 1;
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
		/*rz -= 5;
		if(rz < 0)
			rz += 360;*/
	}

	
	reshape(ww,wh);
	glutPostRedisplay();

}
////////////////////////////////////////////
// This is for me for testing the scene
///////////////////////////////////////////
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

////////////////////////////////////////////
// This is for me for testing the scene
///////////////////////////////////////////
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
/////////////////////////////////////////////
// INIT
///////////////////////////////////////////
void init() {

	/*select clearing (background) color*/
	glClearColor(0.0, 0.0, 0.0, 1.0);
	  
	turnPoliceLampAngle = 0;
	turnOnPoliceLight = false;
	startcar = false;

	// preset dollyzoom, lenszoom
	  atX = atZ = 0;
	  dollyzoom = 3.0f;
	  lenszoom = 25.0;
	  rx = 30;
	  ty = 0.8;
	  tz = 19.2;
	  // TRUE: point camear at the center, 
	  // False: point at the car
	  pointCameraAt = true;
	  switchcamera = 0; //
	    
	  chasecamlookdirection		= vec4(0.0, 0.0 , 0.07,0);
	  viewportcamlookdirection  = vec4(0.0, 0.0 , 0.07,0);
	  viewpointcam				= vec4(0.0, 0.0 , 0.07,0);

	  ///////////////////
	  // assighment 2
	  ///////////////////
	  bmoveForward = true;
	  moveStepZ = 0.0005;
	  currentX = currentZ = 0;

	  // right lamp
	  rightlampSource = vec4(-0.02,-0.97 + 0.05,0.070  ,1); 
	  rightlampDest   = vec4(-0.04,-1   + 0.05 ,20,  0); 

	   
	  leftlampSource = vec4(0.02,-0.97 + 0.05,0.070,1); 
	  leftlampDest   = vec4(0.04,-1   +0.05 ,20,  0); 

	  /////////////////////////////////////////
	  // police light coordinates x,y,zl
	  /////////////////////////////////////////
	  policeredlightlampSource = vec4(0.00, -0.78 - 0.03, -0.08, 1);
	  policeredlightlampDest   = vec4(0.00, -0.8,    -2, 0);

	  policebluelightlampSource = vec4(-0.0, -0.78 - 0.03, -0.08, 1);
	  policebluelightlampDest   = vec4(-0.0, -0.8,   2, 0);

	  turnCarAngle = 0;
	  turnAngle = 0;
	  rollangle = 0;
	  turnEyeAngle = 0;
		// caculate movestepX and vector len for moving car
	  moveStepX = tan(M_PI/180) * moveStepZ;
	  vectorLen = sqrt(moveStepX*moveStepX + moveStepZ*moveStepZ);

   
    // generate objects 
    generateStage();
	generateSimpleObject();
	generateCar();
	generateHeadLightLamps();
	generateHead();
	generateEyes();
	generatePoliceLights();
	generateWheelSides();

    // Load shaders and use the resulting shader program
    program = InitShader( "vshader-phongshading.glsl", "fshader-phongshading.glsl" );
	glUseProgram(0 );
		
	setupShader(program);
	setupStageShader(program);
	setupSimpleObjShader(program);
	setupCarShader(program);
	setupHeadLightLampsShader(program);
	setupHeadShader(program);
	setupEyeShader(program);
	setupPoliceLightsShader(program);
	setupWheelShader(program);

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
/////////////////////////////////
// main
/////////////////////////////////
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
	  glutMouseFunc(mouse);
	  glutMotionFunc(mouse_dragged);

	  glutMainLoop();
	  return 0;
}