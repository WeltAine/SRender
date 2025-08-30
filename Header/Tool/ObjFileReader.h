#pragma once

#include <vector>
#include <string>
#include <fstream>
#include"../Resources/Mesh.h"




void StringSplit(std::string s, char splitchar, std::vector<std::string>& vec);


void ReadObjFile(std::string path, Mesh* obj);
