#define SCAN_LINE_MULT 1650.0

uniform sampler2D texture;

void main()
{
	vec2 texCoord = gl_TexCoord[0].xy;
	vec2 tc = vec2(texCoord.x, texCoord.y);

	// Distance from the center
	float dx = abs(0.5-tc.x);
	float dy = abs(0.5-tc.y);

	// Square it to smooth the edges

	// Get texel, and add in scanline if need be
	vec4 cta = texture2D(texture, vec2(tc.x, tc.y));

	cta.rgb += sin(tc.y * SCAN_LINE_MULT) * 0.04;

	// Cutoff
	if(tc.y > 1.0 || tc.x < 0.0 || tc.x > 1.0 || tc.y < 0.0)
		cta = vec4(0.0);

	// Apply
	gl_FragColor = gl_Color * cta;
}