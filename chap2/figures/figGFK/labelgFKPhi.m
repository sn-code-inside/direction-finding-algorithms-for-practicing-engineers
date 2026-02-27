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
s1 = ['$\varphi_1$ =' num2str(-Cu(ngs,1),3) '$^o$ col 1 of $\bf{A}$'];
subplot(221);polarplot(-C1(:,1)*pi/180,A1(:,1),'-o','MarkerSize',4,...
    'MarkerFaceColor','b');
subtitle(s1,"Position",...
       [270,1.4],"HorizontalAlignment",...
       "center",'color','black','interpreter', 'latex')
thetaticks([0 90 180]);
thetaticklabels({'0^o','90^o','180^o'});
rticks([0.8 1]);
tha =[0 Cu(ngs,1)]; ra =[0 mean(max(A1))];
[xaf yaf] = polarDS2nfu(tha*pi/180,ra);
annotation('arrow',xaf,yaf,'color','red');

subplot(222);polarplot(-C1(:,4)*pi/180,A1(:,4),'-o','MarkerSize',4,...
    'MarkerFaceColor','r');
s1 = ['$\varphi_4$ =' num2str(-Cu(ngs,4),3) '$^o$ col 4 of $\bf{A}$'];
%s1 = [' $\varphi_4$ col 4 of $\bf{A}$ ' num2str(Cu(ngs,4),3) '$^o$'];
subtitle(s1,"Position",...
       [270,1.4],"HorizontalAlignment",...
       "center",'color','black','interpreter', 'latex')
thetaticks([0 90 180]);
thetaticklabels({'0^o','90^o','180^o'});
rticks([0.8 1]);
tha =[0 -Cu(ngs,4)]; ra =[0 mean(max(A1))];
[xaf yaf] = polarDS2nfu(tha*pi/180,ra);
annotation('arrow',xaf,yaf,'color','blue');

% subplot(413); plot(K,Cu);grid;
% xlabel('gFK iteration ','interpreter', 'latex');
% ylabel('$\varphi_{1,2,3,4}$','interpreter', 'latex');
% xa = [K(ngs-9) K(ngs-5)]; 
% ya = [-Cu(ngs-5,4)*2 Cu(ngs-5,4)];
% [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
% hT = annotation('textarrow',xaf,yaf,'String',...
%     ['$\varphi$ =(' num2str(-Cu(ngs-5,:),3) ')$^o$'],'color',...
%     'blue','LineStyle','-.','interpreter', 'latex');
% hT.TextBackgroundColor = 'yellow';
end