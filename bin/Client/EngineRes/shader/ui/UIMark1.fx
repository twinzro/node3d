technique Render
{
    pass P0
    {
		CullMode			= None;
		
		AlphaTestEnable		= True;
		AlphaFunc			= GreaterEqual;
		AlphaRef			= 64;
		
		AlphaBlendEnable	= TRUE;
		BlendOp				= Add;
		SrcBlend			= ZERO;
		DestBlend			= ONE;

		ZEnable				= True;
		ZWriteEnable		= True;

		ColorOp[0]			= Modulate;
		ColorArg1[0]		= Texture;
		ColorArg2[0]		= Diffuse;

		AlphaOp[0]			= Modulate;
		AlphaArg1[0]		= Texture;
		AlphaArg2[0]		= Diffuse;

		ColorOp[1]			= Disable;
		AlphaOP[1]			= Disable;
		
		VertexShader		= NULL;
        PixelShader			= NULL;
    }
}