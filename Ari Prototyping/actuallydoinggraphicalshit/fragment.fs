#version 460 core\n
out vec4 FragColor; 
in vec2 TexCoord; 
in int whichtexture;
uniform sampler2D subTexture; 
uniform sampler2D blockTexture; 

void main() 
{    
	switch(whichtexture){
		case 0:
			FragColor = texture(subTexture, TexCoord);
			break;
		case 1:
			FragColor = texture(blockTexture, TexCoord);
			break;
		case 2:
			FragColor = texture(subTexture, TexCoord);
			break;
 
   FragColor = texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) ; 
}
