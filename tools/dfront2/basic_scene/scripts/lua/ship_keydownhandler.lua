-- print( "key down : " .. keyboard:GetLastKeydownCode() )
if ds:IsCurrentCamera( "scene0", cam0 ) > 0 then
 
  if keyboard:GetLastKeydownCode() == 81 then
    fps0:SetSpeed( 300.0 )
  elseif keyboard:GetLastKeydownCode() == 87 then
    fps0:SetSpeed( -300.0 )
  end
  
end