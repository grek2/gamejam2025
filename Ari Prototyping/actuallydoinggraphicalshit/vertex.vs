version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in int awhichTexture;
out vec3 ourColor;
out vec2 TexCoord;
out int whichtexture;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    whichtexture = awhichtexture;

}
