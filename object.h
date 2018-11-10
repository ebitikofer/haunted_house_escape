class object {

  enum material { wood, metal, glass, ceramic };

  public:
    mat4 matrix;
    material mat;
    // color4 material_ambient;
    // color4 material_diffuse;
    // color4 material_specular;
    // float  material_shininess;
    GLuint uniform;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
    GLfloat h;
    GLfloat d;
    GLfloat r;
    GLfloat g;
    GLfloat b;
    int pitch;
    int yaw;
    int roll;
    int sl;
    int st;
    int type;

};
