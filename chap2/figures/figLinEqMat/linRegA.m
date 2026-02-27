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
function [yp,phat] = linRegA(A,x_val,y_val,N)
%[p] = linRegA(A,x_val,y_val,N) Summary of this function goes here
%   Detailed explanation goes here
% Ap = yp
[Theta R,yp] = A2ThetaR(A,x_val,y_val,N);
phat=inv(A'*A)*A'*yp;
ek=A*phat-yp; sigma=std(ek);
rHat = sqrt(phat(1)*phat(1) + phat(2)*phat(2));
thHat = atan2(phat(2),phat(1));

theta=linspace(0,2*pi,N);
x=phat(1)-sigma*cos(theta);
y=phat(2)-sigma*sin(theta);
th = atan2(y,x); r = sqrt(x.*x + y.*y);

rVal = sqrt(x_val*x_val + y_val*y_val);
thVal = atan2(y_val,x_val);

figure(1)
polarplot(th,r,'-.r',Theta,R,'.',thVal,rVal,'o','MarkerFaceColor','r'); hold on;
polarplot(thHat,rHat,'o','MarkerFaceColor','b'); hold off;
s1 = strMat(A); s2 = strMat(yp);
rmax =rlim;
text(145*pi/180,11,'${\bf{A}}$','interpreter','latex');
text(218*pi/180,0.7*rmax(2),[s1 ' $\pmatrix{x_1 \cr x_2}$ =' s2],...
    'interpreter','latex');
%text(-113*pi/180,11.8,'${\bf{A}}$','interpreter','latex');
%text(-90*pi/180,7.5,'${\bf{p}}$','interpreter','latex');
%text(-67*pi/180,11.8,'${\bf{y}}$','interpreter','latex');
%subtitle(['${\bf{A}}\times{\bf{p}}={\bf{y}}$'],"Position",...
%        [270,rmax(2)*1.2],"HorizontalAlignment",...
%        "center",'color','black','interpreter', 'latex')
thetaticks([0 90 180]);
thetaticklabels({'x_1','x_2','-x_1'});
rticks([5 10]);
% phat
tha = [1.1*thHat thHat]; ra =[5 rHat];
[xaf yaf] = polarDS2nfu(tha,ra);
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            ['$\hat{\bf{p}}=$ (' num2str(phat(1),3) ',' ...
            num2str(phat(2),3) ')'],'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';
% p
tha = [0.8*thVal thVal]; ra =[11 rVal];
[xaf yaf] = polarDS2nfu(tha,ra);
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            ['${\bf{p}}=$ (' num2str(x_val,3) ',' ...
            num2str(y_val,3) ')'],'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';
            


end