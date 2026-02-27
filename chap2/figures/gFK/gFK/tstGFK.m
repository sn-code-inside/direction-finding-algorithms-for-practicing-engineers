clc; clear all;
close all;
config = zeros([1 20]);
rcA(1) = 128; rcA(2) = 4; f = 0.2; phiD = 20;
config(5) = 10; config(6) = 180.0; config(7) = rcA(1);
config(8) = config(7); config(14) = rcA(2)*2;
[S A b fn bins peak config]=gFKtst(config,[f phiD]);
ngs = fix(config(15));
fpk = mean(fn'); fPk =[fpk' fpk'];
Pks =[peak 0*peak];
t = 0:rcA(1)-1; 
X = S(:,1); m = abs(X);
f = linspace(0,1,rcA(1)); 
s = fix(0.45*rcA(1)); e = fix(0.55*rcA(1));
subplot(221); plot(t(s:e),real( A(s:e,:) )+3,'.-',t(s:e),imag( A(s:e,:) ),'.-');grid;
yticks([-1 0 1 2 3 4]);
yticklabels({'-1','0','1','-1','0','1'});
% Polar 
theta = -angle(b(1,:)); r = abs(b(1,:));
Theta =[theta' theta'*0]; R =[r' r'*0];
subplot(222);polarplot(Theta',R','-.',theta,r,'o','MarkerFaceColor','b');
if (abs(theta(1)) < .001 ) theta(1) = 0; end;
title(num2str(theta*180/pi,3),'interpreter','latex');
thetaticks([0 90 180]);
thetaticklabels({'0','90','180'});
rticks([0.5 1]);
%............
[a,ind] = max(m); s=ind-15; e = ind+15;
subplot(313); plot(f(s:e),m(s:e),'.-r',fPk(1,:)',Pks(1,:)','-ob');grid;



