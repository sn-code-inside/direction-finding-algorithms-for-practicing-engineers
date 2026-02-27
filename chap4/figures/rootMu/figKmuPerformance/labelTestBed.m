% Author: Kaluri V. Ranga Rao
% Visiting Scholar, Department of Computer Science,
% The Ohio State University
%
% Copyright (c) 2025 Kaluri V. Ranga Rao
% All rights reserved.
%
% This code is part of the material for the book:
% "Direction Finding Algorithms for Practicing Engineers,"
% published by Springer Nature.
%
% This material is intended for academic and research purposes only.
function [] = labelTestBed(table)
%labelTestBed(X,Y,stX,stY,x,y) Summary of this function goes here
%   Detailed explanation goes here
theta = table(:,2); r = table(:,1);
rHat  = table(:,4); thetaHat = table(:,5);
xrdr = rHat.*sind(thetaHat); yrdr = rHat.*cosd(thetaHat);
comnt = [' Tested using Ti AFE with internal processor '];
%%%%%%
X = r(1:7).*sind(theta(1:7)); Y = r(1:7).*cosd(theta(1:7));
p = polyfit(X,Y,1);
x = linspace(X(1),X(7),100);
y = x*p(1) + p(2);
stX = r(8)*sind(theta(8)); stY = r(8)*cosd(theta(8));

figure(4)
plot(X,Y,'o','MarkerSize', 6,'MarkerFaceColor','r');grid;
hold on;
plot(stX,stY,'s','MarkerSize', 8,'MarkerFaceColor','b'); 
hold off;
hold on;
plot(x,y,'-.b',100,200,xrdr,yrdr,'k^',[-40],[205],'.'); 
hold off;
hold on
plot(0,0,'o','MarkerSize', 4,'MarkerFaceColor','b');
hold off;
xlabel(' Centimeters ' ,'interpreter','latex'); 
ylabel(' Centimeters ' ,'interpreter','latex'); 
title(comnt,'interpreter','latex');
Ax = gca;
Ax.XAxis.TickLabelInterpreter = 'latex';
Ax.YAxis.TickLabelInterpreter = 'latex';
for k=4:6
xa = [0 X(k)]; ya = [0 Y(k)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
annotation('arrow',xaf,yaf,'color','black','linestyle','-.');    
end
xa = [-20 stX]; 
ya = [40 stY];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
annotation('textarrow',xaf,yaf,'color','red','linestyle','-.','string','reference');
% insert image
bounds = axis;
boxa = [35 0 80 80]; boxb = dsxy2figxy(boxa);
axes('pos',boxb)
imshow('cr3.jpg')

end