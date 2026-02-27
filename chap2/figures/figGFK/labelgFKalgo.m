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
function [] = labelgFKPhi(A1,Cu,C1,ngs)
%[] = labelgFKPhi(A1,Cu,C1,ngs) Summary of this function goes here
%   Detailed explanation goes here
sz = size(A1);
K = 1:sz(1);
col = 3;
phi = -Cu(ngs,col)-90; theta = (-C1(:,col) - phi )*pi/180;
s = [num2str(-Cu(ngs,col),3)]; 
sd = [num2str(-Cu(4,col),3) '^o'];
% col 3
subplot(222);polarplot(theta,A1(:,col),'-o','MarkerSize',4,...
    'MarkerFaceColor','r');
s1 = ['$\varphi$ ='  s '$^o$ at gFK peak'];
%s1 = ['$\varphi$ ='  s '$^o$ col ' num2str(col) ' of $\bf{A}$'];
subtitle(s1,"Position",...
       [270,1.4],"HorizontalAlignment",...
       "center",'color','black','interpreter', 'latex')
thetaticks([0 -Cu(4,col)-phi 180]);
thetaticklabels({'',sd,''});
rticks([0.8 1]); rticklabels({'',''})
title('$J-\varphi$ plane','interpreter', 'latex');
% draw arrow
tha =[0 -Cu(ngs,col)-phi]; ra =[0 mean(max(A1))*1.2];
[xaf yaf] = polarDS2nfu(tha*pi/180,ra);
annotation('arrow',xaf,yaf,'color','blue');
% draw text arrow for start
tha =[-50 -Cu(1,col)-phi]; ra =[0.3 A1(ngs,col)];
[xaf yaf] = polarDS2nfu(tha*pi/180,ra);
hT = annotation('textarrow',xaf,yaf,'String',...
    ['start'],'color',...
    'blue','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';




% convergence
subplot(221); plot(K,Cu);grid;
title('$\varphi$ at gFK peak of ${\bf{A}}$','interpreter', 'latex');
xlabel('gFK iteration ','interpreter', 'latex');
ylabel('$\varphi_{1,2,3,4}$','interpreter', 'latex');
xa = [K(ngs-9) K(ngs-5)]; 
ya = [-Cu(ngs-5,4)*2 Cu(ngs-5,4)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['$\varphi$ =(' num2str(-Cu(ngs-5,:),3) ')$^o$'],'color',...
    'blue','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end