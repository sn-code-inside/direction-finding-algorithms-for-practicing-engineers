function [] = polarLabel(name)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
load D.csv
x = D(:,6); y = D(:,7);
r = sqrt(x.*x +y.*y); phi = atan2(x,y)+pi/2;
polarplot(phi,r,'b^');
Ax = gca;
Ax.RAxis.TickLabelInterpreter = 'latex';
Ax.ThetaAxis.TickLabelInterpreter = 'latex';
thetaticks([0 30 60 120 150 180]);
thetaticklabels({'$90^\circ$','$60^\circ$','$30^\circ$',...
    '$-30^\circ$','$-60^\circ$','$-90^\circ$'});
load C.csv
R = C(:,1); Phi = C(:,2)*pi/180 + pi/2;
hold on;
polarplot(Phi,R,'c.');
hold off;
sz = rlim;
subtitle(name,"Position",[270,sz(2)*1.2],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex');

% vertical arrow bore axis
xa =[pi/2 pi/2]; ya =[0 sz(2)*1.1];
[xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','Bore Axis','color',...
    'black','interpreter', 'latex','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% centroid annotation
[th i] = min(Phi);
xa =[0.6*pi Phi(i)]; ya = [ -0.4*sz(2) R(i) ];
[xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String','Centroid of  Moving Object using ${\bf{S}}(t)$','color','black');
hT.TextBackgroundColor = 'yellow';
end