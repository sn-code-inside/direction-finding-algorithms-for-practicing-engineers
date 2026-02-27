function [] = xLabel(kmax,indA,indx)
%[] = xLabel(kmax,indA,indx) Summary of this function goes here
%   Detailed explanation goes here
xc = kmax*1.3; yc = 0;
xa = [kmax xc];
ya = [yc  yc];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('arrow',xaf,yaf,'color','red','LineStyle','-.'); 
text(xc*0.91,-2,[' time '],'interpreter','latex','color','black');
xc = (indA(3)+indx(3))*0.5;
end