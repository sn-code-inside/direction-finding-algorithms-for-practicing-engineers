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
function [] = labelFig3a(config,muS,muDoas,bins)
%[] = labelFig4(config,muS) Summary of this function goes here
%   Detailed explanation goes here
        numberOfTgts = config(5);
        lenMuS =  length(muS);
        phi = linspace(-180,180,lenMuS); theta = asind(phi/180);
        mxMuS = max(muS')';
        doasX =[muDoas muDoas]; doasY =[0*mxMuS mxMuS];
        subplot(312); plot(theta,muS(1,:),'r',theta,muS(2,:),'b',...
            theta,muS(3,:),'k');grid
        xlabel('$\theta^\circ$','interpreter', 'latex');
        ylabel('$\|h(\theta)\|$','interpreter', 'latex');
        title(['$\kappa$MUSIC spectrum at peaks at ' num2str(bins')],...
            'interpreter', 'latex');
        tik = sort([-90 -60 -30  30 60 90 round(muDoas',1)]);
        xticks(tik);
        hold on; plot(doasX',doasY','s-b','MarkerSize', 3,...
            'MarkerFaceColor','b'); hold off;
        facecol=['r' 'b' 'k'];
        for k=1:numberOfTgts
        [pn ln] = findpeaks(muS(k,:));
        hold on; plot(theta(ln),pn,'ko','MarkerSize', 4,'MarkerFaceColor',facecol(k)); hold off;
        legend(['bin ' num2str(bins(1))], ['bin ' num2str(bins(2))],...
            ['bin ' num2str(bins(3))],'Location','northwest' );
        end
end