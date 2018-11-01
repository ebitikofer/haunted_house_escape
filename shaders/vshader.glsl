attribute  vec4 vPosition;
attribute  vec4 vColor;
varying vec4 color;

uniform mat4 model_view;
uniform mat4 camera_view;
uniform mat4 projection;

void main() 
{
  gl_Position = projection*camera_view*model_view*vPosition;
  color = vColor;
}
