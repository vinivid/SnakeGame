#pragma once
#include <vector>

enum VBO_pos{
    vertex_vbo = 0,
    normal_vbo = 1,
    texture_vbo = 2
};

struct vertex{
    std::vector<float> pos;
    std::vector<float> normal;
    std::vector<float> texture;
};

typedef std::vector<unsigned> indexes_obj;

class gl_objects{
    public:
        gl_objects(int qtt);
        gl_objects(gl_objects&&) = delete;
        gl_objects(const gl_objects&) = delete;
        gl_objects& operator=(gl_objects&&) = delete;
        gl_objects& operator=(const gl_objects&) = delete; 
        ~gl_objects();

        //void add_vaos(int qtt_add);
        void config_vao(int index) noexcept;
        void bind_vao(int index) const noexcept;
        void unbind_vao() const noexcept;
        void config_vbo(int index,const vertex &vt) noexcept;
        void config_ibo(int index, const indexes_obj &id) noexcept;
    private:
        std::vector<unsigned> VAOs;
        std::vector<unsigned> VBOs;
        std::vector<unsigned> IBOs;
        int qtt_vaos;
};