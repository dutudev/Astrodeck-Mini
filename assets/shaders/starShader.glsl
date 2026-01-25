#version 330

in vec2 fragTexCoord;


uniform sampler2D texture0;
uniform float time;

out vec4 fragColor;


void main(){
	vec2 uv = fragTexCoord;
	uv.y += time;
	vec4 tex = texture(texture0, fract(uv));
	fragColor = vec4(1.0, 1.0, 1.0, tex.a * 0.6);

}