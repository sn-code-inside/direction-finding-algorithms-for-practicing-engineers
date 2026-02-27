function [] = labelPitchE(x,p,fs)
%[] = labelPitchE(x,p,fs) Summary of this function goes here
%   Detailed explanation goes here
N = length(x); t=1:N; delt = 1/fs;
T = t*delt*1000;
figure(1)
subplot(211); plot(T,p(1,:),'r',T,p(2,:),'b',T,p(3,:),'k',T,0.5*x-0.5,'.-r');grid;
title([' Peak $p_{a,b,c}$ Energy $J_m^{a,b,c}$ ' num2str(N)],'interpreter','latex');
ylabel(' Energy $J_m^{a,b,c}$ ','interpreter','latex');
xticks([0 20 40 60 80 100 120 140]);
xticklabels({'','20mS','','60mS','','100mS','','140mS'});

% time series vk
xa(2) = T(500);   xa(1) = 0.8*xa(2);
ya(2) = x(500)*0.5-0.5; ya(1) = 0.8*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$\tilde{v}_k$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';


% dominant peaks 1
xa(2) = T(400);   xa(1) = 0.8*xa(2);
ya(2) = p(1,400); ya(1) = 0.8*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$J_m^a$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

% dominant peaks 2
xa(2) = T(200);   xa(1) = 0.8*xa(2);
ya(2) = p(2,200); ya(1) = 0.8*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$J_m^b$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

% dominant peaks 3
xa(2) = T(300);   xa(1) = 0.8*xa(2);
ya(2) = p(3,300); ya(1) = 0.8*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$J_m^c$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';


end