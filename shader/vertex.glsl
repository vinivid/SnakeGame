#version 330 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 c_pos;

uniform mat4 translate;

out vec3 col_pos_coord;

void main(){
    gl_Position = translate * vec4(v_pos, 1.0);
    col_pos_coord = c_pos;
}