#pragma once

#include <vector>
class gl_tex{
    public:
        gl_tex(int qtt);
        gl_tex(gl_tex&&) = delete;
        gl_tex(const gl_tex&) = delete;
        gl_tex& operator=(gl_tex&&) = delete;
        gl_tex& operator=(const gl_tex&) = delete;
        ~gl_tex();

        void put_texture(int index,const char *file);
        void unbind_texture(int index);
    private:
        std::vector<unsigned> texx;
        int qtt_tex;
};