//
// Created by Dell on 2021/12/6.
//

#include "objLoader.h"

#include <istream>
#include <iostream>
#include <fstream>
#include <sstream>

objLoader::objLoader() {

}

void objLoader::readFile(std::string filename) {

    vertex * p;
    std::ifstream objFile;
    std::string line;
    std::string head;
    objFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    unsigned int a,b,c;
    int i=0,j=0;
    try{
        objFile.open(filename);
        std::stringstream objStream;
        while(!objFile.eof()&&getline(objFile,line)){
            if(line.length()<=0)
                continue;
            std::istringstream in(line);
            if(line[0]=='v'){
               if(line[1]=='c'){
                   in>>head>>V[i].color.x>>V[i].color.y>>V[i].color.z;
                   i++;
               }else{
                   p = new vertex();
                   in>>head>>p->position.x>>p->position.y>>p->position.z;
                   V.push_back(*p);
               }
            }else if(line[0]=='f'){
                j+=3;
               in>>head>>a>>b>>c;
               S.push_back(a-1);
                S.push_back(b-1);
                S.push_back(c-1);
            }

        }
    }catch (std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}
