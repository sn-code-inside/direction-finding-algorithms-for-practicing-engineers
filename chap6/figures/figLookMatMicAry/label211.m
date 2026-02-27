function [] = label211(muSpk,fs,B,dbyl,doa,pSnap,blocks,tgt)
%[] = label211(muSpk,fs,B,dbyl) 
%   Summary of this function goes here
%   Detailed explanation goes here
lambda = 34.3; d=3.8;
u = B(:,1);
delt = 1/fs; phimax = dbyl*360;
numberOfSamples = length(muSpk); 
phi = linspace(-180,180,numberOfSamples);
indA = find(phi > phimax); e1 = indA(1);
indB = find(phi > -phimax); s1 = indB(1);
phiL = max([phi(s1) phi(e1)]);
phiPeak = phimax*sind(doa);
X =[phiPeak phiPeak]; Y = [0 max(muSpk)];

figure(1);
subplot(211);plot(phi(1:s1),muSpk(1:s1),'.-r', ...
phi(s1:e1),muSpk(s1:e1),'.-b', ...
phi(e1:numberOfSamples),muSpk(e1:numberOfSamples),'.-r', ...
phi(s1), muSpk(s1),'ok',phi(e1), muSpk(e1),'ok',X,Y,'.-r'); 
grid;

xlabel(' $\varphi$ ','interpreter','latex'); 
ylabel('$J(\varphi)$','interpreter','latex');
title(['6 ULA g-MUSIC Spectrum for ${\bf{S}}_{k=' num2str(pSnap) '}$'],...
    'interpreter','latex' );
xticks([-150 -100  -41 0 41 100 150]);
xticklabels({'-150^o','-100^o','-41^o','0^o',...
   '41^o','100^o','150^o'});
text(41,1,['$\lambda=$' num2str(lambda) 'cm $d$ = ' num2str(d) 'cm'],...
    'Interpreter','latex');
% arrow for available phase
xa(2) = phi(s1+5);   xa(1) =2*xa(2);
ya(2) = muSpk(s1+5); ya(1) =0.8*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ... 
['$J(\varphi)$ range $\pm 360(\frac{d}{\lambda}) \pm$' num2str(phiL,2) '$^o$'],...
'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% arrow for gFK phase
xa(2) = phiPeak;   xa(1) = -60;
ya(2) = 0.3; ya(1) = 0.3;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ... 
['gMUSIC $\varphi$ = ' num2str(phiPeak,4) '$^o$ '],...
'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% .. position image 
axes('pos',[.01 .72 1.48 .16]); %lower left corner (0.065 0.65) and width and height (1.4,0.27)
imshow('ulaAu6.jpg');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(212);plot(blocks,tgt,'-.r',...
    blocks(pSnap),tgt(pSnap),'ob',blocks(pSnap),tgt(pSnap),'+r');grid;
title([' Tracking of Audio Target $\frac{d}{\lambda}= $' ... 
    num2str(dbyl)],'interpreter','latex');
ylabel(' DOA $\theta$','interpreter','latex');
xlabel(' index of {\em look} Matrix ${\bf{S}}_k$ ', 'interpreter','latex');
xticks([100 300 500 700 825 900]);
xticklabels({'k=100','300','500','700','k=825','900'});
yticks([-40 0 20])
yticklabels({'-40^o','0^o','20^o'});
% arrow for Audio
sig = std(tgt(425:525)); 
xa(2) = blocks(400);   xa(1) = blocks(500);
ya(2) = tgt(400); ya(1) = tgt(250);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ... 
[' Audio Target $\sigma = $' num2str(sig,3) '$^o$'],...
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






end