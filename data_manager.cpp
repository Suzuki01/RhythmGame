#include "cereal/cereal.hpp"
#include "cereal//archives/json.hpp"
#include <fstream>
#include "data_manager.h"


//
struct VECTOR3 {
	float x, y, z;
	template<class Archive>
	void serialize(Archive& archive) { //���̊֐����͕ς����Ȃ�
		archive(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z)); //�ۑ�����ϐ�
	}
};

struct PlayerData {
	VECTOR3 m_Position;
	int m_Life;
	template<class Archive>
	void serialize(Archive& archive) {
		archive(CEREAL_NVP(m_Position), CEREAL_NVP(m_Life));
	}
};

static VECTOR3 vector;


void DataManager::Save(char* fileName) {
	//�������݂̗�i�܂��Z�[�u�ł��邩�͕s���j
	{
		vector.x = 1.0f;
		vector.y = 2.0f;
		vector.z = 3.0f;

		std::ofstream stream(fileName); //�t�@�C����
		cereal::JSONOutputArchive outArchive(stream); //�^��
		outArchive(vector);
	}
}

void DataManager::Load(char* fileName) {
	//�ǂݍ��݂̗�i�܂����[�h���ł��邩�s���j
	{
		std::ifstream stream(fileName);
		cereal::JSONInputArchive inArcive(stream);

		inArcive(vector);
	}

}