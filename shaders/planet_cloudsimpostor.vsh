
float4x4 matWorldViewProjection: register(c0);
float4x4 matWorldView: register(c4);
float4x4 matWorld: register(c8);
float4x4 matView: register(c12);
float4x4 matCam: register(c16);
float4x4 matProj: register(c20);

float4 flags: register(c24);
    // .x -> mirror mode
    // .y -> planet ground ray
    // .z -> intensite fog

float4 cloud_dims: register(c25); // .x => cloud top; y => cloud bottom; z => cloud color top; w => cloud color bottom

float4 viewer_pos : register(c26);

float4 planetPos : register(c27);

struct VS_INPUT 
{
	float4 Position :  POSITION0;
	float4 Normales :  NORMAL0;
	float4 TexCoord0:  TEXCOORD0;
	float4 Pos:        TEXCOORD7;
	float4 Scale:      TEXCOORD8;
    float4 Sphericals: TEXCOORD6;

};

struct VS_OUTPUT 
{
	float4 Position :   POSITION0;
	float4 TexCoord0:   TEXCOORD0;
	float4 Color:	    TEXCOORD1;
    float4 Posdir:      TEXCOORD2;
    float4 PosCamSpace: TEXCOORD3;

    float Fog:        FOG;
};

#include "landscapes.hlsl"


float ComputeExp2Fog(float4 worldViewPos, float density)
{
    float4 org;
   
    org.x = 0.0;
    org.y = 0.0;
    org.z = 0.0;
    org.w = 1.0;

    float4 d = -worldViewPos[2];
    return 1 / exp2(d * density);
   
   // retour a 0.0 -> brouillard au maximum
}

float4x4 InverseMatrix( float4x4 p_mat )
{
	float4x4 trans = 0;

	trans[0][0] = 1.0;
	trans[1][1] = 1.0;
	trans[2][2] = 1.0;
	trans[3][3] = 1.0;

	trans[3][0] = -p_mat[3][0];
	trans[3][1] = -p_mat[3][1];
	trans[3][2] = -p_mat[3][2];

	p_mat[3][0] = 0.0;
	p_mat[3][1] = 0.0;
	p_mat[3][2] = 0.0;

	float4x4 transp = transpose( p_mat );
	float4x4 res = mul( trans, transp );
	return res;
}

float4x4 BuildRotationMatrix( float4 p_axis, float p_angle )
{
	float4x4 rot;

	float c = cos( p_angle );
    float s = sin( p_angle );
    float omc = (1 - c);

    float4 axis = normalize( p_axis );

    float x = axis[0];
    float y = axis[1];
    float z = axis[2];	
    float xs = x * s;
    float ys = y * s;
    float zs = z * s;
    float xyomc = x * y * omc;
    float xzomc = x * z * omc;
    float yzomc = y * z * omc;

    rot[0][0] = x * x * omc + c;
    rot[0][1] = xyomc + zs;
    rot[0][2] = xzomc - ys;
    rot[0][3] = 0;
    
    rot[1][0] = xyomc - zs;
    rot[1][1] = y * y * omc + c;
    rot[1][2] = yzomc + xs;
    rot[1][3] = 0;
    
    rot[2][0] = xzomc + ys;
    rot[2][1] = yzomc - xs;
    rot[2][2] = z * z * omc + c;
    rot[2][3] = 0;
    
    rot[3][0] = 0;
    rot[3][1] = 0;
    rot[3][2] = 0;
    rot[3][3] = 1;

	return rot;
}

