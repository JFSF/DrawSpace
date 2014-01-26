
float4x4 matViewProjection: register(c0);
float4   flag0:				register(c8);

	// .x -> patch orientation enum integer
	// .ytemp -> patch sidelenght
	// .z -> planet ray

float4   patch_translation:	register(c9);
	/// .x, .y -> patch positionning


struct VS_INPUT 
{
   float4 Position : POSITION0;
   float4 TexCoord0: TEXCOORD0;
      
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float4 TexCoord0: TEXCOORD0;
};

void CubeToSphere( float4 p_in, float4 p_out )
{

}


VS_OUTPUT vs_main( VS_INPUT Input )
{
	VS_OUTPUT Output;

	float4 v_position; // = Input.Position;

	// sidelenght scaling
	v_position.x = Input.Position.x * flag0.y / 2.0;
	v_position.y = Input.Position.y * flag0.y / 2.0;
	v_position.z = Input.Position.z * flag0.y / 2.0;
	v_position.w = 1.0;

	float4 v_position2;

	if( 0.0 == flag0.x ) // front
	{
		v_position2.x = v_position.x;
		v_position2.y = v_position.y;
		v_position2.z = 1.0;   
	}
	else if( 1.0 == flag0.x ) // rear
	{
		v_position2.x = -v_position.x;
		v_position2.y = v_position.y;
		v_position2.z = -1.0;   
	}
	else if( 2.0 == flag0.x ) // left
	{
		v_position2.x = -1.0;
		v_position2.y = v_position.y;
		v_position2.z = v_position.x;   
	}
	else if( 3.0 == flag0.x ) // right
	{
		v_position2.x = 1.0;
		v_position2.y = v_position.y;
		v_position2.z = -v_position.x;   
	}
	else if( 4.0 == flag0.x ) // top
	{
		v_position2.x = v_position.x;
		v_position2.y = 1.0;
		v_position2.z = -v_position.y;   
	}
	else //if( 5.0 == flag0.x ) // bottom
	{
		v_position2.x = v_position.x;
		v_position2.y = -1.0;
		v_position2.z = v_position.y;
	}

	v_position2.w = v_position.w;

	float xtemp = v_position2.x;
	float ytemp = v_position2.y;
	float ztemp = v_position2.z;

	v_position2.x = xtemp * sqrt( 1.0 - ytemp * ytemp * 0.5 - ztemp * ztemp * 0.5 + ytemp * ytemp * ztemp * ztemp / 3.0 );
	v_position2.y = ytemp * sqrt( 1.0 - ztemp * ztemp * 0.5 - xtemp * xtemp * 0.5 + xtemp * xtemp * ztemp * ztemp / 3.0 );
	v_position2.z = ztemp * sqrt( 1.0 - xtemp * xtemp * 0.5 - ytemp * ytemp * 0.5 + xtemp * xtemp * ytemp * ytemp / 3.0 );
   
   
	// final scaling
	float4 v_position3;
	
	v_position3.x = v_position2.x * flag0.z;
	v_position3.y = v_position2.y * flag0.z;   
	v_position3.z = v_position2.z * flag0.z;
	v_position3.w = 1.0;
	

	Output.Position = mul( v_position3, matViewProjection );
	Output.TexCoord0 = Input.TexCoord0;
	  
	return( Output );   
}
