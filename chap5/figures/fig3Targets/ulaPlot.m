function [] = ulaPlot( theta,Jka,x,y,s,annotation,color,marker)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
subplot(s); plot(theta,Jka,color);grid;
title(annotation,'interpreter','latex');
X =[x' x']; Y =[0*y' y'];
hold on; plot(X',Y','ko','MarkerSize', 4,'MarkerFaceColor',marker); hold off;
hold on; plot(X',Y','-.b','MarkerSize', 4,'MarkerFaceColor','c'); hold off;
tiks = sort([0  round(x)]);
xticks([tiks]);
% latex x-ticks
Ax = gca;
Ax.XAxis.TickLabelInterpreter = 'latex';
Ax.XAxis.TickLabels = {[num2str(tiks(1)) '$^\circ$'],[num2str(tiks(2)) '$^\circ$'],...
    [num2str(tiks(3)) '$^\circ$'], [num2str(tiks(4)) '$^\circ$']}; 
Ax.YAxis.TickLabelInterpreter = 'latex';
end 

