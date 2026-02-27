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
function [] = label211(bins,spk,doas,numberOfTgts)
%[] = label211(bins,spk,doas) Summary of this function goes here
%   Detailed explanation goes here
     bounds = axis;
     for p=1:numberOfTgts
        pkBin = bins(p)+1;
        pks = spk(pkBin); zr = 0;
        pkX =[pkBin-1 pkBin-1]; pkY=[zr pks];
        if (p== 1)
            plot(pkX,pkY,'s-r'); 
            ya = [0.4*pks pks]; xa = [pkX(1)*2.6 pkX(1)]; 
            [xaf,yaf] = dsxy2figxy(xa,ya); % Convert to normalized figure units
            s1 =[' Near target at bin ' num2str(bins(p)) ...
                ' at $\theta_L=$' num2str(doas(p),3) '$^\circ$'];
            annotation('textarrow',xaf,yaf,'String',s1,...
                'color','blue','interpreter', 'latex');
        end;

        if (p== 2) 
            plot(pkX,pkY,'o-r'); 
            ya = [0.6*pks pks]; xa = [pkX(1)*1.8 pkX(1)]; 
            [xaf,yaf] = dsxy2figxy(xa,ya); % Convert to normalized figure units
            s1 =[' Target at bin ' num2str(bins(p)) ...
                ' at $\theta_R=$' num2str(doas(p),3) '$^\circ$'];
            annotation('textarrow',xaf,yaf,'String',s1,...
                'color','black','interpreter', 'latex');
        end;

        if (p== 3) 
            plot(pkX,pkY,'^-r'); hold off;
            ya = [0.8*pks pks]; xa = [pkX(1)*1.5 pkX(1)]; 
            [xaf,yaf] = dsxy2figxy(xa,ya); % Convert to normalized figure units
            s1 =[' Far target at bin ' num2str(bins(p)) ...
                ' at $\theta_M=$' num2str(doas(p),3) '$^\circ$'];
            annotation('textarrow',xaf,yaf,'String',s1,...
                'color','red','interpreter', 'latex');
        end;
     end

        boxa = [72 0.18 100 bounds(4)*0.75]; %[xb yb xt yt] of box
        boxb = dsxy2figxy(boxa);
        axes('pos',boxb);
        imshow('cr3.jpg');
end