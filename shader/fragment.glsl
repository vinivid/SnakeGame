#version 330 core

in vec2 tex_pos_coord;

out vec4 frag_vec;

uniform sampler2D texture;

void main(){
    frag_vec = texture2D(texture, tex_pos_coord);
}