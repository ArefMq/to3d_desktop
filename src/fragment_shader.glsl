#version 120

//varying highp vec4 colorGradient;


uniform float pointsCount;
uniform float colorAxisMode;
uniform vec3 pointsBoundMin;
uniform vec3 pointsBoundMax;

varying vec3 vert;
varying vec3 vColor;
varying float pointIdx;


void main() {
//  gl_FragColor = colorGradient;
  // float intensity = pointIdx/pointsCount;
  // if (colorAxisMode == 1) {
  //   intensity = (vert.z + abs(pointsBoundMin.z))/(pointsBoundMax.z - pointsBoundMin.z);
  // }
  gl_FragColor = vec4(vColor.x, vColor.y, vColor.z, 0.);
}
