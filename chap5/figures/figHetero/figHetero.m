clc; clear all;
close all;
omega = 30; omg = omega*pi/180; r = 0.95; 
b =[1 -(r+1/r)*exp(i*omg) exp(2*i*omg)];
w = linspace(-pi,pi,180); phi = w*180/pi;
h = freqz(b,1,w); m = abs(h); 
X =[omega omega]; Y=[0 r]; Y1 =[0 1/r];
hi = freqz(1,b,w); mi = abs(hi); mi = mi/max(mi);
[maxMi indx] = max(mi); detThreshold = maxMi*0.8;
phiDet = linspace(0.2*phi(indx),1.8*phi(indx),10);
rDet = phiDet*0 + detThreshold;
Yi=[0 maxMi];
sA =['$r(\varphi,\theta)=e^{-\frac{\varphi^2}{\sigma_{az}}}'];
s1 =[sA 'e^{-\frac{{(\theta-\pi)}^2}{\sigma_e}}$' ...
     ' and Target at $\varphi_T=$' num2str(omega,2) '$^\circ$'];
subplot(311);plot(phi,mi,'.-r',phiDet,rDet,'.-b');grid;

title(s1,'interpreter','latex');
ylabel('$r(\varphi,\theta)$','interpreter','latex');
xlabel('$\varphi^\circ$','interpreter','latex');
xticks([-180 -90 0 omega 90 180]);
% latex x-ticks
Ax = gca;
Ax.XAxis.TickLabels = {'$-180^\circ$', '$-90^\circ$', '$0^\circ$', ...
    '$\varphi_c(t)^\circ$', '$90^\circ$', '$180^\circ$'}; 
Ax.XAxis.TickLabelInterpreter = 'latex';
% r theta phi detection
xa = [omega-40 omega]; 
ya = [0.7*detThreshold detThreshold];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['Detection of $r(\varphi,\theta)$ at ' num2str(omega,3) '$^\circ$'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

% r theta phi motion
xa = [phi(indx+2)+20 phi(indx+2)]; 
ya = [mi(indx+2) mi(indx+2)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['Linear Sweep $\varphi_c^\circ(t) = 2\pi\frac{\mbox{rpm}}{60}t$'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
