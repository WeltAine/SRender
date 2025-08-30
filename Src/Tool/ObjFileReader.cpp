#include "../../Header/Tool/ObjFileReader.h"
#include <sstream>  // �ṩ std::istringstream
#include <map>
#include <cstdlib>

/// <summary>
/// �ַ�����⣬���Լ������ַ�����
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
	std::string line = "";//��ʱ�洢�ַ�������
	std::string prefix = "";//ǰ׺

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
			iss >> prefix;  // �Զ���ȡ��һ�����ʻ��ַ�

			if (prefix == "v") {

				line.erase(0, 2);//ɾ��������0�����������ַ���Ҳ����0��1
				StringSplit(line, ' ', group);

				Vector3f tem(std::stof(group[0]), std::stof(group[1]), std::stof(group[2]));
				positionBuffer.emplace_back( tem );

			}
			else if(prefix == "vt") {

				line.erase(0, 3);//ɾ��������0�����������ַ���Ҳ����012
				StringSplit(line, ' ', group);

				Vector2f tem(std::stof(group[0]), std::stof(group[1]));
				uvBuffer.emplace_back(tem);

			}
			else if (prefix == "vn") {

				line.erase(0, 3);//ɾ��������0�����������ַ���Ҳ����012
				StringSplit(line, ' ', group);

				Vector3f tem(std::stof(group[0]), std::stof(group[1]), std::stof(group[2]), 0);
				normalBuffer.emplace_back(tem);

			}
			else if (prefix == "f") {

				line.erase(0, 2);//ɾ��������0�����������ַ���Ҳ����0��1
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

							//������µĶ���
							trangleIndex[i] = vertexBuffer.size();//˳���������
							vertexBuffer.insert(std::pair<Vertex, int>(tem, trangleIndex[i]));//����map

							obj->vertexBuffer.push_back(tem);//����mesh

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
