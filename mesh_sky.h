#ifndef MESH_SKY_H_
#define MESH_SKY_H_

void Mesh_Skydome_Initialize(float meshH, float radius, int meshXnum, int meshYnum);
void MeshSky_Update(void);
void MeshSky_Finalize(void);												//���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�e�N�X�`���̂���Ȃ�
void MeshSky_Draw(int texture_index);
//����DrawIndexedPrimitive
//�k�ނ𗘗p�����X�g���b�v�|���S��
//UV�A�h���b�V���O���[�hWRAP�ɂ���

#endif // MESH_SKY_H_