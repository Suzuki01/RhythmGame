#include "cereal/cereal.hpp"
#include "cereal//archives/json.hpp"
#include <fstream>
#include "data_manager.h"


//
struct VECTOR3 {
	float x, y, z;
	template<class Archive>
	void serialize(Archive& archive) { //この関数名は変えられない
		archive(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z)); //保存する変数
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
	//書き込みの例（まだセーブできるかは不明）
	{
		vector.x = 1.0f;
		vector.y = 2.0f;
		vector.z = 3.0f;

		std::ofstream stream(fileName); //ファイル名
		cereal::JSONOutputArchive outArchive(stream); //型名
		outArchive(vector);
	}
}

void DataManager::Load(char* fileName) {
	//読み込みの例（まだロードができるか不明）
	{
		std::ifstream stream(fileName);
		cereal::JSONInputArchive inArcive(stream);

		inArcive(vector);
	}

}