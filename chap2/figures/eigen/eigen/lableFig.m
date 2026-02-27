function [] = lableFig(Lj,Lh,Lm,JkJ,Er,a)
%lableFig(Lj,Lh,Lm,JkJ,Er,a) Summary of this function goes here
%   Detailed explanation goes here
JkL = 1:length(JkJ); K = 1:length(Lm);
subplot(311); plot(K,Lj,'.-r',K,Lh,'+-k',K,Lm,'o');grid;
title(['Overall Error Performance ' num2str(Er)],'interpreter','latex');
legend('Jacobi','House Holder','Matlab','Location','NorthWest');
subplot(312); plot(JkL,JkJ,'.-b');grid;
title([' Size of Hermitian ' num2str(a)],'interpreter','latex');
end