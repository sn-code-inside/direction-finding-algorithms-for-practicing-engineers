% ESPRIT in time Domain
% Kaluri V Ranga Rao Belle Mead NJ 3rd Jun 2025
clear all; close all; clc;
DOAS = [20, -35, 25];

POWS = [1, 1, 1];
std = 0.4;
D = 3; snapShots = 16;
NumOfElements = 31;
numberOfRows = 10;
dbyl = 0.5;
SamplesPerCycle = 8;
rcA = [snapShots NumOfElements];
[A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
for k=1:snapShots
sk = A(k,:);
[phi L Sh omega pole] = espritUla(D,sk,numberOfRows);
theta = asind(-omega/180);
Theta(:,k) = theta;
end
subplot(311);plot(Theta');grid;