VS_OUTPUT vs_main( VS_INPUT Input )
{
    VS_OUTPUT Output;

    float4 centerpos = 0;
    centerpos.w = 1;
    float4 vertexpos;

    vertexpos.z = 0.0;
    vertexpos.w = 1.0;
	
	////// pour les nuages volumetriques
	
    float cloud_color_top;
    float cloud_color_bottom;
	
    cloud_color_top = lerp(cloud_dims.w, cloud_dims.z, (Input.Pos.y + (Input.Scale.y / 2.0) + abs(cloud_dims.y)) / (cloud_dims.x - cloud_dims.y));
    cloud_color_bottom = lerp(cloud_dims.w, cloud_dims.z, (Input.Pos.y - (Input.Scale.y / 2.0) + abs(cloud_dims.y)) / (cloud_dims.x - cloud_dims.y));
		
	//

    if (Input.Normales.x == 1.0)
    {
        vertexpos.x = -0.5 * Input.Scale.x;
        vertexpos.y = 0.5 * Input.Scale.y;
        Output.Color = cloud_color_top;
    }
    else if (Input.Normales.x == 2.0)
    {
        vertexpos.x = 0.5 * Input.Scale.x;
        vertexpos.y = 0.5 * Input.Scale.y;
        Output.Color = cloud_color_top;
    }
    else if (Input.Normales.x == 3.0)
    {
        vertexpos.x = 0.5 * Input.Scale.x;
        vertexpos.y = -0.5 * Input.Scale.y;
        Output.Color = cloud_color_bottom;
    }
    else
    {
        vertexpos.x = -0.5 * Input.Scale.x;
        vertexpos.y = -0.5 * Input.Scale.y;
        Output.Color = cloud_color_bottom;
    }

    float4 xaxis;
    xaxis.x = 1;
    xaxis.y = 0;
    xaxis.z = 0;
    xaxis.w = 0;


    float4 yaxis;
    yaxis.x = 0;
    yaxis.y = 1;
    yaxis.z = 0;
    yaxis.w = 0;

    float theta_pos = 3.1415927 * (Input.Sphericals.y / 180.0);
    float phi_pos = 3.1415927 * (Input.Sphericals.z / 180.0);
    float ray_input = Input.Sphericals.x;

    float4x4 translation = 0.0;

    translation[0][0] = 1.0;
    translation[1][1] = 1.0;
    translation[2][2] = 1.0;
    translation[3][3] = 1.0;
    translation[3][0] = 0.0;
    translation[3][1] = ray_input;
    translation[3][2] = 0.0;

    float4x4 rotation_y = 0.0;
    
    rotation_y[0][0] = cos(theta_pos);
    rotation_y[1][1] = 1.0;
    rotation_y[2][2] = cos(theta_pos);
    rotation_y[3][3] = 1.0;
    rotation_y[3][0] = 0.0;
    rotation_y[3][1] = 0.0;
    rotation_y[3][2] = 0.0;
    rotation_y[2][0] = -sin(theta_pos);
    rotation_y[0][2] = sin(theta_pos);

    float4x4 rotation_x = 0.0;
    
    rotation_x[0][0] = 1.0;
    rotation_x[1][1] = cos(phi_pos);
    rotation_x[2][2] = cos(phi_pos);
    rotation_x[3][3] = 1.0;
    rotation_x[3][0] = 0.0;
    rotation_x[3][1] = 0.0;
    rotation_x[3][2] = 0.0;
    rotation_x[2][1] = sin(phi_pos);
    rotation_x[1][2] = -sin(phi_pos);

    float4x4 spherical;
    // todo completer avec les matrices rot de longitude et latitude
    spherical = mul(mul(translation, rotation_x), rotation_y);

    float4x4 local_trans = 0;

    local_trans[0][0] = 1.0;
    local_trans[1][1] = 1.0;
    local_trans[2][2] = 1.0;
    local_trans[3][3] = 1.0;

    local_trans[3][0] = Input.Pos.x;
    local_trans[3][1] = Input.Pos.y;
    local_trans[3][2] = Input.Pos.z;
    

    // les matrices de rot pour faire face a la camera

	// passer le point ( 0, 0, 0 ) du repere cam vers le repere world	
    float4 centerpos2 = mul(centerpos, matCam);

	// passer le point obtenu du repere world vers le repere local a l'impostor
    float4 centerpos3 = mul(centerpos2, InverseMatrix(mul(mul(local_trans, spherical), matWorld)));

	// il ne reste plus qu'� calculer theta et phi a partir du point obtenu (point 0 camera exprim� dans le repere local � l'impostor)

    float theta = atan2(centerpos3[0], centerpos3[2]);

    float4 theta_dir = centerpos3;
    theta_dir.y = 0;

    float phi = atan2(centerpos3[1], sqrt(theta_dir.x * theta_dir.x + theta_dir.y * theta_dir.y + theta_dir.z * theta_dir.z));
   
    float4x4 facecam_roty = BuildRotationMatrix(yaxis, theta);
    float4x4 facecam_rotx = BuildRotationMatrix(xaxis, -phi);



    float4 vpos = mul(mul(mul(vertexpos, mul(facecam_rotx, facecam_roty)), local_trans), spherical);
    
    if (flags.x > 0.0)
    {
        // calculer normale et position du plan de reflection
        float4 rn = normalize(viewer_pos);
        float4 rp = rn * flags.y;
        rp += planetPos;

        Output.Position = reflected_vertex_pos(vpos, rp, rn, matWorld, matView, matProj);
    }
    else
    {

        Output.Position = mul(vpos, matWorldViewProjection);
    }

    Output.TexCoord0 = Input.TexCoord0;

    //////////////////////////////////////////

    float4 PositionWV = mul(vpos, matWorldView);
    Output.Fog = clamp(0.0, 1.0, ComputeExp2Fog(PositionWV, flags.z));

    //////////////////////////////////////////

    // calcul normale globale correspondant a la pos du nuage

    float4 l_init = { 0.0, 1.0, 0.0, 1.0 };

    float4x4 worldnott = matWorld;
    worldnott[3][0] = 0.0;
    worldnott[3][1] = 0.0;
    worldnott[3][2] = 0.0;
   
    Output.Posdir = mul(mul(mul(l_init, rotation_x), rotation_y), worldnott);

    Output.PosCamSpace = PositionWV;

	return( Output );   
}
