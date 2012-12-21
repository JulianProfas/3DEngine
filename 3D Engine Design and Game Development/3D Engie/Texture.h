#include <string>
#include <d3dx9.h>

class Texture
{
public:
	Texture(std::string& name, LPDIRECT3DTEXTURE9 texture);
	~Texture();
	std::string GetName();
	void* getTexture();
	void setTexture(void* texture);
	Texture* loadTexture();
	
private:
	LPDIRECT3DTEXTURE9 loadedTexture;
	std::string name;
};