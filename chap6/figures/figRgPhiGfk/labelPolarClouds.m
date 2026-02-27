function [] = labelPolarClouds(gfkdata,clouds)
%labelPolarClouds(gfkdata,clouds) Summary of this function goes here
%   Detailed explanation goes here
figure(2); 
r = gfkdata(:,2); phi = gfkdata(:,4);
rbar=[clouds(1,7) clouds(2,7)]; phibar = [clouds(1,8) clouds(2,8)];
[cir,vec] = rgDoa(rbar(1),phibar(1));
[cir1,vec1] = rgDoa(rbar(2),phibar(2));


polarplot((-phi+90)*pi/180,r,'.',cir(:,1),vec(:,1),'-.k',cir1(:,1),vec1(:,1),'-.b');
thetaticks([0 30 60 120 150 180]);
thetaticklabels({'90^o','60^o','30^o','-30^o','-60^o','-90^o'});
rticks([round(rbar(2),2) round(rbar(1),2)]);
Ax = gca;
Ax.RAxis.TickLabelInterpreter = 'latex';
hold on;
polarplot(phibar*pi/180,rbar,'s','MarkerSize', 6,'color','red');
hold off;
% vertical arrow
xa =[pi/2 pi/2];
ya =[0 rbar(1)*1.2];
[xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('arrow',xaf,yaf,'color','blue','LineStyle','-.');
% Two Targets
delphi = phibar(1)-phibar(2);
s1 =['$r_1=$' num2str(rbar(1),4) ' $\varphi_1=$' num2str(90-phibar(1),4) '$^\circ$'];
s2 =['$r_2=$' num2str(rbar(2),4) ' $\varphi_2=$' num2str(90-phibar(2),4) '$^\circ'];
subtitle([s1 ' and ' s2 '~\delta\varphi=$ ' num2str(delphi,3) '$^\circ$'],...
    "Position",[270,rbar(1)*1.2],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex');
% distribution of r and phi
s= clouds(1,1)+1; e = clouds(1,2)+1;
r1 = gfkdata(s:e,2); phi1 = gfkdata(s:e,4);
sigr1 = std(r1); sigphi1 = std(phi1);
s3 =[' $\sigma_r=$' num2str(sigr1,'%2.2e') ' $\sigma^\circ_\varphi =$' num2str(sigphi1,'%2.2e')];
% second
s= clouds(2,1)+1; e = clouds(2,2)+1;
r2 = gfkdata(s:e,2); phi2 = gfkdata(s:e,4);
sigr2 = std(r2); sigphi2 = std(phi2);
s4 =[' $\sigma_r=$' num2str(sigr2,'%2.2e') ' $\sigma^\circ_\varphi =$' num2str(sigphi2,'%2.2e')];

text(230*pi/180,rbar(1)*1.65,s3,'FontSize',10,'Interpreter','latex','BackgroundColor','yellow');
text(275*pi/180,rbar(1)*1.26,s4,'FontSize',10,'Interpreter','latex','BackgroundColor','yellow');



end