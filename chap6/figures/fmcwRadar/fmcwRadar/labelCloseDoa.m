function [] = labelCloseDoa(A,spk,rd,clouds,rg)
%[] = labelCloseDoa(A,spk,rd) Summary of this function goes here
%   Detailed explanation goes here
Ar = real(A); Ai = imag(A);
K = 1:rd; fn = linspace(0,1,rd);
figure;
subplot(211); plot(K,Ar,K,Ai);
title('Temporal and Spatial Sampled Raw Data');
ylabel('Amplitude');
grid;
% fig number
%text(6,310,'\fbox{a}','Interpreter','latex','BackgroundColor','black','Color','white');
% 1.
xa =[max(K)*1.1 max(K) ]; ya = [ 0 0 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','A');
hT.TextBackgroundColor = 'yellow';
% 2.
xa =[max(K)*0.42 max(K)*0.42 ]; ya = [ -400 -1000 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','gFK');
hT.TextBackgroundColor = 'yellow';
% 3.
%xa =[max(K)*0.65 max(K)*0.65 ]; ya = [ -100 -750 ];
xa =[max(K)*0.73 max(K)*0.73 ]; ya = [ -100 -750 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','Raw Data');
hT.TextBackgroundColor = 'yellow';
% 3a.
xa =[max(K)*0.65 max(K)*0.46 ]; ya = [ -120 -300 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf);
hT.TextBackgroundColor = 'yellow';
% 4.
xa =[max(K)*0.79 max(K)*0.87 ]; ya = [ -850 -850 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','\kappa MUSIC');
hT.TextBackgroundColor = 'yellow';

% 5.
xa =[max(K)*0.89 max(K)*0.9 ]; ya = [ -900 -1300 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String','$\varphi$');
hT.TextBackgroundColor = 'yellow';

subplot(223); 
plot(fn,spk);grid
title('Fourier Spectrum'); ylabel('Amplitude');
xlabel('Normalized Frequency');
% fig number
%text(0.025,0.9,'\fbox{b}','Interpreter','latex','BackgroundColor','black','Color','white');
%text(2.1,0.9,'\fbox{c}','Interpreter','latex','BackgroundColor','black','Color','white');

% 6.
[smax ind] = max(spk);
xa =[fn(ind)*1.25 fn(ind)]; ya = [ 0.8*smax smax ]; %
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
%hT = annotation('textarrow',xaf,yaf,'String','amplitude q');
hT = annotation('textarrow',xaf,yaf,'FontSize',12,'Interpreter','latex','String','Amplitude $q$');
hT.TextBackgroundColor = 'yellow';
% 7.
xa =[fn(ind)*1.15 1.1]; ya = [ 0.4 0.4 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf);
text(fn(ind)*0.9,ya(1),'$f_p$','FontSize',14,'Interpreter','latex','BackgroundColor','yellow');
%7a
xa =[1.1 1.62]; ya = [ 0.4 0.4 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'FontSize',14,'Interpreter','latex','String','$r_g$');
hT.TextBackgroundColor = 'yellow';
%7b
xa =[fn(ind) fn(ind)]; ya = [ 0.3 0 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
annotation('textarrow',xaf,yaf);
% ....... next sub figure
h = subplot(224);
[cir,vec] = rgDoa(clouds(1,7),clouds(1,8));
[cir1,vec1] = rgDoa(clouds(2,7),clouds(2,8));
vec0 = [vec vec1];
cir0 = [cir cir1];
polarplot(cir0,vec0,[pi/2 pi/2],[0 20],'.-r');
thetaticks([0 30 60 120 150 180]);
thetaticklabels({'90^o','60^o','30^o','-30^o','-60^o','-90^o'});
rticks([10 15]);
%polar(cir0,vec0);grid; hold on;
%polar([pi/2 pi/2],[0 20],'.-r');
%hold off;
%T = findall(h, 'type', 'text'); % find all text
%delete(T); % delete text
s1 =['$x=r\cos(\varphi)~~y=r\sin(\varphi)$'];
subtitle(s1,"Position",[270,28],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex')
%text(-25,-25,'$x=r\cos(\varphi)~~y=r\sin(\varphi)$','Interpreter','latex','BackgroundColor','yellow');
% fig number
%text(17,5,'\fbox{c}','Interpreter','latex','BackgroundColor','yellow');
text(202*pi/180,rg*fn(ind),'$r$','FontSize',14,'Interpreter','latex','BackgroundColor','yellow');

% add aditional feature for figure(1)
h = figure(1);
aspectRatio = 0.685;
xa =[pi/2 pi/2]; ya = [ 0 16 ];
[xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','Bore Axis','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% show object
offset = 0.16;
r = clouds(1,7)*1.1;
phi = clouds(1,8);
xa =[offset*r*cos(phi*pi/180)*aspectRatio r*cos(phi*pi/180)*aspectRatio]; 
ya = [ offset*r*sin(phi*pi/180) r*sin(phi*pi/180) ];
xa =[phi*pi/180 phi*pi/180];
ya =[0.5 r];
[xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf,'color','black','LineStyle','-.');
title('Perception of Sharp Images ${\bf{S}}(t)$','Interpreter','latex');
end