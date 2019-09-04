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
	void UnInit(void);												//頂点バッファ、インデックスバッファ、テクスチャのさよなら
	void Draw();
};
//一回のDrawIndexedPrimitive
//縮退を利用したストリップポリゴン
//UVアドレッシングモードWRAPにして

#endif // MESH_SKY_H_