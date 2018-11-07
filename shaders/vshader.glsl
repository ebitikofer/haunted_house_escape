attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec4 vNormal;
varying vec4 color;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL;
varying  vec3 fL2;

uniform mat4 model_view;
uniform mat4 camera_view;
uniform mat4 projection;

uniform vec4 LightPosition;
uniform vec4 LightPosition2;

uniform vec4 color_change;
uniform float enable;

void main() {

  mat4 mv = camera_view*model_view;
  fN = (mv*vNormal).xyz;
  fE = (mv*vPosition).xyz;

  // Lights aren't moved with object, so only camera transform
  // (Camera) needs to be applied to them.
  fL = (camera_view*LightPosition).xyz;
  fL2 = (camera_view*LightPosition2).xyz;

  gl_Position = projection*mv*vPosition;
  // if (enable == 1.0) {
    color = color_change;
  // } else {
  //   color = vColor * color_change;
  // }
}
