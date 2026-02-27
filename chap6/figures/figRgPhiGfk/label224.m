function [] = label224(spk,rd,clouds,rg)
%[] = label224(spk,rd,clouds,rg) Summary of this function goes here
%   Detailed explanation goes here
[smax ind] = max(spk);
fn = linspace(0,1,rd);
h = subplot(224);
[cir,vec] = rgDoa(clouds(1,7),clouds(1,8));
[cir1,vec1] = rgDoa(clouds(2,7),clouds(2,8));
vec0 = [vec vec1];
cir0 = [cir cir1];
polarplot(cir0,vec0,[pi/2 pi/2],[0 20],'.-r');
thetaticks([0 30 60 120 150 180]);
thetaticklabels({'90^o','60^o','30^o','-30^o','-60^o','-90^o'});
rticks([10 15]);

s1 =['$r_1=$' num2str(clouds(1,7),3) ' $\varphi_1=$' num2str(90-clouds(1,8),4) '$^\circ$'];
s2 =['$r_2=$' num2str(clouds(2,7),3) ' $\varphi_2=$' num2str(90-clouds(2,8),4) '$^\circ$'];
subtitle([s1 ' and ' s2],"Position",[270,28],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex')
text(202*pi/180,rg*fn(ind),'$r$','FontSize',10,'Interpreter','latex','BackgroundColor','yellow');

offset = 0.16;
r = clouds(1,7)*1.1;
phi = clouds(1,8);
ya = [ offset*r*sin(phi*pi/180) r*sin(phi*pi/180) ];
xa =[phi*pi/180 phi*pi/180];
ya =[0.5 r];
[xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf,'color','black','LineStyle','-.');
%title('Perception of Sharp Images ${\bf{S}}(t)$','Interpreter','latex');
end
