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
function [] = labelFig3(phiSpk,doas,tgtNum,bin,muS,bins,config)
%[] = labelFig3(phiSpk,doas,tgtNum) Summary of this function goes here
%   Detailed explanation goes here
        figure(3); 
        lenPhi =  length(phiSpk);
        phi = linspace(-180,180,lenPhi); theta = asind(phi/180);
        mxPhi = max(phiSpk(tgtNum,:)); kMuDoa = doas(tgtNum);
        doasX =[kMuDoa kMuDoa]; doasY =[0 mxPhi];
        skip = 20;
        thetaSmpl = theta(1:skip:lenPhi); 
        phiSpkSmpl = phiSpk(tgtNum,1:skip:lenPhi);
        subplot(311); 
        muTgtNum = 1;
        plot(thetaSmpl,phiSpkSmpl,'.-r',theta,phiSpk(tgtNum,:),...
            '-.k',theta,muS(muTgtNum,:),'-.b');grid;

        [pn ln] = findpeaks(muS(muTgtNum,:));
        hold on; plot(theta(ln),pn,'ko','MarkerSize', 4,'MarkerFaceColor','b'); hold off;

        hold on;
        plot(doasX,doasY,'o-b','MarkerSize', 3,'MarkerFaceColor','red');
        hold off;
        sA = ['DOA at bin ' num2str(bin) ' using $\kappa$MUSIC'];
        title(sA,'interpreter', 'latex');
        xlabel('$\theta^\circ$','interpreter', 'latex');
        ylabel('$\|h(\theta)\|$','interpreter', 'latex');
        tik = sort([-90 -60 -30 0 30 60 90 round(kMuDoa,2)]);
        xticks(tik);
        % label kMUSIC
        indx = 170;
        xa = [theta(indx) theta(indx)];
        ya = [2*phiSpk(tgtNum,indx) phiSpk(tgtNum,indx)];
        [xaf,yaf] = dsxy2figxy(xa,ya); % Convert to normalized figure units
        annotation('textarrow',xaf,yaf,'String',...
            ['$\kappa$MUSIC Spectrum'],'color','red','interpreter', 'latex');

        % label gMUSIC
        indx = 70;
        xa = [theta(indx-20) theta(indx)];
        ya = [2*muS(tgtNum,indx) muS(tgtNum,indx)];
        [xaf,yaf] = dsxy2figxy(xa,ya); % Convert to normalized figure units
        annotation('textarrow',xaf,yaf,'String',...
            ['$g$MUSIC Spectrum'],'color','blue','interpreter', 'latex');
        
        labelFig3a(config,phiSpk,doas,bins)
end