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
function [] = labelProny(azimuth,mag,doa,mPoles,DOAS,D,pole,SNR,rcA,m)
%labelProny(azimuth,mag,doa,mPoles,DOAS,D,pole) Summary of this function goes here
%   Detailed explanation goes here
subplot(311); plot(azimuth,mag);grid;
ytik=sort([round(max(mag)*1.2,2), 1.2, 0.8 0]);
yticks(ytik);
hold on; plot(doa,mPoles,'bo','MarkerSize', 4,'MarkerFaceColor','b'); hold off;
hold on; plot(doa,pole,'ro','MarkerSize', 3,'MarkerFaceColor','r'); hold off;
st = ['Actual DOA $\theta$ ['   num2str(DOAS(1:D)) ']$^\circ$ ULA ' num2str(rcA(2))];
title([st ' size of Cov matrix ' num2str(m) ' SNR = ' num2str(SNR,3) 'dB'],'interpreter','latex');
ylabel('$|h(z)|$','interpreter','latex');
xlabel('Prony Estimate $\hat\theta^\circ$','interpreter','latex');
Ax = gca;
Ax.XAxis.TickLabelInterpreter = 'latex';
Ax.YAxis.TickLabelInterpreter = 'latex';
sdoa = sort(doa);
xticks(sdoa);
s1 = [num2str(sdoa(1),3) '$^\circ$'];
s2 = [num2str(sdoa(2),3) '$^\circ$'];
if (length(doa) == 3)  s3 = [num2str(sdoa(3),3) '$^\circ$']; end;

%s4 =[s1 ',' s2];
stik = {s1,s2}; 
if(length(doa) == 3) 
    stik ={s1,s2,s3};
    % label roots
    xa = [sdoa(3)*1.2 sdoa(3)]; 
    ya = [pole(1) pole(1)];
    [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
    hT = annotation('textarrow',xaf,yaf,'String',...
      ['roots of the polynomial $h(z)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
    hT.TextBackgroundColor = 'yellow';
end;
xticklabels(stik);

end