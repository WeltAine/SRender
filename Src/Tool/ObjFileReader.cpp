#include "../../Header/Tool/ObjFileReader.h"
#include <sstream>  // 提供 std::istringstream
#include <map>
#include <cstdlib>

/// <summary>
/// 字符串拆解，会自己清理字符向量
/// </summary>
/// <param name="s"></param>
/// <param name="splitchar"></param>
/// <param name="vec"></param>
void StringSplit(std::string s, char splitchar, std::vector<std::string>& vec)
{
	vec.clear();
	std::string tem;

	for (int i = 0; i <= s.size(); i++) {

		if (s[i] == splitchar && i == 0) {

			continue;

		}
		else if(s[i] == splitchar || i == s.size()) {

			vec.push_back(tem);
			tem.clear();
			continue;

		}
		else {
			tem.append(1,s[i]);
		}

	}

}

void ReadObjFile(std::string path, Mesh* obj)
{

	std::ifstream in(path);
	std::string line = "";//临时存储字符串用于
	std::string prefix = "";//前缀

	std::vector<std::string> group;
	std::vector<Vector3f> positionBuffer;
	std::vector<Vector3f> normalBuffer;
	std::vector<Vector2f> uvBuffer;

	group.reserve(5);
	positionBuffer.reserve(240);
	normalBuffer.reserve(240);
	uvBuffer.reserve(240);

	std::map<Vertex, int> vertexBuffer;

	if (in) {

		while (std::getline(in, line)) {

			prefix.clear();
			std::istringstream iss(line);
			iss >> prefix;  // 自动提取第一个单词或字符

			if (prefix == "v") {

				line.erase(0, 2);//删除从索引0开数的两个字符，也就是0和1
				StringSplit(line, ' ', group);

				Vector3f tem(std::stof(group[0]), std::stof(group[1]), std::stof(group[2]));
				positionBuffer.emplace_back( tem );

			}
			else if(prefix == "vt") {

				line.erase(0, 3);//删除从索引0开数的两个字符，也就是012
				StringSplit(line, ' ', group);

				Vector2f tem(std::stof(group[0]), std::stof(group[1]));
				uvBuffer.emplace_back(tem);

			}
			else if (prefix == "vn") {

				line.erase(0, 3);//删除从索引0开数的两个字符，也就是012
				StringSplit(line, ' ', group);

				Vector3f tem(std::stof(group[0]), std::stof(group[1]), std::stof(group[2]), 0);
				normalBuffer.emplace_back(tem);

			}
			else if (prefix == "f") {

				line.erase(0, 2);//删除从索引0开数的两个字符，也就是0和1
				StringSplit(line, ' ', group);

				switch (group.size()) {

				case(3): {

					std::vector<std::string> temIndex;

					int trangleIndex[3];
					for (int i = 0; i < 3; i++) {
						StringSplit(group[i], '/', temIndex);

						int positionIndex = std::stoi(temIndex[0]) - 1;
						int uvIndex = std::stoi(temIndex[1]) - 1;
						int normalIndex = std::stoi(temIndex[2]) - 1;
						

						Vertex tem(positionBuffer[positionIndex], normalBuffer[normalIndex], Color::white, uvBuffer[uvIndex]);

						if (vertexBuffer.find(tem) == vertexBuffer.end()) {

							trangleIndex[i] = vertexBuffer.size();
							vertexBuffer.insert(std::pair<Vertex, int>(tem, trangleIndex[i]));

							obj->vertexBuffer.emplace_back(tem);

						}
						else {
							trangleIndex[i] = vertexBuffer[tem];
						}

					}

					obj->trangleIndexBuffer.emplace_back(trangleIndex[0], trangleIndex[1], trangleIndex[2]);

				}

				case(4): {

					std::vector <std::string> temIndex;

					int trangleIndex[4];
					for (int i = 0; i < 4; i++) {
						StringSplit(group[i], '/', temIndex);

						int positionIndex = std::stoi(temIndex[0]) - 1;
						int uvIndex = std::stoi(temIndex[1]) - 1;
						int normalIndex = std::stoi(temIndex[2]) - 1;


						Vertex tem(positionBuffer[positionIndex], normalBuffer[normalIndex], Color::white, uvBuffer[uvIndex]);


						
						if (vertexBuffer.find(tem) == vertexBuffer.end()) {

							//如果是新的顶点
							trangleIndex[i] = vertexBuffer.size();//顺序新增编号
							vertexBuffer.insert(std::pair<Vertex, int>(tem, trangleIndex[i]));//载入map

							obj->vertexBuffer.push_back(tem);//载入mesh

						}
						else {
							trangleIndex[i] = vertexBuffer[tem];
						}

					}

					obj->trangleIndexBuffer.emplace_back(trangleIndex[0], trangleIndex[1], trangleIndex[2]);
					obj->trangleIndexBuffer.emplace_back(trangleIndex[0], trangleIndex[2], trangleIndex[3]);
				}

				}

			}


		}


	}


}
