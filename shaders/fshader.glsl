varying vec4 color;

// per-fragment interpolated values from the vertex shader
varying vec3 fN;
varying vec3 fL;
varying vec3 fL2;
varying vec3 fE;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform vec4 AmbientProduct2, DiffuseProduct2, SpecularProduct2;
uniform vec4 emissive;
uniform vec4 LightPosition;
uniform vec4 LightPosition2;

uniform float enable;

uniform float Shininess;

uniform mat4 ModelView;

uniform bool light1, light2;

void main() {
  // if (enable == 1.0) {
    // Normalize the input lighting vectors
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    vec3 L2 = normalize(fL2);

    //If nearby light, calculate the direction per fragment.
    if(LightPosition.w != 0.0) {
      L = normalize(fL - fE);
    }

    if(LightPosition2.w != 0.0) {
      L2 = normalize(fL2 - fE);
    }

    vec3 R = reflect(L, N);
    vec3 R2 = reflect(L2, N);

    vec4 ambient = AmbientProduct;
    vec4 ambient2 = AmbientProduct2;

    float Kd = max(dot(L, N), 0.0);
    float Kd2 = max(dot(L2, N), 0.0);

    vec4 diffuse = Kd*DiffuseProduct;
    vec4 diffuse2 = Kd2*DiffuseProduct2;

    float Ks = pow(max(dot(R, E), 0.0), Shininess);
    float Ks2 = pow(max(dot(R2, E), 0.0), Shininess);

    vec4 specular = Ks*SpecularProduct;
    vec4 specular2 = Ks2*SpecularProduct2;

    // discard the specular highlight if the light's behind the vertex
    if(dot(L, N) < 0.0) {
      specular = vec4(0.0, 0.0, 0.0, 0.0);
    }
    // discard the specular highlight if the light's behind the vertex
    if(dot(L2, N) < 0.0) {
      specular2 = vec4(0.0, 0.0, 0.0, 0.0);
    }
    
    gl_FragColor = emissive * color;
    if ((emissive.r == 0.0) && (emissive.g == 0.0) && (emissive.b == 0.0)) {
      if (light1) {
        gl_FragColor += ambient + diffuse + specular;
      }
      if (light2) {
        gl_FragColor += ambient2 + diffuse2 + specular2;
      }
    }
    gl_FragColor.a = 1.0;
  //} else {
  //  gl_FragColor = color;
  //}
}
