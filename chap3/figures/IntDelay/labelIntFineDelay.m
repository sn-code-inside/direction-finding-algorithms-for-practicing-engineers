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
function [] = labelIntFineDelay(wData,N,flag,shift,z,JkR,par)
%[] = labelIntFineDelay(wData,control,detect,Tau,N) Summary of this function goes here
%   Detailed explanation goes here
lead = par(7); detect = par(8:13); Tau = par(4);
rFine = par(5); towF = par(3); tow = par(2);
t = wData(1,:); x1 = wData(2,:); x2 = wData(3,:);
% orthognal detection
temp=sort(detect); wD = temp(3:6);
LenJk = length(JkR);

figure(2);
subplot(311); plot(t,x1,'.-b',t,x2,'.-r');grid;
hold on; plot(t,shift,'o-b','markersize',4); hold off

xticks([wD(1) wD(1)+100 wD(2) wD(3) wD(4)]);
s = ['Lead ' num2str(lead,2) ' intger delay $\hat{\tau}_c $ ' num2str(tow,3) ];
s1 = ['  total delay $\hat{\tau}$ ' num2str((tow-towF)*lead,3) ...
    ' actual delay $\tau$ ',num2str(Tau,3) ' samples'];
title([s s1],'interpreter','latex');
ylabel('Amplitude','interpreter','latex');
%.... coarse Shift wave
[mSh ind] = max(shift);
xa =[t(ind+25) t(ind)]; ya = [0.7*mSh mSh];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['shifted by ' num2str(tow,3) ' $\tilde{x}^B_k$ '];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... xB
[x1m,indB] = max(x1);
xa =[t(indB-40) t(indB)]; ya = [0.7*x1m x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',['$x^B_k$ '],'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... xA
[x2m,indA] = min(x2);
xa =[t(indA+40) t(indA)]; ya = [0.7*x2m x2m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',['$x^A_k$ '],'color','red',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


if (flag == 1)
xtik = [-1 rFine 1]; 
s2 =['pole position $r$'];
rSweep = linspace(-0.95,0.95,LenJk);
else 
    xtik = [0 rFine 360];
    s2 =['phase angle $\varphi^\circ$'];
    rSweep = linspace(5,350,LenJk);
end;

figure(3);
subplot(221); plot(t,shift,'.-b');grid; hold on;
plot(t,z,'-or','MarkerFaceColor','r','markersize',3); hold off;
s = ['frac delay $\hat{\tau}_f $' num2str(towF,3) ' samples'];
title(s,'interpreter','latex');
[mz ind] = min(z); [mS indS] = max(shift);
xticks([t(indS)-100 t(indS) t(indS)+100]);
xlabel('sample $k$','interpreter','latex');
ylabel('Amplitude','interpreter','latex');
%.... coarse Shift wave
xa =[t(indS-20) t(indS)]; ya = [0.7*mS mS];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['shift $\hat{\tau}_c $ ' num2str(tow,3) ' $\tilde{x}^B_k$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... Fine Shift wave
xa =[t(ind-20) t(ind)]; ya = [0.7*mz mz];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['shift $\hat{\tau}_f $' num2str(towF,3) ' $x^\varphi_k$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','red',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% angle
angle = 360*towF/N;
% ...
[mJk ind] = min(JkR);
subplot(222);plot(rSweep,JkR,'.-k');grid
title(['phase $\varphi$ ' num2str(angle,3) '$^\circ$'], 'interpreter','latex');
xlabel(s2,'interpreter','latex');
xticks(xtik);


ylabel('$J_M(r)$','interpreter','latex');
yticks([min(JkR) 0.5*max(JkR) 0.9*max(JkR)]);hold on;
plot(rSweep(ind),mJk,'or','MarkerFaceColor','r','markersize',4); hold off;
%.... gold Minima

indN = ind-7; if (indN < 1) indN = ind+10; end;
xa =[rSweep(indN) rSweep(ind)]; ya = [3*mJk mJk];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['gold minima ' num2str(rFine,3)];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','red',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end