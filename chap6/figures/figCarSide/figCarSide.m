% ... copyright protected Dr Kaluri V Ranga Rao
% ... kaluri@ieee.org
clc; clear all;
close all;
maxblocks = 1;
file = 'DataCarSide.txt'
N = 90;
for blockNumber=0:40
[Data Scene] = getScene(file,blockNumber,maxblocks);
    if (Data<0) break; 
    else 
        clouds = Scene
        gfkdata = Data;
        matrix=labelPolarClouds(gfkdata,clouds);
        LatexFileMatrix('CarSideScene.tex','Scene Matrix',clouds);
    end;
end