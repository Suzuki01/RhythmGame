#ifndef MESH_SKY_H_
#define MESH_SKY_H_

#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "texture.h"
#include "texture_manager.h"

class MeshSky : public GameObject {
public:
	void Init(float meshH, float radius, int meshXnum, int meshYnum);
	void Update(void);
	void UnInit(void);												//���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�e�N�X�`���̂���Ȃ�
	void Draw();
};
//����DrawIndexedPrimitive
//�k�ނ𗘗p�����X�g���b�v�|���S��
//UV�A�h���b�V���O���[�hWRAP�ɂ���

#endif // MESH_SKY_H_