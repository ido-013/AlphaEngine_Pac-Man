#include "SpriteComp.h"
#include "TransformComp.h"
#include "../ResourceManager/ResourceManager.h"

SpriteComp::SpriteComp(GameObject* _owner) : GraphicComponent(_owner), color(), tex(nullptr), textureName()
{

}

SpriteComp::~SpriteComp()
{
	ResourceManager::GetRMPtr()->UnloadResource(textureName);
}

void SpriteComp::Update()
{
	//Create quad
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxVertexList* mesh = AEGfxMeshEnd();

	//Set render mode
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	//Set color to multiply
	AEGfxSetColorToMultiply(1, 1, 1, 1);

	//Set color to add
	AEGfxSetColorToAdd(color.r / 255.f, color.g / 255.f, color.b / 255.f, 0.f);

	//Set blend Mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	//Set transparency
	AEGfxSetTransparency(1);

	//Set texture
	AEGfxTextureSet(tex, 0, 0);

	//Set transform
	//Get the transform from my owner transfrom comp
	AEMtx33 transf = owner->GetComponent<TransformComp>()->GetMatrix();
	AEGfxSetTransform(transf.m);

	//call DrawMesh
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxMeshFree(mesh);
}

void SpriteComp::SetColor(const unsigned char& r, const unsigned char& g, const unsigned char& b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

void SpriteComp::SetTexture(std::string name)
{
	textureName = name;
	tex = ResourceManager::GetRMPtr()->GetResource<AEGfxTexture>(name);
}

void SpriteComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("color");
		color.r = it->begin().value();
		color.g = (it->begin() + 1).value();
		color.b = (it->begin() + 2).value();

		it = compData->find("textureName");
		textureName = it.value();
		SetTexture(textureName);
	}
}

json SpriteComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["color"] = { color.r, color.g, color.b };
	compData["textureName"] = textureName;
	data["compData"] = compData;

	return data;
}

BaseRTTI* SpriteComp::CreateSpriteComponent(GameObject* owner)
{
	BaseRTTI* p = new SpriteComp(owner);
	owner->AddComponent<SpriteComp>(static_cast<SpriteComp*>(p));
	return p;
}
