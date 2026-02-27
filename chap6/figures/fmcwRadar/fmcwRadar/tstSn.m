clc; clear all;
close all;
blocks = 10;
file = 'car-car-bike.txt'
for k=0:40
[D S] = getScene(file,k,blocks);
    if (D<0) break; 
    else 
        S
        D
%        r = S(:,1); 
%        phi = S(:,2);  
%        sig = S(:,3); 
%        delph = S(:,4); 
%        quiver(r.*sind(phi),r.*cosd(phi),sig.*sind(delph),sig.*cosd(delph));
%        hold on; polarplot(phi*pi/180,r,'.','markersize',20*sig); hold off;
pause
    end;
end
