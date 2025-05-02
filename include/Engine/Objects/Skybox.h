#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>

class Skybox {
private:
    unsigned int __shader;
    unsigned int texture;
    unsigned int vao;

public:
    Skybox();
    void set_shader(unsigned int _shader);
    void draw();
    void add_cubemap_image(std::vector<std::string> faces);
    void init();
};

#endif
