//
// Created by Dell on 2021/12/6.
//

#ifndef EXP2_OBJLOADER_H
#define EXP2_OBJLOADER_H
#include "shader.h"
#include "objLoader.h"
#include "camera.h"

#include <vector>


struct vertex{
   glm::vec3 position;
   glm::vec3 normal;
   glm::vec2 texture;
};



class objLoader {
private:
    int i=0,j=0;
public:
    objLoader();
    void readFile(std::string filename);

public:
    std::vector<vertex> V;
    std::vector<unsigned int> S;
};


#endif //EXP2_OBJLOADER_H
