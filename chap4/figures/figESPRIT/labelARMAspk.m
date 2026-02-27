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
function [] = labelARMAspk(omegaD,fn,Xk,f,szr,lambda,str)
%labelARMAspk(omegaD,fn,Xk,f,str) Summary of this function goes here
%   Detailed explanation goes here
ns = length(f); EsPk = lambda(1:ns); EsPk = EsPk/max(EsPk);
omega = omegaD/360;
X =[omega omega]; Y =[0*EsPk EsPk];
subplot(str); plot(fn,Xk);grid;
% peaks of the spectrum
[pk ind] = findpeaks(Xk);
[pks indx] = sort(pk,'descend');
Pk = pks(1:ns); pksInd = ind(indx(1:ns));
X1 =[f' f']; Y1 =[Pk'*0 1.2*Pk'];
hold on; plot(X1',Y1','s-b','MarkerSize', 4,'MarkerFaceColor','b'); hold off;
% ...............................
title(['Spectral Peaks of $x_k$  at [' num2str(f) ']'],'interpreter','latex');
Ax = gca;
Ax.XAxis.TickLabelInterpreter = 'latex';
xticks([f 0.6 0.8 1]);
s1 = '$\frac{18^\circ}{360}$';
s2 = '$\frac{72^\circ}{360}$';
s3 = '$\frac{108^\circ}{360}$';
s4 = '$\frac{162^\circ}{360}$';
s5 = '$\frac{216^\circ}{360}$';
s6= '$\frac{288^\circ}{360}$';
xticklabels({s1,s2,s3,s4,s5,s6});
xlabel(' Normalized Frequency','interpreter','latex');
ylabel('|FFT$(x_k)$|','interpreter','latex');
hold on; plot(X(:,1),Y(:,1),'s','MarkerSize', 3,'MarkerFaceColor','r'); hold off;
hold on; plot(X(:,2),Y(:,2),'o','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
hold on; plot(X',Y','.-r'); hold off;
% label esprit frequencies
f1 =['$\frac{' num2str(omegaD(1),3) '^\circ}{360}$ '];
f2 =['$\frac{' num2str(omegaD(2),3) '^\circ}{360}$ '];
f3 =['$\frac{' num2str(omegaD(3),3) '^\circ}{360}$ '];
f4 =['$\frac{' num2str(omegaD(4),3) '^\circ}{360}$'];
s = ['ESPRIT  [' [f1 f2 f3 f4] ']'];
xa = [0.5 X(4,2)];
ya = [Y(4,2) Y(4,2)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',s,'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
text(X(4,2)*1.1,Y(4,2)*1.3,['Hankel Matrix [' num2str(szr) ']'],'color',...
    'blue','interpreter', 'latex');
end