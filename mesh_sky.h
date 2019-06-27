#ifndef MESH_SKY_H_
#define MESH_SKY_H_

void Mesh_Skydome_Initialize(float meshH, float radius, int meshXnum, int meshYnum);
void MeshSky_Update(void);
void MeshSky_Finalize(void);												//頂点バッファ、インデックスバッファ、テクスチャのさよなら
void MeshSky_Draw(int texture_index);
//一回のDrawIndexedPrimitive
//縮退を利用したストリップポリゴン
//UVアドレッシングモードWRAPにして

#endif // MESH_SKY_H_