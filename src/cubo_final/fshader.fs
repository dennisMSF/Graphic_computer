#version 330 core
out vec4 FragColor;
uniform float time;
//uniform vec3 ourColor;
uniform vec4 color2;
in vec3 ourColor;
in vec2 TexCoord;
uniform vec2 resolution;
uniform sampler2D texture1;
#define pi 3.14159265359
float def(vec2 uv, float f);
void main(){
    vec2 uv=gl_FragCoord.xy / resolution;

    vec2 p = vec2(0.5) - uv;
    float rad = length(p);
    float angulo = atan(p.x,p.y);
    float e = def(uv,0)/2;
    float e2 = def(uv,pi/8)+0.1;
    //float e = sin(rad*pi+ time);
    //float e2 = sin (rad*pi + time);
    vec3 final = vec3(e)*ourColor + vec3(e2)*ourColor;
    //FragColor = vec4(final,1.0); 
    FragColor = texture(texture1, TexCoord) ;
}
float def(vec2 uv, float f){
    float cant = 10;
    float e = 0;
    for(int i=0;i<cant;i++){
        vec2 p = vec2(0.5,i/cant) - uv;
        float rad = length(p)*1;
        float angulo = atan(p.x,p.y);
        e+=sin(rad*10+f+time);
        e+=sin(e*pi)*0.8;
    }
    e/=cant/4;
   
    return abs(e);
}