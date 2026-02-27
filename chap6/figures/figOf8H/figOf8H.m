% ... copyright protected Dr Kaluri V Ranga Rao
% ... kaluri@ieee.org
clc; clear all;
close all;
maxblocks = 30;
file = 'figOf8H.txt'
N = 90;
for blockNumber=0:maxblocks
[Data Scene] = getScene(file,blockNumber,maxblocks);
    if (Data<0) break; 
    else 
        clouds = Scene
        gfkdata = Data;
    end;
end
polarLabel('Horizontal Figure of 8');
