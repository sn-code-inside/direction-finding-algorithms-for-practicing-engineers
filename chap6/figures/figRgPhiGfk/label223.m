function [] = label223(rd,spk,rg)
%label223(rd,spk,rg) Summary of this function goes here
%   Detailed explanation goes here
K = 1:rd; fn = linspace(0,1,rd); maxPeaks = 2;
% peak solid circles
[pn ln] = findpeaks(spk); [pnx indx] = sort(pn,'descend');
pkI = ln(indx(1:maxPeaks)); spkApk = spk(pkI); fnPk = fn(pkI);

subplot(223); plot(fn,spk);grid
hold on; plot(fnPk,spkApk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;

title('Fourier Spectrum','Interpreter','latex'); 
ylabel('Amplitude','Interpreter','latex');
xlabel('Normalized Frequency','Interpreter','latex');
tiks = sort([round(fnPk,1) 1]);
xticks(tiks);

% Amplitude q.
[smax ind] = max(spk);
xa =[fn(ind)*1.25 fn(ind)]; ya = [ 0.8*smax smax ]; %
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'FontSize',10,'Interpreter','latex','String','Amplitude $q$');
hT.TextBackgroundColor = 'yellow';
% f_p.
xa =[fn(ind)*1.15 1.1]; ya = [ 0.4 0.4 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf);
text(fn(ind)*0.9,ya(1),'$f_p$','FontSize',10,'Interpreter','latex','BackgroundColor','yellow');
% r_g
xa =[1.1 1.6]; ya = [ 0.4 0.4 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'FontSize',10,'Interpreter',...
    'latex','String',['$\times r_g($' num2str(rg,3) ')=']);
hT.TextBackgroundColor = 'yellow';
end