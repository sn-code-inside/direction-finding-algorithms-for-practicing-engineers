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
function [] = labelFxBm(location,theta,thetaQ,J1,J2,m,snr)
%[] = labelFxBm(location,theta,J1,J2,m,snr) Summary of this function goes here
%   Detailed explanation goes here
    % change the theta ticks
    thetaticks([0 30 60 90 120 150 180]);
    thetaticklabels({'90^o','60^o','30^o','0^o','-30^o','-60^o','-90^o'});
    % labelling starts
    doa = theta(location);
    s1 = ['Response values $J_1$ =' num2str(J1(location),3) ...
        '  $J_2$= ', num2str(J2(location),3) ...
        ' at DOA =' num2str(doa) ' degrees'];
    title('Beam Forming','interpreter', 'latex'); 
    subtitle(s1,"Position",[270,1.2],"HorizontalAlignment",...
        "center",'color','black','interpreter', 'latex')
    %... doa
    max1 = 1.2*max(J1);
    tha =[0 90 - doa]; ra = [0 max1];

    [xaf,yaf] = polarDS2nfu(tha*pi/180,ra); % Convert to normalized figure units
    hT = annotation('arrow',xaf,yaf,'color','black','LineStyle','-.');
    % annotation for 1st Beam
    tha =[45 (90 - doa)]; ra =[0.6*J1(location) J1(location)];
    [xaf,yaf] = polarDS2nfu(tha*pi/180,ra); % Convert to normalized figure units
    hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
    ['$J_1 =$ ' num2str(J1(location),3)],'color','blue','LineStyle','-.');
    hT.TextBackgroundColor = 'yellow';
    % annotation for 2nd Beam
    tha =[135 (90 - doa)]; ra =[0.63*J2(location) J2(location)];
    [xaf,yaf] = polarDS2nfu(tha*pi/180,ra); % Convert to normalized figure units    
    hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
    ['$J_2 =$ ' num2str(J2(location),3)],'color','red','LineStyle','-.');
    hT.TextBackgroundColor = 'yellow';
    % Beam Data
    text(1.4*max1/2,-max1/2,['Beams Seperation $\delta\Phi$ = ' ...
    num2str(2*thetaQ) ' Degrees'],'color','black','interpreter', 'latex');
    text(1.1*max1/2,-0.8*max1/2,['Number of Weights $m$ = ' ...
    num2str(m)],'color','black','interpreter', 'latex');
    text(0.7*max1/2,-0.8*max1/2,['Beam Ripple SNR = ' ...
    num2str(snr,2) 'dB'],'color','black','interpreter', 'latex');

end