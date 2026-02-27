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
function [A1 A2] = svdA(A,x_val,y_val,N)
%svdA(A,x_val,y_val,N) Summary of this function goes here
%   Detailed explanation goes here
% error circle
[Theta R,yp] = A2ThetaR(A,x_val,y_val,N);
phat=inv(A'*A)*A'*yp;
ek=A*phat-yp; sigma=std(ek);

theta=linspace(0,2*pi,N);
x=phat(1)-sigma*cos(theta);
y=phat(2)-sigma*sin(theta);
th = atan2(y,x); r = sqrt(x.*x + y.*y);
rHat = sqrt(phat(1)*phat(1) + phat(2)*phat(2));
thHat = atan2(phat(2),phat(1));
%...................

[u s v] = svd(A,"econ"); L = diag(s);
b = 1; e = 2;
u1 = u(:,b); v1 = v(:,b);
A1 = L(1)*u1*v1';
u2 = u(:,e); v2 = v(:,e);
A2 = L(2)*u2*v2';

[Theta1 R1,y] = A2ThetaR(A1,x_val,y_val,N);
[Theta2 R2,y] = A2ThetaR(A2,x_val,y_val,N);
rVal = sqrt(x_val*x_val + y_val*y_val);
thVal = atan2(y_val,x_val);
figure(1)
polarplot(th,r,'-.r',Theta1,R1,'.',Theta2,R2,'.',thVal,rVal,'o',...
    'MarkerFaceColor','r'); hold on;
polarplot(thHat,rHat,'o','MarkerFaceColor','b'); hold off;
s1 = strMat(A); s2 = strMat(A1);
s3 = strMat(A2);
rmax =rlim;
text(205*pi/180,0.9*rmax(2),[s1 '=' s2 '+' s3],...
    'interpreter','latex');
%subtitle(['${\bf{A}}={\bf{A}}_1+{\bf{A}}_2$'],"Position",...
%        [270,rmax(2)*1.2],"HorizontalAlignment",...
%        "center",'color','black','interpreter', 'latex')
thetaticks([0 90 180]);
thetaticklabels({'x_1','x_2','-x_1'});
rticks([5 10]);
% A2 matrix
tha = [78 102]; ra =[11.9 11.9];
[xaf yaf] = polarDS2nfu(tha*pi/180,ra);
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            ['${\bf{A}}_2$ '],'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';
% A1 matrix
tha = [154 133]; ra =[11 11];
[xaf yaf] = polarDS2nfu(tha*pi/180,ra);
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            ['${\bf{A}}_1$ '],'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';
tha = [154 154]; ra =[11 8.17];
[xaf yaf] = polarDS2nfu(tha*pi/180,ra);
hT = annotation('arrow',xaf,yaf,'color','blue','LineStyle','-.');      

tha = [154 137]; ra =[11 10.2];
[xaf yaf] = polarDS2nfu(tha*pi/180,ra);
hT = annotation('arrow',xaf,yaf,'color','blue','LineStyle','-.');

% phat
s1 = ['$\hat{\bf{p}}$ (' num2str(phat(1),3) ',' num2str(phat(2),3) ')'];
tha = [0.8*thHat thHat]; ra =[rHat rHat];
[xaf yaf] = polarDS2nfu(tha,ra);
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            s1,'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';
% p
s1 = ['${\bf{p}}$ (' num2str(x_val,3) ',' num2str(y_val,3) ')'];
tha = [1.2*thVal thVal]; ra =[rVal rVal];
[xaf yaf] = polarDS2nfu(tha,ra);
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            s1,'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';
            

end