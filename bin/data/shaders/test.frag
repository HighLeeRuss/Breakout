void main()
{
    // lookup the pixel in the texture
    vec4 c = vec4(gl_TexCoord[0].xy,0,1);// = texture2D(texture, gl_TexCoord[0].xy);
	vec2 uv = gl_TexCoord[0].xy;
	float d = length(gl_TexCoord[0].xy-vec2(0.5,0.5));
	if(d>0.5)
		discard;
    gl_FragColor = c;
}
