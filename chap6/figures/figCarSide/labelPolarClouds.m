function [matrix] = labelPolarClouds(gfkdata,clouds)
%labelPolarClouds(gfkdata,clouds) Summary of this function goes here
%   Detailed explanation goes here
figure(1); 
N = 90;
r = gfkdata(:,2); phi = gfkdata(:,4);
rbar = clouds(:,1); phibar = clouds(:,2);
th = linspace(0,pi,N); rg = ones(size(th)).*rbar;
polarplot((90-phi)*pi/180,r,'.',th,rg,'-.');
thetaticks([0 30 60 120 150 180]);
thetaticklabels({'90^o','60^o','30^o','-30^o','-60^o','-90^o'});
rticks([round(sort(rbar'),1)]);
Ax = gca;
Ax.RAxis.TickLabelInterpreter = 'latex';
hold on;
polarplot((-phibar(1)+90)*pi/180,rbar(1),'o','MarkerSize', 30,'color','red');
hold off;
hold on;
polarplot((-phibar(2)+90)*pi/180,rbar(2),'o','MarkerSize', 10,'color','black');
hold off;
hold on;
polarplot((-phibar(3)+90)*pi/180,rbar(3),'o','MarkerSize', 8,'color','blue');
hold off;
% vertical arrow bore axis
xa =[pi/2 pi/2]; ya =[0 rbar(1)*1.1];
[xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','Bore Axis','color',...
    'black','interpreter', 'latex','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% Two Targets
delphi = phibar(1)-phibar(2);
s1 =['$r_1=$' num2str(rbar(1),4) ' $\varphi_1=$' num2str(phibar(1),4) '$^\circ$'];
s2 =['$r_2=$' num2str(rbar(2),4) ' $\varphi_2=$' num2str(phibar(2),4) '$^\circ'];
subtitle([s1 ' and ' s2 '~\delta\varphi=$ ' num2str(delphi,3) '$^\circ$'],...
    "Position",[270,rbar(1)*1.2],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex');
% scene matrix
sz = size(clouds);
rows = sz(1);
figure(1);
formatSpec = '%4.2f';
rold = ['\bar{r} & \bar{\varphi} & \delta{r} & \delta\varphi'];
for k=1:rows
    ri = [num2str(clouds(k,1),formatSpec) '&' ...
        num2str(clouds(k,2),formatSpec) '&' ...
        num2str(clouds(k,3),formatSpec) '&' num2str(clouds(k,4),formatSpec)];
    rnew = [rold '\cr' ri]; rold = rnew;
end
matrix = ['${\bf{S}}(t)=\pmatrix{' rnew '}$'];
text(210*pi/180,15,matrix,'color','blue','Interpreter','latex');
end