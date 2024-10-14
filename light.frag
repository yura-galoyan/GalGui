// lighting.frag
uniform sampler2D texture;

// Maximum number of lights
const int MAX_LIGHTS = 20;

uniform vec2 lightPositions[MAX_LIGHTS];  // positions of the lights
uniform float lightRadii[MAX_LIGHTS];     // radii of the lights
uniform vec3 lightColors[MAX_LIGHTS];     // colors of the lights
uniform int lightCount;                   // actual number of active lights

void main()
{
    vec2 pixelPosition = gl_FragCoord.xy;
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);

    // Initialize final color with the base texture color
    vec3 finalColor = vec3(0.0);

    // Loop over all lights
    for (int i = 0; i < lightCount; i++)
    {
        // Calculate the distance from the current light source
        float distance = length(pixelPosition - lightPositions[i]);

        // Calculate attenuation (falloff) based on the light radius
        float attenuation = clamp(1.0 - (distance / lightRadii[i]), 0.0, 1.0);

        // Add the contribution of the current light
        finalColor += texColor.rgb * lightColors[i] * attenuation;
    }

    // Output the final color
    gl_FragColor = vec4(finalColor, texColor.a);
}
