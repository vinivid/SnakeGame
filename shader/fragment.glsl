#version 330 core

in vec3 col_pos_coord;

out vec4 frag_vec;

void main(){
    frag_vec = vec4(col_pos_coord, 1.0);
}