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
function [] = labelFigBeam(muDoas,theta,muSpk,ind,En,SNR)
%[] = labelFigBeam(muDoas,theta,aspectRatio) Summary of this function goes here
%   Changing theta ticks
thetaticks([0 30 60 90 120 150 180]);
thetaticklabels({'90^o','60^o','30^o','0^o','-30^o','-60^o','-90^o'});

%   labelling of the polar plot
      % Noise Eigen Vectors  
      b1 = En(1,:); b2 = En(2,:); n = 3;
      s1 = ['${\bf{w}}_1=$  (' num2str(b1(1),n) '), (' num2str(b1(2),n) ... 
      '), (' num2str(b1(3),n) '), (' num2str(b1(4),n) ')'];
      title(s1,'color','red','interpreter', 'latex');

      s2 = ['${\bf{w}}_2=$  (' num2str(b2(1),n) '), (' num2str(b2(2),n) ...
      '), (' num2str(b1(3),n) '), (' num2str(b1(4),n) ')'];
      subtitle(s2,"Position",[270,1.2],"HorizontalAlignment","center",'color','red','interpreter', 'latex')
      text(-120*pi/180,0.5,['SNR = ' num2str(SNR,3) 'dB'],'color','red','interpreter', 'latex');  

           max1 = muSpk(ind(1)); 
            thPk = 90-muDoas(1);
            tha = [0 thPk]; ra =[0 max1];
            tha = [thPk-sign(thPk)*10 thPk]; ra =[0.7*max1 max1];
            [xaf yaf] = polarDS2nfu(tha*pi/180,ra);
            hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            ['$\hat\theta_1 =$ ' num2str(muDoas(1))],'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';

            max2 = muSpk(ind(2));
            thPk = 90-muDoas(2);
            tha = [0 thPk]; ra =[0 max2];
           tha = [thPk-sign(thPk)*10 thPk]; ra =[0.9*max2 max2];
            [xaf yaf] = polarDS2nfu(tha*pi/180,ra);
            hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            ['$\hat\theta_2 =$ ' num2str(muDoas(2))],'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';

            % Objective Function
            if ( muDoas(1) < muDoas(2) ) 
                indx = ind(1); 
            else indx = ind(2); end;
            location = indx-6;
            max3 = muSpk(location); thPk = 90 + theta(location);
            tha = [thPk+sign(thPk)*20 thPk]; ra =[1.1*max3 max3];
       
            [xaf,yaf] = polarDS2nfu(tha*pi/180,ra); % Convert to normalized figure units
            hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
            ['$J(\varphi) = \frac{1}{\Vert{\bf{w}}_1\Vert + \Vert{\bf{w}}_2\Vert}$'],'color','blue','LineStyle','-.');
            hT.TextBackgroundColor = 'yellow';

            %'  using $J_2(\varphi) = \frac{1}{|{\bf{w}}^a_2| + |{\bf{w}}^b_2|}$'
            % axes('pos',[.085 .65 1.4 .27]);
            % imshow('closeDoa.jpg');
end