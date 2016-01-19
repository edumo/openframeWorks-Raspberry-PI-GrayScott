precision highp float; // this will make the default precision high

//we passed this in from our vert shader
varying vec2        texcoord0;

//These are variables we set in our ofApp using the ofShader API

//our texture reference
//passed in by
//shader.setUniformTexture("tex0", sourceImage.getTextureReference(), sourceImage.getTextureReference().texData.textureID);
uniform sampler2D   tex0;
uniform sampler2D   backbuffer;
//width and height that we are working with
//passed in by
//shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
uniform vec2        resolution;

//a changing value to work with
//passed in by
//shader.setUniform1f("time", ofGetElapsedTimef());
uniform float       time;


//Each shader has one main() function you can use
//Below are a few implementations. Make sure you have all but one commented out

//Shaders are compiled at runtime meaning that you can just change the shader file 
//and re-run the ofApp without compiling


float kernel[9];
   vec2 offset[9];
   
  // uniform sampler2DRect backbuffer;
  // uniform sampler2DRect tex0;

   uniform float diffU;
   uniform float diffV;
   uniform float f;
   uniform float k;



// let's wobble the image channels around independently, a bit Fear and Loathing in Las Vegas style
void main()
{
    mediump float newTime = time * 2.0;

  vec2 st   = texcoord0.st;
 kernel[0] = 0.707106781;
kernel[1] = 1.0;
kernel[2] = 0.707106781;
kernel[3] = 1.0;
kernel[4] = -6.82842712;
kernel[5] = 1.0;
kernel[6] = 0.707106781;
kernel[7] = 1.0;
kernel[8] = 0.707106781;

 offset[0] = vec2( -1.0, -1.0);
offset[1] = vec2(  0.0, -1.0);
offset[2] = vec2(  1.0, -1.0);

offset[3] = vec2( -1.0, 0.0);
offset[4] = vec2(  0.0, 0.0);
offset[5] = vec2(  1.0, 0.0);

offset[6] = vec2( -1.0, 1.0);
offset[7] = vec2(  0.0, 1.0);
offset[8] = vec2(  1.0, 1.0);

  vec2 texColor = texture2D( backbuffer, st ).rb;
 float srcTexColor = texture2D( tex0, st ).r;

 vec2 lap = vec2( 0.0, 0.0 );
                                       
for( int i=0; i < 9; i++ ){
   vec2 tmp = texture2D( backbuffer, st + offset[i] ).rb;
   lap += tmp * kernel[i];
}

  float F  = f + srcTexColor * 0.025 - 0.0005;
float K  = k + srcTexColor * 0.025 - 0.0005;

float u  = texColor.r;
float v  = texColor.g + srcTexColor * 0.5;

float uvv = u * v * v;

   float du = diffU * lap.r - uvv + F * (1.0 - u);
float dv = diffV * lap.g + uvv - (F + K) * v;

u += du * 0.6;
v += dv * 0.6;
               gl_FragColor = vec4(clamp( u, 0.0, 1.0 ), 1.0 - u/v ,clamp( v, 0.0, 1.0 ), 1.0);

    vec2 newTexCoord;
   /* newTexCoord.s = texcoord0.s + (cos(newTime + (texcoord0.s*20.0)) * 0.01);
    newTexCoord.t = texcoord0.t + (sin(newTime + (texcoord0.t*20.0)) * 0.01);

    mediump vec2 texCoordRed    = newTexCoord;
    mediump vec2 texCoordGreen  = newTexCoord;
    mediump vec2 texCoordBlue   = newTexCoord;

    texCoordRed     += vec2( cos((newTime * 2.76)), sin((newTime * 2.12)) )* 0.01;
    texCoordGreen   += vec2( cos((newTime * 2.23)), sin((newTime * 2.40)) )* 0.01;
    texCoordBlue    += vec2( cos((newTime * 2.98)), sin((newTime * 2.82)) )* 0.01;  

    mediump float colorR = texture2D( tex0, texCoordRed ).r;
    mediump float colorG = texture2D( tex0, texCoordGreen).g;
    mediump float colorB = texture2D( tex0, texCoordBlue).b;  
	mediump float colorA = texture2D( tex0, texCoordBlue).a;     
    mediump vec4 outColor = vec4( colorR, colorG, colorB, colorA);

  //  gl_FragColor = outColor;*/
}

