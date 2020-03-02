#version 120

//attribute vec2 textureCoordinate;
//varying highp vec4 colorGradient;

uniform float pointSize;
uniform mat4 viewMatrix;

attribute vec4 vertex;
attribute vec4 vertColor;
attribute float pointRowIndex;

varying float pointIdx;
varying vec3 vert;
varying vec3 vColor;


void main() {
  gl_Position = viewMatrix * vertex;
  gl_PointSize  = pointSize;

  // for use in fragment shader
  pointIdx = pointRowIndex;
  vert = vertex.xyz;
  vColor = vertColor.xyz;
}
