clc; clear all;
close all;
% rectangular window
N=10;f=1/N;kmax=31; K=0:kmax;Mark=K*0+16;
x=0.5*cos(2*pi*f*K)+sqrt(-1)*0.5*sin(2*pi*f*K);
subplot(221)
separtion = 1;
plot(K,real(x)+separtion,'o-r','MarkerSize',3,'MarkerFaceColor','r');grid;
hold on;
plot(K,imag(x)-separtion,'o-b','MarkerSize',3,'MarkerFaceColor','b');
hold off;
yticks([-1.5 -1 -0.5 0.5 1 1.5]);
yticklabels({'-0.5','0','0.5','-0.5','0','0.5'});
title(' Rectangular Window ','interpreter','latex');
xlabel(' samples $k$','interpreter','latex');
ylabel('complex $x_k$ ','interpreter','latex');
%real sequence
bin = 13;
xa = [15 bin]; ya = [2 real(x(bin))+separtion];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['real $x_k$ '],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%imag sequence
bin = 13;
xa = [15 bin]; ya = [-2 imag(x(bin))-separtion];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['imag $x_k$ '],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


subplot(222)
sx=abs(fft(x));
stem(K,sx,'b');grid;title(' DFT ','interpreter','latex');
xlabel(' Freq bin \# $n$','interpreter','latex');
ylabel('$|s(\omega)|$ ','interpreter','latex');
yticks([0 5 10 16 20]);
yticklabels({'0','5','10','16','20'});
hold on;plot(K,Mark,'.r');hold off;
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
xa = [20 bin]; ya = [10 0];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['annihilated bin ' num2str(bin)],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
