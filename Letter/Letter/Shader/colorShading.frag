#version 130

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform bool isTexture;
uniform sampler2D curTexture;

void main()	{
	if (isTexture == true)	{
		vec4 textureColor = texture(curTexture, fragmentUV);
		color = textureColor;
	}else	{
		color = fragmentColor;
	}
}