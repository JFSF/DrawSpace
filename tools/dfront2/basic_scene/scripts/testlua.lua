
function globals()
        for n,v in pairs(_G) do
                print(n)
                end
        end


function print_vector( v )
	s = ""
	for i = 0, 3, 1 do
		s = s .. v:Get( i ) .. " "
	end
	print( s )
end

function print_matrix( m )

	for i = 0, 3, 1 do
		s = ""
		for j = 0, 3, 1 do
			s = s .. m:Get( i, j ) .. " "
		end
		print( s )
	end
end

print( "Lua version : " .. _VERSION )

ds = DrawSpace()
ds:DisplayFramerate( 1 )


ds:CreateSceneNodeGraph( "scene0" )

ds:DisplayCurrentCamera( "scene0", 1 )

tf0node = TransformationNode( "mytf0", 1 )
tf0node:LinkTo( "scene0", "scene0" )



tf2 = TransformationNode( "tf2", 2 )
tf2:LinkTo( "scene0", "scene0" )
tf2:LoadScript( "tf_transformnode.lua" )

mat = Matrix()
mat:Translation( 0, 1, -10 )
tf2:UpdateMatrix( 0, mat )

roty_axis = Vector( 0, 1, 0, 1 )

roty = Matrix()
roty:Rotation( roty_axis, 0 )
tf2:UpdateMatrix( 1, roty )


sb0 = SpaceboxNode( "sb0" )
sb0:RegisterPassSlot( "texture_pass" )
sb0:SetPassSlotFxName( "texture_pass", "spacebox_fx" )
sb0:SetPassSlotTextureName( "texture_pass", "texture_sb0", 0, 0 )
sb0:SetPassSlotTextureName( "texture_pass", "texture_sb2", 1, 0 )
sb0:SetPassSlotTextureName( "texture_pass", "texture_sb3", 2, 0 )
sb0:SetPassSlotTextureName( "texture_pass", "texture_sb1", 3, 0 )
sb0:SetPassSlotTextureName( "texture_pass", "texture_sb4", 4, 0 )
sb0:SetPassSlotTextureName( "texture_pass", "texture_shelby", 5, 0 )

sb0:AddPassSlotShaderParam( "texture_pass", "intensity", 1, 12, Vector( 1.0, -2.0, 3.0, -4.0 ) )
sb0:LinkTo( "scene0", "mytf0" )


cube0 = ChunkNode( "cube0" )
cube0:SetMesheName( "cube_meshe" )
cube0:RegisterPassSlot( "texture_pass" )
cube0:SetPassSlotFxName( "texture_pass", "texture_fx" )
cube0:SetPassSlotTextureName( "texture_pass", "texture_shelby", 0 )

cube0:LinkTo( "scene0", "tf2" )

localtf = TransformationNode( "localtf" )
localtf:LinkTo( "scene0", "cube0" )
mat2 = Matrix()
mat2:Translation( 0, 0, 3 )
localtf:AddMatrix( mat2 )

cube1 = ChunkNode( "cube1" )
cube1:SetMesheName( "cube_meshe" )
cube1:RegisterPassSlot( "texture_pass" )
cube1:SetPassSlotFxName( "texture_pass", "texture_fx" )
cube1:SetPassSlotTextureName( "texture_pass", "texture_sb0", 0 )

cube1:LinkTo( "scene0", "localtf" )




keyboard = Keyboard()
mouse = Mouse()

ds:LoadMouseScript( "mousehandler.lua" )
ds:LoadKeyUpScript( "keyuphandler.lua" )
ds:LoadKeyDownScript( "keydownhandler.lua" )

roty_angle = Real()
sb_scale = Matrix()
sb_scale:Scale( 25, 25, 25 )
tf0node:UpdateMatrix( 0, sb_scale )



fps0 = FpsMovementNode( "fps0" )
fps0:SetYMvt( 1 )
fps0:LinkTo( "scene0", "scene0" )



cam0 = CameraPointNode( "cam0" )
cam0:LinkTo( "scene0", "fps0" )

lin0 = LinearMovementNode( "lin0" )
lin0:SetInitpos( -5, 0, -4 )
lin0:SetDirection( 1, 0, 0 )
lin0:LinkTo( "scene0", "scene0" )

cube2 = ChunkNode( "cube2" )
cube2:SetMesheName( "cube_meshe" )
cube2:RegisterPassSlot( "texture_pass" )
cube2:SetPassSlotFxName( "texture_pass", "texture_fx" )
cube2:SetPassSlotTextureName( "texture_pass", "texture_sb0", 0 )

cube2:LinkTo( "scene0", "lin0" )

free0 = FreeMovementNode( "free0" )
free0:SetInitpos( 0, 0, 25 )
free0:LinkTo( "scene0", "scene0" )

cam1 = CameraPointNode( "cam1" )
cam1:LinkTo( "scene0", "free0" )

circ0 = CircularMovementNode( "circ0" )
circ0:SetCenterpos( 6, 0, -6 )
circ0:SetDeltaCenterpos( -2, 0, 0 )
circ0:SetAxis( 0, 1, 0 )
circ0:LinkTo( "scene0", "scene0" )


cube3 = ChunkNode( "cube3" )
cube3:SetMesheName( "cube_meshe" )
cube3:RegisterPassSlot( "texture_pass" )
cube3:SetPassSlotFxName( "texture_pass", "texture_fx" )
cube3:SetPassSlotTextureName( "texture_pass", "texture_sb1", 0 )

cube3:LinkTo( "scene0", "circ0" )


