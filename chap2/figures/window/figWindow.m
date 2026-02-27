clc; clear all;
close all;
% rectangular window
N=10;f=1/N;kmax=31; K=0:kmax;Mark=K*0+16;
x=cos(2*pi*f*K);
subplot(221)
%stem(K,x,'b');grid;
plot(K,x,'o-r','MarkerSize',3,'MarkerFaceColor','r');grid;
title(' Rectangular Window ','interpreter','latex');
xlabel(' samples $k$','interpreter','latex');
ylabel('$x_k$ ','interpreter','latex')
sx=abs(fft(x));
subplot(222)
stem(K,sx,'b');grid;title(' DFT ','interpreter','latex');
xlabel(' Freq bin \# $n$','interpreter','latex');
ylabel('$|s(\omega)|$ ','interpreter','latex');
yticks([0 5 10 16 20]);
yticklabels({'0','5','10','16','20'});
hold;plot(K,Mark,'.r');
hold off;
%bin 3
bin = 3;
xa = [10 bin]; ya = [14 14];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['bin ' num2str(bin)],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% bin 29
bin = 29;
xa = [20 bin]; ya = [10 10];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['bin ' num2str(bin)],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
