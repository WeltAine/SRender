#pragma once


#include <vector>
#include "../Scene Entities/Light.h"
#include "../Scene Entities/Camera.h"
#include "../Math/Matrix.h"
#include "Texture.h"
#include "Buffer.h"
#include "Mesh.h"

namespace newShader{
	class IShader;
}

//���Ĺ����Ǽ�¼������ɫ����Ҫ�õ��Ͳ���������


//͸�ӽ������õĿռ�����MV�еģ�Ŀǰ�������У�Ҳ����������MV�У���ΪZ�ı����ǽ��������Ĺؼ���P�����ƽ�ƣ��ƻ��������������������ʹ��ndc������Ļ����

/// <summary>
/// �����α����������ƬԪ����
/// </summary>
struct FragDate {
	Vertex fragVertex;//����ÿ��ƬԪ��MV�ռ��µ�position, normal, uv��normal������գ�uvûʲô������仯��ԭ��
	Vector2i screenPosition;
	Vector3f interpolations;//��ֵ����
};

struct RenderDate {

	std::vector<Mesh*> aimObjs{};//Ҫ��Ⱦ��ģ��
	std::vector<Texture*> aimTextures;//ģ����ʹ�õ�����
	std::vector<Light*> lights{};//��Դ
	Camera* mainCamera;//��ͷ������ɫ����Ȼ���

	newShader::IShader* shadowShader, * renderShader;


	std::vector<Vertex> aimVertexs;
	std::vector<Vector3f> mvpPositions;//δ��λ�
	std::vector<Vector3f> mvPositions;//����ռ䶥�㣬���մ���ʱʹ��
	std::vector<Vector3f> mvNormals;
	std::vector<Vector3f> ndcPositions;
	std::vector<Vector3f> screenPositions;
	std::vector<FragDate> fragMates;//������ͷ�Ǹ�������Ļ���꣬����������ȫ��ͬ

};




