#version 330

uniform mat4 projMat;
uniform mat4 modelMatrix;
uniform mat4 modelViewMat;                                                                           
// uniform mat4 normalMatrix;


layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 inNormal;

smooth out vec2 vTexCoord;
smooth out vec3 vNormal;
smooth out vec3 vWorldPos;
smooth out vec4 vEyeSpacePos;

uniform mat4 HeightmapScaleMatrix;

void main()
{
  vec4 inPositionScaled = HeightmapScaleMatrix*vec4(inPosition, 1.0);
  mat4 mMVP = projMat*modelViewMat;
   
  gl_Position = mMVP*inPositionScaled;
  vEyeSpacePos = modelViewMat*vec4(inPosition, 1.0);
  
  vTexCoord = inCoord;
  vNormal = inNormal;
   
  vec4 vWorldPosLocal = inPositionScaled;
  vWorldPos = vWorldPosLocal.xyz;
  
}