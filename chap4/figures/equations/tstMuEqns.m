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
clc; clear all
close all
DOA(1) = 35; DOA(2) = -47;
sig(1) = 0.5; sig(2) = 1.0;
snapshots = 128;
fn = 0.1; K=1:snapshots;
g = sign(randn(size(K)));
D = 2; dbyl = 0.5; M = 4;
for k=1:D
    phi(k) = 360*dbyl*sind(DOA(k));
end;
for p=1:snapshots
    for n=1:D
        for k=1:M
            x(n,k) = cosd(k*phi(n)) + sqrt(-1)*sind(k*phi(n));
            x(n,k) = g(p)*sig(n)*x(n,k);
        end;
    end;

    for k=1:M
        s(p,k) = 0;
        for n=1:D
            s(p,k) = s(p,k) + x(n,k);
        end;
    end;
end
 [muSpk doa En SNR] = gMusik(D,dbyl,s);
 subplot(311); plot(muSpk);grid
 