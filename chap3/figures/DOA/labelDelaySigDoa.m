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
function [] = labelDelaySigDoa(x1,x2,t,tow,SNR,N,thetak,thetaEstk,pw)
%labelDelaySig(x1,x2,t,xf,tow,SNR,N) Summary of this function goes here
%   Detailed explanation goes here
[x1m,ind] = max(x1); [x2m,indB] = max(x2);
figure(1);
subplot(311); plot(t,x1,'.-r',t,x2,'.-b');grid;
s =['$\theta=$' num2str(thetak,3) ...
    '$^\circ$ Delayed Signals $x^A_k$ and $x^B_k$ by ' ... 
    num2str(tow,3) ' Cycles (' num2str(tow*N,3) ...
    ' samples) $\hat\theta=$' num2str(thetaEstk,3) '$^\circ$'];
title(s,'interpreter','latex');
%xlabel('$k$ sample number','interpreter','latex');
ylabel('$x^A_k,x^B_k$','interpreter','latex');
xtic = sort([100 200 300 400 indB ind 500 600 700 800 900]);
xticks(xtic);
xticklabels({'100','200','k=300','','\Delta',num2str(ind-indB),'','k=600','700','800','900'});

%.... xA
[x1m,ind] = max(x1);
xa =[t(ind+100) t(ind)]; ya = [0.8*x1m x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','$x^A_k$ reference','color','red',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... xB
[x2m,indB] = max(x2);
xa =[t(indB-120) t(indB)]; ya = [0.7*x2m x2m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',['$x^B_k$ '],'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... SNR
x1m = 0; ind=700;
xa =[t(ind+100) t(ind)]; ya = [0.5 x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['SNR ' num2str(SNR,3) 'dB'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... Samples Cycle
[x2m,ind] = min(x2);
xa =[t(ind-100) t(ind)]; ya = [-0.5 x2m*0.6];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['N=' num2str(N,3) ' Samples/Cycle'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... Pulse Width
[x1m,ind] = min(x1);
xa =[t(ind+100) t(ind)]; ya = [-0.5 x2m*0.6];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['pulse width ' num2str(pw,3) ' Cycles'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% figure(2);
% s=indB-50; e = indB+50;
% tSe = t(s:e); x2Se = x2(s:e); xfSe = xf(s:e); 
% subplot(311);plot(tSe,x2Se,'.-b',tSe,xfSe,'.-k');grid;
% xticks([400 420 440 460 480]);
% xticklabels({'k=400','420','440','460','k=480'});
% %.... xf
% [xfm,indC] = max(xfSe);
% xa =[tSe(indC+20) tSe(indC)]; ya = [xfm xfm];
% [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
% hT = annotation('textarrow',xaf,yaf,'String',['$x^f_k$ '],'color','blue',...
%     'LineStyle','-.','interpreter', 'latex');
% hT.TextBackgroundColor = 'yellow';
% %.... xB
% [x2m,indB] = max(x2Se);
% xa =[tSe(indB-20) tSe(indB)]; ya = [x2m x2m];
% [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
% hT = annotation('textarrow',xaf,yaf,'String',['$x^B_k$ '],'color','blue',...
%     'LineStyle','-.','interpreter', 'latex');
% hT.TextBackgroundColor = 'yellow';
% end