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
clc; clear all;
close all;
fs = 16000; p = 1; samples = 256;
delt = 1/fs; pSnap = 100;
maxk = 55; blockCt = 1;
D = 1; dbyl = 0.11; phimax = dbyl*360;

for i = 1:15
file =['ula' num2str(i)]; cmd = ['load ' file ];
eval(cmd);
% .................
s = 1; 
for k=1:maxk
e = s + 255;    
x = Data(s:e,:);
%A = Ar2Ai(x); 
B = hilbert(x);
%[muSpk doa En SNR] = gMusik(D,dbyl,A);
[muSpk, doa, En, SNR] = gMusik(D,dbyl,B);
tgt(p) = doa;  u = B(:,1);
if ( p == pSnap ) 
    label321(samples,fs,B,dbyl); 
    label211(muSpk,fs,B,dbyl,doa);
    [theta,muSpkClamp] = labelPolar(muSpk,fs,B,dbyl,doa);
    doap = doa;
end
s = e + 1; p = p + 1;
end
blocks =1:p-1;
%X=[p-1 p-1]; Y = [0 tgt(p-1)];
%xa(:,blockCt) = X;
%ya(:,blockCt) = Y;
%blockCt = blockCt + 1;
end
subplot(212);plot(blocks,tgt,'-.r',...
    blocks(pSnap),tgt(pSnap),'ob',blocks(pSnap),tgt(pSnap),'+r');grid;
title(' Tracking of Audio Target','interpreter','latex');
ylabel(' DOA $\theta$','interpreter','latex');
xlabel(' index of {\em look} Matrix ${\bf{S}}_k$ ', 'interpreter','latex');
xticks([100 300 500 700 825 900]);
xticklabels({'k=100','300','500','700','k=825','900'});
yticks([-40 0 20])
yticklabels({'-40^o','0^o','20^o'});
% arrow for Audio
xa(2) = blocks(400);   xa(1) = blocks(500);
ya(2) = tgt(400); ya(1) = tgt(250);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ... 
[' Audio Target '],...
'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% arrow for DOA
xa(2) = blocks(pSnap);   xa(1) = blocks(pSnap+50);
ya(2) = tgt(pSnap); ya(1) = tgt(400);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ... 
[' $\hat\theta$ = ' num2str(tgt(pSnap),4) '$^o$'],...
'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% Polar Audio Beam
figure(3)
max2 = max(muSpkClamp);
thA =[doap doap]*pi/180; rA =[0 max2];
h = polarplot(-theta*pi/180+pi/2,muSpkClamp,'.-r',-thA+pi/2,rA,'-ob');
title('Audio Beam for {\em look} Matrix ${\bf{S}}_{k=100}$',...
    'interpreter', 'latex');
s1 =[' 6 Microphones with $\frac{d}{\lambda}$ =' num2str(dbyl)];
subtitle(s1,"Position",[270,1.4],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex')
thetaticks([0 30 60 90 120 150 180]);
thetaticklabels({'90^o','60^o','30^o','0^o','-30^o','-60^o','-90^o'});
%text(-150*pi/180,0.8,'Audio Beam for {\em look} Matrix ${{S}}_{k=100}$','interpreter', 'latex');
% Arrow at Peak
tha = [-doap*0.5 doap]; ra =[0.8*max2 max2];
[xaf yaf] = polarDS2nfu(-tha*pi/180+pi/2,ra);
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
    ['$\hat\theta = $ ' num2str(doap,4) '$^o$'],'color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
set(h, {'MarkerFaceColor'}, get(h,'Color'));



