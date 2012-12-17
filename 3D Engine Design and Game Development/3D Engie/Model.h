#include <string>
#include <d3dx9.h>

class Model
{
public:
	Model(LPD3DXMESH argMesh, std::string argName);
	~Model();
	void* GetMesh();
	void SetMesh(void* argMesh);
	std::string GetName();
	void SetName(std::string argName);
private:
	LPD3DXMESH mesh;
	std::string name;
};