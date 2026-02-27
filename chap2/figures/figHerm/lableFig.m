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
function [] = lableFig(Lj,Lh,Lm,JkJ,Er,a)
%lableFig(Lj,Lh,Lm,JkJ,Er,a) Summary of this function goes here
%   Detailed explanation goes here
JkL = 1:length(JkJ); K = 1:length(Lm);
subplot(311); plot(K,Lj,'.-r',K,Lh,'+-k',K,Lm,'o');grid;
ylabel('Eigen Values','interpreter','latex');
title(['Overall Error $J_e^M$ ' ...
     num2str(Er(1)) ' $J_e^H$ ' num2str(Er(2)) ' $J_e^J$ ' ... 
     num2str(Er(3))] ,'interpreter','latex');
legend('Jacobi','House Holder','Matlab','Location','NorthWest');
subplot(312); plot(JkL,JkJ,'.-b');grid;
ylabel('Jacobi Function','interpreter','latex');
title([' Size of Hermitian ' num2str(a)],'interpreter','latex');
xlabel('Number of Rotations','interpreter','latex');
end