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
clear all;close all;
%row_max=8;
%A=fix((rand([row_max 2])-0.5)*20);
load adata;
N = 50;
x_val=-5;y_val=7;
[ypA phat] = linRegA(A,x_val,y_val,N);

% zoom show lines
B = A(6:8,:); ypB = ypA(6:8);
[Theta R,yp] = A2ThetaR(B,x_val,y_val,N);
X = R.*cos(Theta); Y = R.*sin(Theta);
X = X-x_val; Y = Y-y_val;
R = sqrt(X.*X + Y.*Y); Theta = atan2(Y,X);
%rVal = sqrt(x_val*x_val + y_val*y_val);
%thVal = atan2(y_val,x_val);
figure(2)
polarplot(Theta(:,1),R(:,1),'.-r',Theta(:,2),R(:,2),'.-b',...
    Theta(:,3),R(:,3),'.-k',0,0,...
    'o','MarkerFaceColor','r'); 
rticks([1 2]);
rticklabels({'',''})
thetaticks([0 90 180]);
thetaticklabels({'x_1','x_2','-x_1'});
s1 = strMat(B); s2 = strMat(ypB);
text(260*pi/180,2.2,'${\bf{A(6:8)}}$','interpreter','latex');
text(218*pi/180,2.1,[s1 ' $\pmatrix{x_1 \cr x_2}$ =' s2],...
    'interpreter','latex');
% p
tha = [120*pi/180 0]; ra =[2 0];
[xaf yaf] = polarDS2nfu(tha,ra);
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            ['${\bf{p}}=$ (' num2str(x_val,3) ',' ...
            num2str(y_val,3) ')'],'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';


