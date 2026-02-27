% ... copyright protected Dr Kaluri V Ranga Rao
% ... kaluri@ieee.org
clc; clear all; close all;
[config file] = initR('closeDoa.txt',2); 
maxNumberOfBlocks = 3; rForMusic = 1; config(15) = maxNumberOfBlocks;
rd = config(9); rds = config(8); config(5) = 2.0; kmax = config(7);  
numberOfTgts = config(5); numOfPhaseSpecSamples = config(6); 
rg = config(12);